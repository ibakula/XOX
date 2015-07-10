#pragma once
#include <cstdint>
#include <cstring>
#include <string>

class packet
{
	char* buffer;
	uint16_t size, itr;
public:
	packet(uint8_t opcode = 0) : buffer(new char[3]), size(3), itr(3) { *buffer = opcode; }
	void Write(const void* buff, size_t s)
	{
		char* buf = new char[size + s];
		memcpy(buf, buffer, size);
		memcpy(buf + size, buff, s);
		size += s;
		delete[] buffer;
		buffer = buf;
	}
	template<class T>
	void Write(T d)
	{
		Write(&d, sizeof(T));
	}
	void Read(void* buff, size_t s)
	{
		memcpy(buff, buffer + itr, s);
		itr += s;
	}
	template<class T>
	T Read()
	{
		T r;
		Read(&r, sizeof(T));
		return r;
	}
	uint8_t opcode()
	{
		return buffer[0];
	}
	char* data()
	{
		return buffer;
	}
	uint16_t getsize()
	{
		return size;
	}
	void Finalize()
	{
		memcpy(buffer + 1, &size, sizeof(uint16_t));
	}
	void Reserve()
	{
		size = *(uint16_t*)(buffer + 1);
		char* buf = new char[size];
		memcpy(buf, buffer, 3);
		delete[] buffer;
		buffer = buf;
	}
};

template <>
std::string packet::Read();
template<>
void packet::Write(std::string str);
