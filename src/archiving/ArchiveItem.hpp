#ifndef ARCHIVEITEM_HPP
#define ARCHIVEITEM_HPP

#include <filesystem>
#include <string>

namespace archiving {

// TODO: Testing?
/**
 * @brief Represents an file/directory in the archive.
 */
class ArchiveItem
{
public:
    /**
     * @brief Creates a new Archive item.
     * @param pathOnDisk
     * @param realativeArchivePath
     * @param type
     * @param isCompressed
     * @param rawSize
     * @param compressedSize
     * @param fileStartingPosition
     */
    ArchiveItem(const std::string &pathOnDisk,
                const std::string &realativeArchivePath,
                std::filesystem::file_type type,
                bool isCompressed,
                uint64_t rawSize,
                uint64_t compressedSize,
                uint64_t fileStartingPosition);

public:
    /**
     * @brief Compares two Archive items by their realativeArchivePath.
     * @param other Archive item to compare against.
     * @return true if this is smaller than other.
     */
    bool operator<(const ArchiveItem &other) const;

    /**
     * @brief Compares two Archive items by their realativeArchivePath.
     * @param other Archive item to compare against.
     * @return true if this is equal to other.
     */
    bool operator==(const ArchiveItem &other) const;

    /**
     * @brief Returns file path on the system.
     */
    std::string getFilePath() const;

    /**
     * @brief Returns file path relative to the archive root.
     */
    std::string getFileRelativePath() const;

    /**
     * @brief Returns if file is compressed.
     */
    bool getIsCompressed() const;

    /**
     * @brief Sets file compression state.
     * @param newIsCompressed New state
     */
    void setIsCompressed(bool newIsCompressed);

    /**
     * @brief Gets uncompressed file size.
     */
    uint64_t getRawSize() const;

    /**
     * @brief Sets file uncompressed size.
     * @param newRawSize New uncompressed size
     */
    void setRawSize(uint64_t newRawSize);

    /**
     * @brief Gets compressed file size.
     */
    uint64_t getCompressedSize() const;

    /**
     * @brief Sets compressed file size.
     * @param newCompressedSize New file compressed size
     */
    void setCompressedSize(uint64_t newCompressedSize);

    /**
     * @brief Gets the byte at which the file date is stored on the archive file.
     */
    uint64_t getFileStartingPosition() const;

    /**
     * @brief Sets the byte at which the file date is stored on the archive file.
     * @param newFileStartingPosition New position
     */
    void setFileStartingPosition(uint64_t newFileStartingPosition);

    /**
     * @brief Gets the file type - regular or directory.
     */
    std::filesystem::file_type getType() const;

    /**
     * @brief Writes the item's data to the given output stream.
     * @param out Stream to write to
     */
    void writeToStream(std::ostream &out) const;

private:
    /**
     * @brief Stores location of the file on the system.
     */
    std::string pathOnDisk;

    /**
     * @brief Stores file path relative to the archive root.
     */
    std::string realativeArchivePath;

    /**
     * @brief Type of the file - regular or directory. Other filetypes will be ignored.
     */
    std::filesystem::file_type type;

    /**
     * @brief True if the file has been compressed
     */
    bool isCompressed;

    /**
     * @brief Uncompressed file size in bytes.
     */
    uint64_t rawSize;

    /**
     * @brief Compressed file size in bytes.
     */
    uint64_t compressedSize;

    /**
     * @brief Byte at which file data is stored int the archive file.
     */
    uint64_t fileStartingPosition;
};

} // namespace archiving

#endif // ARCHIVEITEM_HPP
