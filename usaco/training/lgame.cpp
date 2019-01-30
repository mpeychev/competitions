/*
PROB: lgame
LANG: C++
ID: mompej951
*/

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

int letter2value[32];

void setValues() {
    letter2value['a' - 'a'] = 2;
    letter2value['b' - 'a'] = 5;
    letter2value['c' - 'a'] = 4;
    letter2value['d' - 'a'] = 4;
    letter2value['e' - 'a'] = 1;
    letter2value['f' - 'a'] = 6;
    letter2value['g' - 'a'] = 5;
    letter2value['h' - 'a'] = 5;
    letter2value['i' - 'a'] = 1;
    letter2value['j' - 'a'] = 7;
    letter2value['k' - 'a'] = 6;
    letter2value['l' - 'a'] = 3;
    letter2value['m' - 'a'] = 5;
    letter2value['n' - 'a'] = 2;
    letter2value['o' - 'a'] = 3;
    letter2value['p' - 'a'] = 5;
    letter2value['q' - 'a'] = 7;
    letter2value['r' - 'a'] = 2;
    letter2value['s' - 'a'] = 1;
    letter2value['t' - 'a'] = 2;
    letter2value['u' - 'a'] = 4;
    letter2value['v' - 'a'] = 6;
    letter2value['w' - 'a'] = 6;
    letter2value['x' - 'a'] = 7;
    letter2value['y' - 'a'] = 5;
    letter2value['z' - 'a'] = 7;
}

int n, maxScore;
std::string letters;
std::vector<std::string> dict;
std::vector< std::vector<int> > letterCounts;
std::vector<int> mask2wordIndices[1 << 7];
int mask2score[1 << 7];
std::set<std::string> solutions;

void readDictionary() {
    dict.reserve(40000);
    letterCounts.reserve(40000);

    std::string word;
    std::ifstream fin;
    fin.open("lgame.dict");
    while (fin >> word) {
        if (word == ".") {
            break;
        }
        dict.push_back(word);
        std::vector<int> cnt(26, 0);
        for (char c : word) {
            cnt[c - 'a']++;
        }
        letterCounts.push_back(cnt);
    }
}

void processDictionary() {
    n = (int) letters.size();
    for (int mask = 0; mask < (1 << n); mask++) {
        std::vector<int> curCount(26, 0);
        int curScore = 0;
        for (int i = 0; i < n; i++) {
            if ((mask >> i) & 1) {
                curCount[letters[i] - 'a']++;
                curScore += letter2value[letters[i] - 'a'];
            }
        }
        for (int i = 0; i < (int) dict.size(); i++) {
            if (curCount == letterCounts[i]) {
                mask2wordIndices[mask].push_back(i);
                mask2score[mask] = curScore;
            }
        }
    }
}

void findMaxScore() {
    for (int mask = 0; mask < (1 << n); mask++) {
        if (!mask2wordIndices[mask].empty()) {
            maxScore = std::max(maxScore, mask2score[mask]);
        }
    }
    for (int mask1 = 0; mask1 < (1 << n); mask1++) {
        if (!mask2wordIndices[mask1].empty()) {
            for (int mask2 = mask1 + 1; mask2 < (1 << n); mask2++) {
                if (!mask2wordIndices[mask2].empty() && (mask1 & mask2) == 0) {
                    maxScore = std::max(maxScore, mask2score[mask1] + mask2score[mask2]);
                }
            }
        }
    }
    std::cout << maxScore << std::endl;
}

void findSolutions() {
    if (!maxScore) {
        return;
    }

    for (int mask = 0; mask < (1 << n); mask++) {
        if (!mask2wordIndices[mask].empty() && maxScore == mask2score[mask]) {
            for (int idx : mask2wordIndices[mask]) {
                solutions.insert(dict[idx]);
            }
        }
    }

    for (int mask1 = 0; mask1 < (1 << n); mask1++) {
        if (!mask2wordIndices[mask1].empty()) {
            for (int mask2 = mask1 + 1; mask2 < (1 << n); mask2++) {
                if (!mask2wordIndices[mask2].empty() && (mask1 & mask2) == 0
                        && maxScore == mask2score[mask1] + mask2score[mask2]) {
                    for (int idx1 : mask2wordIndices[mask1]) {
                        for (int idx2 : mask2wordIndices[mask2]) {
                            solutions.insert(std::min(dict[idx1], dict[idx2]) + " "
                                    + std::max(dict[idx1], dict[idx2]));
                        }
                    }
                }
            }
        }
    }

    for (std::string str : solutions) {
        std::cout << str << '\n';
    }
}

int main()
{
    freopen("lgame.in", "r", stdin);
    freopen("lgame.out", "w", stdout);

    setValues();

    std::cin >> letters;
    readDictionary();
    processDictionary();
    findMaxScore();
    findSolutions();

    return 0;
}
