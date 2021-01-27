#include "sdbf/utils.hpp"
#include <iostream>

namespace sdbf {
	bool fileExist(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

	void printHexByte(std::byte* in, std::size_t size) {
		for (std::size_t i = 0; i < size; i++) {
			std::cout << std::hex << (unsigned int)(*(in + i)) << std::endl;
		}
		std::cout << std::dec;
	}

	std::byte* stringToByte(const std::string in, std::size_t size) {
		std::byte* start = new std::byte[size];
		memcpy(start, in.c_str(), size);
		return start;
	}
}

