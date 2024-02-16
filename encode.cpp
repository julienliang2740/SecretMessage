#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <unordered_map>
#include <random>

int generateRandomNumber(int lower_bound, int upper_bound) {
    static std::random_device rd;
    static std::mt19937 gen(rd()); // Standard mersenne_twister_engine seeded with rd()

    std::uniform_int_distribution<> distrib(lower_bound, upper_bound);

    return distrib(gen);
}

std::vector<int> andcode(char c) { // even number
    int numify = c;
    numify -=32;
    int randnumFactor = generateRandomNumber(0,10);
    numify = numify + randnumFactor*95;

    int vecLength = generateRandomNumber(1,5) * 2;
    if (generateRandomNumber(0,1) == 1) numify = numify*-1;
}

std::vector<int> orcode(char c) { // odd number
    int numify = c;
    numify -= 32;
    int randnumFactor = generateRandomNumber(0,10);
    numify = numify + randnumFactor*95;
    
    int vecLength = generateRandomNumber(1,5) * 2 + 1;
    if (generateRandomNumber(0,1) == 1) numify = numify*-1;
}

int main() {
    char c;
    while(std::cin.get(c)) {
        if (c == std::cin.eof()) break;
        else {
            int randnum = generateRandomNumber(0,1);
            std::vector<int> codeNums;
            if (randnum == 0) codeNums = andcode(c);
            else if (randnum == 1) codeNums = orcode(c);

            for (int num : codeNums) {
                std::cout << num;
            }
            std::cout << std::endl;
        }
    }
}
