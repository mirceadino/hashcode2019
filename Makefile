CXX?=g++
CXXFLAGS?=-Wall -O2 -std=c++17
SOURCES=$(wildcard src/*.cpp)
EXECS=$(subst .cpp,,$(SOURCES))

all: $(SOURCES) $(EXECS)

zip:
	zip -r -X hashcode.zip src/
	cp hashcode.zip data/hashcode.zip

clean:
		$(RM) $(EXECS)
