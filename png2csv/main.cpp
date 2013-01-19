//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "structures.h"
#include "analizer.h"

using namespace std;

int main(int argc, const char * argv[]){
    analizer *meteorogram_analizer = new analizer;

    meteorogram_analizer -> load_file((char *) "meteorogram.png");
    //meteorogram_analizer -> analize();
    
    frame _frame = {0,0,540-10,50};
    
    meteorogram_analizer -> analize_frame(_frame);
    
    return 0;
}

