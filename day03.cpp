#include <iostream>

using namespace std;

int main() {
    const int MAX = 200;
    int gears[MAX][MAX];
    bool isgear[MAX][MAX];
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            gears[i][j] = 1;
            isgear[i][j] = false;
        }
    }
    string line;
    vector<string> lines;
    int sum = 0;
	while (getline(cin, line)) {
        lines.push_back(line);
	}
	for (int j = 0; j < lines.size(); j++) {
	    string l = lines[j];
	    vector<int> xs = {j};
	    if (j - 1 >= 0) {
	        xs.push_back(j - 1);
	    }
	    if (j + 1 < lines.size()) {
	        xs.push_back(j + 1);
	    }
	    for (int i = 0; i < l.size(); i++) {
	        if (isdigit(l[i])) {
	            vector<int> ys;
	            int val;
	            sscanf(l.substr(i).c_str(), "%d", &val);
	            cout << "val " << val << endl;
                for (int k = i; k < i + int(log10(val) + 1); k++) {
                    ys.push_back(k);
                }
                if (i - 1 >= 0) {
                    ys.push_back(i - 1);
                }
                i += int(log10(val) + 1);
                if (i < l.size()) {
                    ys.push_back(i);
                }

                bool symbol = false;
                for (auto x : xs) {
                    cout << "x:" << x;
                    for (auto y : ys) {
                        cout << " " << y;
                        if (lines[x][y] != '.' && !isdigit(lines[x][y])) {
                            symbol = true;
                            if (lines[x][y] == '*') {
                                if (gears[x][y] != 1) {
                                    isgear[x][y] = true;
                                }
                                gears[x][y] *= val;
                            }
                        }
                    }
                    cout << endl;
                }
                if (symbol) {
                    sum += val;
                    cout << "symbol" << endl;
                }
	        }
	    }
	}
	cout << "result " << sum << endl;

	int sumgear = 0;
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++) {
            if (isgear[i][j]) {
                sumgear += gears[i][j];
            }
        }
    }
    cout << "gears " << sumgear << endl;
}
