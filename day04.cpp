#include <iostream>

using namespace std;

int main() {
    string line;
    int sum = 0;
    vector<int> cards;
    cards.resize(209);
    for (auto & c : cards) {
        c = 1;
    }
    int card = 0;
	while (getline(cin, line)) {
	    card++;
	    line = line.substr(line.find(":") + 2);
	    vector<int> numbers;
	    vector<int> winning;
	    int val;
	    for (int i = 0; i < 10; i++) {
	        sscanf(line.c_str(), "%d", &val);
	        numbers.push_back(val);
	        line = line.substr(3);
	    }
        line = line.substr(2);
	    for (int i = 0; i < 25; i++) {
	        sscanf(line.c_str(), "%d", &val);
	        winning.push_back(val);
	        if (line.size() >= 3) {
	            line = line.substr(3);
	        }
	    }
	    cout << "numbers ";
	    for (auto n : numbers) {
	        cout << n << " ";
	    }
	    cout << endl;
	    for (auto w : winning) {
	        cout << w << " ";
	    }
	    cout << endl;

        int res = 0;
	    for (auto n : numbers) {
	        if (find(winning.begin(), winning.end(), n) != winning.end()) {
	            res = res == 0 ? 1 : res * 2;
	        }
	    }
	    sum += res;
	    /* part 2 */
        int wins = 0;
	    for (auto n : numbers) {
	        if (find(winning.begin(), winning.end(), n) != winning.end()) {
	            wins++;
	        }
	    }
	    cout << "Card " << card << " wins " << wins << endl;
	    for (int i = card + 1; i <= card + wins; i++) {
	        cards[i] += cards[card];
	        cout << "we have " << cards[i] << " of cards no " << i << endl;
	    }
	}
	cout << "sum " << sum << endl;
	long long res = 0;
	for (auto c : cards) {
	    res += c;
	}
	cout << "cards " << res - 1 << endl;
}
