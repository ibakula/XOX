#include "game.h"
#include <cstring>
#include "packet.h"
#include "tcpconnection.h"

Game::Game(tcp_connection* plr1, tcp_connection* plr2) : plr1(plr1), plr2(plr2)
{
	memset(&Board[1], ' ', 9);
}

void Game::Turn(char c, uint8_t p)
{
	if (Board[p] != ' ')
		return;

	Board[p] = c;
	packet pckt(OPCODE_TURN);
	pckt.Write<char>(c);
	pckt.Write<uint8_t>(p);
	plr1->SendPacket(pckt);
	plr2->SendPacket(pckt);

}

