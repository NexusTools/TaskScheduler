#ifndef POOL_H
#define POOL_H

#include <QThread>

class Task;
class TaskPoolData;
class TaskPoolWorker;

namespace TaskScheduler {

class TaskPool : public QThread
{
public:
    explicit TaskPool(quint8 workers =0);
    ~TaskPool();

    inline quint8 workerCount() const{return _workerCount;}
    void scheduleTask(Task*);

protected:
    void run();
    virtual TaskPoolWorker* createWorker();
    virtual TaskPoolData* createData();

private slots:
    void queueWorker(TaskPoolWorker*);
    void queueTask(Task*);

signals:
    void taskProgress(quint64, quint64);
    void tasksComplete();

private:
    static quint8 physicalCoreCount;

    quint8 _workerCount;
    TaskPoolData* data;

};

}

#endif // POOL_H
