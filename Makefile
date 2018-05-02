CC = g++
CFLAGS = -Wall -lGLU -lglut -lGL -std=c++14

pikado: main.o lighting.o dartboard.o dart.o
	$(CC) $^ -o $@ $(CFLAGS)

main.o: main.cpp lighting.hpp dartboard.hpp
	$(CC) -c $< $(CFLAGS)

lighting.o: lighting.cpp lighting.hpp
	$(CC) -c $< $(CFLAGS)

dartboard.o: dartboard.cpp lighting.hpp dartboard.hpp
	$(CC) -c $< $(CFLAGS)

dart.o: dart.cpp lighting.hpp dart.hpp
	$(CC) -c $< $(CFLAGS)

.PHONY: clean
clean:
	rm *.o pikado
