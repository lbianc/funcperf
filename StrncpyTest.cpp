#include "StrncpyTest.hpp"

#include <cstdlib>

namespace funcperf {
namespace string {

StrncpyTest::StrncpyTest(int bufferSize, char* (*func)(char* dst, const char* src, size_t len))
: m_bufferSize(bufferSize)
, m_func(func)
{
	m_srcBuffer = (char*)malloc(bufferSize);
	m_srcBuffer[bufferSize-1] = '\0';
	m_dstBuffer = (char*)malloc(bufferSize);
	m_dstBuffer[bufferSize-1] = '\0';
}

StrncpyTest::~StrncpyTest()
{
	free(m_srcBuffer);
	free(m_dstBuffer);
}

void StrncpyTest::run()
{
	(*m_func)(m_dstBuffer, m_srcBuffer, m_bufferSize);
}

}
}
