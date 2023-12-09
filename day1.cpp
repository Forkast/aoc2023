#include <iostream>

using namespace std;


vector<pair<string, string>> digits = {
{"zero","0"},
{"one", "1"},
{"two","2"},
{"three","3"},
{"four","4"},
{"five", "5"},
{"six","6"},
{"seven","7"},
{"eight","8"},
{"nine","9"}
};


int main() {
    string line;
    int sum = 0;
	while (getline(cin, line)) {
	    const int MAX = 2000000;
        vector<int> firsts = {};
        vector<int> lasts = {};
	    for (int i = 0; i < digits.size(); i++) {
            int f1 = line.find(digits.at(i).first);
            f1 = f1 == string::npos ? MAX : f1;
            int f2 = line.find(digits.at(i).second);
            f2 = f2 == string::npos ? MAX : f2;
            int first = min(f1, f2);
            int l1 = line.rfind(digits.at(i).first);
            l1 = l1 == string::npos ? -1 : l1;
            int l2 = line.rfind(digits.at(i).second);
            l2 = l2 == string::npos ? -1 : l2;
            int last = max(l1, l2);
            firsts.push_back(first);
            lasts.push_back(last);
        }
        auto last = max_element(begin(lasts), end(lasts));
        auto first = min_element(begin(firsts), end(firsts));
        int res = (first - firsts.begin()) * 10 + last - lasts.begin();
        cout << res << endl;
        sum += res;
        firsts.clear();
        lasts.clear();
	}
	cout << sum << endl;
}
