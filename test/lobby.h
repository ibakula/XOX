#pragma once
#include "tcpconnection.h"
#include <list>
#include <ctime>
#include <cstdlib>
#include "game.h"

class lobby
{
	std::list<tcp_connection::pointer> plrs;
public:
	void AddPlayer(tcp_connection::pointer& plr)
	{
		plrs.push_back(plr);
	}
	void SendLobbyInfo(tcp_connection* plr)
	{
		packet pckt(OPCODE_LOBBY);
		pckt.Write<uint8_t>(plrs.size());
		for (auto it = plrs.begin(); it != plrs.end(); ++it)
			pckt.Write<std::string>((*it)->getName());
		
		plr->SendPacket(pckt);
	}
	void StartGame(tcp_connection* plr, std::string& plr2)
	{
		srand(time(NULL));
		bool plr1c = random() % 2;
		bool plr2c = !plr1c;
		for (auto it = plrs.begin(); it != plrs.end(); ++it)
		{
			if ((*it)->getName() == plr2)
			{
				Game* game = new Game(it->get(), plr);
				packet pckt(OPCODE_GAME_START);
				pckt.Write<std::string>(plr->getName());
				pckt.Write<char>(plr1c ? 'X' : 'O');
				(*it)->SendPacket(pckt);
				pckt = packet(OPCODE_GAME_START);
				pckt.Write<std::string>(plr2);
				pckt.Write<char>(plr2c ? 'X' : 'O');
				plr->SendPacket(pckt);
				(*it)->StartGame(game, plr1c ? 'X' : 'O');
				plr->StartGame(game, plr2c ? 'X' : 'O');
			}
		}
				
	}
};
