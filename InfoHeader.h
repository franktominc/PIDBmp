//
// Created by ftominc on 25/07/16.
//

#ifndef PID_INFOHEADER1_H
#define PID_INFOHEADER1_H


class __attribute__((__packed__)) InfoHeader{

private:
    uint32_t bsize;
    uint32_t width;
    uint32_t height;
    uint16_t nplanes;
    uint16_t bitspp;
    uint32_t compress_type;
    uint32_t bmp_bytesz;
    uint32_t hres;
    uint32_t vres;
    uint32_t ncolors;
    uint32_t nimpcolors;

public:

    uint32_t getBsize() const;

    void setBsize(uint32_t bsize);

    uint32_t getWidth() const;

    void setWidth(uint32_t width);

    uint32_t getHeight() const;

    void setHeight(uint32_t height);

    uint16_t getNplanes() const;

    void setNplanes(uint16_t nplanes);

    uint16_t getBitspp() const;

    void setBitspp(uint16_t bitspp);

    uint32_t getCompress_type() const;

    void setCompress_type(uint32_t compress_type);

    uint32_t getBmp_bytesz() const;

    void setBmp_bytesz(uint32_t bmp_bytesz);

    uint32_t getHres() const;

    void setHres(uint32_t hres);

    uint32_t getVres() const;

    void setVres(uint32_t vres);

    uint32_t getNcolors() const;

    void setNcolors(uint32_t ncolors);

    uint32_t getNimpcolors() const;

    void setNimpcolors(uint32_t nimpcolors);

    friend std::ostream& operator<< (std::ostream& stream, const InfoHeader& infoHeader);

};



#endif //PID_INFOHEADER1_H
