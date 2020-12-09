#include "test.h"

int TaskTest::runTest(int a, int b) {
    std::cout << "execute runTest:\n arguments: " << a <<" * "<< b <<" = ";
    return a*b;
}

std::string MyTest::fullName(std::string name, std::string secondName) {
    std::string full = name + " " + secondName;
    return full;
}

std::string MyTest::personInfo(std::string name, std::string date, std::string age) {
    std::string full = "Name: " + name + "\n" + "Date of Birth: " +date + "\n" +"Age: " + age;
    return full;
}

int MyTest::calcAge(int yearBegin, int yearCurrent) {
    return (yearCurrent-yearBegin);
}
