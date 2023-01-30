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

ArchiveItem::ArchiveItem(std::istream &input)
{
    if (!input.good()) {
        throw std::runtime_error("Error in output stream!");
    }

    std::size_t pathSize;
    input.read((char *) &pathSize, sizeof(pathSize));

    char *path = new char[pathSize + 1];
    input.read((char *) path, pathSize);
    path[pathSize] = '\0';
    this->realativeArchivePath = std::string(path);
    delete[] path;

    this->isCompressed = true;
    input.read((char *) &this->type, sizeof(this->type));
    input.read((char *) &this->fileStartingPosition, sizeof(this->fileStartingPosition));
    input.read((char *) &this->compressedSize, sizeof(this->compressedSize));
    input.read((char *) &this->rawSize, sizeof(this->rawSize));
}

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

void ArchiveItem::writeToStream(std::ostream &out) const
{
    if (!out.good()) {
        throw std::runtime_error("Error in output stream!");
    }
    std::size_t pathSize = this->realativeArchivePath.size();
    out.write(reinterpret_cast<const char *>(&pathSize), sizeof(std::size_t));
    out.write(reinterpret_cast<const char *>(this->realativeArchivePath.c_str()), pathSize);
    out.write(reinterpret_cast<const char *>(&this->type), sizeof(this->type));
    out.write(reinterpret_cast<const char *>(&this->fileStartingPosition),
              sizeof(this->fileStartingPosition));
    out.write(reinterpret_cast<const char *>(&this->compressedSize), sizeof(this->compressedSize));
    out.write(reinterpret_cast<const char *>(&this->rawSize), sizeof(this->rawSize));
}

} // namespace archiving
