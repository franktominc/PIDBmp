//
// Created by ftominc on 25/07/16.
//

#ifndef PID_FILEHEADER_H
#define PID_FILEHEADER_H


#include <cstdint>

class FileHeader {
private:
    uint16_t BfType;
    uint32_t BfSize;             //tamanho total do arquivo (em bytes)
    uint32_t BfOffSetBits;       //Deslocamento até o mapa de bits
public:
    uint16_t getBfType() const;

    void setBfType(uint16_t BfType);

    uint32_t getBfSize() const;

    void setBfSize(uint32_t BfSize);

    uint32_t getBfOffSetBits() const;

    void setBfOffSetBits(uint32_t BfOffSetBits);

};


#endif //PID_FILEHEADER_H
