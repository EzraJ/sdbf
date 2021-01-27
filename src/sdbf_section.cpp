#include "sdbf/sdbf_section.hpp"

namespace sdbf {

	section::section(unsigned int _identifiers, unsigned int _sections) {
		section::_identifiersize = _identifiers;
		section::_sectionsize = _sections;
		section::_identifier_data = new std::byte[section::_identifiersize];
		section::_section_data = new std::byte[section::_sectionsize];
	}

	void section::setIdentifier(std::byte* _in) {
		memcpy(section::_identifier_data, _in, section::_identifiersize);
	}

	void section::setSection(std::byte* _in) {
		memcpy(section::_section_data, _in, section::_sectionsize);
	}

	std::byte* section::getIdentifier() {
		return section::_identifier_data;
	}

	std::byte* section::getSection() {
		return section::_section_data;
	}



	section::~section() {
		//delete[] section::_identifier_data;
		//delete[] section::_section_data;
	}

}