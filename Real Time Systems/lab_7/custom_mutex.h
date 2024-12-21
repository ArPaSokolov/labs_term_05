#ifndef CUSTOM_MUTEX_H
#define CUSTOM_MUTEX_H

#include <Windows.h>

class CustomMutex {
public:
    CustomMutex();
    void lock();
    void unlock();
    ~CustomMutex();

private:
    HANDLE semaphore;
};

#endif // CUSTOM_MUTEX_H