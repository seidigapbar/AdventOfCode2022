#include <iostream>
#include <fstream>
#include <vector>

// Very ugly bruteforce solution :(

std::vector<std::vector<int> > grid;

int treeScore(std::vector<std::vector<int> > grid, size_t x, size_t y) {
    if (x == 0 || x == (grid[0].size() - 1) || y == 0 || y == (grid.size() - 1)) {
        return 0;
    }

    int top = 0, bottom = 0, left = 0, right = 0;

    for(int i = x - 1; i >= 0; i--)
    {
        left = x - i;
        if(grid[y][i] >= grid[y][x]) {
            break;
        }
    }
    for(int i = x + 1; i < grid[0].size(); i++)
    {
        right = i - x;
        if(grid[y][i] >= grid[y][x]) {
            break;
        }
    }
    for(int i = y - 1; i >= 0; i--)
    {
        top = y - i;
        if(grid[i][x] >= grid[y][x]) {
            break;
        }
    }
    for(int i = y + 1; i < grid.size(); i++)
    {
        bottom = i - y;
        if(grid[i][x] >= grid[y][x]) {
            break;
        }
    }
    return top * bottom * left * right;
}

bool checkTree(std::vector<std::vector<int> > grid, size_t x, size_t y) {
    if (x == 0 || x == (grid[0].size() - 1) || y == 0 || y == (grid.size() - 1)) {
        return true;
    }
    for(int i = x - 1; i >= 0; i--)
    {
        if(grid[y][i] >= grid[y][x]) {
            break;
        }
        else if(i == 0) {
            return true;
        }
    }
    for(int i = x + 1; i < grid[0].size(); i++)
    {
        if(grid[y][i] >= grid[y][x]) {
            break;
        }
        else if(i == (grid[0].size() - 1)) {
            return true;
        }
    }
    for(int i = y - 1; i >= 0; i--)
    {
        if(grid[i][x] >= grid[y][x]) {
            break;
        }
        else if(i == 0) {
            return true;
        }
    }
    for(int i = y + 1; i < grid.size(); i++)
    {
        if(grid[i][x] >= grid[y][x]) {
            break;
        }
        else if(i == (grid[0].size() - 1)) {
            return true;
        }
    }
    return false;
}

int handleFile(std::string fileName, bool firstPart){
    int iteration = 0, lines = 0, finalResult = 0;
    std::string line;
    std::ifstream inputFile(fileName);

    while(getline(inputFile, line)){
        std::vector<int> *temp = new std::vector<int>;
        grid.push_back(*temp);
        for(const auto x : line){
            grid[lines].push_back(static_cast<int>(x - '0'));
            iteration++;
        }
        lines++;
    }

    if(firstPart) {
        for (size_t y = 0; y < grid.size(); y++) {
            for (size_t x = 0; x < grid[0].size(); x++) {
                finalResult += int(checkTree(grid, x, y));
            }
        }
        std::cout << "The number of visible trees is: " << finalResult;
    }
    else{
        for (size_t y = 0; y < grid.size(); y++) {
            for (size_t x = 0; x < grid[0].size(); x++) {
                finalResult = std::max(treeScore(grid, x, y), finalResult);
            }
        }
        std::cout << "The highest score of a tree is: " << finalResult;
    }
    return finalResult;
}

int main(int argc, char** argv){
    if(strcmp(argv[1], "1") == 0){
        handleFile("input.txt", true);
    }
    else{
        handleFile("input.txt", false);
    }
}