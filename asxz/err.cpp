void err(){
    std::cout<<"Err"<<std::endl;
}

template<template<typename...> class T, typename t, typename... A>
void err(T<t> a, A... x){
    for (auto v:a){
        std::cout<<v<<" ";
    }
    err(x...);
}

template<typename T, typename... A>
void err(T a, A... x){
    std::cout<<a<<" ";
    err(x...);
}
