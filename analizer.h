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
#include "pngmatrix.h"
#include "patto.h"
#include "structures.h"

/*
 1 3 15429046
 - 5 589824
 0 5 672785844850
 2 5 673340286496
 3 5 673347373682
 4 5 217935742150
 5 5 610709637746
 6 5 672736561778
 7 5 37795291928
 8 5 672820447858
 9 5 672786844274
 */

class analizer {
    // static config
    char *chars;
    int widths[11];
	
    unsigned long long int patterns[11];
	
    // skala zaczyna się od 63
    frame temperature_scale_frame, pressure_scale_frame, wind_scale_frame;
    range temperature_range, pressure_range, wind_range;
    
    // dane skali
    int temperature_v1, temperature_v3, temperature_r1, temperature_r3;
    int pressure_v1, pressure_v3, pressure_r1, pressure_r3;
    int wind_v1, wind_v3, wind_r1, wind_r3;
    
    // obiekty
    patto *pattern_generator;
    
    // parametry pliku
    char *filename;
    time_t epch;
    int station_id;
	
    // metody prywatne
    float temperature_with_column(int);
    int pressure_with_column(int);
    int wind_max_with_column(int);
    int wind_avg_with_column(int);
    
    void set_scales();
    void set_date();
    void set_station_id();
    
    void analize_frame(frame);
    
    int column_for_hour_interval(int);
    time_t timestamp_for_hour_interval(int);
    
public:
	// konstruktor
	analizer();
	  
    void load_file(char *);
    void println_for_hour_interval(int);

};

#endif /* defined(__png2csv__analizer__) */
