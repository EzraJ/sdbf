#include <iostream>
#include "sdbf/sdbf_obj.hpp"

int main() {
	sdbf::sdbf_header myHeader;
	myHeader.identifierSize = 1;
	myHeader.sectionSize = 1;
	sdbf::sdbf_obj fileObj("database.sdbf", myHeader);

	std::cout << sdbf::headerSize << std::endl;

	std::cin.get();

	return 0;
}