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

    if(infoHeader.getBitspp() != 24){
        loadPallete(f);
    }

    loadBMP(f, infoHeader.getBitspp());

    //saveBitMap(filePath + "grey.bmp");
    fclose(f);
}

void BitmapImage::loadBMP(FILE *f, int colorDepth) {

    bitmap.bitmap.resize(infoHeader.getHeight());
    int offset =4-((infoHeader.getWidth()*3)%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < infoHeader.getHeight(); i++) {
        bitmap.bitmap[i].resize((infoHeader.getWidth())*(colorDepth/8)+(offset));
    }

    for (int i = 0; i < bitmap.bitmap.size(); i++) {
        for (int j = 0; j < bitmap.bitmap[i].size(); j++) {
            fread(&bitmap.bitmap[i][j], 1, 1, f);
        }
    }

}

RGBColor BitmapImage::getColorAt(int l, int c){
    uint8_t red, green, blue;
    if(infoHeader.getBitspp() == 24) {
        blue = bitmap.bitmap[l][c * 3];
        green = bitmap.bitmap[l][c * 3 + 1];
        red = bitmap.bitmap[l][c * 3 + 2];
    }else {
        int index = bitmap.bitmap[l][c];
        red = (uint8_t) index;
        blue = (uint8_t) index;
        green = (uint8_t) index;
    }
    return RGBColor(red, green, blue);
}

void BitmapImage::toGrayScale() {
        int offset = 4 - ((infoHeader.getWidth()) % 4);
        if (offset == 4)
            offset = 0;

        //cout << endl;
        vector<vector<uint8_t> > chuva;

        chuva.resize(infoHeader.getHeight());
        //cout << "offset: "<< offset <<endl;
        cout << filePath << endl;
        cout << "Bits: " << infoHeader.getBitspp() << endl;
        for (int i = 0; i < chuva.size(); i++) {
            int j = 0;
            chuva[i].resize(infoHeader.getWidth() + offset);
            for (j = 0; j < chuva[i].size(); j++) {
                if (j < chuva[i].size() - offset) {
                    RGBColor color = getColorAt(i, j);
                    chuva[i][j] = uint8_t(color.getRed() * 0.299 + color.getGreen() * 0.587 + color.getBlue() * 0.114);
                } else chuva[i][j] = 0;

            }
        }
        //cout << "O Tamanho do BMP em tons de cinza é " << chuva.size() << "x" << chuva[0].size() << endl;
        this->infoHeader.setBitspp(8);
        this->fileHeader.setFilesz(
                54 + pow(2, infoHeader.getBitspp()) * 4 + (infoHeader.getWidth() + (offset)) * infoHeader.getHeight());
        this->fileHeader.setBmp_offset(54 + pow(2, infoHeader.getBitspp()) * 4);
        this->infoHeader.setBmp_bytesz(this->fileHeader.getFilesz() - this->fileHeader.getBmp_offset());
        ColorPallete cp = ColorPallete((int) pow(2.0, infoHeader.getBitspp()));
        for (int i = 0; i < pow(2.0, infoHeader.getBitspp()); i++) {
            cp.colors[i * 4] = cp.colors[i * 4 + 1] = cp.colors[i * 4 + 2] = (uint8_t) i;
            cp.colors[i * 4 + 3] = 0;
        }

        colorPallete = cp;
        bitmap.bitmap.resize(0);
        bitmap.bitmap.resize(infoHeader.getHeight());

        for (int k = 0; k < bitmap.bitmap.size(); k++) {
            bitmap.bitmap[k].assign(chuva[k].begin(), chuva[k].end());
        }
    saveBitMap(filePath + "grey.bmp");
}

void BitmapImage::saveBitMap(string path){
    FILE* f = fopen(path.c_str(), "wb+");
    fwrite(&fileHeader,14,1,f);
    fwrite(&infoHeader,40,1,f);

    if(infoHeader.getBitspp() != 24){
        for (int i = 0; i < pow(2,infoHeader.getBitspp())*4; i++) {
            fwrite(&colorPallete.colors[i],1,1,f);
        }
    }
    for (int i = 0; i < bitmap.bitmap.size(); i++) {
        for (int j = 0; j < bitmap.bitmap[i].size(); j++) {
            fwrite(&bitmap.bitmap[i][j], 1,1,f);
        }
    }

    fclose(f);
}

