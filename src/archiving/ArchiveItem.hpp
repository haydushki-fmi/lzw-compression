#ifndef ARCHIVEITEM_HPP
#define ARCHIVEITEM_HPP

#include <filesystem>
#include <string>

namespace archiving {

// TODO: Add docs
// TODO: Testing?
class ArchiveItem
{
public:
    ArchiveItem(const std::string &filePath,
                std::filesystem::file_type type,
                bool isCompressed,
                unsigned int rawSize,
                unsigned int compressedSize,
                unsigned int fileStartingPosition);

public:
    bool operator<(const ArchiveItem &other) const;
    bool operator==(const ArchiveItem &other) const;

    std::string getFilePath() const;
    bool getIsCompressed() const;
    void setIsCompressed(bool newIsCompressed);
    unsigned int getRawSize() const;
    void setRawSize(unsigned int newRawSize);
    unsigned int getCompressedSize() const;
    void setCompressedSize(unsigned int newCompressedSize);
    unsigned int getFileStartingPosition() const;
    void setFileStartingPosition(unsigned int newFileStartingPosition);

    std::filesystem::file_type getType() const;

private:
    std::string filePath;
    std::filesystem::file_type type;
    bool isCompressed;
    unsigned int rawSize;
    unsigned int compressedSize;
    unsigned int fileStartingPosition;
};

} // namespace archiving

#endif // ARCHIVEITEM_HPP
