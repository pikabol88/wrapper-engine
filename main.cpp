#include <iostream>
#include "wrapper_engine.h"
#include "test.h"


int main() {
    TaskTest taskTest;
    Wrapper<int> wrapper(&taskTest, &TaskTest::runTest, { {"arg1", 0}, {"arg2", 0} });
    Engine engine;
    engine.registerCommand<int>(&wrapper, "command1");
    std::cout << engine.execute<int>("command1", { {"arg1", 2}, {"arg2", 10} }) << std::endl;



    std::cout<<"\nTesting different types supporting by filling person info:"<<std::endl;
    MyTest test;
    Wrapper<std::string> name_wrapper(&test, &MyTest::fullName, {{"name", ""}, {"surname", ""} });
    Wrapper<std::string> info_wrapper(&test, &MyTest::personInfo, {{"name", ""}, {"dateOfBirth", ""}, {"age", ""} });
    Wrapper<int> age_wrapper(&test, &MyTest::calcAge, {{"name", 0}, {"dateOfBirth", 0} } );

    Engine engine_pers;
    engine_pers.registerCommand<std::string>(&name_wrapper, "command1");
    engine_pers.registerCommand(&info_wrapper, "command2");
    engine_pers.registerCommand(&age_wrapper, "command3");

    auto fullName = engine_pers.execute<std::string>("command1", { {"name", "Ivan"}, {"surname", "Ivanov"} });
    auto age =  engine_pers.execute<int>("command3", {{"name", 1999}, {"dateOfBirth", 2020} }) ;
    std::cout << engine_pers.execute<std::string>("command2", { {"name", fullName}, {"dateOfBirth", "19.19.1999"}, {"age", std::to_string(age)} }) << std::endl;
}