void BitmapImage::floydSteinberg(){
    //cout << "Convertendo para escala de cinza" << endl;
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;

    //cout << endl;
    vector<vector<uint8_t> > chuva;
    vector<vector<double> > quantizationMatrix;

    chuva.resize(infoHeader.getHeight());
    quantizationMatrix.resize(infoHeader.getHeight());
    //cout << "offset: "<< offset <<endl;
    for (int i = 0; i < chuva.size(); i++) {
        int j=0;
        chuva[i].resize(infoHeader.getWidth()+offset);
        quantizationMatrix[i].resize(chuva[i].size());
        for (j = 0; j < chuva[i].size(); j++) {
            RGBColor color = getColorAt(i,j);
            uint8_t grayTone = uint8_t(color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114);
            if(j < chuva[i].size() - offset){
                grayTone < 127 ? grayTone = 0: grayTone = 255;
                chuva[i][j]= grayTone;
                double quantizationError = color.getRed() - grayTone + color.getBlue() - grayTone + color.getGreen() - grayTone;
                quantizationMatrix[i][j] = quantizationError/3;
            }else{
                chuva[i][j] = 0;
            }
        }
    }
    for (int l = 0; l < chuva.size(); l++) {
        for (int i = 0; i < chuva[l].size(); i++) {
            if(l< chuva.size()-1) {
                chuva[l + 1][l] += (5.0) / 16 * quantizationMatrix[l][i];
                if(i > 0) {
                    chuva[l + 1][i-1] += (3.0) / 16 * quantizationMatrix[l][i];
                }
                if(i < chuva[l].size() - 1) {
                    chuva[l+1][i+1] += (1.0)/16*quantizationMatrix[l][i];
                }
            }
            if(i < chuva[l].size() - 1 ){
                chuva[l][i+1] += (7.0)/16*quantizationMatrix[l][i];
            }
        }
    }
    //cout << "O Tamanho do BMP em tons de cinza é " << chuva.size() << "x" << chuva[0].size() << endl;
    this->infoHeader.setBitspp(8);
    this->fileHeader.setFilesz(54+pow(2,infoHeader.getBitspp())*4+(infoHeader.getWidth()+(offset))*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+pow(2,infoHeader.getBitspp())*4);
    this->infoHeader.setBmp_bytesz(this->fileHeader.getFilesz()-this->fileHeader.getBmp_offset());
    ColorPallete cp = ColorPallete((int) pow(2.0, infoHeader.getBitspp()));
    for (int i = 0; i < pow(2.0,infoHeader.getBitspp()); i++) {
        cp.colors[i*4]=cp.colors[i*4+1]=cp.colors[i*4+2] =(uint8_t) i;
        cp.colors[i*4+3]=0;
    }
    colorPallete = cp;
    bitmap.bitmap.resize(0);
    bitmap.bitmap.resize(infoHeader.getHeight());

    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(chuva[k].begin(), chuva[k].end());
    }
    saveBitMap(filePath + "grey.bmp");
}

void BitmapImage::loadPallete(FILE *f) {
    colorPallete = ColorPallete(pow(2, infoHeader.getBitspp())*4);
    for (int i = 0; i < pow(2, infoHeader.getBitspp())*4; i++) {
        fread(&colorPallete.colors[i],1,1, f);
    }
}

