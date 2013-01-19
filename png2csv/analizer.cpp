//
//  analizer.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "analizer.h"

void analizer::load_file(char *){
    pattern_generator -> load_file((char *) "meteorogram.png");
}

void analizer::analize_frame(frame _frame){
    //char* first_string = new char[5];
    
    int line = -1;
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) {
        for (int y = _frame.y; y < _frame.y + _frame.width; y++) {
            for (int i=0; i<13; i++) {
                if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
                    if (line != x) printf("\n%3i | ", x);
                    printf("%c", chars[i]);
                    line = x;
                    break;
                }
            }
        }
    }
    
    
    //return first_string;
}