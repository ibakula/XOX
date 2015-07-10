#include "tcpconnection.h"
#include "opcode.h"
#include <cassert>

extern OpcodeHandler OpcodeTable[5];

void tcpconnection::Connect()
{
	tcp::resolver::query Query("127.0.0.1", "8342");
	tcp::resolver::iterator it = reslver.resolve(Query);
	boost::system::error_code ec;
	boost::asio::connect(sckt, it, ec);
	assert(!ec);
}

void tcpconnection::SendPacket(packet& Packet)
{
	boost::system::error_code error;
	Packet.Finalize();
	boost::asio::write(sckt, boost::asio::buffer(Packet.data(), Packet.getsize()), boost::asio::transfer_all(), error);
}

void tcpconnection::HandleOpcodeNull()
{
}

void tcpconnection::HandleOpcodeLobby()
{
	uint8_t n = pckt.Read<uint8_t>();
	for (int i = 0; i < n; ++i)
		std::cout << pckt.Read<std::string>() << std::endl;
}

void tcpconnection::HandleOpcodeGame()
{
	std::string OpponentName = pckt.Read<std::string>();
	char c = pckt.Read<char>();
	game.Start(OpponentName, c);
}

void tcpconnection::HandleOpcodeTurn()
{
	char c = pckt.Read<char>();
	uint8_t p = pckt.Read<uint8_t>();
	game.Turn(c, p);
}

void tcpconnection::ReceivePacket()
{
	pckt = packet();
	boost::system::error_code err;
	boost::asio::read(sckt, boost::asio::buffer(pckt.data(), 3), err);
	pckt.Reserve();
	boost::asio::read(sckt, boost::asio::buffer(pckt.data() + 3, pckt.getsize() - 3), err);
	std::clog << OpcodeTable[pckt.opcode()].name << std::endl;
	(this->*OpcodeTable[pckt.opcode()].handler)();
}
