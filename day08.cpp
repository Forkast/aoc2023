#include <iostream>
#include <utility>
#include <vector>
#include <algorithm>
#include <sstream>
#include <map>
#include <memory>

struct Node {
    Node(Node* R, Node* L, std::string label)
    : R{R}, L{L}, label{std::move(label)} {}
    Node *R, *L;
    std::string label;
};

bool done(std::vector<Node*> &nodes) {
    for (auto n : nodes) {
        if (n->label.at(2) != 'Z') {
            return false;
        }
    }
    return true;
}

int main() {
    std::string instructions;
    std::getline(std::cin, instructions);
    std::string line;
    std::vector<std::string> lines;
    std::map<std::string, std::unique_ptr<Node>> nodes;
    std::vector<Node*> current;

    while (std::getline(std::cin, line)) {
        if (line.empty()) continue;
        lines.push_back(line);
        char S[4], L[4], R[4];
        sscanf(line.c_str(), "%s = (%[^,], %[^)])", S, L, R);
        nodes[std::string(S)] = std::make_unique<Node>(nullptr, nullptr, std::string(S));
        if (S[2] == 'A') {
            current.push_back(nodes.at(std::string(S)).get());
            std::cout << "starting with " << std::string(S) << std::endl;
        }
    }

    for (auto &l : lines) {
        char S[4], L[4], R[4];
        sscanf(l.c_str(), "%s = (%[^,], %[^)])", S, L, R);
        nodes.at(std::string(S))->R = nodes.at(std::string(R)).get();
        nodes.at(std::string(S))->L = nodes.at(std::string(L)).get();
    }

    std::vector<int> results;
    for (auto &n : current) {
        int inst = 0;
        int steps = 0;
        std::cout << n->label.at(2) << std::endl;
        while (n->label.at(2) != 'Z') {
            if (instructions[inst] == 'R') {
                n = n->R;
            } else if (instructions[inst] == 'L') {
                n = n->L;
            }
            inst = (inst + 1) % instructions.size();
            steps++;
        }
        results.push_back(steps);
    }
    std::vector<int> primes(20000, 0);
    for (auto &r : results) {
        for (int i = 2; i <= r; i++) {
            int count = 0;
            std::cout << r << "/" << i << " = ?\n";
            while (r % i == 0) {
                std::cout << r << "/" << i << " = ?\n";
                count++;
                r /= i;
            }
            primes.at(i) = std::max(primes.at(i), count);
        }
    }

    long long result = 1;
    for (int i = 2; i < primes.size(); i++) {
        if (primes.at(i) != 0) {
            for (int j = 0; j < primes.at(i); j++) {
                std::cout << "prime " << i << std::endl;
                result *= i;
            }
        }
    }

    std::cout << result << std::endl;
}
