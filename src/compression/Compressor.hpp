#ifndef COMPRESSOR_HPP
#define COMPRESSOR_HPP

#include <ostream>
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
     */
    virtual void compress(std::istream &in, std::ostream &out) = 0;
};
} // namespace compression

#endif // COMPRESSOR_HPP
