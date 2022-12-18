//
// Created by Sanzhar Seidigapbar on 13.12.2022.
//
#include <iostream>
#include <fstream>
#include <vector>
#include <functional>

// Too bothered to write a parser for the input:
// Monkey 0:
// Starting items: 65, 58, 93, 57, 66
// Operation: new = old * 7
// Test: divisible by 19
// If true: throw to monkey 6
// If false: throw to monkey 4
//
// Monkey 1:
// Starting items: 76, 97, 58, 72, 57, 92, 82
//  Operation: new = old + 4
//  Test: divisible by 3
//  If true: throw to monkey 7
//  If false: throw to monkey 5
//
// Monkey 2:
//  Starting items: 90, 89, 96
//  Operation: new = old * 5
//  Test: divisible by 13
//  If true: throw to monkey 5
//  If false: throw to monkey 1
//
// Monkey 3:
//  Starting items: 72, 63, 72, 99
//  Operation: new = old * old
//  Test: divisible by 17
//  If true: throw to monkey 0
//  If false: throw to monkey 4
//
// Monkey 4:
//  Starting items: 65
//  Operation: new = old + 1
//  Test: divisible by 2
//  If true: throw to monkey 6
// If false: throw to monkey 2
//
// Monkey 5:
// Starting items: 97, 71
// Operation: new = old + 8
// Test: divisible by 11
// If true: throw to monkey 7
// If false: throw to monkey 3
//
// Monkey 6:
// Starting items: 83, 68, 88, 55, 87, 67
// Operation: new = old + 2
// Test: divisible by 5
// If true: throw to monkey 2
// If false: throw to monkey 1
//
// Monkey 7:
// Starting items: 64, 81, 50, 96, 82, 53, 62, 92
// Operation: new = old + 5
// Test: divisible by 7
// If true: throw to monkey 3
// If false: throw to monkey 0

enum Operation {MULTIPLY, ADD};

class Monkey{
private:
    std::vector<int64_t> items;
    const int divisionTest, value, monkeyTrue, monkeyFalse;
    const Operation operation;
    int64_t inspectionCount;
    static int commonDivisor;
public:
    static std::vector<Monkey*> Monkeys;
    Monkey(std::vector<int64_t> items, int divisionTest, int monkeyTrue, int monkeyFalse, Operation operation, int value = -100)
    : items(items), divisionTest(divisionTest), monkeyTrue(monkeyTrue), monkeyFalse(monkeyFalse), operation(operation), value(value), inspectionCount(0){}

    void printItems(){
        for(const auto x : this->items){
            std::cout<<x<<" ";
        }
        std::cout<<std::endl;
    }

    int64_t getCount(){
        return this->inspectionCount;
    }

    void performOperation(){
        for(auto &x : this->items){
            if(this->operation == MULTIPLY){
                if(this->value == -100){
                    x = x * x;
                    inspectionCount++;
                }
                else{
                    x = x * this->value;
                    inspectionCount++;
                }
            }
            else{
                x = x + this->value;
                inspectionCount++;
            }
        }
        // TEST:
        for(std::size_t i = 0; i < this->items.size(); i++){
            if (this->items[i] % this->divisionTest == 0){
                passItem(this->Monkeys[monkeyTrue], i);
                i--;
            }
            else{
                passItem(this->Monkeys[monkeyFalse], i);
                i--;
            }
        }
    }

    void passItem(Monkey* receiver, std::size_t itemPosition){
        auto vectorRef = this->items.begin() + itemPosition;
        receiver->items.push_back(this->items[itemPosition]);
        this->items.erase(vectorRef);
    }

    int getCommonDivisor(){
        int cd = 1;
        for(auto &x : Monkeys){
            cd *= x->divisionTest;
        }
        return cd;
    }

    void normalizeItems(){
        for(auto &x : Monkeys){
            for(auto &n : x->items){
                n = n % this->commonDivisor;
            }
        }
    }
};

Monkey *first = new Monkey({65, 58, 93, 57, 66}, 19, 6, 4, MULTIPLY, 7);
Monkey *second = new Monkey({76, 97, 58, 72, 57, 92, 82}, 3, 7, 5, ADD, 4);
Monkey *third = new Monkey({90, 89, 96}, 13, 5, 1, MULTIPLY, 5);
Monkey *fourth = new Monkey({72, 63, 72, 99}, 17, 0, 4, MULTIPLY); // By itself
Monkey *fifth = new Monkey({65}, 2, 6, 2, ADD, 1);
Monkey *sixth = new Monkey({97, 71}, 11, 7, 3, ADD, 8);
Monkey *seventh = new Monkey({83, 68, 88, 55, 87, 67}, 5, 2, 1, ADD, 2);
Monkey *eighth = new Monkey({64, 81, 50, 96, 82, 53, 62, 92}, 7, 3, 0, ADD, 5);

std::vector<Monkey*> Monkey::Monkeys = {first, second, third, fourth, fifth, sixth, seventh, eighth};
int Monkey::commonDivisor = first->getCommonDivisor();

/*
    Monkey *f = new Monkey({79, 98}, 23, 2, 3, MULTIPLY, 19);
    Monkey *s = new Monkey({54, 65, 75, 74}, 19, 2, 0, ADD, 6);
    Monkey *t = new Monkey({79, 60, 97}, 13, 1, 3, MULTIPLY);
    Monkey *fr = new Monkey({74}, 17, 0, 1, ADD, 3);

    std::vector<Monkey*> Monkey::Monkeys = {f, s, t, fr};
    int Monkey::commonDivisor = f->getCommonDivisor();
*/

int64_t solveProblem(int iterations){
    int64_t max1 = 0, max2 = 0, temp = 0;
    for(int i = 0; i < iterations; i++){
        for(auto &x : Monkey::Monkeys){
            x->performOperation();
        }
        Monkey::Monkeys[0]->normalizeItems();
    }
    for(auto &x : Monkey::Monkeys) {
        temp = x->getCount();
        if(max1 < temp){
            max2 = max1;
            max1 = temp;
        }
        else if(max2 < temp){
            max2 = temp;
        }
    }
    std::cout<<max1<<" "<<max2<<std::endl;
    return max1 * max2;
}

int main(int argc, char** argv){
    std::cout<<solveProblem(10000)<<std::endl;
    return 0;
}
