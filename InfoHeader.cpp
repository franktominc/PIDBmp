//
// Created by ftominc on 25/07/16.
//

#include <cstdint>
#include "InfoHeader.h"

uint32_t InfoHeader::getHeader_sz() const {
    return header_sz;
}

void InfoHeader::setHeader_sz(uint32_t header_sz) {
    InfoHeader::header_sz = header_sz;
}

uint32_t InfoHeader::getWidth() const {
    return width;
}

void InfoHeader::setWidth(uint32_t width) {
    InfoHeader::width = width;
}

uint32_t InfoHeader::getHeight() const {
    return height;
}

void InfoHeader::setHeight(uint32_t height) {
    InfoHeader::height = height;
}

uint16_t InfoHeader::getNplanes() const {
    return nplanes;
}

void InfoHeader::setNplanes(uint16_t nplanes) {
    InfoHeader::nplanes = nplanes;
}

uint16_t InfoHeader::getBitspp() const {
    return bitspp;
}

void InfoHeader::setBitspp(uint16_t bitspp) {
    InfoHeader::bitspp = bitspp;
}

uint32_t InfoHeader::getCompress_type() const {
    return compress_type;
}

void InfoHeader::setCompress_type(uint32_t compress_type) {
    InfoHeader::compress_type = compress_type;
}

uint32_t InfoHeader::getBmp_bytesz() const {
    return bmp_bytesz;
}

void InfoHeader::setBmp_bytesz(uint32_t bmp_bytesz) {
    InfoHeader::bmp_bytesz = bmp_bytesz;
}

uint32_t InfoHeader::getHres() const {
    return hres;
}

void InfoHeader::setHres(uint32_t hres) {
    InfoHeader::hres = hres;
}

uint32_t InfoHeader::getVres() const {
    return vres;
}

void InfoHeader::setVres(uint32_t vres) {
    InfoHeader::vres = vres;
}

uint32_t InfoHeader::getNcolors() const {
    return ncolors;
}

void InfoHeader::setNcolors(uint32_t ncolors) {
    InfoHeader::ncolors = ncolors;
}

uint32_t InfoHeader::getNimpcolors() const {
    return nimpcolors;
}

void InfoHeader::setNimpcolors(uint32_t nimpcolors) {
    InfoHeader::nimpcolors = nimpcolors;
}

uint32_t InfoHeader::getBsize() const {
    return bsize;
}

void InfoHeader::setBsize(uint32_t bsize) {
    InfoHeader::bsize = bsize;
}
