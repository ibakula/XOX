#pragma once
#include <boost/asio.hpp>
#include "../test/packet.h"
#include "game.h"

using boost::asio::ip::tcp;

class tcpconnection
{
	tcp::socket sckt;
	tcp::resolver reslver;
	packet pckt;
	Game game;
	public:
		tcpconnection(boost::asio::io_service& ioservice) : sckt(ioservice), reslver(ioservice), game(this) { } 
		void Connect();
		void SendPacket(packet& Packet);
		void ReceivePacket();
		void HandleOpcodeNull();
		void HandleOpcodeLogin();
		void HandleOpcodeLobby();
		void HandleOpcodeGame();
		void HandleOpcodeTurn();
		
};
