.PHONY: clean
CFLAGS=-std=gnu99 -g
CFLAGS+=-I ./inc

ifeq ($(OS),Windows_NT)
LIBS=-L ./zlib -l:zlib1.dll
CFLAGS+= -I ./zlib
else
LIBS=-lz
endif

bin/divPakExporter: obj/main.o obj/div.o obj/divPak.o | bin
	gcc $(LIBS) obj/main.o obj/div.o obj/divPak.o -o bin/divInstallExporter

obj/main.o: src/main.c | obj
	gcc src/main.c $(CFLAGS) -c -o obj/main.o

obj/div.o: src/div.c | obj
	gcc src/div.c $(CFLAGS) -c -o obj/div.o

obj/divPak.o: src/divPak.c | obj
	gcc src/divPak.c $(CFLAGS) -c -o obj/divPak.o

bin:
	mkdir bin

obj:
	mkdir obj

Debug: bin/divPakExporter

clean:
	-rm -r obj bin
	-find . -name '*~' -delete
