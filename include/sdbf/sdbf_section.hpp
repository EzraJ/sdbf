#pragma once
#include <assert.h>
#include <memory.h>
#include <cstddef>

namespace sdbf {

	class section{
	public:
		section(unsigned int _identifiers, unsigned int _sections);
		~section();
		
		void setIdentifier(std::byte* _in);
		void setSection(std::byte* _in);

		

		std::byte* getIdentifier();
		std::byte* getSection();

		void clean() {
			delete[] _identifier_data;
			delete[] _section_data;
		}
	private:
		unsigned int _identifiersize;
		unsigned int _sectionsize;
		
		std::byte* _identifier_data;
		std::byte* _section_data;
	};

}