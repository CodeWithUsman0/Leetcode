//
// Created by Usman Zahid  on 3/12/23.
//

#include <string>
#include <vector>
#include <map>
#include <iostream>

class Solution
{
public:
    int lengthLongestPath(std::string input)
    {
        std::map<short, int> counts;

        short level = 0;
        short maxLevel = 0;
        short currentNodeLength = 0;
        int max = 0;
        bool isFile = false;

        for (char &c : input)
        {
            bool isLast = &c == &input.back();

            if (isLast)
            {
                currentNodeLength++;
            }

            if (c == '\n' || isLast)
            {
                int fullLength = currentNodeLength;

                if (level > 0)
                {
                    auto p = counts[level - 1];
                    fullLength += p + 1;
                }

                for (short i = level; i <= maxLevel; ++i)
                {
                    counts.erase(i);
                }

                counts[level] = fullLength;

                if (isFile && fullLength > max)
                {
                    max = fullLength;
                }

                level = 0;
                currentNodeLength = 0;
                isFile = false;
            }
            else if (c == '\t')
            {
                level++;
                if (level > maxLevel)
                {
                    maxLevel = level;
                }
            }
            else
            {
                currentNodeLength++;
                if (c == '.')
                {
                    isFile = true;
                }
            }
        }

        return max;
    }
};

int main()
{
    auto result = Solution().lengthLongestPath(
        //            "dir\n\tsubdir1\n\t\tfile1.ext\n\t\tsubsubdir1\n\tsubdir2\n\t\tsubsubdir2\n\t\t\tfile2.ext"
        //            "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext"
        //            "dir\n\t        file.txt\n\tfile2.txt"
        "dir\n\tsubdir1\n\tsubdir2\n\t\tfile.ext");

    std::cout << result;

    return 0;
}