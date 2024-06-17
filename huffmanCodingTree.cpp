#include <iostream>
using namespace std;

class HuffmanBaseNode
{
public:
    virtual ~HuffmanBaseNode() = default;
    virtual bool isLeaf() const = 0;
    virtual int getFrequency() const = 0;
    virtual char getElement() = 0;
    virtual HuffmanBaseNode *getLeft() = 0;
    virtual HuffmanBaseNode *getRight() = 0;
};

class HuffmanLeafNode : public virtual HuffmanBaseNode
{
    char element;
    int frequency;

public:
    HuffmanLeafNode() : element(0), frequency(0) {}
    HuffmanLeafNode(char element, int frequency)
        : element(element), frequency(frequency)
    {
    }
    char getElement() override
    {
        return element;
    }
    HuffmanBaseNode *getLeft() override
    {
        return NULL;
    }
    HuffmanBaseNode *getRight() override
    {
        return nullptr;
    }
    int getFrequency() const override
    {
        return frequency;
    }
    bool isLeaf() const override
    {
        return true;
    }
};

class HuffmanInternalNode : public virtual HuffmanBaseNode
{
    int frequency;
    HuffmanBaseNode *left;
    HuffmanBaseNode *right;

public:
    HuffmanInternalNode() : left(nullptr), right(nullptr), frequency(0) {}
    HuffmanInternalNode(HuffmanBaseNode *l, HuffmanBaseNode *r, int frequency)
        : left(l), right(r), frequency(frequency)
    {
    }
    int getFrequency() const override
    {
        return frequency;
    }
    HuffmanBaseNode *getLeft() override
    {
        return left;
    }
    HuffmanBaseNode *getRight() override
    {
        return right;
    }
    char getElement() override
    {
        return '\0';
    }
    bool isLeaf() const override
    {
        return false;
    }
};

class HuffmanCodingTree : public HuffmanBaseNode
{
    HuffmanBaseNode *root;

public:
    HuffmanCodingTree(char element, int frequency)
    {
        // std::cout << "1st " << element << frequency << "\n";
        this->root = new HuffmanLeafNode(element, frequency);
    }

    HuffmanCodingTree(HuffmanBaseNode *l, HuffmanBaseNode *r, int frequency)
    {
        this->root = new HuffmanInternalNode(l, r, frequency);
    }
    ~HuffmanCodingTree()
    {
        delete root;
    }
    HuffmanBaseNode *getRoot() const
    {
        return root;
    }
    // @TODO: keep an eye here
    int getFrequency() const override
    {
        return root->getFrequency();
    }
    bool isLeaf() const override
    {
        return root->isLeaf();
    }
    char getElement() override
    {
        return root->getElement();
    }
    HuffmanBaseNode *getLeft() override
    {
        return root->getLeft();
    }
    HuffmanBaseNode *getRight() override
    {
        return root->getRight();
    }
    
};