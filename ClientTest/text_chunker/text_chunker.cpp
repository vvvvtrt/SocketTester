#include "text_chunker.hpp"


TextChunker::TextChunker(const std::string& filename, size_t n) {
    std::ifstream infile(filename);
    if (!infile.is_open()) {
        std::cerr << "Error opening file: " << filename << std::endl;
        return;
    }

    fullText.assign((std::istreambuf_iterator<char>(infile)),
        std::istreambuf_iterator<char>());
    infile.close();

    splitTextIntoChunks(n);
}

const std::string& TextChunker::operator[](size_t index) const {
    if (index < chunks.size()) {
        return chunks[index];
    }
    else {
        throw std::out_of_range("Index out of range");
    }
}

size_t TextChunker::getChunkCount() const noexcept {
    return chunks.size();
}

void TextChunker::splitTextIntoChunks(size_t n) {
    for (size_t i = 0; i < fullText.size(); i += n) {
        chunks.push_back(fullText.substr(i, n));
    }
}