#pragma once
#include <string>

class tcpconnection;
class Game
{
public:
	Game(tcpconnection* plr);

	void Start(std::string& Opponent, char c);
	void Turn(char c, uint8_t p);

private:
	void Reset();
	void Draw();
	void LocalTurn();
	char Board[10];
	tcpconnection* player;
	bool Over;
};
