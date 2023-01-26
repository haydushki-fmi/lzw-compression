add_library(compression STATIC)

target_sources(
        compression
        PRIVATE
        Compressor.hpp
        Decompressor.hpp
        CompressorFactory.hpp
        CompressorFactory.cpp
        DecompressorFactory.hpp
        DecompressorFactory.cpp
        implementations/LZWCompressor.cpp
        implementations/LZWCompressor.hpp
)
