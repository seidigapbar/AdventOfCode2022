# Parsing is pretty trash, but it works, so why bother :D

#include <iostream>
#include <fstream>
#include <vector>
#include <unordered_map>
#include <set>
#include <queue>
#include <stack>

#define MAP_WIDTH 159
#define MAP_HEIGHT 41

class Node{
private:
    const char elevation;
    const std::size_t height, width;
    std::vector<Node*> neighbours;
public:
    Node(char elevation, std::size_t height, std::size_t width)
    : elevation(elevation), height(height), width(width){}

    bool endOfPath(){
        return this->elevation == 'E' ? true : false;
    }

    int getHeight(){
        return this->height;
    }

    int getWidth(){
        return this->width;
    }

    void printInfo(){
        std::cout<<"Current Node is: "<<this->elevation<<" The coordinates are: "<<this->width + 1<<" "<<this->height + 1<<std::endl;
    }

    char getChar(){
        char ans;
        this->elevation =='E' ? ans = 'z' : ans = this->elevation;
        return ans;
    }

    void addNeighbours(std::vector<std::vector<Node*>> mountainMap){
        char elev;
        // If S then a, if E then z, else it's the same....
        this->elevation == 'S' ? elev = 'a' : elev = this->elevation;

        if(this->height > 0){
            if((elev - mountainMap[this->height - 1][this->width]->getChar()) >= -1){
                neighbours.push_back(mountainMap[this->height - 1][this->width]);
            }
        }
        if(this->height < MAP_HEIGHT - 1) {
            if((elev - mountainMap[this->height + 1][this->width]->getChar()) >= -1){
                neighbours.push_back(mountainMap[this->height + 1][this->width]);
            }
        }
        if(this->width > 0){
            if((elev - mountainMap[this->height][this->width - 1]->getChar()) >= -1){
                neighbours.push_back(mountainMap[this->height][this->width - 1]);
            }
        }
        if(this->width < MAP_WIDTH - 1){
            if((elev - mountainMap[this->height][this->width + 1]->getChar()) >= -1){
                neighbours.push_back(mountainMap[this->height][this->width + 1]);
            }
        }
    }

    void addQueue(std::queue<std::pair<Node*, int>> &nodeQueue, int steps, std::set<Node*> &visitedNodes){
        for(const auto x : neighbours){
            if(visitedNodes.find(x) == visitedNodes.end()) {
                nodeQueue.push(std::make_pair(x, steps + 1));
                visitedNodes.insert(x);
            }
        }
    }
};

int solveBFS(Node* startingNode, std::vector<std::vector<Node*>> mountainMap){
    int steps = 0;
    std::set<Node*> visitedNodes;
    std::queue<std::pair<Node*, int>> nodeQueue;
    Node* topNode;
    nodeQueue.push(std::make_pair(startingNode, steps));
    visitedNodes.insert(startingNode);
    while(nodeQueue.size()){
        topNode = nodeQueue.front().first;
        steps = nodeQueue.front().second;
        if(topNode->endOfPath()) {
            return steps;
        }
        nodeQueue.pop();
        topNode->printInfo();
        topNode->addQueue(nodeQueue, steps, visitedNodes);
    }
    return -1;
}

std::vector<std::vector<Node*>> mountainMap;

int handleFile(std::string fileName, bool secondPart){
    std::string line;
    std::ifstream inputFile(fileName);
    std::size_t x = 0, y = 0;
    Node* startingNode;
    std::stack<Node*> startingNodesStack; // For the second part

    while(getline(inputFile, line)){
        x = 0;
        for(const auto &c : line) {
            mountainMap.push_back({});
            Node* newNode = new Node(c, y, x);

            if(secondPart && c == 'a'){
                startingNodesStack.push(newNode);
            }

            if(c == 'S'){
                startingNode = newNode;
            }
            mountainMap[y].push_back(newNode);
            x++;
        }
        y++;
    }

    for(std::size_t y = 0; y < MAP_HEIGHT; y++){
        for(std::size_t x = 0; x < MAP_WIDTH; x++)
        {
            mountainMap[y][x]->addNeighbours(mountainMap);

        }
    }

    int ans = solveBFS(startingNode, mountainMap);

    if (secondPart){
        int min = ans;
        while(!startingNodesStack.empty())
        {
            int tmp = solveBFS(startingNodesStack.top(), mountainMap);
            if (tmp != -1) {
                min = std::min(min, tmp);
            }
            startingNodesStack.pop();
        }
        ans = min;
    }

    for(auto y : mountainMap){
        for(auto x : y) {
            free(x);
        }
    }

    return ans;
}

int main(int argc, char** argv){
    std::cout<<handleFile("input.txt", true)<<std::endl;
}
