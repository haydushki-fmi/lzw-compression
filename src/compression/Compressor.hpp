#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include <ios>
namespace compression {

/**
 * @brief Interface for compression algorithm implementations.
 */
class Compressor
{
public:
    /**
     * @brief Compresses data read from input stream and writes it to the output stream.
     * @param in Input data to compress.
     * @param out Output for compressed data.
     * @throws std::runtime_error if given input and output streams aren't in initial good state.
     */
    virtual void compress(std::istream &in, std::ostream &out) = 0;

    /**
     * @brief Decompresses data read from input stream and writes it to the output stream.
     * @param in Input data.
     * @param bytesToRead Amount of bytes to read from input stream.
     * @param out Output for decoded data.
     * @throws std::runtime_error if given input and output streams aren't in initial good state.
     */
    virtual void decompress(std::istream &in, unsigned int bytesToRead, std::ostream &out) = 0;
};
} // namespace compression

#endif // COMPRESSOR_HPP
