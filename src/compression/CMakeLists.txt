add_library(compression STATIC)

target_sources(
        compression
        PRIVATE
        Compressor.hpp
        CompressorFactory.hpp
        CompressorFactory.cpp
        implementations/LZWCompressor.cpp
        implementations/LZWCompressor.hpp
)
