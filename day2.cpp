#include <iostream>

using namespace std;
// R G B
vector<pair<string, int>> limit = {{"red", 12}, {"green", 13}, {"blue", 14}};


int main() {
    int game = 0;
    int result = 0;
    int sum = 0;
    string line;
	while (getline(cin, line)) {
        vector<int> maxs = {0, 0, 0};
	    cout << "line " << line << endl;
	    game++;
	    bool valid = true;
	    string balls = line.substr(line.find(":") + 1);
	    while (true) {
	        string iteration = balls.substr(0, balls.find(";"));
	        while (true) {
	            string b = iteration.substr(0, iteration.find(","));
	            int val;
	            char col[10];
	            sscanf(b.c_str(), "%d %s", &val, col);
	            int ind = 0;
	            for (auto l : limit) {
	                if (l.first.compare(col) == 0) {
                        if (val > l.second) {
                            valid = false;
                        }
                        if (val > maxs.at(ind)) {
                            maxs.at(ind) = val;
                        }
	                }
	                ind++;
	            }
	            if (iteration.find(",") == string::npos) {
	                break;
	            }
	            iteration = iteration.substr(iteration.find(",") + 1);
	        }
	        if (balls.find(";") == string::npos) {
	            break;
	        }
	        balls = balls.substr(balls.find(";") + 1);
	    }
	    int power = maxs.at(0) * maxs.at(1) * maxs.at(2);
	    cout << "red " << maxs.at(0) << " green " << maxs.at(1) << " blue " << maxs.at(2) << endl;
	    sum += power;
	    if (valid) {
	        result += game;
	    }
	    cout << "game " << game << endl;
	    cout << "result " << result << endl;
	    cout << "power " << sum << endl;
	}
}
