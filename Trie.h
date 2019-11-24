#pragma once
#include "Node.h"

template <typename type>
class Trie {
	Node<type>* root;

public:
	Trie() {
	    root = new Node<type>();
	}
	~Trie() {
        //delete root;
    }

	void insert(const std::string& word) {
		Node<type>* temp = root;
		for (auto it : word) {
			bool found = false;
			for (auto& [letter, node] : temp->children) {
			    std::string a(letter);
			    std::string b(1, it);
			    if (a == b) {
			        temp = node;
			        found = true;
			        break;
			    }
			}

			if (!found) {
                auto *newNode = new Node<type>();
                temp->children.insert(std::pair<type, Node<type>*>{std::string(1, it), newNode});
                temp = newNode;
			}
		}
		temp->is_word = true;
	}

	void find_word(const std::string& word) {
		Node<type>* temp = root;
		for (auto it : word) {
            for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
                std::string a(itr->first);
                std::string b(1, it);
                if (a == b) { temp = itr->second; break; }
            }
		}
		if (temp->is_word) { std::cout << word << " Word Found" << std::endl; }
	}

	bool find_prefix(const std::string& word) {
	    Node<type>* temp = root;
	    for (auto it : word) {
	        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
	            std::string a(itr->first);
	            std::string b(1, it);
	            if (a == b) { temp = itr->second; break; }
	            return false;
	        }
	    }
	    return true;
	}

	void delete_word(const std::string& word, Node<type>* temp, int& index) {

        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            std::string a(itr->first);
            std::string b(1, word[index]);
            if (a == b) {
                index++;
                if (index == word.length()) {
                    if (!(itr->second->children.empty())) {
                        temp->is_word = false;
                    }
                    else {
                        temp->children.erase(itr);
                        return;
                    }
                }
                delete_word(word, itr->second, index);
                if (itr->second->children.empty()) {
                    temp->children.erase(itr);
                    return;
                }
                else {
                  temp->is_word = false;
                }
            }
        }

	}

	void delete_word(const std::string& word) {
        Node<type>* temp = root;
        int index = 0;
        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            std::string a(itr->first);
            std::string b(1, word[index]);
            if (a == b) {
                index++;
                delete_word(word, itr->second, index);
                if (itr->second->children.empty()) {
                    temp->children.erase(itr);
                    return;
                }
                else {
                    temp->is_word = false;
                }
            }
        }
	}

	void convertToRadix(Node<type>* temp, std::string& word, bool& CC) {
	    if (temp->is_word) {
            return;
        }
        else if (temp->children.size() != 1) {
            std::string word_1;
            convertToPatricia(temp, word_1);
            CC = true;
            return;
        }
        else {
            if (!(temp->children.empty())) {
                temp = (temp->children.begin())->second;
                convertToRadix(temp, word, CC);
            }
        }
        if (!(temp->children.empty()) && !CC) {
            word = temp->children.begin()->first + word;
            temp->children.erase(temp->children.begin());
            return;
        }
        else {
            if (temp->children.empty() || temp->children.size() != 1) { return; }
            word = temp->children.begin()->first + word;
            return;
        }
	}

	void convertToPatricia(Node<type>* temp, std::string& word) {
        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            std::string _word;
            bool CC = false;
            convertToRadix(itr->second, _word, CC);
            auto* newNode = new Node<type>();
            _word = itr->second->children.begin()->first + _word;
            itr->second->children.erase(itr->second->children.begin()->first);
            itr->second->children.insert(std::pair<type, Node<type>*>{_word, newNode});
            _word = itr->first + _word;
            newNode->word = _word;
        }
	}

	Node<type>* FindDouble(Node<type>* _temp) {
	    while (_temp->children.size() != 1) {
	        _temp = _temp->children.begin()->second;
	    }
        return _temp->children.begin()->second;
	}

	Trie<type> convertToPatricia() {
        Node<type>* temp = root;
        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            std::string word;
            bool CC = false;
            convertToRadix(itr->second, word, CC);
            if (CC) {
                Node<type>* _temp = FindDouble(itr->second);
                word = itr->second->children.begin()->first;
                word = itr->first + word;
                temp->children.erase(itr->first);
                temp->children.insert(std::pair<type, Node<type>*>{word, _temp});
                return *this;
            }
            else {
                auto* newNode = new Node<type>();
                word = itr->second->children.begin()->first + word;
                itr->second->children.erase(itr->second->children.begin()->first);
                itr->second->children.insert(std::pair<type, Node<type>*>{word, newNode});
                word = itr->first + word;
                newNode->word = word;
            }
        }
        return *this;
	}

    void print(Node<type>* temp, int& i) {
        int iter = 0;
        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            if (iter > 0) {
                for (int j = 0; j < i; j++) {
                    std::cout << "\" ";
                }
            }
            std::cout << itr->first << ' ';
            i++;
            print(itr->second, i);
            if (itr->second->is_word) {
                std::cout << std::endl;
            }
            i--;
            iter++;
        }
    }

    void print() {
        Node<type>* temp = root;
        int i = 0;
        for (auto& [letter, node] : temp->children) {
            std::cout << letter << ' ';
            i++;
            print(node, i);
            std::cout << std::endl;
            i = 0;
        }
    }

    void print_patricia(Node<type>* temp, int& i) {
        int iter = 0;
        for (auto itr = temp->children.begin(); itr != temp->children.end(); itr++) {
            if (iter > 0) {
                for (int j = 0; j < i-1; j++) {
                    std::cout << " ";
                }
            }
            std::cout << itr->first << ' ';
            i = i + itr->first.length() + 1;
            print_patricia(itr->second, i);
            if (itr->second->word != "") {
                std::cout << itr->second->word << std::endl;
            }
            i--;
            iter++;
        }
    }

    void print_patricia() {
        Node<type>* temp = root;
        int i = 0;
        for (auto& [letter, node] : temp->children) {
            std::cout << letter << ' ';
            i++;
            print_patricia(node, i);
            std::cout << std::endl;
            i = 0;
        }
    }
};