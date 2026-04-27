#include "../include/dawg.h"
#include <cassert>
#include <cctype>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>

DawgNode::DawgNode(Tile t) {
        parents = std::vector<DawgNode *>();
        children = std::vector<DawgNode *>();
        this->t = t;
}

Dawg::Dawg(std::string file_path) : start(Tile::START), end(Tile::END) {
        std::fstream file = std::fstream(file_path.c_str(), std::ios_base::in);
        // read in file

        std::string line;

        while (std::getline(file, line)) {
                std::string word = "";
                std::istringstream stream(line);
                if(!(stream >> word)){
                        std::cerr << line << '\n';
                        continue;
                }
                add_word(word);
        }

        for(DawgNode *d : this->end.parents){
                std::cout << char(d->t + 64);
        }
}

void Dawg::add_word(std::string word){
        DawgNode *current = &this->start;
        for(char c : word){
                DawgNode *next = NULL;
                for (DawgNode* node : current->children){
                        if(node->t != Tile(c - 64)){
                                continue;
                        }
                        next = node;
                        break;
                }
                if(next != NULL){
                        current = next;
                }
                else{
                        //add new node
                        next = new DawgNode(Tile(c - 64));
                        next->parents.push_back(current);
                        current->children.push_back(next);
                        current = next;
                }
        }

        current->children.push_back(&this->end);
        end.parents.push_back(current);
}


