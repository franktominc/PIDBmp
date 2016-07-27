//
// Created by ftominc on 26/07/16.
//

#include "BitmapImage.h"
#include <iostream>
#include <stdlib.h>
#include <malloc.h>
#include <cstdio>

using namespace std;
BitmapImage::BitmapImage(string path) {
    FILE *f = fopen(path.c_str(), "rb+");

    fread(&fileHeader,1 , 14, f);
    fread(&infoHeader,1 , 40, f);

    if(infoHeader.getBitspp() != 24){
        loadPallete(f);
    }
    loadBMP(f, infoHeader.getBitspp());

    cout << "O arquivo foi carregado com sucesso" << flush;
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

void BitmapImage::loadPallete(FILE *f) {
    colorPallete = ColorPallete((fileHeader.getBmp_offset()-54)/4);
    fread(colorPallete.colors, sizeof(uint32_t), (fileHeader.getBmp_offset()-54)/4, f);
}
