//
// Created by ftominc on 25/07/16.
//

#include <cstdint>
#include "InfoHeader.h"


uint32_t infoHeader::getBiWidth() const {
    return BiWidth;
}

void infoHeader::setBiWidth(uint32_t BiWidth) {
    infoHeader::BiWidth = BiWidth;
}

uint32_t infoHeader::getBiHeight() const {
    return BiHeight;
}

void infoHeader::setBiHeight(uint32_t BiHeight) {
    infoHeader::BiHeight = BiHeight;
}

uint16_t infoHeader::getBiBitCount() const {
    return BiBitCount;
}

void infoHeader::setBiBitCount(uint16_t BiBitCount) {
    infoHeader::BiBitCount = BiBitCount;
}

uint32_t infoHeader::getBiClrImportant() const {
    return BiClrImportant;
}

void infoHeader::setBiClrImportant(uint32_t BiClrImportant) {
    infoHeader::BiClrImportant = BiClrImportant;
}
