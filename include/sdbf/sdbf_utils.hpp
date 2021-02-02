#pragma once
#include <string>
#include <assert.h>

#ifdef SDBF_LINUX
#include <unistd.h>
#include <sys/stat.h>
#endif

namespace sdbf {

	typedef char byte; // std::byte is cool and all, but this is easier to deal with

	bool fileExist(const std::string& name) {
		struct stat buffer;
		return (stat(name.c_str(), &buffer) == 0);
	}

}