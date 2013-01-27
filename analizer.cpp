//
//  analizer.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "analizer.h"

#define PATTERNS_COUNT 11

analizer::analizer(){
	chars = (char *) "1-023456789";
	
	widths[0] = 3;
	widths[1] = 5;
	widths[2] = 5;
	widths[3] = 5;
	widths[4] = 5;
	widths[5] = 5;
	widths[6] = 5;
	widths[7] = 5;
	widths[8] = 5;
	widths[9] = 5;
	widths[10] = 5;
	
	patterns[0] = 15429046;
	patterns[1] = 589824;
	patterns[2] = 672785844850;
	patterns[3] = 673340286496;
	patterns[4] = 673347373682;
	patterns[5] = 217935742150;
	patterns[6] = 610709637746;
	patterns[7] = 672736561778;
	patterns[8] = 37795291928;
	patterns[9] = 672820447858;
	patterns[10] = 672786844274;
	
	pattern_generator = new patto;
	wind_v1 = wind_v3 = wind_r1 = wind_r3 = 0;
    temperature_v1 = temperature_v3 = temperature_r1 = temperature_r3 = 0;
    pressure_v1 = pressure_v3 = pressure_r1 = pressure_r3 = 0;
	
	temperature_scale_frame.x = 51;
	pressure_scale_frame.x = 221;
	wind_scale_frame.x = 307;
	
	temperature_scale_frame.y = pressure_scale_frame.y = wind_scale_frame.y = 30;
	temperature_scale_frame.width = pressure_scale_frame.width = wind_scale_frame.width = 33;
	temperature_scale_frame.height = pressure_scale_frame.height = wind_scale_frame.height = 86;
    
    temperature_range.loc = 58;
    temperature_range.len = 76;
	
    pressure_range.loc = 230;
    pressure_range.len = 76;
	
    wind_range.loc = 316;
    wind_range.len = 76;
}

void analizer::load_file(char * _filename){
    filename = _filename;
    pattern_generator -> load_file(_filename);
    set_scales();
    set_date();
    set_station_id();
}

void analizer::set_station_id(){
    long int first_separator = strchr(filename,'_') - filename + 1;
    long int last_separator = strrchr(filename,'_') - filename + 1;
    long int dot = strrchr(filename,'.') - filename + 1;
    
    char buff[4];
    
    memcpy(buff, &filename[first_separator], last_separator - first_separator - 1);
    buff[last_separator-first_separator - 1] = '\0';
    int row = atoi(buff);
    
    memcpy(buff, &filename[last_separator], dot - last_separator - 1);
    buff[dot-last_separator - 1] = '\0';
    int column = atoi(buff);
    
    station_id = (column - 52)/14 * 25 + (row - 10)/14;
}

int analizer::column_for_hour_interval(int interval){return 51 + 7 * interval;}
time_t analizer::timestamp_for_hour_interval(int interval){return epch + interval * 60 * 60;}

void analizer::println_for_hour_interval(int interval){
    time_t timestamp = timestamp_for_hour_interval(interval);

    int column = column_for_hour_interval(interval);
    
    float temperature = temperature_with_column(column);
    int pressure = pressure_with_column(column);
    int wind_max = wind_max_with_column(column);
    int wind_avg = wind_avg_with_column(column);
    
    // station_id / timestamp / temperature / pressure / wind_max / wind_avg
    printf("%i, %li, %.1f, %i, %i, %i\n", station_id, timestamp, temperature, pressure, wind_max, wind_avg);
}

float analizer::temperature_with_column(int column){
    range _range = temperature_range;
    float temperature_r2 = 0;
    // dwie kolejne 255
    
    int repeater = 0;
    while (!temperature_r2) {
        for (int row = _range.loc; row < _range.loc + _range.len ; row++) {
            //printf("[%i:%i]\t%i\n", row, column, pattern_generator -> png -> red_pixel(column, row));
            if(pattern_generator -> png ->red_pixel(column+repeater, row) == 255 && pattern_generator -> png ->red_pixel(column+repeater, row+1) == 255){
                temperature_r2 = row;
                break;
            }
        }
        repeater++;
    }
    return temperature_v1 + (temperature_r2 - temperature_r1) * (temperature_v3 - temperature_v1) / (temperature_r3 - temperature_r1);
}

int analizer::pressure_with_column(int column){
    range _range = pressure_range;
    float pressure_r2 = 0;
    // dwa kolejne 0
    
    int repeater = 0;
    while (!pressure_r2) {
        for (int row = _range.loc; row < _range.loc + _range.len ; row++) {
            //printf("[%i:%i]\t%i\n", row, column, pattern_generator -> png -> red_pixel(column, row));
            if(pattern_generator -> png ->red_pixel(column+repeater, row) == 0 &&
               pattern_generator -> png ->red_pixel(column+repeater, row+1) == 0){
                pressure_r2 = row;
                break;
            }
        }
        repeater++;
    }
    return pressure_v1 + (pressure_r2 - pressure_r1) * (pressure_v3 - pressure_v1) / (pressure_r3 - pressure_r1);
}

