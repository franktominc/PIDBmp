//
// Created by ftominc on 25/07/16.
//

#include "FileHeader.h"

uint16_t FileHeader::getBfType() const {
    return BfType;
}

void FileHeader::setBfType(uint16_t BfType) {
    FileHeader::BfType = BfType;
}

uint32_t FileHeader::getBfSize() const {
    return BfSize;
}

void FileHeader::setBfSize(uint32_t BfSize) {
    FileHeader::BfSize = BfSize;
}

uint32_t FileHeader::getBfOffSetBits() const {
    return BfOffSetBits;
}

void FileHeader::setBfOffSetBits(uint32_t BfOffSetBits) {
    FileHeader::BfOffSetBits = BfOffSetBits;
}
