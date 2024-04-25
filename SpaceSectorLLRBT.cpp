#include "SpaceSectorLLRBT.h"
#include <iomanip>

using namespace std;

SpaceSectorLLRBT::SpaceSectorLLRBT() : root(nullptr) {}

void SpaceSectorLLRBT::printTreeStructure() {
    printTreeStructure(root, 0);
}


void SpaceSectorLLRBT::printTreeStructure(Sector* node, int indent) {
    if (node != nullptr) {
        printTreeStructure(node->right, indent + 4);
        std::cout << std::setw(indent) << " ";
        std::cout << node->sector_code << std::endl;
        printTreeStructure(node->left, indent + 4);
    }
}

void SpaceSectorLLRBT::readSectorsFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        int number = 0;
      
        std::string line;
        while (std::getline(file, line)) {
            if (number == 0) {
                number++;
                continue;
            }
           
            std::vector<std::string> coordinates;
            std::istringstream stream(line);
            std::string coordinate;
            while (std::getline(stream, coordinate, ',')) {
                coordinates.push_back(coordinate);
            }
            int x = std::stoi(coordinates[0]);
            int y = std::stoi(coordinates[1]);
            int z = std::stoi(coordinates[2]);

            insertSectorByCoordinates(x, y, z);
            number++;
        }
    }
}

SpaceSectorLLRBT::~SpaceSectorLLRBT() {
    // Özyineleme ile aðacý temizle
    clearTree(root);
}

void SpaceSectorLLRBT::clearTree(Sector* node) {
    if (node == nullptr) {
        return;
    }
    clearTree(node->left);
    clearTree(node->right);
    delete node;
}

void SpaceSectorLLRBT::insertSectorByCoordinates(int x, int y, int z) {
    Sector* thesector = new Sector(x, y, z);
    sectors.push_back(thesector);
    if (root == nullptr) {
        root = thesector;
    }
    else {
        insert(root, thesector);
    }
}

void SpaceSectorLLRBT::insert(Sector*& current, Sector* newsector) {
    
    if (compareCoordinates(current, newsector) > 0) {
        if (current->right == nullptr) {
            current->right = newsector;
            newsector->parent = current;
        }
        else {
           insert(current->right, newsector);
        }
       
    }
    else if (compareCoordinates(current, newsector) < 0) {
        if (current->left == nullptr) {
            current->left = newsector;
            newsector->parent = current;
        }
        else {
            insert(current->left, newsector);
        }
    }
   
    balanceTree(current);
   
}

void SpaceSectorLLRBT::balanceTree(Sector*& node) { // 3 durum olcak
    if (redornot(node->right) && !redornot(node->left)) {  // saða eklenen red olduðu duurm
        node = rotateLeft(node);
    }
    if (redornot(node->left) && redornot(node->left->left)) { // iki left alta alta olduðu durum
        node = rotateRight(node);
    }
    if (redornot(node->left) && redornot(node->right)) {
        flipcolors(node);
    }
}

bool SpaceSectorLLRBT::redornot(Sector* node) {
    if (node == nullptr) {
        return false;
    }
    if (node->color == RED) {
        return true;
    }
    else {
        return false;
    }
}

Sector* SpaceSectorLLRBT::rotateLeft(Sector*& node) {
    Sector* temp = node->right;
    node->right = temp->left;
    if (temp->left != nullptr) {
        temp->left->parent = node;
    }
    temp->left = node;
    temp->parent = node->parent;
    node->parent = temp;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

Sector* SpaceSectorLLRBT::rotateRight(Sector*& node) {
    Sector* temp = node->left;
    node->left = temp->right;
    if (temp->right != nullptr) {
        temp->right->parent = node;
    }
    temp->right = node;
    temp->parent = node->parent;
    node->parent = temp;
    temp->color = node->color;
    node->color = RED;
    return temp;
}

void SpaceSectorLLRBT::flipcolors(Sector* node) {
    node->color = RED;
    node->left->color = BLACK;
    node->right->color = BLACK;
}

int SpaceSectorLLRBT::compareCoordinates(const Sector* current, const Sector* newsector) {
 
    if (current->x != newsector->x) {
       // std::cout << "ethem0";
        return newsector->x - current->x;
    }
    else if (current->y != newsector->y) {
        
        return newsector->y - current->y;
    }
    else {
       // std::cout << "ethem0";
        return newsector->z - current->z;
    }
}
void SpaceSectorLLRBT::displaySectorsInOrder() {
    std::cout << "Space sectors inorder traversal:";
    inordertraversal(root);
    // TODO: Traverse the space sector BST map in-order and print the sectors 
    // to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPreOrder() {
    std::cout << "Space sectors preorder traversal:"; //BURADA DA KONTROL ETMK LAZIM NULLPTR MI
    preordertraversal(root);
    // TODO: Traverse the space sector BST map in pre-order traversal and print 
    // the sectors to STDOUT in the given format.
}

void SpaceSectorLLRBT::displaySectorsPostOrder() {
    std::cout << "Space sectors postorder traversal:";
    postordertraversal(root);
    // TODO: Traverse the space sector BST map in post-order traversal and print 
    // the sectors to STDOUT in the given format.

}
void SpaceSectorLLRBT::postordertraversal(Sector* node) {
    if (node != nullptr) {
        postordertraversal(node->left);
        postordertraversal(node->right);
        std::cout << node->sector_code << "\n";
    }
}
void SpaceSectorLLRBT::preordertraversal(Sector* node) {
    if (node != nullptr) {

        std::cout << node->sector_code << "\n";
        preordertraversal(node->left);
        preordertraversal(node->right);

    }
}
void SpaceSectorLLRBT::inordertraversal(Sector* node) {
    if (node != nullptr) {
        inordertraversal(node->left);
        std::cout << node->sector_code << "\n";
        inordertraversal(node->right);

    }
}
std::vector<Sector*> SpaceSectorLLRBT::getStellarPath(const std::string& sector_code) {
    std::vector<Sector*> path;
    Sector* finalsector = pathhelper(sector_code);
    if (sectors.empty()) {
        std::cout << "its null";
    }
    if (finalsector == nullptr) {
        std::cout << "its null";
    }
    if (finalsector != nullptr) {

        while (finalsector != nullptr) {
            
            path.push_back(finalsector);
            finalsector = finalsector->parent;
        }
        std::reverse(path.begin(), path.end()); //tersine veriyo
    }
    
    return path;

}
Sector* SpaceSectorLLRBT::findSector(Sector* node, const std::string& sector_code) const {
    if (node == nullptr || node->sector_code == sector_code) {
        return node;
    }

    if (sector_code < node->sector_code) {
        return findSector(node->left, sector_code);
    }
    else {
        return findSector(node->right, sector_code);
    }
}
Sector* SpaceSectorLLRBT::pathhelper(const std::string sector_code) {
    for (Sector* thesector : sectors) {
        std::cout << thesector->sector_code << "\n";
        
        if (thesector->sector_code == sector_code) {
            
            return thesector;
        }
    }
    return nullptr;
}
void SpaceSectorLLRBT::printStellarPath(const std::vector<Sector*>& path) {
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