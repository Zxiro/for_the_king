// Singleton<GameManager>::instance()->value;

template <typename T>
class Singleton {
    Singleton() = default;
    ~Singleton() = default;
public:
    Singleton(Singleton  &&) = delete;
    Singleton(const Singleton  &) = delete;
    void operator = (const Singleton  &) = delete;
    T *operator &() = delete;
    static T* instance()
    {
        static T object;
        return &object;
    }
};