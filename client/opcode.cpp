#include "tcpconnection.h"
#include "opcode.h"

OpcodeHandler OpcodeTable[6] =
{
	{ "OPCODE_NULL", &tcpconnection::HandleOpcodeNull },
	{ "OPCODE_LOGIN", &tcpconnection::HandleOpcodeNull },
	{ "OPCODE_LOBBY", &tcpconnection::HandleOpcodeLobby },
	{ "OPCODE_GAME_START", &tcpconnection::HandleOpcodeGame },
	{ "OPCODE_TURN", &tcpconnection::HandleOpcodeTurn }
};
