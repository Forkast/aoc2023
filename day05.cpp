#include <iostream>

using namespace std;

vector<long long> parse_seed(string line) {
    line = line.substr(line.find(" ") + 1);
    vector<long long> seeds;
    line.push_back(' ');
    while (line.size() > 1) {
        long long seed;
        sscanf(line.c_str(), "%lld", &seed);
        seeds.push_back(seed);
        line = line.substr(line.find(" ") + 1);
    }
    return seeds;
}
struct Map {
    long long dest;
    long long src;
    long long n;
};

vector<vector<Map>> parse_maps() {
    string line;
    vector<vector<Map>> maps;
    while (getline(cin, line)) {
        if (line == "") {
            maps.push_back({});
            continue;
        }
        if (!isdigit(line[0])) {
            continue;
        }
        long long dest, src, n;
        sscanf(line.c_str(), "%lld %lld %lld", &dest, &src, &n);
        maps.back().push_back({dest, src, n});
    }
    return maps;
}

void part1(vector<long long> seeds, vector<vector<Map>> maps) {
	for (auto &s : seeds) {
	    for (auto m : maps) {
	        bool mapped = false;
	        for (auto mapping : m) {
                if (s >= mapping.src && s <= mapping.src + mapping.n && !mapped) {
                    s -= mapping.src;
                    s += mapping.dest;
                    mapped = true;
                }
	        }
	    }
	}
	long long min = seeds.at(0);
	for (auto &s : seeds) {
	    cout << "seed " << s << endl;
	    min = s < min ? s : min;
	}
	cout << "min " << min << endl;
}

pair<long long, long long> mapp(pair<long long, long long> range, Map mapping) {
    range.first -= mapping.src;
    range.first += mapping.dest;
    range.second -= mapping.src;
    range.second += mapping.dest;
    return range;
}

long long minn(long long a, long long b) {
    return a < b ? a : b;
}

long long min_mapped(pair<long long, long long> range, const vector<vector<Map>> &maps, int depth) {
    if (depth == maps.size()) {
        return range.first;
    }
    int new_depth = depth + 1;
    long long min = 184467440737095516L;
    long long res = min;
    const vector<Map> &map = maps.at(depth);
    for (int i = 0; i < map.size(); i++) {
        const auto &mapping = map.at(i);
        if (range.first >= mapping.src && range.second <= mapping.src + mapping.n) { // seeds within mapping
            res = min_mapped(mapp(range, mapping), maps, new_depth);
        } else if (range.first >= mapping.src && range.first <= mapping.src + mapping.n) { // start within
            res = min_mapped(mapp({range.first, mapping.src + mapping.n}, mapping), maps, new_depth);
        } else if (range.first >= mapping.src && range.first <= mapping.src + mapping.n) { // end within
            res = min_mapped(mapp({mapping.src, range.second}, mapping), maps, new_depth);
        } else if (range.first < mapping.src && range.second > mapping.src + mapping.n) { // mapping within seeds
            res = min_mapped(mapp({mapping.src, mapping.src + mapping.n}, mapping), maps, new_depth);
        }
        min = res < min ? res : min;
        if (i - 1 < map.size()) {
            if (mapping.src + mapping.n > range.first && mapping.src + mapping.n < range.second) {
                res = min_mapped({mapping.src + mapping.n, minn(map.at(i + 1).src, range.second)}, maps, new_depth);
            }
        }
        min = res < min ? res : min;
    }
    return min;
}

void part2(vector<long long> seeds, vector<vector<Map>> maps) {
    vector<pair<long long, long long>> ranges;
    for (int i = 0; i < seeds.size(); i += 2) {
        ranges.push_back({seeds.at(i), seeds.at(i) + seeds.at(i + 1)});
    }
    for (auto range : ranges) {
        cout << range.first << ", " << range.second << " - " << min_mapped(range, maps, 0) << endl;
    }
}

int main() {
    string line;
	getline(cin, line);
	vector<long long> seeds = parse_seed(line);
	for (auto s : seeds) {
	    cout << s << endl;
	}
	vector<vector<Map>> maps = parse_maps();
	for (auto &m : maps) {
	    sort(m.begin(), m.end(), [](auto &m1, auto &m2) { return m1.src < m2.src;});
	}

	part2(seeds, maps);
}
