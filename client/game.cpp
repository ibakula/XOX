#include "game.h"
#include <iostream>
#include <cstring>
#include "../test/packet.h"
#include "opcode.h"

Game::Game(tcpconnection* plr) : player(plr), Over(false)
{	
	Reset();
}

void Game::Start(std::string& Opponent, char c)
{
	int potez = (c == 'X'); // X igra prvi
	std::cout << "ti si: " << c << std::endl;
	while (!Over)
	{
		Draw();
		if (potez % 2)
			LocalTurn();
		player->ReceivePacket();
		potez++;
	}
	Reset();
}

void Game::Reset()
{
	for (int i = 1; i <= 9; ++i)
		Board[i] = '0' + i;
	Over = false;
}

void Game::Turn(char c, uint8_t p)
{
	Board[p] = c;
	if ((Board[1] == Board[2]) && Board[1] == Board[3] && Board[1] != ' ') Over = true;
	else if ((Board[4] == Board[5]) && Board[4] == Board[6] && Board[4] != ' ') Over = true;
	else if ((Board[7] == Board[8]) && Board[7] == Board[9] && Board[7] != ' ') Over = true;
	else if ((Board[7] == Board[4]) && Board[7] == Board[1] && Board[7] != ' ') Over = true;
	else if ((Board[8] == Board[5]) && Board[8] == Board[2] && Board[8] != ' ') Over = true;
	else if ((Board[9] == Board[6]) && Board[9] == Board[3] && Board[9] != ' ') Over = true;
	else if ((Board[7] == Board[5]) && Board[7] == Board[3] && Board[7] != ' ') Over = true;
	else if ((Board[9] == Board[5]) && Board[9] == Board[1] && Board[9] != ' ') Over = true;
	if (Over) std::cout << c << " je pobjedio!" << std::endl;
}


void Game::LocalTurn()
{
	uint8_t potez;
	std::cout << "potez: ";
	std::cin >> potez;
	packet pckt(OPCODE_TURN);
	pckt.Write<uint8_t>(potez - '0');
	player->SendPacket(pckt);
}

void Game::Draw()
{
	std::cout << Board[7] << "|" << Board[8] << "|" << Board[9] << std::endl;
	std::cout << "-+-+-" << std::endl;
	std::cout << Board[4] << "|" << Board[5] << "|" << Board[6] << std::endl;
	std::cout << "-+-+-" << std::endl;
	std::cout << Board[1] << "|" << Board[2] << "|" << Board[3] << std::endl;
}
