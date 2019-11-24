#pragma once
#include <map>

template <typename type>
class Node {

    template <typename T>
    friend class Trie;

	bool is_word = false;
	std::map <type, Node*> children;
	std::string word;

public:
	~Node() {
        if (!(children.empty())) {
            for (auto& [letter, node] : children) {
                delete node;
            }
	    }
	}
};
