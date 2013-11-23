#ifndef TASKPOOLWORKER_H
#define TASKPOOLWORKER_H

#include <QThread>

namespace TaskScheduler {

class TaskPool;
class Task;

class TaskPoolWorker : public QThread
{
    friend class TaskPool;
public:
    explicit TaskPoolWorker();

private slots:
    void runTask(Task*);

signals:
    void finishedTask(TaskPoolWorker*);

private:
};

}

#endif // TASKPOOLWORKER_H
