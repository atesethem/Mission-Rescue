#include "SpaceSectorBST.h"
#include <filesystem>
#include <iomanip>
using namespace std;

SpaceSectorBST::SpaceSectorBST() : root(nullptr) {}

SpaceSectorBST::~SpaceSectorBST() {
    if (root != nullptr) {
        deleteTree(root);
        root = nullptr;
    }
}

void SpaceSectorBST::deleteTree(Sector* node) {
    if (node != nullptr) {
        deleteTree(node->left);
        deleteTree(node->right);
        delete node;
    }
}

void SpaceSectorBST::printTreeStructure() {
    printTreeStructure(root, 0);
}


void SpaceSectorBST::printTreeStructure(Sector* node, int indent) {
    if (node != nullptr) {
        printTreeStructure(node->right, indent + 4);
        std::cout << std::setw(indent) << " ";
        std::cout << node->sector_code << std::endl;
        printTreeStructure(node->left, indent + 4);
    }
}
void SpaceSectorBST::readSectorsFromFile(const std::string& filename) {
    // TODO: read the sectors from the input file and insert them into the BST sector map
    // according to the given comparison critera based on the sector coordinates.
    std::ifstream file(filename);
   
    if (file.is_open()) {
        
        int number = 0;
        std::string line;
        while (std::getline(file, line)) {
          
            if (number == 0) {
                number++;
                continue;
            }
           
            std::vector<string> coordinates; // deðerleri string okuma hatasý verebilir
            
            std::istringstream stream(line);
            string coordinate;
            
            while (std::getline(stream, coordinate, ',')) {
                coordinates.push_back(coordinate);
            }
            int x = std::stoi(coordinates[0]);
            int y = std::stoi(coordinates[1]);
            int z = std::stoi(coordinates[2]);
            
            insertSectorByCoordinates(x,y,z);
            number++;
        }
    }
}

void SpaceSectorBST::insertSectorByCoordinates(int x, int y, int z) {

    Sector* newsector = new Sector(x, y, z);
    sectors.push_back(newsector);
    if (root == nullptr) {
        root = newsector;
    }
    else {
        insertSectorByCoordinatesHelper(root, newsector);
    }

    
}
void SpaceSectorBST::insertSectorByCoordinatesHelper(Sector* current, Sector* newsector) {
    if (compareCoordinates(current, newsector) > 0) {
        if (current->left == nullptr) {
            current->left = newsector;
            newsector->parent = current;
        }
        else {
            insertSectorByCoordinatesHelper(current->left, newsector);
        }
    }
    else if (compareCoordinates(current, newsector) < 0) {
        if (current->right == nullptr) {
            current->right = newsector;
            newsector->parent = current;
        }
        else {
            insertSectorByCoordinatesHelper(current->right, newsector);
        }
    }


}
int SpaceSectorBST::compareCoordinates(const Sector* sector1, const Sector* sector2) const {
    if (sector1->x != sector2->x) {
        return sector1->x - sector2->x;
    }
    else if (sector1->y != sector2->y) {
        return sector1->y - sector2->y;
    }
    else {
        return sector1->z - sector2->z;
    }
}


void SpaceSectorBST::deleteSector(const std::string& sector_code) {
    // TODO: Delete the sector given by its sector_code from the BST.
}


void SpaceSectorBST::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:";
    std::cout << "\n";
    inordertraversal(root);
    std::cout << "\n";
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:"; //BURADA DA KONTROL ETMK LAZIM NULLPTR MI
    std::cout << "\n";
    preordertraversal(root);
    std::cout << "\n";
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorBST::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:";
    std::cout << "\n";
    postordertraversal(root);
    std::cout << "\n";
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.
    
}
void SpaceSectorBST::postordertraversal(Sector* node) {
    // TODO: Traverse the space sector BST map in post-order traversal and print 
 // the sectors to STDOUT in the given format.
    if (!node) return;
    postordertraversal(node->left);
    postordertraversal(node->right);
    cout << node->sector_code << endl;


}
void SpaceSectorBST::preordertraversal(Sector* node) {
    if (!node) return;
    cout << node->sector_code << endl;
    postordertraversal(node->left);
    postordertraversal(node->right);
    
}
void SpaceSectorBST::inordertraversal(Sector* node) {
    if (!node) return;
    
    postordertraversal(node->left);
    cout << node->sector_code << endl;
    postordertraversal(node->right);
}
std::vector<Sector*> SpaceSectorBST::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* finalsector = pathhelper(sector_code); 
    std::cout << "etehm";
    if (finalsector != nullptr) { 
        std::cout << "etehm";
        while (finalsector != nullptr) {
            path.push_back(finalsector);
            finalsector = finalsector->parent;
        }
        std::reverse(path.begin(), path.end()); //tersine veriyo
    }

    return path;

    // TODO: Find the path from the Earth to the destination sector given by its
    // sector_code, and return a vector of pointers to the Sector nodes that are on
    // the path. Make sure that there are no duplicate Sector nodes in the path!

}
Sector* SpaceSectorBST::pathhelper(const std::string& sector_code) {
    for (Sector* thesector : sectors) {
        if (thesector->sector_code == sector_code) {
            return thesector;
        }       
    }
    return nullptr;
}
void SpaceSectorBST::printStellarPath(const std::vector<Sector*>& path) {
    // TODO: Print the stellar path obtained from the getStellarPath() function 
    // to STDOUT in the given format.
    if (path.empty()) {
        std::cout << "A path to Dr. Elara could not be found.";
    }
    else {
        std::cout << "The stellar path to Dr. Elara: ";
        for (int i = 0; i < path.size(); i++) {
            std::cout << path[i]->sector_code + "->";
        }
    }
}
