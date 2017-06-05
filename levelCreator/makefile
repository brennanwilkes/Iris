INCLUDES=-I/usr/include/python2.6 -I/usr/include/panda3d
#INCLUDES=-I/usr/include/python2.7 -I/usr/include/panda3d -I/usr/include/eigen3

CFLAGS=-Wall -g -std=c++11 -lglut -Wno-reorder -Wno-unused-local-typedefs $(INCLUDES) -O2

LDFLAGS=-L/usr/lib64/panda3d
#LDFLAGS=-L/usr/lib/x86_64-linux-gnu/panda3d -L/usr/include/eigen3 

LDLIBS=-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub
#LDLIBS=-lp3framework -lpanda -lpandafx -lpandaexpress -lp3dtoolconfig -lp3dtool -lp3pystub -lp3direct -pthread

LINK=../obj/level.o

$(info $(shell echo -e "\033[94mcompile command:\033[0m") g++ $(CFLAGS) -o file.o -c file.cc)

all: levelCreator
	@echo -e "\033[92mDone!\033[0m"
    
levelCreator: levelCreator.o $(LINK)
	@echo Linking...
	g++ $(LDFLAGS) -o levelCreator levelCreator.o $(LINK) $(LDLIBS)

levelCreator.o: levelCreator.cc
	@echo -e "Compiling\033[91m $<... \033[0m"
	@g++ $(CFLAGS) -o $@ -c $<

clean:
	rm -f levelCreator *.o
