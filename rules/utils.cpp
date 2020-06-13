
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
}
