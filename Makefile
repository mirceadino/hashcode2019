CXX?=g++
CXXFLAGS?=-Wall -O2 -std=c++17
SOURCES=$(wildcard src/*.cpp)
EXECS=$(subst .cpp,,$(SOURCES))

all: $(EXECS)

zip:
	zip -r -X hashcode.zip src/

clean:
		$(RM) $(EXECS)
