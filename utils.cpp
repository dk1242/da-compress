#include <functional>
#include <queue>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <string>
#include "huffmanCodingTree.cpp"

using namespace std;

struct CompareNodes
{
    bool operator()(const HuffmanBaseNode *lhs, const HuffmanBaseNode *rhs) const
    {
        return lhs->getFrequency() > rhs->getFrequency();
    }
};

HuffmanBaseNode *buildTree(vector<int> freq)
{
    priority_queue<HuffmanBaseNode *, vector<HuffmanBaseNode *>, CompareNodes> huffmanHeap;

    for (int i = 32; i < 128; i++)
    {
        if (freq[i])
        {
            // cout << "first" << char(i) << freq[i] << "\n";
            HuffmanCodingTree *temp = new HuffmanCodingTree(i, freq[i]);
            huffmanHeap.push(temp);
        }
    }
    HuffmanBaseNode *temp1, *temp2, *temp3;
    while (huffmanHeap.size() > 1)
    {
        temp1 = huffmanHeap.top();
        huffmanHeap.pop();
        temp2 = huffmanHeap.top();
        huffmanHeap.pop();
        temp3 = new HuffmanInternalNode(temp1, temp2, temp1->getFrequency() + temp2->getFrequency());
        huffmanHeap.push(temp3);
    }

    return temp3;
}

void traverseTree(HuffmanBaseNode *root, std::map<char, pair<int, string>> &lookup, string curr)
{
    if (root->isLeaf())
    {
        char element = root->getElement();
        int freq = root->getFrequency();
        lookup[element] = {freq, curr};
        return;
    }
    else
    {
        traverseTree(root->getLeft(), lookup, curr + "0");
        traverseTree(root->getRight(), lookup, curr + "1");
    }
}
void createLookupTable(HuffmanBaseNode *root, std::map<char, pair<int, string>> &lookup)
{
    string curr = "";
    traverseTree(root, lookup, curr);
}

void writeBit(std::ofstream &outFile, int bit, char &bitBuffer, int &bitCount)
{
    bitBuffer = (bitBuffer << 1) | (bit & 1);
    bitCount++;

    if (bitCount == 8)
    {
        outFile.write(&bitBuffer, 1);
        bitBuffer = 0;
        bitCount = 0;
    }
}
void flushBits(std::ofstream &outFile, char &bitBuffer, int &bitCount)
{
    if (bitCount > 0)
    {
        bitBuffer <<= (8 - bitCount);
        outFile.write(&bitBuffer, 1);
        bitBuffer = 0;
        bitCount = 0;
    }
}
void createCompressedFile(std::map<char, pair<int, string>> &lookup, std::ifstream &file)
{
    std::ofstream outFile("test_compressed", std::ios::out | std::ios::binary);
    if (outFile.is_open())
    {
        char bitBuffer = 0;
        int bitCount = 0;
        char ch;
        while (file.get(ch))
        {
            string compressedBitsRepresentation = lookup[ch].second;
            // cout << ch << " " << compressedBitsRepresentation << " " << compressedBitsRepresentation.length() << "\n";
            for (int i = 0; i < compressedBitsRepresentation.length(); i++)
            {
                writeBit(outFile, compressedBitsRepresentation[i] - '0', bitBuffer, bitCount);
            }
        }
        flushBits(outFile, bitBuffer, bitCount);
        outFile.close();
    }
    else
    {
        std::cerr << "Error in generating compressed file" << std::endl;
    }
}