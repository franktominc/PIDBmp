//
// Created by ftominc on 26/07/16.
//

#ifndef PID_COLORPALLETE_H
#define PID_COLORPALLETE_H


#include <cstdint>
#include <vector>

class ColorPallete {
public:
    ColorPallete(int n);

    std::vector<uint8_t> colors;
};


#endif //PID_COLORPALLETE_H
