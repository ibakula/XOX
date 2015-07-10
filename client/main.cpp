#include <iostream>
#include "../test/packet.h"
#include "opcode.h"

int main()
{
	try{
		boost::asio::io_service io;
		tcpconnection TcpConn(io);
		TcpConn.Connect();
		std::string Name;
		std::cout << "upisi nick: ";
		std::cin >> Name;
		packet pckt(OPCODE_LOGIN);
		pckt.Write<std::string>(Name);
		TcpConn.SendPacket(pckt);


		while (true)
		{
			pckt = packet(OPCODE_LOBBY);
			TcpConn.SendPacket(pckt);
			TcpConn.ReceivePacket();
			int choice;
			std::cout << "igrat(1)/cekat(2)";
			std::cin >> choice;
			if (choice == 1)
			{
				std::cout << "skim oces igrat: ";
				std::cin >> Name;
				pckt = packet(OPCODE_GAME_START);
				pckt.Write<std::string>(Name);
				TcpConn.SendPacket(pckt);
			}
			TcpConn.ReceivePacket();
		}
	}
	catch (std::exception& e)
	{
		std::cerr << e.what() << std::endl;
	}
}
