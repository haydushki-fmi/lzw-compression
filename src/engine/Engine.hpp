#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "archiving/FileSystem.hpp"
#include "common_data_structures/implementations/RBTree.hpp"
#include "common_data_structures/implementations/StdSetWrapper.hpp"

namespace engine {

using fileSystemSetType = RBTree<archiving::ArchiveItem>;
//    = common_data_structures_implementations::StdSetWrapper<archiving::ArchiveItem>;

// TODO: Testing?
class Engine
{
public:
    Engine();

public:
    void run();

private:
    void demoCompressFiles();
    void demoDecompressFiles();
    void demoDecompressFilesInCustomDirectory();

private:
    archiving::FileSystem<fileSystemSetType> fs;
};
} // namespace engine

#endif // ENGINE_HPP
