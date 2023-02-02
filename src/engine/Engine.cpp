#include "Engine.hpp"

namespace engine {

Engine::Engine()
{
    this->fs = new archiving::FileSystem<fileSystemSetType>();
}

Engine &Engine::getEngine()
{
    static Engine theEngine;
    return theEngine;
}

void Engine::run() const
{
    this->demoCompressFiles();
    //this->demoDecompressFiles();
    //this->demoDecompressFilesInCustomDirectory();
}

Engine::~Engine()
{
    this->clearFs();
}

void Engine::demoCompressFiles() const
{
    const std::string ARCHIVE_NAME = "testArchive.lzw";
    std::vector<std::string> paths = {"/some/path/outside/working/dir",
                                      "someFolderInside",
                                      "someFolder/inside2",
                                      "someFileInside.txt"};

    this->fs->scanPaths(paths);
    this->fs->archiveAllItems(ARCHIVE_NAME);
    this->fs->printAllInfo();
}

void Engine::demoDecompressFiles() const
{
    const std::string PATH_TO_ARCHIVE
        = "testArchive.lzw"; // Path to archive located in the working directory of the program

    this->fs->loadArchiveData(PATH_TO_ARCHIVE);
    this->fs->printAllInfo();
    this->fs->decompressAllItems(PATH_TO_ARCHIVE);
}

void Engine::demoDecompressFilesInCustomDirectory() const
{
    const std::string PATH_TO_ARCHIVE
        = "/absolute/path/to/archive/testArchive.lzw"; // Absolute path to archive
    std::filesystem::current_path("/some/custom/path/whichExists");

    this->fs->loadArchiveData(PATH_TO_ARCHIVE);
    this->fs->printAllInfo();
    this->fs->decompressAllItems(PATH_TO_ARCHIVE);
}

void Engine::clearFs()
{
    delete this->fs;
}

} // namespace engine
