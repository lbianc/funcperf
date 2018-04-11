#pragma once

#include "ITest.hpp"

#include <cstddef>

namespace funcperf {
namespace string {

class StrncpyTest : public funcperf::ITest
{
public:
	StrncpyTest(int bufferSize, char* (*func)(char* dst, const char* src, size_t len));
	virtual ~StrncpyTest();

	void run();

private:
	int m_bufferSize;
	char* (*m_func)(char* dst, const char* src, size_t len);
	char* m_srcBuffer;
	char* m_dstBuffer;
};

}
}
