all:
	clang++ -std=gnu++11 -stdlib=libc++ `libpng-config --cflags --ldflags` main.cpp analizer.cpp patto.cpp pngmatrix.cpp -O0 -o png2csv
