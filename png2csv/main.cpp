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
    unsigned long long int pattern = pattern_generator -> full_pattern_for_file((char *) "E.png");
    
    printf("pattern: %lli", pattern);
    return 0;
}

