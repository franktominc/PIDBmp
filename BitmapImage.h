//
// Created by ftominc on 26/07/16.
//

#ifndef PID_BITMAPIMAGE_H
#define PID_BITMAPIMAGE_H


#include <iostream>
#include "FileHeader.h"
#include "InfoHeader.h"
#include "ColorPallete.h"
#include "Bitmap.h"
#include "RGBColor.h"

class BitmapImage {
private:
    InfoHeader infoHeader;
    FileHeader fileHeader;
    ColorPallete colorPallete = ColorPallete(0);
    Bitmap bitmap;
    void loadBMP(FILE *f, int colorDepth);
    void loadPallete(FILE* f);
public:
    BitmapImage(std::string path);
    void toGrayScale();
    //void print();

    RGBColor getColorAt(int l, int c);

    void saveBitMap(string path);
};


#endif //PID_BITMAPIMAGE_H
