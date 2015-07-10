#pragma once
#include <cstdint>

class tcp_connection;
class Game
{
public:
	Game(tcp_connection* plr1, tcp_connection* plr2);
	void Turn(char c, uint8_t p);

private:
	char Board[10];
	tcp_connection* plr1, *plr2;
};
