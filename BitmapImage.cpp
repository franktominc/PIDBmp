//
// Created by ftominc on 26/07/16.
//

#include "BitmapImage.h"
#include "RGBColor.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <cstdio>
#include <cmath>

using namespace std;
BitmapImage::BitmapImage(string path) {
    FILE *f = fopen(path.c_str(), "rb+");

    fread(&fileHeader,1 , 14, f);

    fread(&infoHeader,1 , 40, f);

    cout << fileHeader << endl << infoHeader;

    if(infoHeader.getBitspp() != 24){
        loadPallete(f);
    }


    loadBMP(f, infoHeader.getBitspp());



    cout << "O arquivo foi carregado com sucesso" << endl;
    fclose(f);
}

void BitmapImage::loadBMP(FILE *f, int colorDepth) {
    bitmap.bitmap.resize(infoHeader.getHeight());
    for (int i = 0; i < infoHeader.getHeight(); i++) {
        bitmap.bitmap[i].resize((infoHeader.getWidth())*(colorDepth/8));
    }

    cout << "O tamanho do bitmap criado eh "
         << bitmap.bitmap.size()
         << " x "
         << bitmap.bitmap[0].size()
         << endl;
    cout << "O tamanho do bitmap segundo o cabecalho eh "
         << infoHeader.getHeight()
         << " x "
         << infoHeader.getWidth()
         << endl;
    for (int i = 0; i < bitmap.bitmap.size(); i++) {
        for (int j = 0; j < bitmap.bitmap[i].size(); j++) {
            fread(&bitmap.bitmap[i][j], 1, 1 ,f);
        }
        if((4-((infoHeader.getWidth() * (colorDepth/8)) % 4)) < 4){
            fseek(f, 4-((infoHeader.getWidth() * (colorDepth/8)) % 4), SEEK_CUR);
        }
    }
}

RGBColor BitmapImage::getColorAt(int l, int c){
    uint8_t blue=bitmap.bitmap[l][c*3];
    uint8_t green=bitmap.bitmap[l][c*3+1];
    uint8_t red=bitmap.bitmap[l][c*3+2];

    return RGBColor(red, green, blue);
}

void BitmapImage::toGrayScale() {
    this->fileHeader.setFilesz(54+1024+infoHeader.getWidth()*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+1024);
    this->infoHeader.setBitspp(8);
    this->infoHeader.setBmp_bytesz(infoHeader.getWidth()*infoHeader.getHeight());
    ColorPallete cp = ColorPallete(pow(2,infoHeader.getBitspp()));
    for (int i = 0; i < pow(2,infoHeader.getBitspp()); i++) {
        cp.colors[i*4]=cp.colors[i*4+1]=cp.colors[i*4+2] =(uint8_t) i;
        cp.colors[i*4+3]=0;
    }
    for (int i = 0; i < 1024; i++) {
        printf("%x ", cp.colors[i]);
    }
    vector<vector<uint8_t> > chuva;
    chuva.resize(infoHeader.getHeight());
    int offset =4-((infoHeader.getWidth()*3)%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < chuva.size(); i++) {
        chuva[i].resize(infoHeader.getWidth()+offset);
        for (int j = 0; j < chuva[i].size()-offset; j++) {
            RGBColor color = getColorAt(i,j);
            chuva[i][j]= uint8_t(color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114);
        }
        for (int j = chuva[i].size()-offset; j < chuva[i].size(); j++) {
            chuva[i][j]=0;
        }
    }
    colorPallete = cp;
    bitmap.bitmap=chuva;
    saveBitMap("/home/ftominc/rute/out.bmp");
}

void BitmapImage::saveBitMap(string path){
    cout << "teste" << endl;
    FILE* f = fopen(path.c_str(), "wb+");
    fwrite(&fileHeader,14,1,f);
    fwrite(&infoHeader,40,1,f);
    fwrite(&colorPallete.colors,fileHeader.getBmp_offset()-54,1,f);
    fwrite(&bitmap.bitmap, infoHeader.getBmp_bytesz(),1,f);
    fclose(f);
}

void BitmapImage::loadPallete(FILE *f) {
    colorPallete = ColorPallete((fileHeader.getBmp_offset()-54)/4);
    fread(&colorPallete.colors, sizeof(uint32_t), (fileHeader.getBmp_offset()-54)/4, f);
}
