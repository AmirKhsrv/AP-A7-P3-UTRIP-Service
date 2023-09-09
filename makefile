CC=g++
STD=-std=c++11 -Wall -pedantic
CF=$(STD)
BUILD_DIR=build

all: $(BUILD_DIR) myserver.out

$(BUILD_DIR):
	mkdir -p $(BUILD_DIR)

$(BUILD_DIR)/response.o: utils/response.cpp utils/response.hpp utils/include.hpp
	$(CC) $(CF) -c utils/response.cpp -o $(BUILD_DIR)/response.o

$(BUILD_DIR)/request.o: utils/request.cpp utils/request.hpp utils/include.hpp utils/utilities.hpp
	$(CC) $(CF) -c utils/request.cpp -o $(BUILD_DIR)/request.o

$(BUILD_DIR)/utilities.o: utils/utilities.cpp utils/utilities.hpp
	$(CC) $(CF) -c utils/utilities.cpp -o $(BUILD_DIR)/utilities.o

$(BUILD_DIR)/server.o: server/server.cpp server/server.hpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/server.cpp -o $(BUILD_DIR)/server.o

$(BUILD_DIR)/route.o: server/route.cpp server/route.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c server/route.cpp -o $(BUILD_DIR)/route.o

$(BUILD_DIR)/handlers.o: examples/handlers.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
	$(CC) $(CF) -c examples/handlers.cpp -o $(BUILD_DIR)/handlers.o

# $(BUILD_DIR)/my_server.o: examples/my_server.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp
# 	$(CC) $(CF) -c examples/my_server.cpp -o $(BUILD_DIR)/my_server.o

$(BUILD_DIR)/main.o: examples/main.cpp server/server.hpp utils/utilities.hpp utils/response.hpp utils/request.hpp utils/include.hpp examples/Utrip.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/main.cpp -o $(BUILD_DIR)/main.o

$(BUILD_DIR)/Utrip.o: examples/Utrip.cpp examples/Utrip.hpp examples/Filter.hpp examples/User.hpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/Reserve.hpp examples/InitialData.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/Utrip.cpp -o $(BUILD_DIR)/Utrip.o

$(BUILD_DIR)/ReadData.o: examples/ReadData.cpp examples/ReadData.hpp examples/ReadData.hpp examples/Filter.hpp examples/User.hpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/Reserve.hpp examples/Utrip.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/ReadData.cpp -o $(BUILD_DIR)/ReadData.o

$(BUILD_DIR)/Filter.o: examples/Filter.cpp examples/Filter.hpp examples/Filter.hpp examples/User.hpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/Reserve.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/Filter.cpp -o $(BUILD_DIR)/Filter.o

$(BUILD_DIR)/Reserve.o: examples/Reserve.cpp examples/Reserve.hpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/Reserve.cpp -o $(BUILD_DIR)/Reserve.o

$(BUILD_DIR)/User.o: examples/User.cpp examples/User.hpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/Reserve.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/User.cpp -o $(BUILD_DIR)/User.o

$(BUILD_DIR)/Hotel.o: examples/Hotel.cpp examples/Hotel.hpp examples/Room.hpp examples/Exception.hpp examples/InitialData.hpp
	$(CC) $(CF) -c examples/Hotel.cpp -o $(BUILD_DIR)/Hotel.o

$(BUILD_DIR)/Room.o: examples/Room.cpp examples/Room.hpp
	$(CC) $(CF) -c examples/Room.cpp -o $(BUILD_DIR)/Room.o

$(BUILD_DIR)/Exception.o: examples/Exception.cpp examples/Exception.hpp 
	$(CC) $(CF) -c examples/Exception.cpp -o $(BUILD_DIR)/Exception.o

myserver.out: $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/ReadData.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o 
	$(CC) $(CF) $(BUILD_DIR)/Utrip.o $(BUILD_DIR)/ReadData.o $(BUILD_DIR)/Filter.o $(BUILD_DIR)/Reserve.o $(BUILD_DIR)/User.o $(BUILD_DIR)/Hotel.o $(BUILD_DIR)/Room.o $(BUILD_DIR)/Exception.o $(BUILD_DIR)/main.o $(BUILD_DIR)/handlers.o $(BUILD_DIR)/response.o $(BUILD_DIR)/request.o $(BUILD_DIR)/utilities.o $(BUILD_DIR)/server.o $(BUILD_DIR)/route.o  -o myserver.out

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR) *.o *.out &> /dev/null
