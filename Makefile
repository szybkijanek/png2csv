# Oto makefile dla programu png2csv
# Nie wiem jak to działa, więc załóżmy,
# że tak to ma wyglądać

CC=clang++
OBJS=main.cpp analizer.cpp patto.cpp pngmatrix.cpp
PNGFLAGS=`libpng-config --cflags --ldflags`
LFLAGS=-std=gnu++11 -stdlib=libc++ $(PNGFLAGS) -O0

all: png2csv

png2csv: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@

.PHONY: install clean

install:
	cp png2csv /usr/local/bin/

clean:
	rm png2csv
