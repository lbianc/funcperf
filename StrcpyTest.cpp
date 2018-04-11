#include "StrcpyTest.hpp"

#include <cstdlib>

namespace funcperf {
namespace string {

StrcpyTest::StrcpyTest(int bufferSize, char* (*func)(char* dst, const char* src))
: m_bufferSize(bufferSize)
, m_func(func)
{
	m_srcBuffer = (char*)malloc(bufferSize);
	m_srcBuffer[bufferSize-1] = '\0';
	m_dstBuffer = (char*)malloc(bufferSize);
	m_dstBuffer[bufferSize-1] = '\0';
}

StrcpyTest::~StrcpyTest()
{
	free(m_srcBuffer);
	free(m_dstBuffer);
}

void StrcpyTest::run()
{
	(*m_func)(m_dstBuffer, m_srcBuffer);
}

}
}
