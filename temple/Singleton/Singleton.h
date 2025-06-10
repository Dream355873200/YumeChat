//
// Created by 残梦 on 2025/6/3.
//
//单例模板类
#ifndef SINGLETON_H
#define SINGLETON_H
#include <memory>

template <typename T>
class Singleton {
public:
    Singleton(const Singleton&) = delete;
    void operator=(const Singleton&) = delete;

    static std::shared_ptr<T> GetInstance()
    {
        static std::shared_ptr<T> instance(new T());
        return instance;
    }

protected:
    Singleton() = default;
    ~Singleton() = default;
};
#endif //SINGLETON_H
