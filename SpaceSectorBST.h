#ifndef SPACESECTORBST_H
#define SPACESECTORBST_H

#include <iostream>
#include <fstream>  
#include <sstream>
#include <vector>
#include <algorithm>

#include "Sector.h"

class SpaceSectorBST {

public:
    Sector* root;
    std::vector<Sector*> sectors;
    SpaceSectorBST();
    ~SpaceSectorBST();
    void readSectorsFromFile(const std::string& filename);
    void insertSectorByCoordinates(int x, int y, int z);
    void deleteSector(const std::string& sector_code);
    void displaySectorsInOrder();
    void displaySectorsPreOrder();
    void displaySectorsPostOrder();
    void postordertraversal(Sector* node);
    void preordertraversal(Sector* node);
    void inordertraversal(Sector* node);
    void deleteTree(Sector* node);
    std::vector<Sector*> getStellarPath(const std::string& sector_code);
    void printStellarPath(const std::vector<Sector*>& path);
    void printTreeStructure();
    void printTreeStructure(Sector* node, int indent);
   Sector* pathhelper(const std::string& sector_code);
    void insertSectorByCoordinatesHelper(Sector* current, Sector* newsector);
    int compareCoordinates(const Sector* sector1, const Sector* sector2) const;
};

#endif // SPACESECTORBST_H
