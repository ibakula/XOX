#pragma once
#include "boost/asio.hpp"
#include "boost/bind.hpp"
#include "boost/enable_shared_from_this.hpp"
#include <iostream>
#include "packet.h"
#include "opcode.h"
#include <queue>

class lobby;
class Game;
extern OpcodeHandler OpcodeTable[5];

using boost::asio::ip::tcp;

class tcp_connection
	: public boost::enable_shared_from_this<tcp_connection>
{
public:
	typedef boost::shared_ptr<tcp_connection> pointer;

	static pointer create(boost::asio::io_service& io_service, lobby* lby)
	{
		return pointer(new tcp_connection(io_service, lby));
	}

	tcp::socket& socket();
	void start();
	void HandleOpcodeNull();
	void HandleOpcodeLogin();
	void HandleOpcodeLobby();
	void HandleOpcodeGame();
	void HandleOpcodeTurn();
	void SendPacket(packet& pckt);
	std::string getName() { return plrName; }

	void StartGame(Game* game, char c)
	{
		this->game = game;
		this->c = c;
	}

private:
	tcp_connection(boost::asio::io_service& io_service, lobby* lby);

	void handle_write(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/);
	void handle_read(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/);
	void handle_pckt(const boost::system::error_code& /*error*/,
		size_t /*bytes_transferred*/);
	void WriteNextPacket();

	char c;
	tcp::socket socket_;
	packet pckt;
	lobby* plobby;
	Game* game;
	std::queue<packet> packets;
	std::string plrName;
};
