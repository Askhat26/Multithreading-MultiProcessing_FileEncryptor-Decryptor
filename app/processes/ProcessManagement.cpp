#include <iostream>
#include <queue>
#include <memory>
#include <cstring>
#include <thread>
#include <vector>
#include <condition_variable>
#include <unistd.h>
#include "ProcessManagement.hpp"
#include "../encryptDecrypt/Cryption.hpp"
#include <sys/fcntl.h>
#include <sys/mman.h>
#include <atomic>

class ProcessManagement {
private:
    static constexpr size_t MAX_QUEUE_SIZE = 1000;
    static constexpr size_t THREAD_POOL_SIZE = 2;
    
    struct SharedMemory {
        char tasks[MAX_QUEUE_SIZE][256];
        std::atomic<int> front{0};
        std::atomic<int> rear{0};
        std::atomic<int> size{0};
    };

    int shmFd;
    SharedMemory* sharedMem;
    std::mutex queueLock;
    std::condition_variable cv;
    std::vector<std::thread> threadPool;
    std::atomic<bool> running{true};
    
    static constexpr const char* SHM_NAME = "/task_queue";

    void workerThread() {
        while (running) {
            char taskStr[256];
            {
                std::unique_lock<std::mutex> lock(queueLock);
                // Wait if queue is empty
                cv.wait(lock, [this]() { 
                    return sharedMem->size > 0 || !running; 
                });
                
                if (!running && sharedMem->size == 0) return;

                strcpy(taskStr, sharedMem->tasks[sharedMem->front]);
                sharedMem->front = (sharedMem->front + 1) % MAX_QUEUE_SIZE;
                sharedMem->size.fetch_sub(1);
            }
            cv.notify_all();
            executeCryption(taskStr);
        }
    }

public:
    ProcessManagement() {
        // Initialize shared memory
        shmFd = shm_open(SHM_NAME, O_CREAT | O_RDWR, 0666);
        ftruncate(shmFd, sizeof(SharedMemory));
        sharedMem = static_cast<SharedMemory*>(
            mmap(nullptr, sizeof(SharedMemory), 
                 PROT_READ | PROT_WRITE, MAP_SHARED, shmFd, 0)
        );
        
        // Initialize thread pool
        for (size_t i = 0; i < THREAD_POOL_SIZE; ++i) {
            threadPool.emplace_back(&ProcessManagement::workerThread, this);
        }
    }

    ~ProcessManagement() {
        // Cleanup
        running = false;
        cv.notify_all();
        
        for (auto& thread : threadPool) {
            if (thread.joinable()) {
                thread.join();
            }
        }
        
        munmap(sharedMem, sizeof(SharedMemory));
        shm_unlink(SHM_NAME);
        close(shmFd);
    }

    bool submitToQueue(std::unique_ptr<Task> task) {
        std::unique_lock<std::mutex> lock(queueLock);
        
        if (sharedMem->size >= MAX_QUEUE_SIZE) {
            return false;
        }

        strcpy(sharedMem->tasks[sharedMem->rear], task->toString().c_str());
        sharedMem->rear = (sharedMem->rear + 1) % MAX_QUEUE_SIZE;
        sharedMem->size.fetch_add(1);
        
        lock.unlock();
        cv.notify_one();
        return true;
    }

    
};
