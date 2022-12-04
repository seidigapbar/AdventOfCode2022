#include <iostream>
#include <sstream>
#include <fstream>
#include <set>

using namespace std;

void checkAnElf(int (&array)[53], string elf){
    int ASCII = 0;
    fill(array, array+53, 0);
    for(size_t i = 0; i < elf.size(); i++){
    if(isupper(elf[i])){
        ASCII = int(elf[i]) - 38;
    }
    else{
        ASCII = int(elf[i]) - 96;
    }
        array[ASCII]++;
    }
}

int errorPriority(string elf1, string elf2, string elf3){
    int ASCII = 0;
    int firstPart[53], secondPart[53];
    checkAnElf(firstPart, elf1);
    checkAnElf(secondPart, elf2);
    
    for(size_t i = 0; i < elf3.size(); i++){
    if(isupper(elf3[i])){
        ASCII = int(elf3[i]) - 38;
    }
    else{
        ASCII = int(elf3[i]) - 96;
    }
    if((firstPart[ASCII] != 0) && (secondPart[ASCII] != 0)){
        return ASCII;

    }   }
}

int checkPair(string elfPair){
    stringstream ss;
    ss << elfPair;
    string temp;
    int number[4];
    uint16_t iter = 0;
    fill(number, number+4, 0);
    while(iter < 4){
        if(iter % 2 == 1){
            getline(ss, temp, ',');
        }
        else{
            getline(ss, temp, '-');
        }
        number[iter] = stoi(temp);
        iter++;
    }
    if((number[1] >= number[2] && number[1] <= number[3])
     ||(number[3] >= number[0] && number[3] <= number[1])){
        cout<<" The pair that overlaps is "<<elfPair<<endl;
        return 1;
     }
    return 0;
}

int handleFile(string fileName){
    string line;
    int finalResult = 0;
    ifstream inputFile(fileName);

    while(getline(inputFile, line)){
        /*line1 = line;
        getline(inputFile, line2);
        getline(inputFile, line3);*/
        finalResult += checkPair(line);
    }
    return finalResult;
}


int main()
{
    cout << handleFile("test.txt") << endl;
    cout << handleFile("input.txt");
    return 0;
}