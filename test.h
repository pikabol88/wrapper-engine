#ifndef TEST_H
#define TEST_H
#include <iostream>

class TaskTest {
public:
    int runTest( int a, int b);;
};


class MyTest {
public:
    std::string fullName( std::string name, std::string secondName);

    std::string personInfo( std::string name, std::string date, std::string age);

    int calcAge(int yearBegin, int yearCurrent);
};
#endif //TEST_H
