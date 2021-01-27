//#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>


#include <iostream>
#include <string>
#include <memory>
#include "sdbf/sdbf_file.hpp"




int main() {

	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	std::string input;
	std::string fName;
	sdbf::DF_FILE* myDatabase;
	sdbf::section* current = nullptr;

	std::cout << "Enter filename: ";
	std::getline(std::cin, fName);

	if (sdbf::fileExist(fName)) {
		myDatabase = new sdbf::DF_FILE(fName);
	}
	else {
		std::cout << "File doesn\'t exist; input header info(unsigned int all; section #, section size in bytes, section identifier size in bytes, max amount of sections\n";
		sdbf::sdbf_header header;
		std::cin >> header._sections;
		std::cin >> header._section_size;
		std::cin >> header._section_identifier_size;
		std::cin >> header._sections_max;
		myDatabase = new sdbf::DF_FILE(fName, header, false);
	}
	std::cout << "LIST SELECT CREATE SAVE AVAIL\n";

	bool running = true;

	while (running) {
		std::getline(std::cin, input);

		if (input == "LIST") {
			if (current == nullptr) {
				std::cout << "No section is currently selected\n";
				continue;
			}
			else {
				std::cout << "Identifier: \n";
				sdbf::printHexByte(current->getIdentifier(), myDatabase->returnHeader()->_section_identifier_size);
				std::cout << "\nSection: \n";
				sdbf::printHexByte(current->getSection(), myDatabase->returnHeader()->_section_size);
			}
		}else if(input == "SELECT"){
			std::cout << "Enter identifier: \n";
			std::getline(std::cin, input);
			current = myDatabase->edit(input);
		}
		else if (input == "CREATE") {
			std::cout << "Enter identifier: \n";
			std::getline(std::cin, input);
			std::string iden = input;
			std::cout << "Enter section data: \n";
			std::getline(std::cin, input);
			myDatabase->write(sdbf::stringToByte(iden, myDatabase->returnHeader()->_section_identifier_size), sdbf::stringToByte(input, myDatabase->returnHeader()->_section_size));
			current = myDatabase->edit(sdbf::stringToByte(iden, myDatabase->returnHeader()->_section_identifier_size));
		}
		else if (input == "SAVE") {
			myDatabase->save();
		}
		else if (input == "EXIT") {
			running = false;
		}
		else if (input == "AVAIL") {
			std::vector<std::string> x = myDatabase->index();
			for (auto& e : x) {
				std::cout << e << std::endl;
			}
		}

	}
	
	std::cin.get();

	_CrtDumpMemoryLeaks();

	return 0;
}