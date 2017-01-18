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
BitmapImage::BitmapImage(string path, string fileName) {

    filePath.assign(path);
    this->fileName.assign(fileName);


    FILE *f = fopen(filePath.c_str(), "rb+");



    fread(&fileHeader,1 , 14, f);

    fread(&infoHeader,1 , 40, f);

    cout << fileHeader << endl << infoHeader;

    if(infoHeader.getBitspp() != 24){
        cout << "Carregando a Paleta" << endl;
        loadPallete(f);
        cout << "foi" << endl;
    }

    cout << "Carregando o BMP" << endl;
    loadBMP(f, infoHeader.getBitspp());



    cout << "O arquivo foi carregado com sucesso" << endl;
    fclose(f);
}

void BitmapImage::loadBMP(FILE *f, int colorDepth) {
    cout << "Altura: " << dec << infoHeader.getHeight() << endl;
    cout << "Largura: " << infoHeader.getWidth() << endl;
    cout << "Color Depth: " << colorDepth << endl;

    bitmap.bitmap.resize(infoHeader.getHeight());
    cout << "Criado" << endl;
    int offset =4-((infoHeader.getWidth()*3)%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < infoHeader.getHeight(); i++) {
        bitmap.bitmap[i].resize((infoHeader.getWidth())*(colorDepth/8)+offset);
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
            fread(&bitmap.bitmap[i][j], 1, 1, f);
            if(j > infoHeader.getWidth()*3)
                printf("%X ", bitmap.bitmap[i][j]);
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
    cout << "Convertendo para escala de cinza" << endl;
    int offset =4-((infoHeader.getWidth()*3)%4);
    if(offset == 4)
        offset=0;
    this->fileHeader.setFilesz(54+1024+(infoHeader.getWidth()+offset)*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+1024);
    this->infoHeader.setBitspp(8);
    this->infoHeader.setBmp_bytesz(infoHeader.getWidth()*infoHeader.getHeight());
    ColorPallete cp = ColorPallete(pow(2.0,infoHeader.getBitspp()));
    for (int i = 0; i < pow(2.0,infoHeader.getBitspp()); i++) {
        cp.colors[i*4]=cp.colors[i*4+1]=cp.colors[i*4+2] =(uint8_t) i;
        cp.colors[i*4+3]=0;
    }
    for (int i = 0; i < 1024; i++) {
        printf("%x ", cp.colors[i]);
    }
    cout << endl;
    vector<vector<uint8_t> > chuva;

    chuva.resize(infoHeader.getHeight());

    for (int i = 0; i < chuva.size(); i++) {
        chuva[i].resize(infoHeader.getWidth()+offset);
        for (int j = 0; j < chuva[i].size(); j++) {
            RGBColor color = getColorAt(i,j);

            j < chuva[i].size() - offset?chuva[i][j]= uint8_t(color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114): chuva[i][j] = 0;
            if(j>chuva[i].size() - offset)
                printf("%X ",chuva[i][j]);
        }
    }
    cout << "O Tamanho do BMP em tons de cinza é " << chuva.size() << "x" << chuva[0].size() << endl;
    colorPallete = cp;
    bitmap.bitmap.resize(0);
    bitmap.bitmap.resize(infoHeader.getHeight());
    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(chuva[k].begin(), chuva[k].end());
    }
    saveBitMap(filePath + "grey.bmp");
}

void BitmapImage::saveBitMap(string path){
    cout << "teste" << endl;
    cout << "O TAMANHO DESSE DEMONIO DOS INFERNOS É " << infoHeader.getHeight() << " x " << infoHeader.getWidth() << endl;
    FILE* f = fopen(path.c_str(), "wb+");
    fwrite(&fileHeader,14,1,f);
    fwrite(&infoHeader,40,1,f);
    char nil = 0;
    for (int i = 0; i < 1024; i++) {
        fwrite(&colorPallete.colors[i],1,1,f);
    }
    int offset =4-((infoHeader.getWidth()*3)%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < infoHeader.getHeight(); i++) {
        for (int j = 0; j < infoHeader.getWidth(); j++) {
            if(j> infoHeader.getWidth() - offset)
                for (int k = 0; k < offset; k++) {
                    fwrite(&nil, 1,1,f);
                };
            fwrite(&bitmap.bitmap[i][j], 1,1,f);
        }
    }

    fclose(f);
}

void BitmapImage::loadPallete(FILE *f) {
    colorPallete = ColorPallete((fileHeader.getBmp_offset()-54)/4);
    for (int i = 0; i < (fileHeader.getBmp_offset()-54)/4; i++) {
        fread(&colorPallete.colors[i],1,1, f);
    }
    cout << "Lendo " << fileHeader.getBmp_offset()-54 << " bytes para a paleta" << endl;
}

