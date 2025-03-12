CC = g++
CFLAGS = `wx-config --cxxflags`
LDFLAGS = `wx-config --libs`
SRC = main.cpp frames_paint.cpp dates.cpp picked_date_management.cpp Tile.cpp edit_day_paint.cpp methods.cpp
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
