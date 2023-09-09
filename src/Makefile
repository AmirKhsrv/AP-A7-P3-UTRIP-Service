CC := g++ -std=c++11

all: utrip.out

utrip.out: main.o ReadData.o Interface.o Utrip.o Filter.o User.o Hotel.o Room.o Exception.o Reserve.o
	$(CC) main.o ReadData.o Interface.o Utrip.o Filter.o  User.o Hotel.o Room.o Exception.o Reserve.o -o utrip.out

main.o: main.cpp ReadData.hpp Utrip.hpp Hotel.hpp User.hpp Room.hpp Exception.hpp Filter.hpp Reserve.hpp InitialData.hpp
	$(CC) -c main.cpp -o main.o

Utrip.o: Utrip.hpp Utrip.cpp Hotel.hpp User.hpp Room.hpp Exception.hpp Filter.hpp Reserve.hpp InitialData.hpp
	$(CC) -c Utrip.cpp -o Utrip.o

Interface.o: Interface.hpp Interface.cpp Exception.hpp Filter.hpp Utrip.hpp Hotel.hpp User.hpp Room.hpp Reserve.hpp InitialData.hpp
	$(CC) -c Interface.cpp -o Interface.o

ReadData.o: ReadData.hpp ReadData.cpp Utrip.hpp Hotel.hpp User.hpp Room.hpp Exception.hpp Filter.hpp Reserve.hpp InitialData.hpp
	$(CC) -c ReadData.cpp -o ReadData.o

Filter.o: Filter.hpp Filter.cpp Exception.hpp Hotel.hpp User.hpp Room.hpp Reserve.hpp InitialData.hpp
	$(CC) -c Filter.cpp -o Filter.o

Reserve.o: Reserve.hpp Reserve.cpp Hotel.hpp Room.hpp Exception.hpp InitialData.hpp
	$(CC) -c Reserve.cpp -o Reserve.o

User.o: User.hpp User.cpp Hotel.hpp Room.hpp Exception.hpp Reserve.hpp InitialData.hpp
	$(CC) -c User.cpp -o User.o

Hotel.o: Hotel.hpp Hotel.cpp Room.hpp Exception.hpp InitialData.hpp
	$(CC) -c Hotel.cpp -o Hotel.o

Room.o: Room.hpp Room.cpp Exception.hpp InitialData.hpp
	$(CC) -c Room.cpp -o Room.o

Exception.o: Exception.hpp Exception.cpp 
	$(CC) -c Exception.cpp -o Exception.o

clean:
	rm -r *.o
	rm -r *.out