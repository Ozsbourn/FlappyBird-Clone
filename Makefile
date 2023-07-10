TARGET = flappy.exe
CXX = g++
DEBUG = -g
OPT = -O2
WARN = -Wall
SFMLDIRECTORY = -L"D:\Dev\Libs\SFML-2.5.1\lib"
SFMLINCLUDES = -I"D:\Dev\Libs\SFML-2.5.1\include"
SFML = $(SFMLINCLUDES) $(SFMLDIRECTORY) -lsfml-graphics -lsfml-window -lsfml-system
CXXFLAGS = $(DEBUG) $(OPT) $(WARN) $(SFML) -std=c++11

LD = g++
OBJS = main.o flappy.o 

all: $(OBJS)
	$(LD) -o $(TARGET) $(OBJS) $(CXXFLAGS) 

main.o:	main.cxx
	$(CXX) -c $(CXXFLAGS) main.cxx -o main.o 

flappy.o: flappy.cxx
	$(CXX) -c $(CXXFLAGS) flappy.cxx -o flappy.o

clean:
	rm -rf *.o 