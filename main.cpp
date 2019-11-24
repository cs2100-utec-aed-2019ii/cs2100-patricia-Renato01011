#include <iostream>
#include "Trie.h"

int main() {

    Trie<std::string> t;
    t.insert("Renato");
    t.insert("Renzo");
    t.insert("Gabriel");
    t.insert("Lorenzo");
    t.insert("Lorenza");
    t.find_word("Renato");
    t.find_word("Renzo");
    t.find_word("Gabriel");
    std::cout << t.find_prefix("Re") << std::endl;
    t.print();
    t.delete_word("Lorenza");
    t.delete_word("Gabriel");
    std::cout << "After Delete" << std::endl;
    std::cout << "//////////////////////////////////////////////" << std::endl;
    t.print();
    std::cout << "Convert to Patricia" << std::endl;
    std::cout << "//////////////////////////////////////////////" << std::endl;
    t.convertToPatricia();
    t.print_patricia();

    return 0;
}
