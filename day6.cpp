#include <iostream>
#include <sstream>
#include <fstream>
#include <set>
#include <queue>

int getMarkerPos(std::string input, bool firstPart){
    std::set<char> uniqueCharacters;
    std::queue<char> consequentCharacters;
    int16_t MESSAGE_SIZE = firstPart ? 4 : 14;
    size_t inputSize = input.size();
    int lastPos[26];

    for(size_t i = 0; i < inputSize; i++){
        consequentCharacters.push(input[i]);
        lastPos[input[i]-97] = i;
        uniqueCharacters.insert(input[i]);
        if(i > MESSAGE_SIZE - 1){
            char frontChar = consequentCharacters.front();
            if(lastPos[frontChar-97] < i - (MESSAGE_SIZE - 1)){
                std::cout<<"Last pos is: "<<lastPos[frontChar-97]<<" The char itself is: "<<frontChar<<" And the iteration is: "<<i<<std::endl;
                uniqueCharacters.erase(consequentCharacters.front());
            }
            consequentCharacters.pop();
        }
        if(uniqueCharacters.size() == MESSAGE_SIZE){
            return i + 1; // In the problem chars start from 1
        }
    }
    std::cout<<"Couldn't find the first four unique characters..."<<std::endl;
    return -1;
}

int handleFile(std::string fileName, bool firstPart){
    int iteration = 0;
    std::string line;
    bool input = true;
    int finalResult = 0;
    std::ifstream inputFile(fileName);

    while(getline(inputFile, line)){
        finalResult = getMarkerPos(line, firstPart);
    }
    return finalResult;
}


int main(int argc, char *argv[])
{
    if(strcmp(argv[1], "1")){
        std::cout << handleFile("input.txt", true);
    }
    else{
        std::cout << handleFile("input.txt", false);
    }
    return 0;
}