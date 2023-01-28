#ifndef FILESYSTEM_HPP
#define FILESYSTEM_HPP

#include "archiving/ArchiveItem.hpp"
#include "common_data_structures/SetFactory.hpp"
#include <string>

namespace archiving {

const std::string DEFAULT_SET_TYPE = "StdSetWrapper";

// TODO: Testing?
template<class SetType>
class FileSystem
{
public:
    FileSystem()
    {
        // TODO: Use SetFactory after it's refactor
        this->set = new SetType;
    }

public:
    void scanDirectory(const std::string &dirPath) const {}
    void archiveAllItems(const std::string &archiveName) const
    {
        for (auto item : *(this->set)) {
            //do stuff
        }
    }

public:
    ~FileSystem() { delete this->set; }

private:
    SetType *set;
};

} // namespace archiving

#endif // FILESYSTEM_HPP
