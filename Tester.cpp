#include "TestRunner.hpp"
#include "MemcpyTest.hpp"
#include "StrncpyTest.hpp"
#include "StrcpyTest.hpp"

#include <iostream>
#include <cstring>

#include <stdint.h>
#include <dlfcn.h>
#include <map>

enum type {
	memcpy_t,
	strncpy_t,
	strcpy_t
};

int main(int argc, char** argv)
{
        if (argc <= 1) {
		std::cerr << "Error: Test type must be specified!" << std::endl;
                std::cerr << "Available options: {memcpy; strncpy; strcpy}" << std::endl;
		return 1;
	}
        std::string testType(argv[1]); 
	std::map<std::string, type> typeMap; 

	typeMap["memcpy"]	= memcpy_t;
	typeMap["strncpy"]	= strncpy_t;
	typeMap["strcpy"]      = strncpy_t;

	std::cout << "Running tests using " << testType << "." << std::endl;

	std::cout << "Loading candidate shared library...  ";
	// load candidate shared library
	void *soHandle = dlopen("/usr/obj/usr/src/powerpc.powerpc64/lib/libc/libc.so.7", RTLD_NOW);
	if (soHandle == NULL) {
		std::cerr << "Error loading shared library\n" << std::endl;
		return 1;
	}

	std::cout << "OK."  << std::endl;

	funcperf::TestRunner testRunner;
	funcperf::ITest* testReference;
	funcperf::ITest* testCandidate;

	std::cout << "Creating test objects... ";

	switch (typeMap[testType]) {
		case memcpy_t:
			testReference = new funcperf::string::MemcpyTest(10*1024*1024, &memcpy);
			testCandidate = new funcperf::string::MemcpyTest(10*1024*1024, (void* (*)(void*, const void*, size_t))dlfunc(soHandle, argv[1]));
			break;
		case strncpy_t:
			testReference = new funcperf::string::StrncpyTest(10*1024*1024, &strncpy);
			testCandidate = new funcperf::string::StrncpyTest(10*1024*1024, (char* (*)(char*, const char*, size_t))dlfunc(soHandle, argv[1]));
			break;
		case strcpy_t:
			testReference = new funcperf::string::StrcpyTest(10*1024*1024, &strcpy);
			testCandidate = new funcperf::string::StrcpyTest(10*1024*1024, (char* (*)(char*, const char*))dlfunc(soHandle, argv[1]));
			break;
	}

	std::cout << "OK." << std::endl;

	std::cout << "Running reference... ";
	int64_t nanoDiffReference = testRunner.runTest(*testReference, 1000);
	std::cout << "OK." << std::endl;
	std::cout << "Running candidate... ";
	int64_t nanoDiffCandidate = testRunner.runTest(*testCandidate, 1000);
	std::cout << "OK." << std::endl;

	std::cout << "Reference time: " << static_cast<double>(nanoDiffReference) / 1000000  << "ms." << std::endl;
	std::cout << "Candidate time: " << static_cast<double>(nanoDiffCandidate) / 1000000  << "ms." << "(" << (100.0 * nanoDiffCandidate) / nanoDiffReference << "%)" << std::endl;

	dlclose(soHandle);
}
