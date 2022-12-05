#include <iostream>
#include <sstream>
#include <fstream>
#include <deque>
#include <stack>

std::deque<char> dequeArray[10]; // Using deque here because of nearly-impossible parsing of the input

void moveItemsFirstPart(int instructions[3]){
    char moveCrate;
    for(int i = 0; i < instructions[0]; i++){
        if (!dequeArray[instructions[1]-1].empty()){
            moveCrate = dequeArray[instructions[1]-1].front();
            dequeArray[instructions[2]-1].push_front(moveCrate);
            dequeArray[instructions[1]-1].pop_front();
        }
        else{
            std::cout<<"Empty stack! Skipping instruction.."<<std::endl;
        }
    }
}

void moveItemsSecondPart(int instructions[3]){
    std::stack<char> moveCrate;
    for(int i = 0; i < instructions[0]; i++){
        if (!dequeArray[instructions[1]-1].empty()){
            moveCrate.push(dequeArray[instructions[1]-1].front());
            dequeArray[instructions[1]-1].pop_front();
        }
        else{
            std::cout<<"Empty stack! Skipping instruction.."<<std::endl;
        }
    }
    for(int i = 0; i < instructions[0] && !moveCrate.empty(); i++){
        dequeArray[instructions[2]-1].push_front(moveCrate.top());
        moveCrate.pop();
    }
}

int fillDeques(std::string input, std::deque<char> dequeArray[10]){
    size_t inputLength = input.size();
    if(!inputLength){
        return 1;
    }
    else if(input[1] == '1'){
        return 1;
    }
    for(size_t i = 1; i < inputLength; i += 4){
        if(input[i] != ' ')
            dequeArray[i/4].push_back(input[i]);
    }
    return 0;
}

void handleDeques(std::string inputInstruction, std::deque<char> dequeArray[10]){
    if(!inputInstruction.size()){
        return;
    }
    std::stringstream ss;
    std::string tempNumberFetcher;
    int instructions[3];
    uint16_t iter = 0;

    ss << inputInstruction;
    
    while(!ss.eof() && iter < 3){
        ss >> tempNumberFetcher;
        if(std::stringstream(tempNumberFetcher) >> instructions[iter]){
            iter++;
        }
    }
    // moveItemsFirstPart(instructions); Uncomment this for the first part
    moveItemsSecondPart(instructions);
}

int handleFile(std::string fileName){
    int iteration = 0;
    std::string line;
    bool input = true;
    int finalResult = 0;
    std::ifstream inputFile(fileName);

    while(getline(inputFile, line)){
        if(input){
            if(fillDeques(line, dequeArray) == 1){
                input = false;
            }
            iteration++;
        }
        else{
            handleDeques(line, dequeArray);
        }
    }
    for(int i = 0; i < 10; i++){
        if(!dequeArray[i].empty()){
            std::cout<<"The element number "<<i<<" "<<dequeArray[i].front()<<std::endl;
        }
    }

    return finalResult;
}


int main()
{
    std::cout << handleFile("input.txt");
    return 0;
}