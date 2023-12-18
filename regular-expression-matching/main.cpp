//
// Created by Usman Zahid on 26/06/23.
//

#include <string>
#include <iostream>

#define isMatchP(s, p) (s && p && (p == '.' || s == p))

class Solution {
public:
    bool isMatch(std::string s, std::string p) {
        unsigned short sc = 0;
        unsigned short pc = 0;
        char starChar = false;
        char lastStarChar = false;

        if (p.empty()) {
            return s.empty();
        }

        auto mpc = p.size() - 1;
        auto sEmpty = s.empty();
        auto msc = sEmpty ? 0 : s.size() - 1;

        while (true) {
            char schar = (sc > msc || sEmpty) ? false : s[sc];
            char cpchar = pc > mpc ? false : p[pc];
            char pchar = starChar ? starChar : cpchar;

            if (!schar && !pchar) {
                return true;
            }

            if (!starChar && pc < mpc && p[pc + 1] == '*') {
                starChar = pchar;
                pc += 2;

                continue;
            }

            auto match = isMatchP(schar, pchar);

            if (starChar && match && isMatch(s.substr(sc), p.substr(pc))) {
                return true;
            } else if (match) {
                sc++;

                if (!starChar) {
                    pc++;
                    lastStarChar = false;
                } else {
                    lastStarChar = pchar;
                }
            } else if (starChar || isMatchP(schar, lastStarChar)) {
                starChar = false;
            } else {
                return false;
            }
        }
    }
};

#define assert(s, p, e) if(solution.isMatch(s, p) != e) { std::cout << #s << " match " #p << " should return " << e << "\n"; } else { std::cout << "ok\n"; }

int main() {
    auto solution = Solution();

    assert("aa", "a", false);
    assert("aaa", "aaaa", false);
    assert("aa", "a*", true);
    assert("aaa", "a*a", true);
    assert("a", "a*a", true);
    assert("ab", ".*", true);
    assert("aab", "c*a*b", true);
    assert("mississippi", "mis*is*ip*.", true);
    assert("ab", ".*c", false);
    assert("cccaaacaccabaab", "a*c*c*b*b*b*b*a*c", false);
    assert("aaa", "ab*a*c*a", true);
    assert("bbbba", ".*a*a", true);
    assert("ab", ".*..", true);
    assert("a", ".*..a", false);
    assert("a", ".*..a*", false);
    assert("", ".*", true);
    assert("bbba", ".*b", false);
    assert("abcdede", "ab.*de", true);
    assert("aasdfasdfasdfasdfas", "aasdf.*asdf.*asdf.*asdf.*s", true);
    assert("bccbbabcaccacbcacaa", ".*b.*c*.*.*.c*a*.c", false);
    assert("abbaaaabaabbcba", "a*.*ba.*c*..a*.a*.", true);

    std::cout << "Done !";
}
