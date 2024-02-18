#include <iostream>
#include <vector>
#include <queue>
#include <string>

using namespace std;

// A Tree leaf
struct Huffleaf {
    char data;
    unsigned freq;
    Huffleaf *left, *right;

    Huffleaf(char data, unsigned freq) : data(data), freq(freq), left(nullptr), right(nullptr) {}
};

// For comparison of two heap leaves (needed in min heap)
struct Compare {
    bool operator()(Huffleaf* l, Huffleaf* r) {
        return (l->freq > r->freq);
    }
};

// Recursively prints the Huffman codes for each character from the Huffman tree.
// It traverses the tree in preorder and prints leaf nodes' codes.
void printCodes(Huffleaf* root, const string &str) {
    if (!root) return;

    // If this is a leaf Huffleaf (i.e., not the special internal Huffleaf), print its code
    if (root->data != '$') {
        cout << root->data << " : " << str << "\n";
    }

    // Preorder traversal: root -> left -> right
    printCodes(root->left, str + "0");
    printCodes(root->right, str + "1");
}

// Builds the Huffman tree given a set of characters and their frequencies.
// Then it prints the Huffman codes by calling printCodes.
void buildHuffmanTree(const string &data, const vector<unsigned> &freq, size_t size) {
    Huffleaf *left, *right, *top;

    // Create a min heap & inserts all characters of data[]
    priority_queue<Huffleaf*, vector<Huffleaf*>, Compare> minHeap;

    for (size_t i = 0; i < size; ++i) {
        minHeap.push(new Huffleaf(data[i], freq[i]));
    }

    // Iterate while size of heap doesn't become 1
    while (minHeap.size() != 1) {
        // Extract the two minimum freq items from min heap
        left = minHeap.top(); minHeap.pop();
        right = minHeap.top(); minHeap.pop();

        // Create a new internal node with children being the two extracted trees
       // The new node's frequency is the sum of its children's frequencies
        top = new Huffleaf('$', left->freq + right->freq);
        top->left = left;
        top->right = right;

        minHeap.push(top);
    }

    // The heap will now have only one element which is the root of Huffman Tree
    Huffleaf* root = minHeap.top();

    // Print Huffman codes using the Huffman tree built above
    printCodes(root, "");
}

// Driver program to test above functions
int main() {
    string data = "abcdef";
    vector<unsigned> freq = {5, 9, 12, 13, 16, 45};


    // Build the Huffman tree and print the codes
    buildHuffmanTree(data, freq, data.size());

    return 0;
}
