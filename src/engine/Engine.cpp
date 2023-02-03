#include "Engine.hpp"

namespace engine {

Engine::Engine()
    : fs(archiving::FileSystem<fileSystemSetType>())
{}

void Engine::run()
{
    this->demoCompressFiles();
    //this->demoDecompressFiles();
    //this->demoDecompressFilesInCustomDirectory();
}

void Engine::demoCompressFiles()
{
    const std::string ARCHIVE_NAME = "testArchive.lzw";
    std::vector<std::string> paths = {"/some/path/outside/working/dir",
                                      "someFolderInside",
                                      "someFolder/inside2",
                                      "someFileInside.txt"};

    this->fs.scanPaths(paths);
    this->fs.archiveAllItems(ARCHIVE_NAME);
    this->fs.printAllInfo();
}

void Engine::demoDecompressFiles()
{
    const std::string PATH_TO_ARCHIVE
        = "testArchive.lzw"; // Path to archive located in the working directory of the program

    this->fs.loadArchiveData(PATH_TO_ARCHIVE);
    this->fs.printAllInfo();
    this->fs.decompressAllItems(PATH_TO_ARCHIVE);
}

void Engine::demoDecompressFilesInCustomDirectory()
{
    const std::string PATH_TO_ARCHIVE
        = "/absolute/path/to/archive/testArchive.lzw"; // Absolute path to archive
    std::filesystem::current_path("/some/custom/path/whichExists");

    this->fs.loadArchiveData(PATH_TO_ARCHIVE);
    this->fs.printAllInfo();
    this->fs.decompressAllItems(PATH_TO_ARCHIVE);
}

} // namespace engine
