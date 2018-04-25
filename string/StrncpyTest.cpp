#include "StrncpyTest.hpp"

#include <cstdlib>
#include <cstring>
#include <sstream>

namespace funcperf {
namespace string {

StrncpyTest::StrncpyTest(const MemcpyTestParams& testParams)
: m_testParams(testParams)
{
	int srcBufferSize = m_testParams.getSrcOffset() + m_testParams.getBytesToCopy();
	int dstBufferSize = m_testParams.getDstOffset() + m_testParams.getBytesToCopy();
	m_srcBuffer = (char *)malloc(srcBufferSize);
	m_dstBuffer = (char *)malloc(dstBufferSize);
	m_verifyBuffer = (char *)malloc(dstBufferSize);

        m_srcBuffer[srcBufferSize - 1] = '\0';
        m_dstBuffer[dstBufferSize - 1] = '\0';

        for (int i = m_testParams.getSrcOffset(); i < srcBufferSize - 1; i++) {
                char rand = i % 0xfe;
                if (rand == '\0') rand = 'a';
                m_srcBuffer[i] = rand;
        }

	// prepare verification buffer
	memcpy(m_verifyBuffer, m_dstBuffer, dstBufferSize);
	strncpy(m_verifyBuffer + m_testParams.getDstOffset(), m_srcBuffer + m_testParams.getSrcOffset(), m_testParams.getBytesToCopy());
}

StrncpyTest::~StrncpyTest()
{
	free(m_srcBuffer);
	free(m_dstBuffer);
	free(m_verifyBuffer);
}

std::string StrncpyTest::getId()
{
	std::stringstream ss;

	ss << "STRNCPY_" << m_testParams.getCSVValues("_");

	return ss.str();
}

void StrncpyTest::run(void* func)
{
	char* (*strncpy_func)(char* dst, const char* src, size_t len) = (char* (*)(char*, const char*, size_t len))func;

	(*strncpy_func)(m_dstBuffer + m_testParams.getDstOffset(), m_srcBuffer + m_testParams.getSrcOffset(), m_testParams.getBytesToCopy());
}

bool StrncpyTest::verify()
{
	return memcmp(m_dstBuffer, m_verifyBuffer, m_testParams.getDstOffset() + m_testParams.getBytesToCopy()) == 0;
}

}
}
