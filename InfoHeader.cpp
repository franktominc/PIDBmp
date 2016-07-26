//
// Created by ftominc on 25/07/16.
//

#include <cstdint>
#include "InfoHeader.h"


uint32_t infoHeader::getBiWidth(){
    return this->BiWidth;
}

uint32_t infoHeader::getBiHeight(){
    return this->BiHeight;
}

uint16_t infoHeader::getBiBitCount(){
    return this->BiBitCount;
}

uint32_t infoHeader::getBiClrImportant() const {
    return BiClrImportant;
}

void infoHeader::setBiClrImportant(uint32_t BiClrImportant) {
    infoHeader::BiClrImportant = BiClrImportant;
}
