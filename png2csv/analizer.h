//
//  analizer.h
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#ifndef __png2csv__analizer__
#define __png2csv__analizer__

#include <iostream>

class analizer {
    char *chars = (char *) "1o023456789EN";
    int widths[13] = {3,4,5,5,5,5,5,5,5,5,5,5,6};
    unsigned long long int patterns[13] = {15429046, 3132751872, 672785844850, 673340286496, 673347373682, 217935742150, 610709637746, 672736561778, 37795291928, 672820447858, 672786844274, 18824611360, 80465050134820};
    
public:
    
};

#endif /* defined(__png2csv__analizer__) */
