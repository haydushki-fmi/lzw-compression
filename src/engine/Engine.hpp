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
private:
    Engine();

public:
    static Engine &getEngine();

public:
    void run() const;

public:
    ~Engine();

private:
    void demoCompressFiles() const;
    void demoDecompressFiles() const;
    void demoDecompressFilesInCustomDirectory() const;

private:
    void clearFs();

private:
    archiving::FileSystem<fileSystemSetType> *fs;
};
} // namespace engine

#endif // ENGINE_HPP
