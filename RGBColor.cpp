//
// Created by ftominc on 27/07/16.
//

#include "RGBColor.h"

RGBColor::RGBColor(uint8_t red, uint8_t green, uint8_t blue) : red(red), green(green), blue(blue) {}

uint8_t RGBColor::getRed() const {
    return red;
}

void RGBColor::setRed(uint8_t red) {
    RGBColor::red = red;
}

uint8_t RGBColor::getBlue() const {
    return blue;
}

void RGBColor::setBlue(uint8_t blue) {
    RGBColor::blue = blue;
}

uint8_t RGBColor::getGreen() const {
    return green;
}

void RGBColor::setGreen(uint8_t green) {
    RGBColor::green = green;
}