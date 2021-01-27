#pragma once
#include "sdbf/sdbf_obj.hpp"
#include <string>
#include <utility>
#include <iostream>
#include <unordered_map>

namespace sdbf {

	class DF_FILE {
	public:
		DF_FILE(std::string fName);
		DF_FILE(std::string fName, sdbf::sdbf_header header, bool readSec);
		~DF_FILE();

		//sdbf::section read(std::byte* index);
		//sdbf::section read(std::string index);

		sdbf::section* edit(std::byte* index);
		sdbf::section* edit(std::string index);

		SDBF_STATUS write(sdbf::section* sec_in);
		SDBF_STATUS write(std::byte* identifier, std::byte* section_data);

		SDBF_STATUS save(std::string fName);
		SDBF_STATUS save();

		sdbf::sdbf_header* returnHeader() {
			return fileHeader;
		}

		std::vector<std::string> index() {
			std::vector<std::string> ret;
			for (auto& e : data) {
				ret.push_back(e.first);
			}
			return ret;
		}

	private:
		std::string fileName;
		sdbf::sdbf_obj* fileObj;
		sdbf::sdbf_header* fileHeader;
		std::unordered_map<std::string, sdbf::section*> data;
	};

}
