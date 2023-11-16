#pragma once
#include <mutex>
template <typename T>
class mutexObj
{
private:
    std::mutex objMutex;
    
public:  
    T obj;

    void lock() { objMutex.lock(); };
    void unlock() { objMutex.unlock(); };
    T& get() { return obj };

    mutexObj& operator = (const mutexObj& a1);
    T& operator = (const T& a1);
};

mutexObj& mutexObj::operator = (const mutexObj& a1) {}