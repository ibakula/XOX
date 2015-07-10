#include "packet.h"

template <>
std::string packet::Read()
{
	std::string r;
	while (buffer[itr])
	{
		r += buffer[itr];
		itr += 1;
	}
	itr += 1;
	return r;
}

template<>
void packet::Write(std::string str)
{
	Write(str.c_str(), str.size() + 1);
}
