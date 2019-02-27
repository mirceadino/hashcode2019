CXX?=g++
CXXFLAGS?=-Wall -O2 -std=c++17
SOURCES=$(wildcard *.cpp)
EXECS=$(subst .cpp,,$(SOURCES))

all: $(EXECS)

clean:
		$(RM) $(EXECS)
