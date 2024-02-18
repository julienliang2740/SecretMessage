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
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
    return distrib(gen);
}

int numify(char c) { // returns the number representing the character that we will encode (can be either pos or neg)
    int numified = c;
    numified -= 32;
    int randnumFactor = generateRandomNumber(0,10);
    numified = numified + randnumFactor*95;
    if (generateRandomNumber(0,1) == 1) numified = numified*-1;
    return numified;
}

std::vector<int> binaryVec(int num) {
    std::vector<int> twosComplement(32, 0);
    // fill vector with bits of the number
    for (int i = 31; i >= 0; --i) {
        twosComplement[i] = (num >> (31 - i)) & 1;
    }
    return twosComplement;
}

std::vector<int> andcode(char c) { // even number
    int numified = numify(c);
    int vecLength = generateRandomNumber(1,5) * 2;

    // TEMP CODE
    std::cout << numified << std::endl;
    return binaryVec(numified);
}

std::vector<int> orcode(char c) { // odd number
    int numified = numify(c);    
    int vecLength = generateRandomNumber(1,5) * 2 + 1;

    // TEMP CODE
    std::cout << numified << std::endl;
    return binaryVec(numified);
}

int main() {
    char c;
    while(std::cin.get(c)) {
        std::cout << c << std::endl;
        if (c == std::cin.eof()) break;
        else {
            int randnum = generateRandomNumber(0,1);
            std::vector<int> codeNums;
            if (randnum == 0) codeNums = andcode(c);
            else if (randnum == 1) codeNums = orcode(c);

            // testing
            for (int num : codeNums) {
                std::cout << num;
            }
            std::cout << std::endl;
        }
    }
}
