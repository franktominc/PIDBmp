//
// Created by ftominc on 25/07/16.
//

#ifndef PID_INFOHEADER1_H
#define PID_INFOHEADER1_H


class infoHeader{

private:
    uint32_t BiWidth;
    //largura da imagem (em pixels)
    uint32_t BiHeight;        //altura da imagem (em pixels)
    uint16_t BiBitCount;      //numero de bits por cor (define o numero de cores da imagem)
    //uint32_t BiSizeImag;      //(?) precisa?
    uint32_t BiClrImportant;
public:
    uint32_t getBiWidth() const;

    void setBiWidth(uint32_t BiWidth);

    uint32_t getBiHeight() const;

    void setBiHeight(uint32_t BiHeight);

    uint16_t getBiBitCount() const;

    void setBiBitCount(uint16_t BiBitCount);

    uint32_t getBiClrImportant() const;

    void setBiClrImportant(uint32_t BiClrImportant);

};



#endif //PID_INFOHEADER1_H
