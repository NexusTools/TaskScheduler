#include <unistd.h>

#include <QEventLoop>
#include <QDebug>

#include "internal/taskpooldata.h"
#include "taskpoolworker.h"
#include "taskpool.h"
#include "task.h"

namespace TaskScheduler {

TaskPool::TaskPool(quint8 workers) {
    if(workers < 1)
        workers = physicalCoreCount > 1 ? physicalCoreCount : 1;

    _workerCount = workers;
    metaObject()->invokeMethod(this, "start", Qt::QueuedConnection);
}

void TaskPool::run() {
    data = createData();

    for(quint8 i = 0; i < _workerCount; i++) {
        TaskPoolWorker* worker = createWorker();
        data->workers.append(worker);
        queueWorker(worker);
    }

    QThread::run();

    // Cleanup remaining tasks
    foreach(Task* task, data->taskQueue) {
        task->error(Task::ThreadPoolDestroyedError);
        task->complete(false);
    }

    foreach(TaskPoolWorker* worker, data->workers)
        ((QThread*)worker)->quit();

    foreach(TaskPoolWorker* worker, data->workers) {
        ((QThread*)worker)->wait();
        ((QThread*)worker)->deleteLater();
    }

    delete data;
}

TaskPool::~TaskPool() {
    if(isRunning()) {
        QEventLoop eLoop;
        connect(this, SIGNAL(finished()), &eLoop, SLOT(quit()));
        quit();

        while(isRunning())
            eLoop.processEvents(QEventLoop::WaitForMoreEvents);
    }

}

TaskPoolWorker* TaskPool::createWorker() {
    return new TaskPoolWorker();
}

TaskPoolData* TaskPool::createData() {
    return new TaskPoolData();
}

quint8 detectSystemThreadCount() {
#ifdef Q_OS_LINUX
    return sysconf( _SC_NPROCESSORS_ONLN );
//#elif defined(Q_OS_MAC) || defined(Q_OS_BSD)
//
#elif defined(Q_OS_WIN)
    SYSTEM_INFO sysinfo;
    GetSystemInfo( &sysinfo );

    return sysinfo.dwNumberOfProcessors;
#else
    return 0;
#endif
}

quint8 TaskPool::physicalCoreCount = detectSystemThreadCount();


}
