#ifndef PARAMETERSYSTEM
#define PARAMETERSYSTEM
#include "Parameters.h"

template<typename T>
void setParameter(T& paramType, float value) {
    paramType.set(value);
}

template<typename T>
auto getParameter(T& paramType){
    return paramType.get();
}


#endif