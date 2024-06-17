#include <iostream>
#include <fstream>
#include <sstream>
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
        if (ch >= 0 && ch < 128)
        {
            frequency[ch]++;
        }
    }
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        std::cerr << "Usage: adcd [--option] <filename>" << "\n";
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
    std::ifstream file(filename);
    if (!file)
    {
        std::cerr << "Error: could not open file\n";
        return 1;
    }
    bool toCompress = true;
    if (toCompress)
    {
        vector<int> frequency(256, 0);
        calculateFrequency(frequency, file);
        file.clear();
        file.seekg(0);
        for (int i = 0; i < 128; i++)
        {
            if (frequency[i])
                cout << i << " " << char(i) << " " << frequency[i] << "\n";
        }
        cout << "Building tree------------------------------->\n";
        HuffmanBaseNode *root = buildTree(frequency);
        std::map<char, pair<int, string>> lookup;
        createLookupTable(root, lookup);
        createCompressedFile(lookup, file);
        // for (auto &it : lookup)
        // {
        //     cout << it.first << " " << it.second.first << " " << it.second.second << " " << it.second.second.size() << "\n";
        // }
    }
    file.close();
    return 0;
}