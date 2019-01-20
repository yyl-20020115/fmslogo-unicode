#ifndef __CUTHREAD_H__
#define __CUTHREAD_H__

#include <pthread.h>
#include <sys/types.h>

class CUThread
{
public:
    CUThread();
    ~CUThread();
public:
    void start();
    void join();
    virtual void run()= 0;
    bool getIsRunning() const;
    pthread_t get_tid() const;

private:
    static void *runInThread (void *);
    pthread_t  tid_;
    bool isRuning_;
};


#endif
