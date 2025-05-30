build:
	gcc ./src/*.c \
	./src/sdl/*.c \
	-o ./out/tutorialgame.exe \
	-lSDL3 -lSDL3_image

run:
	./out/tutorialgame.exe

compile: build run

run:
	./out/tutorialgame.exe

compile: build run