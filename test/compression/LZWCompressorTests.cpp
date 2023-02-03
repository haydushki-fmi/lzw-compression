#include "catch2/catch_all.hpp"
#include "compression/implementations/LZWCompressor.hpp"
#include <sstream>

// TODO: Better way of testing streams?

const unsigned int DICTIONARY_READABLE_CHAR_OFFSET = 128;
using codeType = compression_implementations::LZWCompressor::CodeType;

TEST_CASE("LZWCompressor::compress() throws when stream is not in good state",
          "[compression][lzw-compression]")
{
    std::istringstream inputStream;
    std::ostringstream outputStream;
    compression_implementations::LZWCompressor comp;

    SECTION("fail state for inputStream")
    {
        inputStream.setstate(std::ios_base::failbit);

        CHECK_THROWS_AS(comp.compress(inputStream, outputStream), std::runtime_error);
    }

    SECTION("fail state for outputStream")
    {
        outputStream.setstate(std::ios_base::failbit);

        CHECK_THROWS_AS(comp.compress(inputStream, outputStream), std::runtime_error);
    }

    SECTION("bad state for inputStream")
    {
        inputStream.setstate(std::ios_base::badbit);

        CHECK_THROWS_AS(comp.compress(inputStream, outputStream), std::runtime_error);
    }

    SECTION("bad state for outputStream")
    {
        outputStream.setstate(std::ios_base::badbit);

        CHECK_THROWS_AS(comp.compress(inputStream, outputStream), std::runtime_error);
    }
}

TEST_CASE("LZWCompressor::compress() correctly compresses a single char",
          "[compression][lzw-compression]")
{
    std::istringstream inputData("c");
    std::ostringstream outputStream(std::ios_base::ate);
    compression_implementations::LZWCompressor comp;

    comp.compress(inputData, outputStream);

    std::istringstream resultInterpr(outputStream.str());
    codeType res;
    resultInterpr.read((char *) &res, sizeof(res));
    CHECK(res == (codeType) 'c' + DICTIONARY_READABLE_CHAR_OFFSET);
}

TEST_CASE("LZWCompressor::compress() correctly compresses a simple string",
          "[compression][lzw-compression]")
{
    std::istringstream inputData("abababab");
    std::ostringstream outputStream(std::ios_base::ate);
    compression_implementations::LZWCompressor comp;

    // Expected dictionary entries (old an new):
    // dictionary["a"] = 225 = 'a' + DICTIONARY_READABLE_CHAR_OFFSET;
    // dictionary["b"] = 226 = 'b' + DICTIONARY_READABLE_CHAR_OFFSET;
    // Newly added:
    // dictionary["ab"] = 256
    // dictionary["ba"] = 257
    // dictionary["aba"] = 258
    // dictionary["abab"] = 259
    unsigned expectedCodesCount = 5;
    codeType expectedCodes[] = {225, 226, 256, 258, 226};

    comp.compress(inputData, outputStream);

    std::istringstream resultInterpr(outputStream.str());
    for (unsigned i = 0; i < expectedCodesCount; ++i) {
        codeType res;
        resultInterpr.read((char *) &res, sizeof(res));

        CHECK(res == expectedCodes[i]);
    }
}

TEST_CASE("LZWCompressor::decompress() throws when given stream is not in good state",
          "[compression][lzw-compression]")
{
    std::istringstream inputStream;
    std::ostringstream outputStream;
    compression_implementations::LZWCompressor comp;

    SECTION("fail state for inputStream")
    {
        inputStream.setstate(std::ios_base::failbit);

        CHECK_THROWS_AS(comp.decompress(inputStream, 0, outputStream), std::runtime_error);
    }

    SECTION("fail state for outputStream")
    {
        outputStream.setstate(std::ios_base::failbit);

        CHECK_THROWS_AS(comp.decompress(inputStream, 0, outputStream), std::runtime_error);
    }

    SECTION("bad state for inputStream")
    {
        inputStream.setstate(std::ios_base::badbit);

        CHECK_THROWS_AS(comp.decompress(inputStream, 0, outputStream), std::runtime_error);
    }

    SECTION("bad state for outputStream")
    {
        outputStream.setstate(std::ios_base::badbit);

        CHECK_THROWS_AS(comp.decompress(inputStream, 0, outputStream), std::runtime_error);
    }
}

TEST_CASE("LZWCompressor::decompress() can decompreess a LZW compressed string",
          "[compression][lzw-compression]")
{
    std::string originalString = "abababab";
    std::istringstream compressionIn(originalString);
    std::ostringstream compressionOut(std::ios_base::ate);
    compression_implementations::LZWCompressor comp;
    comp.compress(compressionIn, compressionOut);

    std::istringstream inputToDecompress(compressionOut.str());
    std::ostringstream outputDecompressed(std::ios_base::ate);
    comp.decompress(inputToDecompress, 10, outputDecompressed);

    CHECK(outputDecompressed.str() == originalString);
}
