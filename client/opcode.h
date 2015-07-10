#pragma once
#include "tcpconnection.h"

enum
{
	OPCODE_NULL,
	OPCODE_LOGIN,
	OPCODE_LOBBY,
	OPCODE_GAME_START,
	OPCODE_TURN
};

class tcp_connection;
struct OpcodeHandler
{
	const char* name;
	void (tcpconnection::*handler)();
};
