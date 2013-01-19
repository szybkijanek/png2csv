//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include <iostream>
#include "pngmatrix.h"

using namespace std;

int main(int argc, const char * argv[])
{
    cout << "Hello, World!\n";
    
    pngmatrix *png = new pngmatrix;
    png -> read_png_file("0.png");
    png -> process_file();
    // insert code here...
    return 0;
}

