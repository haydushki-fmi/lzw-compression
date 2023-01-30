#include "archiving/ArchiveItem.hpp"
#include "catch2/catch_all.hpp"
#include <fstream>
#include <sstream>

TEST_CASE("ArchiveItem::writeToStream() throws when stream is not in good state",
          "[archiving][archiveItem]")
{
    archiving::ArchiveItem
        item("path1", "path2", std::filesystem::file_type::regular, false, 0, 0, 0);
    std::ostringstream outputStream;

    SECTION("bad state for outputStream")
    {
        outputStream.setstate(std::ios_base::badbit);

        CHECK_THROWS_AS(item.writeToStream(outputStream), std::runtime_error);
    }

    SECTION("fail state for outputStream")
    {
        outputStream.setstate(std::ios_base::failbit);

        CHECK_THROWS_AS(item.writeToStream(outputStream), std::runtime_error);
    }
}

TEST_CASE("ArchiveItem::writeToStream() correctly writes info to stream", "[archiving][archiveItem]")
{
    archiving::ArchiveItem
        item("path1", "path2", std::filesystem::file_type::regular, false, 1, 2, 10);
    std::ostringstream outputStream;

    item.writeToStream(outputStream);

    std::istringstream resultInterpr(outputStream.str());

    std::size_t pathSize;
    resultInterpr.read((char *) &pathSize, sizeof(pathSize));
    CHECK(pathSize == 5);

    char pathName[5];
    resultInterpr.read((char *) &pathName, pathSize);
    CHECK(std::string(pathName) == "path2");

    std::filesystem::file_type type;
    resultInterpr.read((char *) &type, sizeof(type));
    CHECK(type == std::filesystem::file_type::regular);

    uint64_t fileStartingPosition;
    resultInterpr.read((char *) &fileStartingPosition, sizeof(fileStartingPosition));
    CHECK(fileStartingPosition == 10);

    uint64_t compressedSize;
    resultInterpr.read((char *) &compressedSize, sizeof(compressedSize));
    CHECK(compressedSize == 2);

    uint64_t rawSize;
    resultInterpr.read((char *) &rawSize, sizeof(rawSize));
    CHECK(rawSize == 1);
}

TEST_CASE("ArchiveItem can be created from data from input stream", "[archiving][archiveItem]")
{
    archiving::ArchiveItem
        item("path1", "path2", std::filesystem::file_type::regular, false, 1, 2, 10);
    std::ostringstream outputStream;

    item.writeToStream(outputStream);

    std::istringstream resultInterpr(outputStream.str());

    archiving::ArchiveItem resultItem(resultInterpr);

    CHECK(resultItem.getFilePath() == "");
    CHECK(resultItem.getFileRelativePath() == item.getFileRelativePath());
    CHECK(resultItem.getType() == item.getType());
    CHECK(resultItem.getIsCompressed());
    CHECK(resultItem.getCompressedSize() == item.getCompressedSize());
    CHECK(resultItem.getRawSize() == item.getRawSize());
    CHECK(resultItem.getFileStartingPosition() == item.getFileStartingPosition());
}
