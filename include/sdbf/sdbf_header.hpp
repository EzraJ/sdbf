#pragma once

namespace sdbf {

	struct sdbf_header {
		unsigned int identifierSize;
		unsigned int sectionSize;
		bool valid;
		char buf[3] = { 0,0,0 }; // for padding purposes, keeps the first 12 bytes handled by the header. Use these for whatever ig
		sdbf_header(unsigned int is = 0, unsigned int ss = 0, bool v = true) : valid(v), sectionSize(ss), identifierSize(is) {}
		
	};
	sdbf_header mask{ 0, 0, false };

	constexpr unsigned int headerSize = sizeof(sdbf_header);
}