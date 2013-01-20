//
//  patto.h
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#ifndef __png2csv__patto__
#define __png2csv__patto__

#include <iostream>
#include "pngmatrix.h"

class patto {
    char *filename;

public:
    pngmatrix *png;

    void load_file(char *);

    char character();
    int width();
    unsigned long long int full_pattern();

    unsigned long long int pattern_for_point_and_size(int _x, int _y, int _width, int _height);
};

#endif /* defined(__png2csv__patto__) */
