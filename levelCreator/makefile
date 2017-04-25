INCLUDES=-I/usr/include/python2.6 -I/usr/include/panda3d
#INCLUDES=-I/usr/include/panda3d -I/usr/include/python2.7 -I/usr/include/eigen3
CFLAGS=-Wall -std=c++11 -Wno-reorder -Wno-unused-local-typedefs $(INCLUDES)
LDFLAGS=-L/usr/lib64/panda3d
#LDFLAGS=-L/usr/lib/x86_64-linux-gnu/panda3d -L/usr/local/include/eigen3
LDLIBS=-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct
#LDLIBS=-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct -pthread

SOURCES=
OBJECTS=$(SOURCES:.cc=.o)
HEADERS=$(SOURCES:.cc=.hpp)
OTHER_SRCS=

all: $(SOURCES) $(OTHER_SRCS) main
    
main: main.o $(OBJECTS)
	g++ $(LDFLAGS) -o main main.o $(OBJECTS) $(LDLIBS)

main.o:main.cc $(OTHER_SRCS)
	g++ $(CFLAGS) -o $@ -c $<

%.o:%.cc %.hpp
	g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f $(OBJECTS) main
