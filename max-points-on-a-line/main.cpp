struct Point {
    int x;
    int y;

    Point() : x(0), y(0) {}

    Point(int a, int b) : x(a), y(b) {}
};

#include <vector>
#include <string>
#include <map>
#include <iostream>
#include <sstream>
#include <algorithm>

/**
 * Definition for a point.
 * struct Point {
 *     int x;
 *     int y;
 *     Point() : x(0), y(0) {}
 *     Point(int a, int b) : x(a), y(b) {}
 * };
 */
class Solution {
public:
    int maxPoints(std::vector<Point> points) {
        int n = points.size();

        if(n <= 2) {
            return n;
        }

        auto max = 0;

        auto pairs = std::map<std::pair<int, int>, int>();

        for (int i = 0; i < n; ++i) {
            auto verticals = 0;
            auto overlapping = 0;
            auto lmax = 0;

            auto p1 = points[i];

            for (int j = i + 1; j < n; ++j) {
                auto p2 = points[j];

                if(p2.x == p1.x) {
                    if(p2.y == p1.y) {
                        overlapping++;
                    } else {
                        verticals++;
                    }
                } else {
                    auto xd = p1.x - p2.x;
                    auto yd = p1.y - p2.y;

                    auto gcd = std::__gcd(xd, yd);

                    xd /= gcd;
                    yd /= gcd;

                    auto p = std::pair<int, int>(xd, yd);

                    if(pairs.find(p) == pairs.end()) {
                        pairs.emplace(p, 0);
                    }

                    pairs[p]++;

                }
            }

            for (auto const &[k, v] : pairs) {
                lmax = std::max(lmax, v);
            }

            lmax = std::max(lmax, verticals);
            max = std::max(max, lmax + overlapping + 1);

            pairs.clear();
        }

        return max;
    }
};

#define assert(e, ...) {auto r = solution.maxPoints(parse(__VA_ARGS__)); if(r != e) { std::cout << #__VA_ARGS__ << " expects " << #e << " got " << r << "\n"; } else { std::cout << "ok\n"; }}

std::vector<Point> parse(std::vector<std::vector<int>> in) {
    auto points = std::vector<Point>();

    for(auto p : in) {
        points.emplace_back(p[0], p[1]);
    }

    return points;
}


int main() {
    auto solution = Solution();

    assert(3, {{1,1},{2,2},{3,3}})
    assert(3, {{1,1},{1,1},{2,3}})
    assert(4, {{1,1},{3,2},{5,3},{4,1},{2,3},{1,4}})
    assert(6, {{84,250},{0,0},{1,0},{0,-70},{0,-70},{1,-1},{21,10},{42,90},{-42,-230}})
    assert(3, {{4,0},{4,-1},{4,5}})

    std::cout << "done";
}
