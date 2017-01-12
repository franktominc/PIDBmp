//
// Created by ftominc on 27/07/16.
//

#ifndef PID_RGBCOLOR_H
#define PID_RGBCOLOR_H


#include <cstdint>

class RGBColor {

public:
    RGBColor(uint8_t red, uint8_t green, uint8_t blue);

    uint8_t getGreen() const;

    void setGreen(uint8_t green);

    uint8_t getRed() const;

    void setRed(uint8_t red);

    uint8_t getBlue() const;

    void setBlue(uint8_t blue);

private:
    uint8_t red;
    uint8_t green;
    uint8_t blue;
};


#endif //PID_RGBCOLOR_H
