#include "CUThread.h"

CUThread::CUThread()
    :tid_(0),isRuning_(false)
{ }

CUThread::~CUThread()
{
    if(isRuning_)
    {
        pthread_detach(tid_);
    }
}

void *CUThread::runInThread (void *arg)
{
    CUThread *pt = static_cast<CUThread*>(arg);
    pt->run();
    return NULL;
}

void CUThread::start()
{
    pthread_create(&tid_, NULL, CUThread::runInThread,this);
    isRuning_ =true;
}

void CUThread::join()
{
    //assert(isRuning_);
    pthread_join(tid_,NULL);
    isRuning_ = false;
}
pthread_t CUThread::get_tid() const
{
    return this->tid_;
}
bool CUThread::getIsRunning() const
{
    return this->isRuning_;
}

