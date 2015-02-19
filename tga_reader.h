#ifndef __TGA_READER_H_
#define __TGA_READER_H_

#include "types.h"

#include <iostream>
#include <fstream>
#include <vector>

enum class ReadResult
{
    good = 0,
    error = 1
};

struct TgaHeader
{
    static const u32 LENGTH = 18;

    enum DataType
    {
        NO_IMG_DATA = 0, // No image data included.
        UNCOMPRESSED_CM = 1, // Uncompressed, color-mapped images.
        UNCOMPRESSED_RGB = 2, // Uncompressed, RGB images.
        UNCOMPRESSED_BW = 3, // Uncompressed, black and white images.
        RUNLENGTH_ENC_CM = 9, // Runlength encoded color-mapped images.
        RUNLENGTH_ENC_RGB = 10, // Runlength encoded RGB images.
        COMPRESSED_BW = 11, // Compressed, black and white images.
        COMPRESSED_CM_RUNLENGTH_ENC = 32, // Compressed color-mapped data, using Huffman, Delta, and runlength encoding.
        COMPRESSED_CM_RUNLENGTH_ENC_4_PASS = 33, // Compressed color-mapped data, using Huffman, Delta, and runlength encoding. 4-pass quadtree-type process.
    };

    u8 idLength;
    u8 colorMapType;
    u8 dataType;
    u16 colorMapOrigin;
    u16 colorMapLength;
    u8 colorMapDepth;
    u16 xOrigin;
    u16 yOrigin;
    u16 width;
    u16 height;
    u8 bitsPerPixel;
    u8 imageDescriptor;
};

ReadResult readTgaFile(const std::string& filename, std::vector<u8> imageData, u32& width, u32& height);

#endif __TGA_READER_H_