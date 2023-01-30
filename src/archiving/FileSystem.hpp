#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "archiving/ArchiveItem.hpp"
#include "common_data_structures/SetFactory.hpp"
#include "compression/implementations/LZWCompressor.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

namespace fs = std::filesystem;

namespace archiving {

const std::string DEFAULT_SET_TYPE = "StdSetWrapper";

// TODO: Testing?
template<class SetType>
class FileSystem
{
public:
    FileSystem()
        : set(SetType())
    {}

    FileSystem(const FileSystem<SetType> &other) = delete;
    FileSystem<SetType> &operator=(const FileSystem<SetType> &other) = delete;

public:
    /**
     * @brief Iterates over the given paths, checks if they exist and based on their type adds them to the filesystem.
     *
     * If a given path is a directory it will be recursively scanned. Paths outside the program root path will be stripped down.
     * For example, if working dir is ~/lzw-project and a given path is /tmp/somefile.txt, the result will be only somefile.txt.
     *
     * NOTICE: Currently globs are not supported! Symlinks will not be followed!
     *
     * @param filePaths Paths to scan
     */
    void scanPaths(const std::vector<std::string> &filePaths)
    {
        for (const auto &pathString : filePaths) {
            // TODO: If pathString contains a glob char do extra parsing.
            // TODO: If it starts with . or ..

            fs::path currentPath = fs::absolute(pathString);
            fs::file_type currentType = fs::status(currentPath).type();

            switch (currentType) {
            case fs::file_type::regular: {
                this->addFile(currentPath);
                break;
            }
            case fs::file_type::directory: {
                this->scanDirectory(currentPath);
                break;
            }
            default:
                continue;
                break;
            }
        }
    }

    /**
     * @brief Creates an archive file with a given filename.
     *
     * Info in file is:
     * - Number of files;
     * - File names and other metadata;
     * - Compressed file data.
     *
     * @param archiveName Name of the file to create.
     */
    void archiveAllItems(const std::string &archiveName) const
    {
        if (this->set.size() == 0) {
            return;
        }

        std::ofstream output;
        output.open(archiveName);
        if (!output.is_open()) {
            throw std::invalid_argument("Invalid archive name!");
        }

        // Write file count and file list
        std::size_t setSize = this->set.size();
        output.write(reinterpret_cast<const char *>(&setSize), sizeof(std ::size_t));
        auto setPosition = output.tellp();

        for (const auto &item : this->set) {
            item->writeToStream(output);
        }

        // Write compressed file data
        compression_implementations::LZWCompressor compressor;
        auto currentItemPosition = output.tellp();
        for (auto item : this->set) {
            item->setFileStartingPosition(currentItemPosition);

            std::ifstream fileDataInput;
            fileDataInput.open(item->getFilePath());
            compressor.compress(fileDataInput, output);
            fileDataInput.close();

            item->setIsCompressed(true);
            item->setCompressedSize(output.tellp() - currentItemPosition);
            currentItemPosition = output.tellp();
        }

        // Rewrite file list with updated file sizes and starting position
        output.seekp(setPosition);
        for (const auto &item : this->set) {
            item->writeToStream(output);
        }

        output.close();
    }

    /**
     * @brief Reads file metadata from archive file.
     * @param path Path to archive
     */
    void loadArchiveData(const std::string &path)
    {
        std::ifstream input;
        input.open(path);

        if (!input.is_open()) {
            throw std::invalid_argument("Invalid archive name!");
        }

        std::size_t itemCount;
        input.read((char *) &itemCount, sizeof(itemCount));
        for (std::size_t i = 0; i < itemCount; ++i) {
            ArchiveItem item(input);
            this->set.insert(item);
        }

        input.close();
    }

    /**
     * @brief Decompresses a signle file from a given archive.
     * @param path File path/name to decompress
     * @param archivePath Path to archive to read from
     */
    void decompressItem(const std::string &path, const std::string &archivePath) const
    {
        if (this->set.size() == 0) {
            throw std::runtime_error("Archive is empty!");
        }

        const ArchiveItem *item = this->set.search(
            ArchiveItem("", path, fs::file_type::regular, false, 0, 0, 0));
        if (!item) {
            throw std::invalid_argument("File doesn't exist in archive!");
        }

        // If it's just a directory simply create it
        if (item->getType() == fs::file_type::directory) {
            fs::create_directories(item->getFileRelativePath());
            return;
        }

        std::ifstream input;
        input.open(archivePath);

        if (!input.is_open()) {
            throw std::invalid_argument("Invalid archive name!");
        }

        input.seekg(item->getFileStartingPosition());

        // If the file is inside some directories create them first before writing the file.
        if (item->getFileRelativePath().find('/') != std::string::npos) {
            fs::path fp(item->getFileRelativePath());
            fs::create_directories(fp.parent_path());
        }

        std::ofstream outputFile;
        outputFile.open(item->getFileRelativePath());

        if (!outputFile.is_open()) {
            throw std::runtime_error("Error decompressing file!");
        }

        compression_implementations::LZWCompressor compressor;
        compressor.decompress(input, item->getCompressedSize(), outputFile);

        outputFile.close();
        input.close();
    }

    /**
     * @brief Decompresses all files in an archive.
     * @param archivePath Path to the archive to read from
     */
    void decompressAllItems(const std::string &archivePath) const
    {
        if (this->set.size() == 0) {
            throw std::runtime_error("Archive is empty!");
        }

        for (const auto item : this->set) {
            this->decompressItem(item->getFileRelativePath(), archivePath);
        }
    }

    /**
     * @brief Prints items' paths. For deubgging purposes.
     */
    void printAllItems() const
    {
        std::cout << "Files list:" << std::endl;
        for (const auto item : this->set) {
            std::cout << item->getFileRelativePath() << "\t->\t" << item->getFilePath()
                      << std::endl;
        }
    }

private:
    /**
     * @brief Recursively iterates over a directory adding it's contents to the set.
     * @param dirPath Path to the directory to iterate over
     */
    void scanDirectory(const fs::path &dirPath)
    {
        for (auto const &dir_entry : fs::recursive_directory_iterator(dirPath)) {
            const fs::path currentPath = dir_entry.path();
            const fs::file_type type = fs::status(currentPath).type();
            switch (type) {
            case fs::file_type::directory:
            case fs::file_type::regular: {
                this->set.insert(ArchiveItem(currentPath.string(),
                                             trimParentPath(currentPath, dirPath),
                                             type,
                                             false,
                                             0,
                                             0,
                                             0));
                break;
            }
            default:
                continue;
                break;
            }
        }
    }

    /**
     * @brief Removes part of the path before a given subpath.
     * @param absolutePath Path to remove from
     * @param currentPath Part after which the contents should be preserved
     * @return resulting path as a std::string
     */
    std::string trimParentPath(const fs::path &absolutePath, const fs::path &currentPath)
    {
        std::string trimmedPath = currentPath.string().substr(
            currentPath.parent_path().string().length() + 1);
        return absolutePath.string().substr(absolutePath.string().find(trimmedPath));
    }

    /**
     * @brief Adds a single regular file to the set of files.
     * @param filePath Path to file to add
     */
    void addFile(const fs::path &filePath)
    {
        this->set.insert(ArchiveItem(filePath.string(),
                                     trimParentPath(filePath, filePath),
                                     fs::file_type::regular,
                                     false,
                                     0,
                                     0,
                                     0));
    }

private:
    SetType set;
};

} // namespace archiving

#endif // FILESYSTEM_HPP
