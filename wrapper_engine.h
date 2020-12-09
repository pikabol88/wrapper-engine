#ifndef UNTITLED1_WRAPPER_ENGINE_H
#define UNTITLED1_WRAPPER_ENGINE_H

#include <iostream>
#include <functional>
#include <map>
#include <vector>

template <class Type>
class Wrapper {

    typedef struct arguments {
        std::vector<std::string> name;
        std::vector<Type> value;
    }arguments_t;

    arguments_t arguments;
    std::function<Type(const std::vector<Type>& argsList)> f;

public:
    template<typename Subject, class... Args>
    [[maybe_unused]] Wrapper(Subject *subj, Type(Subject::*fun)(Args...), const std::vector<std::pair<std::string, Type>> argsList) {
        parseArguments(argsList);
        initializeFun(subj,fun);
    }

    Type execute(const std::map<std::string, Type> &argsMap) {
        std::vector<Type> argsList;
        for (auto &el : arguments.name) {
            argsList.push_back(argsMap.find(el)->second);
        }
        return f(argsList);
    }

private:
    void parseArguments(const std::vector<std::pair<std::string, Type>> argsList){
        for (auto& el : argsList) {
            arguments.name.push_back(el.first);
            arguments.value.push_back(el.second);
        }
    }
    template<typename Subject, class... Args>
    void initializeFun(Subject *subj, Type(Subject::*fun)(Args...)){
        f = [this, subj, fun](const std::vector<Type>& argsForFun) {
            return myFun(subj, fun, argsForFun, std::make_index_sequence<sizeof...(Args)>{});
        };
    }
    template<typename Subject, typename Name, size_t... Indexis>
    Type myFun(Subject* subj, Name functionName, const std::vector<Type>& argsList, std::index_sequence<Indexis...>) {
        return ((subj->*functionName)(argsList[Indexis]...));
    }
};

class Engine {
private:
    std::map<std::string,void*> functions;
public:
    template<typename Type>
    void registerCommand(Wrapper<Type> *wrapper, std::string functionName) {
        if (functions.find(functionName) != functions.end())  return;
        functions[functionName] = wrapper;
    }
    template<typename Type>
    Type execute(std::string name, const std::map<std::string, Type> &argsMap) {
        auto el = functions.find(name);
        if (el == functions.end())
            return 0;
        Wrapper<Type> *myWrapper = static_cast<Wrapper<Type>*>((el)->second);
        return (myWrapper->execute(argsMap));
    }
};

#endif //UNTITLED1_WRAPPER_ENGINE_H
