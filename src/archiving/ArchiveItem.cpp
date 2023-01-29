#include "ArchiveItem.hpp"

namespace archiving {
ArchiveItem::ArchiveItem(const std::string &pathOnDisk,
                         const std::string &realativeArchivePath,
                         std::filesystem::file_type type,
                         bool isCompressed,
                         uint64_t rawSize,
                         uint64_t compressedSize,
                         uint64_t fileStartingPosition)
    : pathOnDisk(pathOnDisk)
    , realativeArchivePath(realativeArchivePath)
    , type(type)
    , isCompressed(isCompressed)
    , rawSize(rawSize)
    , compressedSize(compressedSize)
    , fileStartingPosition(fileStartingPosition)
{}

bool ArchiveItem::operator<(const ArchiveItem &other) const
{
    return this->realativeArchivePath < other.realativeArchivePath;
}

bool ArchiveItem::operator==(const ArchiveItem &other) const
{
    return this->realativeArchivePath == other.realativeArchivePath;
}

std::string ArchiveItem::getFilePath() const
{
    return this->pathOnDisk;
}

bool ArchiveItem::getIsCompressed() const
{
    return this->isCompressed;
}

void ArchiveItem::setIsCompressed(bool newIsCompressed)
{
    this->isCompressed = newIsCompressed;
}

uint64_t ArchiveItem::getRawSize() const
{
    return this->rawSize;
}

void ArchiveItem::setRawSize(uint64_t newRawSize)
{
    this->rawSize = newRawSize;
}

uint64_t ArchiveItem::getCompressedSize() const
{
    return this->compressedSize;
}

void ArchiveItem::setCompressedSize(uint64_t newCompressedSize)
{
    this->compressedSize = newCompressedSize;
}

uint64_t ArchiveItem::getFileStartingPosition() const
{
    return this->fileStartingPosition;
}

void ArchiveItem::setFileStartingPosition(uint64_t newFileStartingPosition)
{
    this->fileStartingPosition = newFileStartingPosition;
}

std::filesystem::file_type ArchiveItem::getType() const
{
    return this->type;
}

std::string ArchiveItem::getFileRelativePath() const
{
    return this->realativeArchivePath;
}

} // namespace archiving
