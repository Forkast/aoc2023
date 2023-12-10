#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <memory>
#include <queue>

using namespace std;

struct pipe {
    int x, y, step;
};

bool visit(pipe p, vector<vector<bool>> &visited, queue<pipe> &Q) {
    if (!visited.at(p.x).at(p.y)) {
        Q.push(p);
        return true;
    }
    return false;
}

int main() {
    string line;
    vector<string> lines;
    while (std::getline(std::cin, line)) {
        lines.push_back(line);
    }

    const char empty = '*';
    for (auto & l : lines) {
        l.insert(l.begin(), empty);
        l.insert(l.end(), empty);
    }
    string dots(lines.at(0).size(), empty);
    lines.insert(lines.begin(), dots);
    lines.insert(lines.end(), dots);

    queue<pipe> Q;
    vector<bool> fal(lines.at(0).size(), false);
    vector<vector<bool>> visited(lines.size(), fal);
    for (int i = 0; i < lines.size(); i++) {
        for (int j = 0; j < lines.at(i).size(); j++) {
            if (lines.at(i).at(j) == 'S') {
                Q.push({i, j, 0});
                visited.at(i).at(j) = true;
            }
        }
    }

    auto start = Q.front();
    if (lines.at(start.x + 1).at(start.y) == 'L' || lines.at(start.x + 1).at(start.y) == '|' || lines.at(start.x + 1).at(start.y) == 'J') {
        Q.push({start.x + 1, start.y, start.step + 1});
    }
    if (lines.at(start.x - 1).at(start.y) == 'F' || lines.at(start.x - 1).at(start.y) == '|' || lines.at(start.x - 1).at(start.y) == '7') {
        Q.push({start.x - 1, start.y, start.step + 1});
    }
    if (lines.at(start.x).at(start.y - 1) == 'F' || lines.at(start.x).at(start.y - 1) == '-' || lines.at(start.x).at(start.y - 1) == 'L') {
        Q.push({start.x, start.y - 1, start.step + 1});
    }
    if (lines.at(start.x).at(start.y + 1) == 'J' || lines.at(start.x).at(start.y + 1) == '-' || lines.at(start.x).at(start.y + 1) == '7') {
        Q.push({start.x, start.y + 1, start.step + 1});
    }
    Q.pop();

    int maxStep = 0;
    while (!Q.empty()) {
        auto curr = Q.front();
        visited.at(curr.x).at(curr.y) = true;
        if (lines.at(curr.x).at(curr.y) == '|') {
            visit({curr.x - 1, curr.y, curr.step + 1}, visited, Q);
            visit({curr.x + 1, curr.y, curr.step + 1}, visited, Q);
        } else if (lines.at(curr.x).at(curr.y) == '-') {
            visit({curr.x, curr.y - 1, curr.step + 1}, visited, Q);
            visit({curr.x, curr.y + 1, curr.step + 1}, visited, Q);
        } else if (lines.at(curr.x).at(curr.y) == 'L') {
            visit({curr.x - 1, curr.y, curr.step + 1}, visited, Q);
            visit({curr.x, curr.y + 1, curr.step + 1}, visited, Q);
        } else if (lines.at(curr.x).at(curr.y) == 'J') {
            visit({curr.x - 1, curr.y, curr.step + 1}, visited, Q);
            visit({curr.x, curr.y - 1, curr.step + 1}, visited, Q);
        } else if (lines.at(curr.x).at(curr.y) == '7') {
            visit({curr.x, curr.y - 1, curr.step + 1}, visited, Q);
            visit({curr.x + 1, curr.y, curr.step + 1}, visited, Q);
        } else if (lines.at(curr.x).at(curr.y) == 'F') {
            visit({curr.x, curr.y + 1, curr.step + 1}, visited, Q);
            visit({curr.x + 1, curr.y, curr.step + 1}, visited, Q);
        }
        maxStep = maxStep < curr.step ? curr.step : maxStep;
        Q.pop();
    }

    int count = 0;
    for (int i = 0; i < lines.size(); i++) {
        bool inside = false;
        char entrance = '*';
        for (int j = 0; j < lines.at(i).size(); j++) {
            char c = lines.at(i).at(j);
            if (visited.at(i).at(j) && entrance == '*' && c != '-' && c != 'S') {
                inside = !inside;
                if (c != '|')
                    entrance = c;
            } else if (visited.at(i).at(j) && entrance != '*') {
                if ((entrance == '7' && c == 'F')
                || (entrance == 'F' && c == '7')
                || (entrance == 'L' && c == 'J')
                || (entrance == 'J' && c == 'L')) {
                    inside = !inside;
                    entrance = '*';
                } else if (c != '-' && c != 'S') {
                    entrance = '*';
                }
            }
            if (!visited.at(i).at(j) && inside && c != '*') {
                count++;
            }
        }
    }
    cout << maxStep << endl;
    cout << count << endl;
}