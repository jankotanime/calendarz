CC = g++
CFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`

SRC = $(wildcard src/*.cpp) $(wildcard src/*/*.cpp)
OBJ = $(SRC:src/%.cpp=build/%.o)
EXE = bin/calendarz

$(EXE): directories $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXE)

build/%.o: src/%.cpp
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -rf build bin

.PHONY: directories run clean

directories:
	mkdir -p bin build