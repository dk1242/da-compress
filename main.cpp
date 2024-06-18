#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include "utils.cpp"
// #include "huffmanCodingTree.cpp"

using namespace std;

void calculateFrequency(vector<int> &frequency, std::ifstream &file)
{
    char ch;
    while (file.get(ch))
    {
        if (ch >= 0 && ch < 256)
        {
            frequency[ch]++;
        }
    }
}
int ifCompressed(string filename)
{
    std::ifstream file(filename, std::ios::binary | ios::in);
    if (!file)
    {
        // std::cerr << "Error: could not open file a\n";
        return 2;
    }
    else
    {
        char ch;
        string curr = "";
        while (file.get(ch) && curr.length() < 15)
        {
            curr += ch;
            size_t found = curr.find("decode_start,");
            if (found != string::npos)
            {
                file.close();
                return true;
            }
        }
        return false;
    }
    return 2;
}
int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: dacompress [--option] <filename>" << "\n";
        std::cerr << "options:" << "\n";
        std::cerr << "--compress: to compress an uncompressed file" << "\n";
        std::cerr << "--decompress: to decompress a compressed file" << "\n";
        return 1;
    }
    string option = "";
    if (argc == 3)
    {
        option = argv[argc - 2];
    }

    string filename = argv[argc - 1];

    if (filename.empty())
    {
        std::cerr << "Error: No input file specified\n";
        return 1;
    }

    int isCompressed = ifCompressed(filename);
    if (isCompressed == 2)
    {
        std::cerr << "Error: Could not open file. Provide correct file path.\n";
        return 1;
    }
    if (option == "--compress" && isCompressed)
    {
        std::cerr << "Upload an uncompressed file while using --compress\n";
        return 1;
    }
    if (option == "--decompress" && !isCompressed)
    {
        std::cerr << "Upload a compressed file while using --decompress\n";
        return 1;
    }
    if (!isCompressed)
    {
        std::ifstream file(filename);
        if (!file)
        {
            std::cerr << "Error: could not open file\n";
            return 1;
        }
        vector<int> frequency(256, 0);
        calculateFrequency(frequency, file);
        file.clear();
        file.seekg(0);
        // for (int i = 0; i < 128; i++)
        // {
        //     if (frequency[i])
        //         cout << i << " " << char(i) << " " << frequency[i] << "\n";
        // }
        // cout << "Building tree------------------------------->\n";
        HuffmanBaseNode *root = buildTree(frequency);
        std::map<char, pair<int, string>> lookup;
        createLookupTable(root, lookup);
        createCompressedFile(lookup, file, filename);
        file.close();
    }
    else
    {
        std::ifstream file(filename, std::ios::binary | ios::in);
        if (!file)
        {
            std::cerr << "Error: could not open file\n";
            return 1;
        }
        std::map<string, char> lookup;
        getLookupTable(file, lookup);
        createDecompressedFile(filename, file, lookup);
        file.close();
    }
    return 0;
}