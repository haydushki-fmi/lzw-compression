#ifndef ENGINE_HPP
#define ENGINE_HPP

#include "archiving/FileSystem.hpp"

namespace engine {

using fileSystemSetType
    = common_data_structures_implementations::StdSetWrapper<archiving::ArchiveItem>;

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
    void clearFs();

private:
    archiving::FileSystem<fileSystemSetType> *fs;
};
} // namespace engine

#endif // ENGINE_HPP
