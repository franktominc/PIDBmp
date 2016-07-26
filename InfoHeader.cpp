//
// Created by ftominc on 25/07/16.
//

#include <cstdint>
#include "InfoHeader.h"

uint32_t infoHeader::getHeader_sz() const {
    return header_sz;
}

void infoHeader::setHeader_sz(uint32_t header_sz) {
    infoHeader::header_sz = header_sz;
}

uint32_t infoHeader::getWidth() const {
    return width;
}

void infoHeader::setWidth(uint32_t width) {
    infoHeader::width = width;
}

uint32_t infoHeader::getHeight() const {
    return height;
}

void infoHeader::setHeight(uint32_t height) {
    infoHeader::height = height;
}

uint16_t infoHeader::getNplanes() const {
    return nplanes;
}

void infoHeader::setNplanes(uint16_t nplanes) {
    infoHeader::nplanes = nplanes;
}

uint16_t infoHeader::getBitspp() const {
    return bitspp;
}

void infoHeader::setBitspp(uint16_t bitspp) {
    infoHeader::bitspp = bitspp;
}

uint32_t infoHeader::getCompress_type() const {
    return compress_type;
}

void infoHeader::setCompress_type(uint32_t compress_type) {
    infoHeader::compress_type = compress_type;
}

uint32_t infoHeader::getBmp_bytesz() const {
    return bmp_bytesz;
}

void infoHeader::setBmp_bytesz(uint32_t bmp_bytesz) {
    infoHeader::bmp_bytesz = bmp_bytesz;
}

uint32_t infoHeader::getHres() const {
    return hres;
}

void infoHeader::setHres(uint32_t hres) {
    infoHeader::hres = hres;
}

uint32_t infoHeader::getVres() const {
    return vres;
}

void infoHeader::setVres(uint32_t vres) {
    infoHeader::vres = vres;
}

uint32_t infoHeader::getNcolors() const {
    return ncolors;
}

void infoHeader::setNcolors(uint32_t ncolors) {
    infoHeader::ncolors = ncolors;
}

uint32_t infoHeader::getNimpcolors() const {
    return nimpcolors;
}

void infoHeader::setNimpcolors(uint32_t nimpcolors) {
    infoHeader::nimpcolors = nimpcolors;
}
