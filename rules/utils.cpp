
#include <algorithm>

#include "utils.hpp"


namespace utils
{
    std::vector<int> fill(int max)
    {
        std::vector<int> r;

        for(int i = 0; i < max; i++)
            r.push_back(i + 1);

        return r;
    }

    void erase(std::vector<int>& v, int value)
    {
        const auto last = std::remove(v.begin(), v.end(), value);
        v.erase(last, v.end());
    }
}
