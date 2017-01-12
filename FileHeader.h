//
// Created by ftominc on 25/07/16.
//

#ifndef PID_FILEHEADER_H
#define PID_FILEHEADER_H


#include <cstdint>
#include <ostream>


class __attribute__((__packed__)) FileHeader{

private:
    unsigned char magic[2];
    uint32_t filesz;
    uint16_t creator1;
    uint16_t creator2;
    uint32_t bmp_offset;

public:
    const unsigned char *getMagic() const;

    uint32_t getFilesz() const;

    void setFilesz(uint32_t filesz);

    uint16_t getCreator1() const;

    void setCreator1(uint16_t creator1);

    uint16_t getCreator2() const;

    void setCreator2(uint16_t creator2);

    uint32_t getBmp_offset() const;

    void setBmp_offset(uint32_t bmp_offset);


    friend std::ostream& operator<< (std::ostream& stream, const FileHeader& fileHeader);
};


#endif //PID_FILEHEADER_H
