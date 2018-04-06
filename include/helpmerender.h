#ifndef HELPMERENDER_H
#define HELPMERENDER_H

#include <iostream>

struct xyz{
    xyz(int x, int y, int z):x(x=0),y(y=0),z(z=0){}
    int x;
    int y;
    int z;
};

//cout print overload
std::ostream &operator<<(std::ostream &os, const xyz &m){
    return os<<m.x<<", "<<m.y<<", "<<m.z;
}


#endif //HELPMERENDER_H
