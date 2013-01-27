all:
	clang++ -std=gnu++11 -stdlib=libc++ -L/usr/local/Cellar/libpng/1.5.13/lib -lpng15 -I/usr/local/Cellar/libpng/1.5.13/include/libpng15 main.cpp analizer.cpp patto.cpp pngmatrix.cpp -O0 -o png2csv
