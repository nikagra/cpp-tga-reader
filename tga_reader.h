#ifndef __TGA_READER_H_
#define __TGA_READER_H_

#include <iostream>
#include <fstream>
#include <vector>
#include <cstdint>

enum class ReadResult
{
    good = 0,
    error = 1
};

struct TgaHeader
{
    static const unsigned LENGTH = 18;

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

    std::uint8_t idLength;
    std::uint8_t colorMapType;
    std::uint8_t dataType;
    std::uint16_t colorMapOrigin;
    std::uint16_t colorMapLength;
    std::uint8_t colorMapDepth;
    std::uint16_t xOrigin;
    std::uint16_t yOrigin;
    std::uint16_t width;
    std::uint16_t height;
    std::uint8_t bitsPerPixel;
    std::uint8_t imageDescriptor;
};

ReadResult readTgaFile(const std::string& filename, std::vector<unsigned char> imageData, unsigned& width, unsigned& height);

#endif __TGA_READER_H_