int analizer::wind_max_with_column(int column){
    range _range = wind_range;
    int wind_r2 = 0;
    // pierwsze r255 g0
    int repeater = 0;
    while (!wind_r2) {
        for (int row = _range.loc; row < _range.loc + _range.len ; row++) {
            //printf("[%i:%i]\t%i - %i\n", row, column, pattern_generator -> png -> red_pixel(column, row), pattern_generator -> png -> green_pixel(column, row));
            if(pattern_generator -> png ->red_pixel(column+repeater, row) == 255 &&
               pattern_generator -> png ->green_pixel(column+repeater, row) == 0){
                wind_r2 = row;
                break;
            }
        }
        repeater++;
    }
	
	printf("v1: %d | v3: %d | r1: %d | r2: %d | r3: %d\n", wind_v1, wind_v3, wind_r1, wind_r2, wind_r3);
    // Dont ask why -1
    return wind_v1 + (wind_r2 - wind_r1) * (wind_v3 - wind_v1) / (wind_r3 - wind_r1) - 1;
}

int analizer::wind_avg_with_column(int column){
    range _range = wind_range;
    int wind_r2 = 0;
    // pierwsze dwa r17
    int repeater = 0;
    while (!wind_r2) {
        for (int row = _range.loc; row < _range.loc + _range.len ; row++) {
            //printf("[%i:%i]\t%i - %i\n", row, column, pattern_generator -> png -> red_pixel(column, row), pattern_generator -> png -> green_pixel(column, row));
            if(pattern_generator -> png ->red_pixel(column+repeater, row) == 17 &&
               pattern_generator -> png ->red_pixel(column+repeater, row + 1) == 17){
                wind_r2 = row;
                break;
            }
        }
        repeater++;
    }
    
    return wind_v1 + (wind_r2 - wind_r1) * (wind_v3 - wind_v1) / (wind_r3 - wind_r1) - 1;
}


void analizer::set_date(){
    char buff[3];
    
    tm date;
    date.tm_sec = 0;
    date.tm_min = 0;
    date.tm_hour = 0;
    
    // dzień
    memcpy(buff, &filename[6], 2);
    buff[2] = '\0';
    date.tm_mday = atoi(buff);
    
    // miesiąc
    memcpy(buff, &filename[4], 2);
    buff[2] = '\0';
    date.tm_mon = atoi(buff)-1;
    
    // rok
    memcpy(buff, &filename[2], 2);
    buff[2] = '\0';
    date.tm_year = atoi(buff)+100;
    
    date.tm_isdst = 0;
    
    epch = mktime(&date);
    
    //printf("%li -> %s", epch, asctime(gmtime(&epch)));
}
void analizer::set_scales(){
    frame _frame;
    int line = 0, counter=0;
    char* buffer;
    
    // Temperatura
    //printf("Temperature:\n");
    _frame = temperature_scale_frame;
    line = -1;
    counter = 0;
    buffer = new char[5];
    // first line
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    temperature_v1 = atoi(buffer);
    temperature_r1 = line + 4;
    //printf("%i\t] first line:\t%i\n", temperature_v1, temperature_r1);
    
    line = -1;
    counter = 0;
    buffer = new char[5];
    // last line
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    temperature_v3 = atoi(buffer);
    temperature_r3 = line + 4;
    //printf("%i\t] first line:\t%i\n", temperature_v3, temperature_r3);
    
    // Ciśnienie
    //printf("Pressure:\n");
    _frame = pressure_scale_frame;
    line = -1;
    counter = 0;
    buffer = new char[5];
    // first line
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    pressure_v1 = atoi(buffer);
    pressure_r1 = line + 4;
    //printf("%i\t] first line:\t%i\n", pressure_v1, pressure_r1);
    
    line = -1;
    counter = 0;
    buffer = new char[5];
    // last line
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    pressure_v3 = atoi(buffer);
    pressure_r3 = line + 4;
    //printf("%i\t] first line:\t%i\n", pressure_v3, pressure_r3);

    
    // Wiatr
    //printf("Wind:\n");
    _frame = wind_scale_frame;
    line = -1;
    counter = 0;
    buffer = new char[5];
    // first line
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    wind_v1 = atoi(buffer);
    wind_r1 = line + 4;
    //printf("%i\t] first line:\t%i\n", wind_v1, wind_r1);
    
    line = -1;
    counter = 0;
    buffer = new char[5];
    // last line
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<PATTERNS_COUNT; i++)
        if (patterns[i] == pattern_generator -> pattern_for_point_and_size(x, y, widths[i], 8)) {
            if (line != x && line != -1) break;
            buffer[counter++] = chars[i];
            line = x;
            break;
        }
    wind_v3 = atoi(buffer);
    wind_r3 = line + 4;
    //printf("%i\t] first line:\t%i\n", wind_v3, wind_r3);
}
void analizer::analize_frame(frame _frame){    
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
}