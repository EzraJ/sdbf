#include "sdbf/sdbf_obj.hpp"
#include <iostream>

namespace sdbf {

	sdbf_obj::sdbf_obj(std::string fName, bool readSections = true) {
		
		sdbf_obj::fileHeader = new sdbf::sdbf_header;
		sdbf_obj::_headermode = true;
		std::cout << "READING: " << fName << "\n";
		sdbf_obj::fileName = fName;
		sdbf_obj::fileObj.open(sdbf_obj::fileName, std::ios::binary | std::ios::in | std::ios::out);
		sdbf_obj::fileObj.read((char*)sdbf_obj::fileHeader, sdbf::sdbf_header_size);
		sdbf_obj::_headermode = false;
		sdbf_obj::_headermode = false;

		sdbf_obj::_sections = new std::vector<sdbf::section>;

		if (readSections) {
			sdbf_obj::readSections();
		}

	}

	sdbf_obj::sdbf_obj(std::string fName, sdbf_header fHeader, bool readSections = true) {
		sdbf_obj::fileHeader = new sdbf::sdbf_header;
		*sdbf_obj::fileHeader = fHeader;
		sdbf_obj::_headermode = false;
		sdbf_obj::_headermode = false;
		sdbf_obj::fileName = fName;

		sdbf_obj::fileObj.open(sdbf_obj::fileName, std::ios::binary | std::ios::in | std::ios::out);
		sdbf_obj::_sections = new std::vector<sdbf::section>;

		if (readSections) {
			sdbf_obj::readSections();
		}
	}


	SDBF_STATUS sdbf_obj::readSections() {
		sdbf::section buf(sdbf_obj::fileHeader->_section_identifier_size, sdbf_obj::fileHeader->_section_size);
		std::byte* identifier = new std::byte[sdbf_obj::fileHeader->_section_identifier_size];
		std::byte* section = new std::byte[sdbf_obj::fileHeader->_section_size];

		for (unsigned int i = 0; i < sdbf_obj::fileHeader->_sections; i++) {
			sdbf_obj::fileObj.read((char*)identifier, sdbf_obj::fileHeader->_section_identifier_size);
			sdbf_obj::fileObj.read((char*)section, sdbf_obj::fileHeader->_section_size);
			buf.setIdentifier(identifier);
			buf.setSection(section);
			sdbf_obj::_sections->push_back(buf);
			memset(identifier, 0, sdbf_obj::fileHeader->_section_identifier_size);
			memset(section, 0, sdbf_obj::fileHeader->_section_size);
		}

		return SDBF_OK;
	}

	sdbf_obj::~sdbf_obj() {
		delete sdbf_obj::fileHeader;
		for (auto& e : *sdbf_obj::_sections) {
			e.clean();
		}
		delete sdbf_obj::_sections;
	}


}