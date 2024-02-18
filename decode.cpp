#include <iostream>
#include <sstream>
#include <string>
#include <vector>
#include <bitset>
#include <fstream>
#include <unordered_map>

char decode(std::vector<int> numbers) {
    int num;
    if (numbers.size() % 2 == 0) { // even -> and 
        num = ~0;
        for (int i = 0; i < numbers.size(); ++i) {
            num = num & numbers[i];
        }
    }
    else if (numbers.size() % 2 == 1) { // odd -> or
        num = 0;
        for (int i = 0; i < numbers.size(); ++i) {
            num = num | numbers[i];
        }
    }

    // use ascii range 32 -> 126 (space to ~)
    std::cout << num << std::endl;
    num = (abs(num) % 95) + 32;
    std::cout << num << std::endl;
    char c = static_cast<char>(num);
    std::cout << c << std::endl;
}

int main() {
    std::string line;
    while(getline(std::cin, line)) {
        std::istringstream iss(line);
        std::vector<int> numbers;
        int number;
        while (iss >> number) { 
            numbers.push_back(number);
        }
        for (int num: numbers) {
            std::cout << num << " ";
        }
        std::cout << std::endl;
        decode(numbers);
    }
}
