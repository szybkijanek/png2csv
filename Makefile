CC=clang++
OBJS=main.cpp analizer.cpp patto.cpp pngmatrix.cpp
LIBPNG=`libpng-config --cflags --ldflags`
LFLAGS=-std=gnu++11 -stdlib=libc++ $(LIBPNG) -O0
png2csv: $(OBJS)
	$(CC) $(LFLAGS) $^ -o $@
