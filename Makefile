.PHONY: clean
CFLAGS=-std=gnu99 -g

CFLAGS+=-I ./inc

bin/divPakExporter: obj/main.o obj/div.o obj/divPak.o | bin
	gcc obj/main.o obj/div.o obj/divPak.o -o bin/divInstallExporter

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