void BitmapImage::applyErosion(){
    vector<vector<uint8_t > > newBitmap;
    newBitmap.resize(bitmap.bitmap.size());
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < newBitmap.size(); i++) {
        newBitmap[i].resize(bitmap.bitmap[0].size());
        for (int j = 0; j < newBitmap[i].size()-offset; ++j) {
            if(i == 0){
                if(j == 0){
                    if(bitmap.bitmap[i][j+1] == 0 && bitmap.bitmap[i+1][j+1] == 0 && bitmap.bitmap[i+1][j] == 0 && bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else if(j == newBitmap[i].size()-1){
                    if(bitmap.bitmap[i][j-1] == 0 && bitmap.bitmap[i+1][j-1] == 0 && bitmap.bitmap[i+1][j] == 0 && bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else{
                    if(bitmap.bitmap[i][j-1] == 0 &&
                            bitmap.bitmap[i+1][j-1] == 0 &&
                            bitmap.bitmap[i][j] == 0 &&
                            bitmap.bitmap[i+1][j] == 0 &&
                            bitmap.bitmap[i][j+1] == 0 &&
                            bitmap.bitmap[i+1][j+1] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }
            }else if(i == newBitmap.size()-1){
                if(j == 0){
                    if(bitmap.bitmap[i][j+1] == 0 && bitmap.bitmap[i-1][j+1] == 0 && bitmap.bitmap[i-1][j] == 0 && bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else if(j == newBitmap[i].size()-1){
                    if(bitmap.bitmap[i][j-1] == 0 && bitmap.bitmap[i-1][j-1] == 0 && bitmap.bitmap[i-1][j] == 0 && bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else{
                    if(bitmap.bitmap[i][j-1] == 0 &&
                       bitmap.bitmap[i-1][j-1] == 0 &&
                       bitmap.bitmap[i][j] == 0 &&
                       bitmap.bitmap[i-1][j] == 0 &&
                       bitmap.bitmap[i][j+1] == 0 &&
                       bitmap.bitmap[i-1][j+1] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }
            }else{
                if(bitmap.bitmap[i-1][j-1] == 0 &&
                   bitmap.bitmap[i-1][j] == 0 &&
                   bitmap.bitmap[i-1][j+1] == 0 &&
                   bitmap.bitmap[i][j-1] == 0 &&
                   bitmap.bitmap[i][j] == 0 &&
                   bitmap.bitmap[i][j+1] == 0 &&
                   bitmap.bitmap[i+1][j-1] == 0 &&
                   bitmap.bitmap[i+1][j] == 0 &&
                   bitmap.bitmap[i+1][j+1] == 0
                   ){
                    newBitmap[i][j] = 0;
                }else{
                    newBitmap[i][j] = 255;
                }
            }
        }
        for (int k = bitmap.bitmap[i].size() - offset; k < bitmap.bitmap[i].size(); ++k) {
            newBitmap[i][k] = 0;
        }
    }

    //cout << "New Bitmap Size " << newBitmap.size() << "x" << bitmap.bitmap[0].size() << endl;
    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(newBitmap[k].begin(), newBitmap[k].end());
    }
}

void BitmapImage::Erode(int times) {
    for (int i = 0; i < times; ++i) {
        applyErosion();
    }
}

void BitmapImage::applyDilation(){
    vector<vector<uint8_t > > newBitmap;
    newBitmap.resize(bitmap.bitmap.size());
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;
    for (int i = 0; i < newBitmap.size(); i++) {
        newBitmap[i].resize(bitmap.bitmap[0].size());
        for (int j = 0; j < newBitmap[i].size()-offset; ++j) {
            if(i == 0){
                if(j == 0){
                    if(bitmap.bitmap[i][j+1] == 0 || bitmap.bitmap[i+1][j+1] == 0 || bitmap.bitmap[i+1][j] == 0 || bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else if(j == newBitmap[i].size()-1){
                    if(bitmap.bitmap[i][j-1] == 0 || bitmap.bitmap[i+1][j-1] == 0 || bitmap.bitmap[i+1][j] == 0 || bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else{
                    if(bitmap.bitmap[i][j-1] == 0 ||
                       bitmap.bitmap[i+1][j-1] == 0 ||
                       bitmap.bitmap[i][j] == 0 ||
                       bitmap.bitmap[i+1][j] == 0 ||
                       bitmap.bitmap[i][j+1] == 0 ||
                       bitmap.bitmap[i+1][j+1] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }
            }else if(i == newBitmap.size()-1){
                if(j == 0){
                    if(bitmap.bitmap[i][j+1] == 0 || bitmap.bitmap[i-1][j+1] == 0 || bitmap.bitmap[i-1][j] == 0 ||bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else if(j == newBitmap[i].size()-1){
                    if(bitmap.bitmap[i][j-1] == 0 || bitmap.bitmap[i-1][j-1] == 0 || bitmap.bitmap[i-1][j] == 0 || bitmap.bitmap[i][j] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }else{
                    if(bitmap.bitmap[i][j-1] == 0 ||
                       bitmap.bitmap[i-1][j-1] == 0 ||
                       bitmap.bitmap[i][j] == 0 ||
                       bitmap.bitmap[i-1][j] == 0 ||
                       bitmap.bitmap[i][j+1] == 0 ||
                       bitmap.bitmap[i-1][j+1] == 0){
                        newBitmap[i][j] = 0;
                    }else{
                        newBitmap[i][j] = 255;
                    }
                }
            }else{
                if(bitmap.bitmap[i-1][j-1] == 0 ||
                   bitmap.bitmap[i-1][j] == 0 ||
                   bitmap.bitmap[i-1][j+1] == 0 ||
                   bitmap.bitmap[i][j-1] == 0 ||
                   bitmap.bitmap[i][j] == 0 ||
                   bitmap.bitmap[i][j+1] == 0 ||
                   bitmap.bitmap[i+1][j-1] == 0 ||
                   bitmap.bitmap[i+1][j] == 0 ||
                   bitmap.bitmap[i+1][j+1] == 0
                        ){
                    newBitmap[i][j] = 0;
                }else{
                    newBitmap[i][j] = 255;
                }
            }
        }
        for (int k = bitmap.bitmap[i].size() - offset; k < bitmap.bitmap[i].size(); ++k) {
            newBitmap[i][k] = 0;
        }
    }

    //cout << "New Bitmap Size " << newBitmap.size() << "x" << bitmap.bitmap[0].size() << endl;
    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(newBitmap[k].begin(), newBitmap[k].end());
    }
}

void BitmapImage::Dilate(int times){
    for (int i = 0; i < times; ++i) {
        applyDilation();
    }
}

void BitmapImage::findTopLeftRectangle(){

    int c = infoHeader.getHeight();
    for (int i = 30; ; ) {
        for (int j = --c; j < infoHeader.getHeight(); j++,i++) {
            if(bitmap.bitmap[j][i]==0){
                topLeft = Point(j-(0.044585*infoHeader.getHeight()),i+(0.027027*infoHeader.getWidth()));
                return;
            }
        }
        i = 30;
    }


}

void BitmapImage::findTopRightRectangle(){

    int c = infoHeader.getWidth()-30;
    for (int i = c; ; ) {
        for (int j = infoHeader.getHeight()-1; i < infoHeader.getWidth()-30; j--,i++) {
            if(bitmap.bitmap[j][i]==0){
                topRight = Point(j-(0.044585*infoHeader.getHeight()),i-(0.027027*infoHeader.getWidth()));
                return;
            }
        }
        i = --c;
    }

}

void BitmapImage::findBotLeftRectangle(){

    int c = 0;
    for (int i = 30; ; ) {
        for (int j = c++; j >= 0 ; j--,i++) {
            if(bitmap.bitmap[j][i]==0){
                botLeft = Point(j+(0.044585*infoHeader.getHeight()),i+(0.027027*infoHeader.getWidth()));
                return ;
            }
        }
        i = 30;
    }
}

void BitmapImage::drawRect(Point a, Point b) {
    double m, y = 0;

    if(a.x < b.x){
        y = a.y;
        m = 1.0*(b.y - a.y) / (b.x - a.x);
        for (int x = a.x ; x < b.x ; ++x) {
            bitmap.bitmap[x][y] = 2;
            y+=m;
        }

    }else{
        y = b.y;
        m = 1.0*(a.y-b.y)/(a.x - b.x);
        for (int x = b.x ; x < a.x ; ++x) {
            bitmap.bitmap[x][y] = 2;
            y+=m;
        }
    }
    saveBitMap(filePath + "grey.bmp");
}

void BitmapImage::findAnswers(Point topLeft, Point b) {
    double k=0.09393939393939;
    double k0=0.08181818181818;
    Point squareOffset =Point((topLeft.x-botLeft.x),(topLeft.y-botLeft.y) );
    Point virtualSquare = Point(topRight.x-squareOffset.x,topRight.y-squareOffset.y);
    for (int i = 0; i < 10; i++) {
        Point interpolado = Point((1-(k*i+k0))*topLeft.x+ (k*i+k0)*topRight.x,(1-k0-i*k)*topLeft.y+ (k*i+k0)*topRight.y);
        Point interpoladoBot = Point((1-(k*i+k0))*botLeft.x+ (k*i+k0)*virtualSquare.x,(1-(k*i+k0))*botLeft.y+ (k*i+k0)*virtualSquare.y);
        //drawRect(interpolado,interpoladoBot);
        scanLine(interpolado, interpoladoBot, i);
    }
}

void BitmapImage::scanLine(Point top, Point bot, int teste) {
    double y = top.x;
    double porcentagem = 0;
    double m = 1.0*(top.y - bot.y) / (top.x - bot.x);;
    int maior=0, menor=100;
    y = bot.y;;
    //cout << "Teste:" << teste << endl;
    //drawRect(top, bot);
    for (int x = bot.x ; x < top.x ; ++x) {
        if(bitmap.bitmap[x][y] == 0){
            porcentagem=(top.x-x)*100/(top.x-bot.x);
            //cout << "Porcentagem:" << porcentagem << endl;
            if(porcentagem > maior)
                maior = porcentagem;
            if(porcentagem<menor)
                menor = porcentagem;
        }
        y+=m;
    }
    if(maior-menor <20 && maior - menor > 0){
        int media= (maior+menor)/2;
        switch(media){
            case 0 ... 20:
                answers.push_back('A');
                break;
            case 21 ... 40:
                answers.push_back('B');
                break;
            case 41 ... 60:
                answers.push_back('C');
                break;
            case 61 ... 80:
                answers.push_back('D');
                break;
            default:
                answers.push_back('E');
                break;
        }
    }else{
        if(maior-menor==-100)
            answers.push_back('O');
        else
            answers.push_back('X');
    }

}

void BitmapImage::toBlackAndWhite() {
    //cout << "Convertendo para escala de cinza" << endl;
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;
    //cout << endl;
    vector<vector<uint8_t> > chuva;

    chuva.resize(infoHeader.getHeight());
    //cout << "offset: "<< offset <<endl;
    for (int i = 0; i < chuva.size(); i++) {
        int j=0;
        chuva[i].resize(infoHeader.getWidth()+offset);
        for (j = 0; j < chuva[i].size(); j++) {
            RGBColor color = getColorAt(i,j);

            j < chuva[i].size() - offset ?chuva[i][j]= uint8_t(color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114): chuva[i][j] = 0;
            chuva[i][j] < 70?chuva[i][j] = 0: chuva[i][j] = 255;

        }
    }
    //cout << "O Tamanho do BMP em tons de cinza é " << chuva.size() << "x" << chuva[0].size() << endl;
    this->infoHeader.setBitspp(8);
    this->fileHeader.setFilesz(54+pow(2,infoHeader.getBitspp())*4+(infoHeader.getWidth()+(offset))*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+pow(2,infoHeader.getBitspp())*4);
    this->infoHeader.setBmp_bytesz(this->fileHeader.getFilesz()-this->fileHeader.getBmp_offset());
    ColorPallete cp = ColorPallete((int) pow(2.0, infoHeader.getBitspp()));
    for (int i = 0; i < pow(2.0,infoHeader.getBitspp()); i++) {
        cp.colors[i*4]=cp.colors[i*4+1]=cp.colors[i*4+2] =(uint8_t) i;
        cp.colors[i*4+3]=0;
    }
    colorPallete = cp;
    bitmap.bitmap.resize(0);
    bitmap.bitmap.resize(infoHeader.getHeight());

    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(chuva[k].begin(), chuva[k].end());
    }
    saveBitMap(filePath + "grey.bmp");
}
