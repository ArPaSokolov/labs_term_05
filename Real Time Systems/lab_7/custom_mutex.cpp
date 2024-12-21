#include "custom_mutex.h"

CustomMutex::CustomMutex() {
    semaphore = CreateSemaphore(NULL, 1, 1, NULL); // создание семафора
}

void CustomMutex::lock() {
    WaitForSingleObject(semaphore, INFINITE); // ожидание семафора
}

void CustomMutex::unlock() {
    ReleaseSemaphore(semaphore, 1, NULL); // освобождение семафора
}

CustomMutex::~CustomMutex() {
    CloseHandle(semaphore); // закрытие семафора
}
