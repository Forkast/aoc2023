#include <iostream>
#include <algorithm>

using namespace std;


int main() {
    string tline;
	getline(cin, tline);
    string dline;
	getline(cin, dline);
	tline = tline.substr(tline.find(":") + 1);
	dline = dline.substr(dline.find(":") + 1);
	tline.erase(remove(tline.begin(), tline.end(), ' '), tline.end());
	dline.erase(remove(dline.begin(), dline.end(), ' '), dline.end());
    cout << "tline " << tline << endl;
    cout << "dline " << dline << endl;
    long long time, distance;
    sscanf(tline.c_str(), "%lld", &time);
    sscanf(dline.c_str(), "%lld", &distance);
	cout << int(sqrt(time * time - 4 * distance)) << endl;
}
