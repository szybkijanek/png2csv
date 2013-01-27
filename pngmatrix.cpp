//
//  pngmatrix.cpp
//  png2csv
//
//  Created by Paweł Ksieniewicz on 19.01.2013.
//  Copyright (c) 2013 Paweł Ksieniewicz. All rights reserved.
//

#include "pngmatrix.h"

void pngmatrix::read_png_file(char* file_name){
    char header[8];    // 8 is the maximum size that can be checked
    
    /* open file and test for it being a png */
    FILE *fp = fopen(file_name, "rb");
    fread(header, 1, 8, fp);
    
    //if (png_sig_cmp(header, 0, 8))
    //    abort_("[read_png_file] File %s is not recognized as a PNG file", file_name);
    
    
    /* initialize stuff */
    png_ptr = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    
    info_ptr = png_create_info_struct(png_ptr);
    
    png_init_io(png_ptr, fp);
    png_set_sig_bytes(png_ptr, 8);
    
    png_read_info(png_ptr, info_ptr);
    
    width = png_get_image_width(png_ptr, info_ptr);
    height = png_get_image_height(png_ptr, info_ptr);
    color_type = png_get_color_type(png_ptr, info_ptr);
    bit_depth = png_get_bit_depth(png_ptr, info_ptr);
    
    number_of_passes = png_set_interlace_handling(png_ptr);
    png_read_update_info(png_ptr, info_ptr);
    
    
    /* read file */
    
    row_pointers = (png_bytep*) malloc(sizeof(png_bytep) * height);
    for (y=0; y<height; y++)
        row_pointers[y] = (png_byte*) malloc(png_get_rowbytes(png_ptr,info_ptr));
    
    png_read_image(png_ptr, row_pointers);
    
    fclose(fp);
}


int pngmatrix::red_pixel(int _x, int _y){
    png_byte* row = row_pointers[_y];
    png_byte* ptr = &(row[_x*4]);
    return ptr[0];
}

int pngmatrix::green_pixel(int _x, int _y){
    png_byte* row = row_pointers[_y];
    png_byte* ptr = &(row[_x*4]);
    return ptr[1];
}

void pngmatrix::process_file(void){
    for (y=0; y<height; y++) {
        png_byte* row = row_pointers[y];
        for (x=0; x<width; x++) {
            png_byte* ptr = &(row[x*4]);
            printf("Pixel at position [ %d - %d ] has RGBA values: %d - %d - %d - %d\n",
                   x, y, ptr[0], ptr[1], ptr[2], ptr[3]);
            
            /* set red value to 0 and green value to the blue one */
            ptr[0] = 0;
            ptr[1] = ptr[2];
        }
    }
}