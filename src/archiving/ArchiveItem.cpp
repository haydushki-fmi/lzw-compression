#include "ArchiveItem.hpp"

namespace archiving {
ArchiveItem::ArchiveItem(const std::string &filePath,
                         std::filesystem::file_type type,
                         bool isCompressed,
                         unsigned int rawSize,
                         unsigned int compressedSize,
                         unsigned int fileStartingPosition)
    : filePath(filePath)
    , type(type)
    , isCompressed(isCompressed)
    , rawSize(rawSize)
    , compressedSize(compressedSize)
    , fileStartingPosition(fileStartingPosition)
{}

bool ArchiveItem::operator<(const ArchiveItem &other) const
{
    return this->filePath < other.filePath;
}

bool ArchiveItem::operator==(const ArchiveItem &other) const
{
    return this->filePath == other.filePath;
}

std::string ArchiveItem::getFilePath() const
{
    return this->filePath;
}

bool ArchiveItem::getIsCompressed() const
{
    return this->isCompressed;
}

void ArchiveItem::setIsCompressed(bool newIsCompressed)
{
    this->isCompressed = newIsCompressed;
}

unsigned int ArchiveItem::getRawSize() const
{
    return this->rawSize;
}

void ArchiveItem::setRawSize(unsigned int newRawSize)
{
    this->rawSize = newRawSize;
}

unsigned int ArchiveItem::getCompressedSize() const
{
    return this->compressedSize;
}

void ArchiveItem::setCompressedSize(unsigned int newCompressedSize)
{
    this->compressedSize = newCompressedSize;
}

unsigned int ArchiveItem::getFileStartingPosition() const
{
    return this->fileStartingPosition;
}

void ArchiveItem::setFileStartingPosition(unsigned int newFileStartingPosition)
{
    this->fileStartingPosition = newFileStartingPosition;
}

std::filesystem::file_type ArchiveItem::getType() const
{
    return this->type;
}

} // namespace archiving
