#pragma once
#include <iostream>
#include <fstream>

#include "sdbf/sdbf_header.hpp"
#include "sdbf/sdbf_utils.hpp"

namespace sdbf {

	class sdbf_obj{
	public:
		sdbf_obj(std::string fName, sdbf::sdbf_header headerIn = sdbf::mask) {
			if (headerIn.valid) {
				// header is provided
				assert(headerIn.identifierSize != 0);
				fileHeader = new sdbf::sdbf_header(headerIn);
				fileObj = new std::fstream(fName, std::ios_base::out);
				fileObj->write((char*)fileHeader, sdbf::headerSize);
				fileObj->close();
				fileObj->open(fName, std::ios_base::in | std::ios_base::out | std::ios_base::binary);
			}
			else {
				// header not provided
				fileHeader = new sdbf::sdbf_header();
				fileObj = new std::fstream(fName, std::ios_base::out | std::ios_base::in | std::ios_base::binary);
				fileObj->read((char*)fileHeader, sdbf::headerSize);
				assert(fileHeader->identifierSize != 0);
			}
			fileName = fName;
		}

		~sdbf_obj() {
			std::cout << "Closing file\n";
			fileObj->close();
		}
	
	private:
		sdbf::sdbf_header* fileHeader;
		std::fstream* fileObj;
		std::string fileName;
	};


}