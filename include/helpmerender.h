#ifndef HELPMERENDER_H
#define HELPMERENDER_H

#include <iostream>

#define TO_C_ARRAY(__TRIANGLE__) {__TRIANGLE__.v1.x,__TRIANGLE__.v1.y,__TRIANGLE__.v1.z,\
                                __TRIANGLE__.v2.x,__TRIANGLE__.v2.y,__TRIANGLE__.v2.z,\
                                __TRIANGLE__.v3.x,__TRIANGLE__.v3.y,__TRIANGLE__.v3.z}


struct xyz{
    xyz(float x=0, float y=0, float z=0):x(x),y(y),z(z){}
    void operator()(float _x, float _y, float _z){x=_x;y=_y;z=_z;}
    float x,y,z;
};
//cout print overload
std::ostream &operator<<(std::ostream &os, const xyz &m){
    return os<<m.x<<", "<<m.y<<", "<<m.z;
}

struct triangle{
    triangle(){}
    triangle(xyz v1, xyz v2, xyz v3):v1(v1),v2(v2),v3(v3){}
    void operator()(xyz _v1, xyz _v2, xyz _v3){v1=_v1;v2=_v2;v3=_v3;}
    xyz v1,v2,v3;
};
//cout print overload
std::ostream &operator<<(std::ostream &os, const triangle &m){
    return os<<'{'<<m.v1<<"}, {"<<m.v2<<"}, {"<<m.v3<<'}';
}

#endif //HELPMERENDER_H
