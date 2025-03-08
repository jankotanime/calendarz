CC = g++
CFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`
SRC = main.cpp frames_paint.cpp dates.cpp
OBJ = $(SRC:.cpp=.o)
EXE = ../calendarz.exe

$(EXE): $(OBJ)
	$(CC) $(OBJ) $(LDFLAGS) -o $(EXE)

.cpp.o:
	$(CC) $(CFLAGS) -c $< -o $@

run: $(EXE)
	./$(EXE)

clean:
	rm -f $(OBJ) $(EXE)
