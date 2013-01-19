//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include <iostream>
#include "pngmatrix.h"
#include "patto.h"

using namespace std;

int main(int argc, const char * argv[]){
    patto *pattern_generator = new patto;
    
    pattern_generator -> load_file((char *) "E.png");
    
    printf("pattern: %c %i %lli\n", pattern_generator -> character(), pattern_generator -> width(), pattern_generator -> full_pattern());
    
    
    pattern_generator -> load_file((char *) "meteorogram.png");
    // 540 x 660
    printf("pattern: %lli\n", pattern_generator -> full_pattern());
    
    return 0;
}

