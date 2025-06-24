#include <iostream>
#include <fstream>
#include <string>

void compressFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream in(inputPath, std::ios::in);
    std::ofstream out(outputPath, std::ios::out);
    if (!in || !out) {
        std::cout << "Error opening files.\n";
        return;
    }
    char prev, curr;
    int count = 1;
    in.get(prev);
    while (in.get(curr)) {
        if (curr == prev && count < 255) {
            count++;
        } else {
            out << prev << count;
            prev = curr;
            count = 1;
        }
    }
    if (in.gcount() > 0) {
        out << prev << count;
    }
    std::cout << "Compression complete.\n";
}

void decompressFile(const std::string& inputPath, const std::string& outputPath) {
    std::ifstream in(inputPath, std::ios::in);
    std::ofstream out(outputPath, std::ios::out);
    if (!in || !out) {
        std::cout << "Error opening files.\n";
        return;
    }
    char ch;
    unsigned char count;
    while (in.get(ch)) {
        in >> count;
        for (int i = 0; i < count; ++i) {
            out << ch;
        }
        in.get(); // consume the newline or next char
    }
    std::cout << "Decompression complete.\n";
}

int main() {
    int choice;
    std::string inFile, outFile;
    std::cout << "File Compression Tool\n";
    std::cout << "1. Compress\n2. Decompress\nChoose option: ";
    std::cin >> choice;
    std::cout << "Enter input file path: ";
    std::cin >> inFile;
    std::cout << "Enter output file path: ";
    std::cin >> outFile;

    if (choice == 1) {
        compressFile(inFile, outFile);
    } else if (choice == 2) {
        decompressFile(inFile, outFile);
    } else {
        std::cout << "Invalid choice.\n";
    }
    return 0;
}