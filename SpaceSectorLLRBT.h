#ifndef SPACESECTORLLRBT_H
#define SPACESECTORLLRBT_H

#include "Sector.h"
#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <algorithm>

class SpaceSectorLLRBT {
public:
    Sector* root;
    std::vector<Sector*> sectors;
    SpaceSectorLLRBT();
    ~SpaceSectorLLRBT();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);  
    void balanceTree(Sector*& node);
    void clearTree(Sector* node);
    void insert(Sector*& current, Sector* newsector);
    Sector* rotateLeft(Sector*& node);
    Sector* rotateRight(Sector*& node);       
    int compareCoordinates(const Sector* current, const Sector* newsector);
    bool redornot(Sector* node);
    void flipcolors(Sector* node);
    void printTreeStructure();
    void printTreeStructure(Sector* node, int indent);
    void postordertraversal(Sector* node);
    void preordertraversal(Sector* node);
    void inordertraversal(Sector* node);
    Sector* findSector(Sector* node, const std::string& sector_code) const;
    Sector* pathhelper(const std::string sector_code);
};

#endif // SPACESECTORLLRBT_H