#pragma once
#include "sdbf/sdbf_header.hpp"
#include "sdbf/sdbf_section.hpp"
#include "sdbf/utils.hpp"
#include <vector>
#include <fstream>
#include <string>

namespace sdbf {

	// No writing.

	class sdbf_obj {
	public:
		sdbf_obj(std::string fName, bool readSections);
		sdbf_obj(std::string fName, sdbf_header fHeader, bool readSections);
		~sdbf_obj();

		SDBF_STATUS readSections();
		
		sdbf_header copyHeader() {
			return *fileHeader;
		}

		sdbf_header* headptr() {
			return fileHeader;
		}

		std::vector<sdbf::section>* getSections() {
			return sdbf_obj::_sections;
		}

		

	private:
		std::string fileName;
		std::byte* read;
		bool _headermode;
		std::fstream fileObj;
		sdbf_header* fileHeader;
		std::vector<sdbf::section>* _sections;
	};

}