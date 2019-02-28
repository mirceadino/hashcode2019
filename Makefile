CXX?=g++
CXXFLAGS?=-Wall -O2 -std=c++17
SOURCES=$(wildcard src/*.cpp)
EXECS=$(subst .cpp,,$(SOURCES))

all: $(SOURCES) $(EXECS)

zip:
	zip -r -X hashcode.zip src/
	cp hashcode.zip data/hashcode.zip

run:
	./src/main < data/a.in > data/a.out
	./src/main < data/b.in > data/b.out
	./src/main < data/c.in > data/c.out
	./src/main < data/d.in > data/d.out
	./src/main < data/e.in > data/e.out

clean:
		$(RM) $(EXECS)
