#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>

class Directory{
public:
    static int sizeOfDirectories;
    static int totalSpace;
    static int min;
    int size;
    bool sizeCalculated;
    const std::string name;
    Directory* parent;
    std::unordered_map<std::string, Directory*> children;

    Directory(std::string name, Directory* parent)
    : name(name), parent(parent) {size = 0; sizeCalculated = false;}

    void freeAll(){
        for (auto &x : children)
        {
            free(x.second);
        }
        free(this);
    }

    Directory* getChild(std::string childName){
        if (children.find(childName) != children.end()){
            return this->children[childName];
        }
        return nullptr;
    }

    int getMin() {
       if (this->size + totalSpace >= 30000000){
           min = std::min(this->size, min);
       }
       for (const auto x : children){
           min = std::min(min, x.second->getMin());
       }
       return min;
    }

    int calculateSize() {
        for (const auto x: children) {
            if (!x.second->sizeCalculated) {
                this->size += x.second->calculateSize();
                x.second->sizeCalculated = true;
            } else {
                this->size += x.second->size;
            }
        }
        if (this->size <= 100000) {
            sizeOfDirectories += this->size;
        }
        this->sizeCalculated = true;
        return this->size;
    }

    void addChild(std::pair<std::string, Directory*> newChild) {
        this->children.insert(newChild);
    }

    void addFile(int fileSize) {
        this->size += fileSize;
    }
};

int Directory::sizeOfDirectories = 0;
int Directory::totalSpace = 70000000;
int Directory::min = 70000000;

int handleFile(std::string fileName, bool firstPart){
    std::string line;
    std::ifstream inputFile(fileName);
    getline(inputFile, line); // rootDir omitted
    Directory *rootDir = new Directory("/", nullptr);
    Directory *parent = rootDir;

    while(getline(inputFile, line)){
        std::stringstream ss;
        ss << line;
        std::string first, second, third;
        if (ss >> first, first == "$"){
            if(ss >> second, second == "cd"){
                ss >> third;
                if(third == "..") {
                    parent = parent->parent;
                }
                else {
                    parent = parent->getChild(third);
                }
            }
        }
        else if(first == "dir"){
            ss >> second;
            auto newPair = std::make_pair(second, new Directory(second, parent));
            if(parent->getChild(second) == nullptr) {
                parent->addChild(newPair);
            }
        }
        else{
            parent->addFile(std::stoi(first));
        }
    }
    rootDir->calculateSize();
    int returnValue = rootDir->sizeOfDirectories;
    Directory::totalSpace -= rootDir->size;
    std::cout<<"Min is: "<<rootDir->getMin()<<std::endl;
    rootDir->freeAll();
    return returnValue;
}


int main(int argc, char** argv){
    std::cout << handleFile("input.txt", true);
    return 0;
}
