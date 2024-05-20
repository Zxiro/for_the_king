// Singleton<GameManager>::instance()->value;
#ifndef SINGLETON_H
#define SINGLETON_H

template <typename T>
class Singleton {
private:
    Singleton() = default;
    ~Singleton() = default;
public:
    Singleton(Singleton  &&) = delete;
    Singleton(const Singleton  &) = delete;
    void operator = (const Singleton  &) = delete;
    T *operator &() = delete;
    static T& instance()
    {
        static T object;
        return object;
    }
};
#endif