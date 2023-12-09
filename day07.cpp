/*
ChatGPT generated code to brain generated solution
*/

#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>

bool compareChars(char ch1, char ch2) {
    // Define custom order for characters
    const std::string customOrder = "AKQT98765432J";
    return customOrder.find(ch1) > customOrder.find(ch2);
}

bool compareStrings(const std::string& str1, const std::string& str2) {
    // Count occurrences of each character in both strings
    std::vector<int> count1(256, 0), count2(256, 0);
    for (char ch : str1) count1[ch]++;
    for (char ch : str2) count2[ch]++;
    
    int j1 = count1.at('J');
    int j2 = count2.at('J');
    count1.at('J') = 0;
    count2.at('J') = 0;
    
    std::sort(count1.begin(), count1.end(), [](int a, int b) { return a > b; });
    std::sort(count2.begin(), count2.end(), [](int a, int b) { return a > b; });
    
    int maxCount1 = count1.at(0) + j1;
    int secondMaxCount1 = count1.at(1);
    int maxCount2 = count2.at(0) + j2;
    int secondMaxCount2 = count2.at(1);

    // Compare by maximal count and then by second maximal count
    if (maxCount1 != maxCount2) {
        return maxCount1 < maxCount2;
    } else if (secondMaxCount1 != secondMaxCount2) {
        return secondMaxCount1 < secondMaxCount2;
    } else {
        // If counts are equal, compare lexicographically with custom ordering
        for (std::size_t i = 0; i < str1.size(); ++i) {
            if (str1[i] != str2[i]) {
                return compareChars(str1[i], str2[i]);
            }
        }
        return false; // Equal strings
    }
}

int main() {
    // Read input strings with numbers separated by space
    std::vector<std::pair<std::string, int>> stringsWithNumbers;
    std::string input;
    while (std::getline(std::cin, input)) {
        std::istringstream iss(input);
        std::string str;
        int number;
        if (iss >> str >> number) {
            stringsWithNumbers.emplace_back(str, number);
        }
    }

    // Sort the strings based on custom comparison
    std::sort(stringsWithNumbers.begin(), stringsWithNumbers.end(), [&](const auto& pair1, const auto& pair2) {
        return compareStrings(pair1.first, pair2.first);
    });

    // Calculate and output the sum of numbers multiplied by their position
    int sum = 0;
    for (std::size_t i = 0; i < stringsWithNumbers.size(); ++i) {
        std::cout << "pos " << i + 1 << " seq " << stringsWithNumbers[i].first << std::endl;
        sum += (i + 1) * stringsWithNumbers[i].second;
    }

    std::cout << "Sum: " << sum << std::endl;

    return 0;
}
