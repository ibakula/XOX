#include "tcpconnection.h"
#include "opcode.h"

OpcodeHandler OpcodeTable[5] =
{
	{ "OPCODE_NULL", &tcp_connection::HandleOpcodeNull },
	{ "OPCODE_LOGIN", &tcp_connection::HandleOpcodeLogin },
	{ "OPCODE_LOBBY", &tcp_connection::HandleOpcodeLobby },
	{ "OPCODE_GAME_START", &tcp_connection::HandleOpcodeGame },
	{ "OPCODE_TURN", &tcp_connection::HandleOpcodeTurn }
};
