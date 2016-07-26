//
// Created by ftominc on 25/07/16.
//

#ifndef PID_INFOHEADER1_H
#define PID_INFOHEADER1_H


class infoHeader{

private:
    uint32_t BiWidth;         //largura da imagem (em pixels)
    uint32_t BiHeight;        //altura da imagem (em pixels)
    uint16_t BiBitCount;      //numero de bits por cor (define o numero de cores da imagem)
    //uint32_t BiSizeImag;      //(?) precisa?
    uint32_t BiClrImportant;
public:
    void setBiClrImportant(uint32_t BiClrImportant);

public:
    uint32_t getBiClrImportant() const;
    //numero de cores importantes (precisa?)
public:
    uint32_t getBiWidth();
    uint32_t getBiHeight();
    uint16_t getBiBitCount();
    uint32_t getBiClrImpor();
    void setBiWidth(uint32_t _BiWidth);
    void setBiHeight(uint32_t _BiHeight);
    void setBiBitCount(uint16_t _BiBitCount);
    void setBiClrImpor(uint32_t _BiClrImpor);
};



#endif //PID_INFOHEADER1_H
