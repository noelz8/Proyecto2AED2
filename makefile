# the compiler:
CC = g++

# compiler flags:
#  -g    adds debugging information to the executable file
#  -Wall turns on most, but not all, compiler warnings
CFLAGS=-std=c++11 #-g #-Wall

# the build target executable:
TARGET=checkers

# the desired compile command
COMM=-c

# rules:
$(TARGET): main.o PC.o Tablero.o Jugador.o Move.o Piece.o
	$(CC) $(CFLAGS) -o $(TARGET) main.o PC.o Tablero.o Jugador.o Move.o Piece.o

main.o: main.cpp PC.h Jugador.h Tablero.h 
	$(CC) $(CFLAGS) $(COMM) main.cpp

PC.o: PC.h PC.cpp Player.h Typedefs.h
	$(CC) $(CFLAGS) $(COMM) PC.cpp
	
Tablero.o: Tablero.h Tablero.cpp Piece.h Move.h Typedefs.h
	$(CC) $(CFLAGS) $(COMM) Tablero.cpp

Jugador.o: Jugador.h Jugador.cpp Tablero.h Move.h Piece.h Typedefs.h
	$(CC) $(CFLAGS) $(COMM) Jugador.cpp

Move.o: Move.h Move.cpp Piece.h Tablero.h Typedefs.h
	$(CC) $(CFLAGS) $(COMM) Move.cpp

Piece.o: Piece.h Piece.cpp Tablero.h Move.h Typedefs.h
	$(CC) $(CFLAGS) $(COMM) Piece.cpp

clean:
	$(RM) $(TARGET) *.o *.gch
