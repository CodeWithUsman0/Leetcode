#include <string>
#include <iostream>

class Solution {
public:
    void trim2(std::string &str) {
        std::string trim_chars = " ";
        std::string::size_type pos = str.find_last_not_of(trim_chars);
        if (pos != std::string::npos) {
            str.erase(pos + 1);
            pos = str.find_first_not_of(trim_chars);
            if (pos != std::string::npos) {
                str.erase(0, pos);
            }
        } else {
            str.erase(str.begin(), str.end());
        }
    }

    bool isNumber(std::string s) {
        this->trim2(s);

        if (s.empty()) {
            return false;
        }

        bool hadN = false;
        bool hadE = false;
        bool hadDot = false;
        bool hadSign = false;

        for (auto c : s) {
            if (c == ' ') {
                return false;
            } else if (c == '-' || c == '+') {
                if (hadSign || hadN || hadDot) {
                    return false;
                }

                hadSign = true;
            } else if (std::isdigit(c)) {
                hadN = true;
            } else if (c == '.') {
                if (hadDot || hadE) {
                    return false;
                }

                hadDot = true;
            } else if (c == 'e') {
                if (hadE || !hadN) {
                    return false;
                }

                hadN = false;
                hadSign = false;
                hadDot = false;
                hadE = true;
            } else {
                return false;
            }
        }

        char lastC = s.back();
        if (lastC == 'e' || lastC == '-' || lastC == '+' || (!hadN && lastC == '.')) {
            return false;
        }

        return true;
    }
};

#define assert(s, e) if(solution.isNumber(s) != e) { std::cout << #s << " should return " << e << "\n"; } else { std::cout << "ok\n"; }

int main() {
    auto solution = Solution();

    assert("0", true);
    assert("", false);
    assert(" ", false);
    assert(".", false);
    assert(" 0.1 ", true);
    assert("abc", false);
    assert("1 a", false);
    assert("2e10", true);
    assert(" -90e3   ", true);
    assert(" 1e", false);
    assert("e3", false);
    assert(" 6e-1", true);
    assert(" 99e2.5 ", false);
    assert("53.5e93", true);
    assert(" --6 ", false);
    assert("-+3", false);
    assert("95a54e53", false);
    assert("3.", true);
    assert(".-4", false);
    assert("+.8", true);

    std::cout << "Done !";
}
