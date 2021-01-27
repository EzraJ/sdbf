#pragma once
#include <cstddef>
#include <string>

#define SDBF_OK 1
#define SDBF_ERROR 0


namespace sdbf {

	typedef unsigned char SDBF_STATUS;
	bool fileExist(const std::string& name);

	void printHexByte(std::byte* in, std::size_t size);
	std::byte* stringToByte(const std::string in, std::size_t size);

}