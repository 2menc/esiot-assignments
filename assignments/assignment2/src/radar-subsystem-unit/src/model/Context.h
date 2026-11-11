#ifndef __CTX__
#define __CTX__

class Context {
private:
    bool started;
    bool stopped;

public:
    Context();

    void setStarted();
    void setStopped();

    bool isStarted();
    bool isStopped();
    void reset();
};

#endif