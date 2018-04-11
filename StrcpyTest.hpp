#pragma once

#include "ITest.hpp"

#include <cstddef>

namespace funcperf {
namespace string {

class StrcpyTest : public funcperf::ITest
{
public:
	StrcpyTest(int bufferSize, char* (*func)(char* dst, const char* src));
	virtual ~StrcpyTest();

	void run();

private:
	int m_bufferSize;
	char* (*m_func)(char* dst, const char* src);
	char* m_srcBuffer;
	char* m_dstBuffer;
};

}
}
