//
// Created by ftominc on 25/07/16.
//

#include "FileHeader.h"

const unsigned char *FileHeader::getMagic() const {
    return magic;
}

uint32_t FileHeader::getFilesz() const {
    return filesz;
}

void FileHeader::setFilesz(uint32_t filesz) {
    FileHeader::filesz = filesz;
}

uint16_t FileHeader::getCreator1() const {
    return creator1;
}

void FileHeader::setCreator1(uint16_t creator1) {
    FileHeader::creator1 = creator1;
}

uint16_t FileHeader::getCreator2() const {
    return creator2;
}

void FileHeader::setCreator2(uint16_t creator2) {
    FileHeader::creator2 = creator2;
}

uint32_t FileHeader::getBmp_offset() const {
    return bmp_offset;
}

void FileHeader::setBmp_offset(uint32_t bmp_offset) {
    FileHeader::bmp_offset = bmp_offset;
}
