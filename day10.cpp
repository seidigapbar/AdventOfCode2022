//
// Created by Sanzhar Seidigapbar on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

const std::set<int> numbers = {20, 60, 100, 140, 180, 220};
const std::set<int> secondTaskNumbers = {40, 80, 120, 160, 200, 240};

void runCycleSecondTask(int &cycle, const std::set<int> &secondTaskNumbers, const int &X){
    int normalCycle = cycle - 1;
    while(normalCycle >= 40){
        normalCycle = normalCycle % 40;
    }
    if(abs(X - normalCycle) > 1){
        std::cout<<".";
    }
    else{
        std::cout<<"#";
    }
    if(secondTaskNumbers.find(cycle) != secondTaskNumbers.end()){
        std::cout<<std::endl;
    }
    cycle++;
}

void runCycle(int &cycle, const std::set<int> &numbers, int &finalValue, const int &X){
    if(numbers.find(cycle) != numbers.end()){
        finalValue += (X * cycle);
        std::cout<<"The cycle is: "<<cycle<<", the value is: "<<X<<std::endl;
    }
    cycle++;
}

int handleFile(std::string fileName, bool firstPart){
    int cycle = 1, X = 1, finalSum = 0;
    std::string line;
    std::ifstream inputFile(fileName);
    while(getline(inputFile, line)){
        std::stringstream ss;
        ss << line;
        std::string operation;
        ss >> operation;
        if (operation == "addx"){
            int addValue = 0;
            ss >> addValue;
            if(firstPart) {
                runCycle(cycle, numbers, finalSum, X);
                runCycle(cycle, numbers, finalSum, X);
            }
            else{
                runCycleSecondTask(cycle, secondTaskNumbers, X);
                runCycleSecondTask(cycle, secondTaskNumbers, X);
            }
            X += addValue;
        }
        else{
            if(firstPart) {
                runCycle(cycle, numbers, finalSum, X);
            }
            else{
                runCycleSecondTask(cycle, secondTaskNumbers, X);
            }
        }
    }
    return finalSum;
}

int main(int argc, char** argv){
    if(strcmp(argv[1], "1") == 0){
        std::cout<<handleFile("input.txt", true)<<std::endl;
    }
    else{
        std::cout<<handleFile("input.txt", false)<<std::endl;
    }
    return 0;
}
