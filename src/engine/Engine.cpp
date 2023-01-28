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
    this->fs->archiveAllItems("sample");
}

Engine::~Engine()
{
    this->clearFs();
}

void Engine::clearFs()
{
    delete this->fs;
}

} // namespace engine
