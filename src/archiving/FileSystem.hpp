#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "archiving/ArchiveItem.hpp"
#include "common_data_structures/SetFactory.hpp"
#include <filesystem>
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

    void archiveAllItems(const std::string &archiveName) const
    {
        for (const auto &item : this->set) {
            //do stuff
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

    void addFile(const fs::path &filePath)
    {
        // TODO: implement
    }

private:
    SetType set;
};

} // namespace archiving

#endif // FILESYSTEM_HPP
