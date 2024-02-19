#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <unordered_map>
#include <random>
#include <algorithm>

int generateRandomNumber(int lower_bound, int upper_bound) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(lower_bound, upper_bound);
    return distrib(gen);
}

void shuffleVector(std::vector<int> & vec) {
    std::random_device rd;
    std::mt19937 g(rd());
    std::shuffle(vec.begin(), vec.end(), g);
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

int setBitToOne(int num, int bitPosition) {
    int mask = 1 << bitPosition;
    num |= mask;
    return num;
}

int setBitToZero(int num, int bitPosition) {
    int mask = ~(1 << bitPosition);
    num &= mask;
    return num;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

typedef int(*bitChangeFunc)(int, int); // either setBitToOne or setBitToZero

std::vector<int> makeOutput(std::vector<int> randomizedBitPlaces, int numNumsReturn, bitChangeFunc changeBit, int maskNum) {
    std::vector<int> toReturn;
    std::vector<int> constCopyBitPlaces = randomizedBitPlaces; // we keep this one constant, gets shuffled though
    std::vector<int> mutableCopyBitPlaces = randomizedBitPlaces; // we mutate this copy, but DONT shuffle order
    for (int i = 0; i < numNumsReturn; ++i) {
        int toAppend = maskNum;
        if (mutableCopyBitPlaces.size() == 0) { // we finished early
            shuffleVector(constCopyBitPlaces);
            int n = generateRandomNumber(1, constCopyBitPlaces.size());
            for (int j = 0; j < n; ++j) changeBit(toAppend, constCopyBitPlaces[j]);
        }
        else if (i-1 == numNumsReturn) { // we finished late
            for (int num : mutableCopyBitPlaces) changeBit(toAppend, num);
        }
        else { // do at normal pace
            int n = generateRandomNumber(1, mutableCopyBitPlaces.size());
            for (int j = 0; j < n; ++j) changeBit(toAppend, mutableCopyBitPlaces[j]);
        }
        toReturn.emplace_back(toAppend);
    }
    shuffleVector(toReturn);
    return toReturn;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

std::vector<int> andcode(char c) { // even number
    int numified = numify(c);
    int codeNumsAmount = generateRandomNumber(1,5) * 2;
    
    std::vector<int> binVec = binaryVec(numified);
    std::vector<int> hasZeroes;
    int numbits = binVec.size();
    for (int i = 0; i < numbits; ++i) {
        if(binVec[i] == 0) hasZeroes.push_back(numbits-i-1);
    }

    std::vector<int> binVecShuffled = binVec; 
    shuffleVector(binVecShuffled);
    std::vector<int> output = makeOutput(binVecShuffled, codeNumsAmount, setBitToZero, -1);

    // TEMP CODE
    std::cout << "Numification: " << numified << std::endl;
    std::cout << "Conversion: AND" << std::endl;
    std::cout << "Output number: " << codeNumsAmount << std::endl;
    for (int num : hasZeroes) std::cout << num << " " << std::endl;
    return output;
}

std::vector<int> orcode(char c) { // odd number
    int numified = numify(c);    
    int codeNumsAmount = generateRandomNumber(1,5) * 2 + 1;

    std::vector<int> binVec = binaryVec(numified);
    std::vector<int> hasOnes;
    int numbits = binVec.size();
    for (int i = 0; i < numbits; ++i) {
        if(binVec[i] == 1) hasOnes.push_back(numbits-i-1);
    }

    std::vector<int> binVecShuffled = binVec; 
    shuffleVector(binVecShuffled);
    std::vector<int> output = makeOutput(binVecShuffled, codeNumsAmount, setBitToZero, 0);

    // TEMP CODE
    std::cout << "Numification: " << numified << std::endl;
    std::cout << "Conversion: OR" << std::endl;
    std::cout << "Output number: " << codeNumsAmount << std::endl;
    for (int num : hasOnes) std::cout << num << " " << std::endl;
    return output;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

int main() {
    char c;
    while(std::cin.get(c)) {
        std::cout << "Character: " << c << std::endl;
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
