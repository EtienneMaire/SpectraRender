all: build

args := "src/main.c" -Wall

build:
	x86_64-w64-mingw32-gcc $(args) -o "bin/SpectraRender.exe"

clean:
	rm -rf bin/*