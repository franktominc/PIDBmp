//
// Created by ftominc on 26/07/16.
//

#include "BitmapImage.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>

BitmapImage::BitmapImage(std::string path) {
    FILE *f = fopen(path, "rb+");
    fread(fileHeader,1 , 14, f);
    fread(infoHeader,1 , 40, f);
    if(fileHeader.getBmp_offset()!=54){
        colorPallete = ColorPallete((fileHeader.getBmp_offset()-54)/4);
        fread(colorPallete.colors, sizeof(uint32_t), (fileHeader.getBmp_offset()-54)/4, f);
    }
    bitmap.bitmap = (uint8_t **) calloc(infoHeader.getHeight(), sizeof(uint8_t));
    for (int i = 0; i < infoHeader.getHeight(); i++) {
        bitmap.bitmap[i] = (uint8_t *) calloc(infoHeader.getWidth(), sizeof(uint8_t));
        fread(bitmap.bitmap[i], 1, infoHeader.getWidth()*8, f);
    }
}
