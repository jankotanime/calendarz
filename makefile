CC = g++
CFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`


SRC := $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
SRC := $(filter-out src/NotificationService.cpp, $(SRC))
OBJ = $(SRC:src/%.cpp=build/%.o)
EXE = bin/calendarz

SRC_NTF = src/NotificationService.cpp src/data_manage.cpp src/methods.cpp src/class/Event.cpp src/class/Tile.cpp
OBJ_NTF = $(SRC_NTF:src/%.cpp=build_ntf/%.o)
EXE_NTF = bin/notificationService

$(EXE): directories $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXE)

$(EXE_NTF): directories $(OBJ_NTF)
	$(CC) $(OBJ_NTF) $(LDFLAGS) -o $(EXE_NTF)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

build_ntf/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf build build_ntf bin

.PHONY: directories run clean

directories:
	mkdir -p bin build build_ntf

noti: $(EXE_NTF)

notirun: $(EXE_NTF)
	./$(EXE_NTF)