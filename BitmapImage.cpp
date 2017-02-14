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
        bitmap.bitmap[i].resize((infoHeader.getWidth())*(colorDepth/8)+(offset));
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
        }
    }

}

RGBColor BitmapImage::getColorAt(int l, int c){
    uint8_t red, green, blue;
        blue = bitmap.bitmap[l][c * 3];
        green = bitmap.bitmap[l][c * 3 + 1];
        red = bitmap.bitmap[l][c * 3 + 2];
    return RGBColor(red, green, blue);
}

void BitmapImage::toGrayScale() {
    //cout << "Convertendo para escala de cinza" << endl;
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;
    this->infoHeader.setBitspp(8);
    this->fileHeader.setFilesz(54+pow(2,infoHeader.getBitspp())*4+(infoHeader.getWidth()+(offset))*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+pow(2,infoHeader.getBitspp())*4);
    this->infoHeader.setBmp_bytesz(this->fileHeader.getFilesz()-this->fileHeader.getBmp_offset());
    ColorPallete cp = ColorPallete((int) pow(2.0, infoHeader.getBitspp()));
    for (int i = 0; i < pow(2.0,infoHeader.getBitspp()); i++) {
        cp.colors[i*4]=cp.colors[i*4+1]=cp.colors[i*4+2] =(uint8_t) i;
        cp.colors[i*4+3]=0;
    }
    cp.colors[9] = 255;
    cp.colors[8] = cp.colors[10] = cp.colors[11] = 0;
    cout << endl;
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
    colorPallete = cp;
    bitmap.bitmap.resize(0);
    bitmap.bitmap.resize(infoHeader.getHeight());

    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(chuva[k].begin(), chuva[k].end());
    }
}

void BitmapImage::to2Colors() {
    toGrayScale();
    int offset =4-((infoHeader.getWidth())%4);
    if(offset == 4)
        offset=0;
    this->infoHeader.setBitspp(8);
    this->fileHeader.setFilesz(54+pow(2,infoHeader.getBitspp())*4+(infoHeader.getWidth()+(offset))*infoHeader.getHeight());
    this->fileHeader.setBmp_offset(54+pow(2,infoHeader.getBitspp())*4);
    this->infoHeader.setBmp_bytesz(this->fileHeader.getFilesz()-this->fileHeader.getBmp_offset());
    ColorPallete cp = ColorPallete((int) pow(2.0, infoHeader.getBitspp()));

    cp.colors[0]=cp.colors[1]=cp.colors[2] =(uint8_t) 0;
    cp.colors[3]=0;
    cp.colors[4]=cp.colors[5]=cp.colors[6] =(uint8_t) 255;
    cp.colors[7]=0;
    vector<vector<uint8_t> > chuva;
    chuva.resize(infoHeader.getHeight());
    for (int i = 0; i < chuva.size(); i++) {
        int j=0;
        chuva[i].resize(infoHeader.getWidth()+offset);
        for (j = 0; j < chuva[i].size(); j++) {
            RGBColor color = getColorAt(i,j);
            uint8_t a = uint8_t(color.getRed()*0.299+color.getGreen()*0.587+color.getBlue()*0.114);
            j < chuva[i].size() - offset ?(chuva[i][j]= (unsigned char) (a < 100 ? 0 : 1)) : chuva[i][j] = 0;


        }
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
    //cout << "teste" << endl;
    //cout << "O TAMANHO DESSE DEMONIO DOS INFERNOS É " << infoHeader.getHeight() << " x " << infoHeader.getWidth() << endl;
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

    //fclose(f);
}

void BitmapImage::loadPallete(FILE *f) {
    colorPallete = ColorPallete((fileHeader.getBmp_offset()-54)/4);
    for (int i = 0; i < (fileHeader.getBmp_offset()-54)/4; i++) {
        fread(&colorPallete.colors[i],1,1, f);
    }
    cout << "Lendo " << fileHeader.getBmp_offset()-54 << " bytes para a paleta" << endl;
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

    cout << "New Bitmap Size " << newBitmap.size() << "x" << bitmap.bitmap[0].size() << endl;
    for (int k = 0; k < bitmap.bitmap.size(); k++) {
        bitmap.bitmap[k].assign(newBitmap[k].begin(), newBitmap[k].end());
    }
    saveBitMap(filePath + "grey.bmp");
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
    saveBitMap(filePath + "grey.bmp");
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

void BitmapImage::drawGrid(Point a, Point b) {
    Point interpolado = Point((1-0.08181818181818)*topLeft.x+ 0.08181818181818*topRight.x,(1-0.08181818181818)*topLeft.y+ 0.08181818181818*topRight.y);
    Point virtualSquare =
    drawRect(interpolado,teste);

    /*
    double m, y = 0;
    double mlr, angulo;


    mlr = 1.0*(topLeft.y - topRight.y)/ (topLeft.x - topRight.x);
    angulo = atan(-mlr);
    a.y = (int) (a.y + infoHeader.getWidth() * 0.06944444444);
    b.y = (int) (b.y + infoHeader.getWidth() * 0.06944444444);

    a.x = (int) (a.x * cos(angulo) - a.y * sin(angulo));
    a.y = (int) (a.x * sin(angulo) + a.y * cos(angulo));

    b.x = (int) (b.x * cos(angulo) - b.y * sin(angulo));
    b.y = (int) (b.x * sin(angulo) + b.y * cos(angulo));

    printf("%d %d\n", a.x, a.y);
    printf("%d %d\n", b.x, b.y);
    if(a.x < b.x){
        y = a.y;
        m = 1.0*(b.y - a.y) / (b.x - a.x);
        for (int x = a.x ; x < b.x ; ++x) {
            bitmap.bitmap[x][y] = 2;
            y+=m;
        }

    }else {
        y = b.y;
        m = 1.0 * (a.y - b.y) / (a.x - b.x);
        for (int x = b.x; x < a.x; ++x) {
            bitmap.bitmap[x][y] = 2;
            y += m;
        }
    }
    saveBitMap(filePath + "grey.bmp");*/
}