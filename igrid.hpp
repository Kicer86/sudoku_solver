
#ifndef IGRID_HPP
#define IGRID_HPP

template<typename T>
class IGrid
{
public:
    virtual ~IGrid() = default;

    virtual int rows() const = 0;
    virtual int columns() const = 0;
    virtual void set(int r, int c, const T& v) = 0;
    virtual const T& get(int r, int c) const = 0;
};

#endif
