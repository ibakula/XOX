#include "tcpconnection.h"
#include "lobby.h"

tcp_connection::tcp_connection(boost::asio::io_service& io_service, lobby* lby) : socket_(io_service), plobby(lby)
{
}

void tcp_connection::start()
{
	pckt = packet();
	boost::asio::async_read(socket_, boost::asio::buffer(pckt.data(), 3),
		boost::bind(&tcp_connection::handle_read, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::HandleOpcodeNull()
{
}

void tcp_connection::HandleOpcodeLobby()
{
	plobby->SendLobbyInfo(this);
}

void tcp_connection::HandleOpcodeGame()
{
	std::string TargetName = pckt.Read<std::string>();
	plobby->StartGame(this, TargetName);
}

void tcp_connection::HandleOpcodeTurn()
{
	uint8_t p = pckt.Read<uint8_t>();
	game->Turn(c, p);
}

tcp::socket& tcp_connection::socket()
{
	return socket_;
}

void tcp_connection::handle_write(const boost::system::error_code& /*error*/,
	size_t /*bytes_transferred*/)
{
	packets.pop();
	if (!packets.empty())
		WriteNextPacket();
}

void tcp_connection::handle_read(const boost::system::error_code& /*error*/,
	size_t /*bytes_transferred*/)
{
	pckt.Reserve();
	boost::asio::async_read(socket_, boost::asio::buffer(pckt.data() + 3, pckt.getsize() - 3),
		boost::bind(&tcp_connection::handle_pckt, shared_from_this(),
		boost::asio::placeholders::error,
		boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::handle_pckt(const boost::system::error_code& /*error*/,
	size_t /*bytes_transferred*/)
{
	std::clog << "recv: " << OpcodeTable[pckt.opcode()].name << std::endl;
	(this->*OpcodeTable[pckt.opcode()].handler)();
	start();
}

void tcp_connection::SendPacket(packet& pckt)
{
	std::clog << "send: " << OpcodeTable[pckt.opcode()].name << std::endl;
	pckt.Finalize();
	packets.push(pckt);
	if (packets.size() == 1)
		WriteNextPacket();
}

void tcp_connection::WriteNextPacket()
{
	boost::asio::async_write(socket_, boost::asio::buffer(packets.front().data(), packets.front().getsize()), 
		boost::bind(&tcp_connection::handle_write, shared_from_this(), boost::asio::placeholders::error, boost::asio::placeholders::bytes_transferred));
}

void tcp_connection::HandleOpcodeLogin()
{
	plrName = pckt.Read<std::string>();
}
