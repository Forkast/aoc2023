#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <memory>

using namespace std;

int main() {
    string line;
    long long sumLeft = 0;
    long long sumRight = 0;
    while (std::getline(std::cin, line)) {
        line.push_back(' ');
        vector<vector<int>>values(1);
        while (!line.empty()) {
            int val;
            sscanf(line.c_str(), "%d", &val);
            values.at(0).push_back(val);
            line = line.substr(line.find(' ') + 1);
        }
        bool cont = true;
        int level = 0;
        while (cont) {
            values.push_back({});
            cont = false;
            for (int i = 0; i < values.at(level).size() - 1; i++) {
                values.at(level + 1).push_back(values.at(level).at(i + 1) - values.at(level).at(i));
                if (values.at(level + 1).back() != 0) {
                    cont = true;
                }
            }
            level++;
        }
        int left = 0;
        int right = 0;
        for (int i = level; i > 0; i--) {
            right = right + values.at(i - 1).back();
            left = values.at(i - 1).front() - left;
        }
        sumLeft += left;
        sumRight += right;
    }
    cout << sumLeft << endl;
    cout << sumRight << endl;
}
