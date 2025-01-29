#ifndef FILE_RW
#define FILE_RW

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <stdexcept> 

class TextChunker {
public:
    TextChunker(const std::string& filename, size_t n);
    ~TextChunker() = default;

    [[nodiscard]] const std::string& operator[](size_t index) const;

    size_t getChunkCount() const noexcept;

private:
    std::string fullText;
    std::vector<std::string> chunks;

    void splitTextIntoChunks(size_t n);
};


#endif FILE_RW