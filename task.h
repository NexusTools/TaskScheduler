#ifndef TASK_H
#define TASK_H

#include <QVariant>

namespace TaskScheduler {

class Task : public QObject {
public:
    enum ErrorType {
        UnknownError,
        UncaughtExceptionError,
        ThreadPoolDestroyedError
    };

    virtual void run();

    inline virtual void error(ErrorType=UnknownError, QVariant=QVariant()) {}
    inline virtual void complete(bool=true) {if(destroyOnComplete())deleteLater();}
    inline virtual bool destroyOnComplete() {return true;}

};

}

#endif // TASK_H
