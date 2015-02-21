#include "tga_reader.h"

unsigned bitsToBytes(const unsigned& depth);
ReadResult readTgaHeader(std::ifstream& source, TgaHeader& header);

ReadResult readTgaFile(const std::string& filename, std::vector<unsigned char> imageData, unsigned& width, unsigned& height)
{
    std::ifstream file;
    file.open(filename, std::fstream::in | std::fstream::binary);
    if (!file.is_open())
    {
        return ReadResult::error;
    }

    // 1. read header
    TgaHeader tgaHeader;
    if (readTgaHeader(file, tgaHeader) != ReadResult::good)
    {
        return ReadResult::error;
    }

    // 2. read image id of size idLength
    file.ignore(tgaHeader.idLength); // FIXME: ignored for now

    // 3. read color map of size colorMapLength * bitsToBytes(colorMapDepth)
    file.ignore(tgaHeader.colorMapLength * bitsToBytes(tgaHeader.colorMapDepth)); // FIXME: ignored for now

    // 4. read image data of size width * height * bitsToBytes(bitsPerPixel)
    if (tgaHeader.dataType != TgaHeader::NO_IMG_DATA)
    {
        unsigned imageDataSize = tgaHeader.width * tgaHeader.height * bitsToBytes(tgaHeader.bitsPerPixel);
        char *imageDataBuffer = new char[imageDataSize];
        file.read(imageDataBuffer, imageDataSize);
        imageData.assign(imageDataBuffer, imageDataBuffer + imageDataSize);
        delete[] imageDataBuffer;
    }

    return ReadResult::good;
}

ReadResult readTgaHeader(std::ifstream& source, TgaHeader& header)
{
    char *headerBuffer = new char[TgaHeader::LENGTH];
    source.read(headerBuffer, TgaHeader::LENGTH);

    header.idLength = headerBuffer[0];
    header.colorMapType = headerBuffer[1];
    header.dataType = headerBuffer[2];
    header.colorMapOrigin = *reinterpret_cast<std::uint16_t*>(&headerBuffer[3]);
    header.colorMapLength = *reinterpret_cast<std::uint16_t*>(&headerBuffer[5]);
    header.colorMapDepth = headerBuffer[7];
    header.xOrigin = *reinterpret_cast<std::uint16_t*>(&headerBuffer[8]);
    header.yOrigin = *reinterpret_cast<std::uint16_t*>(&headerBuffer[10]);
    header.width = *reinterpret_cast<std::uint16_t*>(&headerBuffer[12]);
    header.height = *reinterpret_cast<std::uint16_t*>(&headerBuffer[14]);
    header.bitsPerPixel = headerBuffer[16];
    header.imageDescriptor = headerBuffer[17];

    delete[] headerBuffer;

    return ReadResult::good;
}

unsigned bitsToBytes(const unsigned& depth)
{
    return depth >> 3;
}