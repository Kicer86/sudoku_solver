
#ifndef IGRID_HPP
#define IGRID_HPP

template<typename T>
class IGrid
{
public:
    virtual ~IGrid() = default;

    virtual void set(int r, int c, const T& v) = 0;
    virtual const T& get(int r, int c) const = 0;
};

#endif
