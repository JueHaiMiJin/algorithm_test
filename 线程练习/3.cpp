#include <semaphore.h>
class H2O
{
protected:
    sem_t H_t;
    sem_t O_t;
    int H_count = 0;

public:
    H2O()
    {
        sem_init(&H_t, 0, 0);
        sem_init(&O_t, 0, 0);
    }

    void hydrogen(function<void()> releaseHydrogen)
    {

        // releaseHydrogen() outputs "H". Do not change or remove this line.
        releaseHydrogen();
    }

    void oxygen(function<void()> releaseOxygen)
    {

        // releaseOxygen() outputs "O". Do not change or remove this line.
        releaseOxygen();
        H_count = 0;
    }
};

class Semaphore
{
private:
    int n_;
    mutex mu_;
    condition_variable cv_;

public:
    Semaphore(int n) : n_{n} {}

public:
    void wait()
    {
        unique_lock<mutex> lock(mu_);
        if (!n_)
        {
            cv_.wait(lock, [this] { return n_; });
        }
        --n_;
    }

    void signal()
    {
        unique_lock<mutex> lock(mu_);
        ++n_;
        cv_.notify_one();
    }
};

class H2O
{
private:
    Semaphore s_hIn, s_oIn;
    Semaphore s_hBarrier, s_oBarrier;

public:
    H2O() : s_hIn{2}, s_oIn{1}, s_hBarrier{0}, s_oBarrier{0} {}

    void hydrogen(function<void()> releaseHydrogen)
    {
        s_hIn.wait();
        s_oBarrier.signal();
        s_hBarrier.wait();
        releaseHydrogen();
        s_hIn.signal();
    }

    void oxygen(function<void()> releaseOxygen)
    {
        s_oIn.wait();
        s_oBarrier.wait();
        s_oBarrier.wait();
        s_hBarrier.signal();
        s_hBarrier.signal();
        releaseOxygen();
        s_oIn.signal();
    }
};

#include <semaphore.h>
class H2O
{
protected:
    int h_count = 0;
    int o_count = 0;
    mutex mu_;
    condition_variable cv_;

public:
    H2O() {}

    void hydrogen(function<void()> releaseHydrogen)
    {
        unique_lock<mutex> lock(mu_);
        cv_.wait(lock, [this] { return h_count < 2; });
        releaseHydrogen();
        h_count++;
        if (h_count + o_count == 3)
        {
            h_count = 0;
            o_count = 0;
        }
        cv_.notify_all();
    }

    void oxygen(function<void()> releaseOxygen)
    {
        unique_lock<mutex> lock(mu_);
        cv_.wait(lock, [this] { return o_count < 1; });
        releaseOxygen();
        o_count++;
        if (h_count + o_count == 3)
        {
            h_count = 0;
            o_count = 0;
        }
        cv_.notify_all();
    }
};