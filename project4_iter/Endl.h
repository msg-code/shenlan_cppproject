#ifndef ENDL_H
#define ENDL_H
#include<iostream>
#include<unistd.h>
class Endl
{
private:
    /* data */

public:
};

inline std::ostream& operator<<(std::ostream& out, const Endl&){
    sleep(5);
    out<< std::endl;
    return out;
}
#endif