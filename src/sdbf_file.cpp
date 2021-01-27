#include "sdbf/sdbf_file.hpp"

namespace sdbf {

	DF_FILE::DF_FILE(std::string fName) {
		//DF_FILE::fileHeader = new sdbf_header;
		DF_FILE::fileObj = new sdbf_obj(fName, true);
		DF_FILE::fileHeader = DF_FILE::fileObj->headptr();
		DF_FILE::fileName = fName;
		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		for (auto& e : *DF_FILE::fileObj->getSections()) {
			memcpy(buf, e.getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
			*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
			std::string ind(buf);
			DF_FILE::data.insert(std::make_pair(buf, &e));

		}
		free(buf);
	}

	DF_FILE::DF_FILE(std::string fName, sdbf::sdbf_header header, bool readSec = true) {
		DF_FILE::fileHeader = new sdbf_header;
		memcpy(DF_FILE::fileHeader, &header, sdbf::sdbf_header_size);
		DF_FILE::fileObj = new sdbf_obj(fName, header, readSec);
		//*DF_FILE::fileHeader = header;
		DF_FILE::fileHeader = DF_FILE::fileObj->headptr();
		DF_FILE::fileName = fName;

		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		for (auto& e : *DF_FILE::fileObj->getSections()) {
			memcpy(buf, e.getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
			*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
			std::string ind(buf);
			DF_FILE::data.insert(std::make_pair(buf, &e));

		}
		free(buf);

	}



	/*sdbf::section DF_FILE::read(std::byte* index) {
		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		memcpy(buf, index, DF_FILE::fileHeader->_section_identifier_size);
		*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
		std::string x(buf);
		return *(DF_FILE::data.at(x));
		//return *DF_FILE::data.at(index);
	}*/

	/*sdbf::section DF_FILE::read(std::string index) {
		return *(DF_FILE::data.at(index));
	}*/


	sdbf::section* DF_FILE::edit(std::byte* index) {
		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		memcpy(buf, index, DF_FILE::fileHeader->_section_identifier_size);
		*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
		std::string x(buf);
		free(buf);
		return DF_FILE::data.at(x);
	}

	sdbf::section* DF_FILE::edit(std::string index) {
		try {
			return DF_FILE::data.at(index);
		}
		catch (std::exception& e) {
			std::cout << e.what() << std::endl;
			return nullptr;
		}
	}

	SDBF_STATUS DF_FILE::write(sdbf::section* sec_in) {
		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		memcpy(buf, sec_in->getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
		*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
		std::string x(buf);
		DF_FILE::data[x] = sec_in;
		DF_FILE::fileHeader->_sections++;
		free(buf);
		return SDBF_OK;
	}

	SDBF_STATUS DF_FILE::write(std::byte* identifier, std::byte* section_data) {

		section* tmp = new section(DF_FILE::fileHeader->_section_identifier_size, DF_FILE::fileHeader->_section_size);
		tmp->setIdentifier(identifier);
		tmp->setSection(section_data);

		char* buf = (char*)malloc(DF_FILE::fileHeader->_section_identifier_size + 1);
		memcpy(buf, tmp->getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
		*(buf + DF_FILE::fileHeader->_section_identifier_size) = '\0';
		std::string x(buf);

		DF_FILE::data[x] = tmp;
		DF_FILE::fileHeader->_sections++;

		free(buf);
		return SDBF_OK;
	}

	SDBF_STATUS DF_FILE::save(std::string fName) {
		std::ofstream out(fName, std::ios_base::binary | std::ios_base::out);
		out.write((char*)DF_FILE::fileHeader, sdbf::sdbf_header_size);
		int i = 0;
		for (auto& e : DF_FILE::data) {
			if (i == DF_FILE::fileHeader->_sections_max) {
				break;
			}
			out.write((char*)e.second->getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
			out.write((char*)e.second->getSection(), DF_FILE::fileHeader->_section_size);
			i++;
		}
		out.close();
		return SDBF_OK;
	}

	SDBF_STATUS DF_FILE::save() {
		std::ofstream out(DF_FILE::fileName, std::ios_base::binary | std::ios_base::out);
		out.write((char*)DF_FILE::fileHeader, sdbf::sdbf_header_size);
		int i = 0;
		for (auto& e : DF_FILE::data) {
			if (i == DF_FILE::fileHeader->_sections_max) {
				break;
			}
			out.write((char*)e.second->getIdentifier(), DF_FILE::fileHeader->_section_identifier_size);
			out.write((char*)e.second->getSection(), DF_FILE::fileHeader->_section_size);
			i++;
		}
		out.close();
		return SDBF_OK;
	}

	DF_FILE::~DF_FILE() {
		
		//delete DF_FILE::fileHeader;

		/*for (auto& e : DF_FILE::data) {
			delete e.second;
		}*/
		
		delete DF_FILE::fileObj; // delete this last; contains everything useful and important
	}

}
