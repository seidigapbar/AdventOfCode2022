//
// Created by Sanzhar Seidigapbar on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>
#include <map>
#include <vector>

template <typename T, typename U>
std::pair<T, U> operator+(const std::pair<T,U> &firstPair, const std::pair<T, U> &secondPair){
    return std::make_pair(firstPair.first + secondPair.first, firstPair.second + secondPair.second);
}

const std::map<char, std::pair<int, int> > directions = {
        {'R', std::make_pair(1, 0)},
        {'L', std::make_pair(-1, 0)},
        {'U', std::make_pair(0, 1)},
        {'D', std::make_pair(0, -1)}
};

void moveTail(std::pair<int, int> &tail, const std::pair<int, int> &head){
    int horizontalDiff = 0, verticalDiff = 0;
    horizontalDiff = std::abs(tail.first - head.first);
    verticalDiff = std::abs(tail.second - head.second);
    if (verticalDiff <= 1 && horizontalDiff <= 1)
        return;
    if(horizontalDiff > 1){
        tail = tail.first < head.first ? (tail + directions.at('R')) : (tail + directions.at('L'));
        if(std::abs(verticalDiff)){
            tail = tail.second < head.second ? (tail + directions.at('U')) : (tail + directions.at('D'));
        }
    }
    else if(verticalDiff > 1){
        tail = tail.second < head.second ? (tail + directions.at('U')) : (tail + directions.at('D'));
        if(std::abs(horizontalDiff)){
            tail = tail.first < head.first ? (tail + directions.at('R')) : (tail + directions.at('L'));
        }
    }
}

std::size_t solveProblem(std::string fileName, bool firstPart){
    std::string line;
    std::ifstream inputFile(fileName);
    std::set<std::pair<int, int> > visitedPositions;
    std::pair<int, int> positionOfHead = std::make_pair(0, 0), positionOfTail = std::make_pair(0, 0);
    std::vector<std::pair<int, int>> knots;
    for (int i = 0; i < 8; i++)
    {
        knots.push_back(std::make_pair(0, 0));
    }

    while(getline(inputFile, line)){
        std::stringstream ss;
        ss << line;
        char direction;
        int iterations = 0;
        ss >> direction >> iterations;
        if(firstPart) {
            for (int i = 0; i < iterations; i++) {
                positionOfHead = positionOfHead + directions.at(direction);
                moveTail(positionOfTail, positionOfHead);
                visitedPositions.insert(positionOfTail);
            }
        }
        else {
            for (int i = 0; i < iterations; i++) {
                positionOfHead = positionOfHead + directions.at(direction);
                for (std::size_t j = 0; j < 8; j++){
                    if(j == 0) {
                        moveTail(knots[j], positionOfHead);
                    }
                    else {
                        moveTail(knots[j], knots[j - 1]);
                    }
                }
                moveTail(positionOfTail, knots[7]);
                visitedPositions.insert(positionOfTail);
            }
        }
    }
    return visitedPositions.size();
}

int main(int argc, char** argv){
    if(strcmp(argv[1], "1") == 0) {
        std::cout << solveProblem("input.txt", 1) << std::endl;
    }
    else{
        std::cout<<solveProblem("input.txt", 0)<<std::endl;
    }
    return 0;
}