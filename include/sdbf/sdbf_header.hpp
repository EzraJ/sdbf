#pragma once
#include <cstddef>


/*
header begin
header end
identifier
section begin
_section_size
section end
identifer
*/

namespace sdbf {

	struct sdbf_header {
		unsigned int _sections; // # of sections, to load into memory
		unsigned int _section_size; // eg: 512 bytes
		unsigned int _section_identifier_size; // eg: size of a identifier
		unsigned int _sections_max;
	};

	const std::size_t sdbf_header_size = sizeof(sdbf_header);
}

