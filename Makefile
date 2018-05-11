CC = g++
CFLAGS = -Wall -lGLU -lglut -lGL -std=c++14 -I./include

all: obj pikado

pikado: obj/main.o obj/lighting.o obj/dartboard.o obj/dart.o obj/game.o obj/camera.o
	$(CC) $^ -o $@ $(CFLAGS)

obj/main.o: main.cpp include/lighting.hpp include/dartboard.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/game.o: game.cpp include/game.hpp include/dartboard.hpp include/dart.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/lighting.o: lighting.cpp include/lighting.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/dartboard.o: dartboard.cpp include/lighting.hpp include/dartboard.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/camera.o: camera.cpp include/camera.hpp include/dart.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj/dart.o: dart.cpp include/lighting.hpp include/dart.hpp
	$(CC) -c -o $@ $< $(CFLAGS)

obj:
	@test ! -d $@ && mkdir $@

.PHONY: clean
clean:
	rm -rf obj/ pikado
