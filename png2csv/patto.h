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

#define PATTERN_HEIGHT

class patto {
public:
    unsigned long long int full_pattern_for_file(char *);
};

#endif /* defined(__png2csv__patto__) */
