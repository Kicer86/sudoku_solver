
#ifndef IRULE_HPP
#define IRULE_HPP

#include <vector>

class IRule
{
public:
    virtual ~IRule() = default;

    virtual std::vector<int> validNumbers(int row, int col) const = 0;
};

#endif
