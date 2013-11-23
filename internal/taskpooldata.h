#ifndef POOLDATA_H
#define POOLDATA_H

#include <QList>

namespace TaskScheduler {

class TaskPoolWorker;
class Task;

class TaskPoolData
{
public:
    QList<TaskPoolWorker*> workers;
    QList<Task*> taskQueue;
};


}

#endif // POOLDATA_H
