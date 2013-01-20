//
//  main.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "structures.h"
#include "analizer.h"

#include "patto.h"

using namespace std;

int main(int argc, const char * argv[]){
    /*
    patto *patogen = new patto;
    patogen -> load_file("-.png");
    printf("[%lli]\n", patogen -> full_pattern());
    */
    analizer *meteorogram_analizer = new analizer;

    meteorogram_analizer -> load_file((char *)argv[1]);

    return 0;
}

