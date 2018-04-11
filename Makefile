CXX=g++

SRCS=MemcpyTest.cpp StrncpyTest.cpp StrcpyTest.cpp TestRunner.cpp Tester.cpp
OBJS=${SRCS:S/.cpp/.o/}

all: tester

tester: ${OBJS}
	${CXX} ${LDFLAGS} -o tester ${OBJS} ${LDLIBS}

clean:
	rm -f ${OBJS} tester
