//
//  analizer.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "analizer.h"

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
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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
    for (int x = _frame.x; x < _frame.x + _frame.height; x++) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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
    for (int x = _frame.x + _frame.height - 1; x >= _frame.x; x--) for (int y = _frame.y; y < _frame.y + _frame.width; y++) for (int i=0; i<13; i++)
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