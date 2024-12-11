all: proj5.exe

random.o: random.h random.cpp
	g++ -std=c++98 -g -Wall -c random.cpp -o random.o

CarClass.o: constants.h CarClass.h CarClass.cpp
	g++ -std=c++98 -g -Wall -c CarClass.cpp -o CarClass.o

EventClass.o: constants.h EventClass.h EventClass.cpp
	g++ -std=c++98 -g -Wall -c EventClass.cpp -o EventClass.o

IntersectionSimulationClass.o: constants.h random.h LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl CarClass.h EventClass.h IntersectionSimulationClass.h IntersectionSimulationClass.cpp
	g++ -std=c++98 -g -Wall -c IntersectionSimulationClass.cpp -o IntersectionSimulationClass.o

project5.o: constants.h random.h LinkedNodeClass.h LinkedNodeClass.inl SortedListClass.h SortedListClass.inl FIFOQueueClass.h FIFOQueueClass.inl CarClass.h EventClass.h IntersectionSimulationClass.h project5.cpp
	g++ -std=c++98 -g -Wall -c project5.cpp -o project5.o

proj5.exe: random.o CarClass.o EventClass.o IntersectionSimulationClass.o project5.o
	g++ -std=c++98 random.o CarClass.o EventClass.o IntersectionSimulationClass.o project5.o -o proj5.exe

clean:
	rm -f *.o *.exe
