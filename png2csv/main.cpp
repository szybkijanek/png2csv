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

    meteorogram_analizer -> load_file((char *) "meteorogram.png");    
    
    // skala zaczyna się na 63
    frame temperature_scale_frame = {51,30,33,86};
    frame pressure_scale_frame = {221,30,33,86};
    frame wind_scale_frame = {307,30,33,86};
    
    printf("Temperature:\n");
    meteorogram_analizer -> analize_frame(temperature_scale_frame);
    printf("\n\nPressure:\n");
    meteorogram_analizer -> analize_frame(pressure_scale_frame);
    printf("\n\nWind:\n");
    meteorogram_analizer -> analize_frame(wind_scale_frame);
    
    return 0;
}

