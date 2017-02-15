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
#include "Point.h"

class BitmapImage {
private:
    InfoHeader infoHeader;
    FileHeader fileHeader;
    ColorPallete colorPallete = ColorPallete(0);
    Bitmap bitmap;
    void loadBMP(FILE *f, int colorDepth);
    void loadPallete(FILE* f);
public:
    vector<char> answers;
    Point topLeft;
    Point topRight;
    Point botLeft;
    string fileName;
    string filePath;
    BitmapImage(std::string path, std::string fileName);
    void toGrayScale();
    //void print();

    RGBColor getColorAt(int l, int c);

    void saveBitMap(string path);


    void applyErosion();

    void Erode(int times);

    void applyDilation();

    void Dilate(int times);

    void findTopLeftRectangle();

    void findTopRightRectangle();

    void drawRect(Point a, Point b);

    void findBotLeftRectangle();

    void findAnswers(Point a);

    void scanLine(Point a, Point b);

    void floydSteinberg();

    void toBlackAndWhite();
};


#endif //PID_BITMAPIMAGE_H
