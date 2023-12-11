#include <iostream>
#include <cctype>

using namespace std;

int main() {
    string line;
    int x = 0;
    vector<string> lines;
    vector<pair<int,int>> points;
    vector<int> empty_xs;
    while (getline(cin, line)) {
        lines.push_back(line);
        bool empty = true;
        for (int y = 0; y < line.size(); y++) {
            if (line.at(y) == '#') {
                points.push_back({x, y});
                empty = false;
            }
        }
        if (empty) {
            empty_xs.push_back(x);
        }
        x++;
    }
    vector<int> empty_ys;
    for (int y = 0; y < lines.at(0).size(); y++) {
        bool empty = true;
        for (auto &l : lines) {
            if (l.at(y) == '#') {
                empty = false;
            }
        }
        if (empty) {
            empty_ys.push_back(y);
        }
    }

    long long sum = 0;
    for (int i = 0; i < points.size(); i++) {
        for (int j = i + 1; j < points.size(); j++) {
            int dist = abs(points.at(i).first - points.at(j).first) + abs(points.at(i).second - points.at(j).second);
            dist += 999999 * abs(lower_bound(empty_xs.begin(), empty_xs.end(), points.at(i).first) - lower_bound(empty_xs.begin(), empty_xs.end(), points.at(j).first));
            dist += 999999 * abs(lower_bound(empty_ys.begin(), empty_ys.end(), points.at(i).second) - lower_bound(empty_ys.begin(), empty_ys.end(), points.at(j).second));
            sum += dist;
            cout << "distance between: (" << points.at(i).first << ", " << points.at(i).second << ") and (" << points.at(j).first << ", " << points.at(j).second << ") is " << dist << endl;
        }
    }
    cout << sum << endl;
}
