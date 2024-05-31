#pragma once
#include <algorithm>
#include <iterator>
#include <iostream>

#include <vector>

namespace oho {

template <typename T>
std::ostream& operator<<(std::ostream& out, const std::vector<T>& vec) {
    if (vec.size() > 0) {
        std::copy(vec.begin(), vec.end() - 1,
            std::ostream_iterator<T>(out, ", ")
        );
        out << *(vec.end() - 1);
    }
    return out;
}

template <typename B>
concept is_binary_tree = requires (B tree) {
    tree.left;
    tree.right;
};

template <is_binary_tree BT>
void outputBinaryTree(BT* node, void(*output_func)(BT*), const std::string& previos = "", const std::string& connection = "", int depth = 0) {
    if (node == nullptr) return;
    std::cout << (depth < 2 ? "" : previos.substr(0, previos.size() - 2)) << connection;
    output_func(node);
    std::cout << std::endl;
    outputBinaryTree(node->left,  output_func, previos + "\xB3 ", "\xC3\xC4", depth + 1);
    outputBinaryTree(node->right, output_func, previos + "  "   , "\xC0\xC4", depth + 1);
}

}