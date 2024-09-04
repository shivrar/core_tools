#pragma once
#include <memory>
#include <mutex>

// Singleton class template
template <typename T, typename... Args>
class Singleton {
public:
    static T& getInstance(Args... args) {
        std::call_once(initFlag, [&] {
            instance.reset(new T(std::forward<Args>(args)...));
        });
        return *instance;
    }

    // Delete copy constructor and assignment operator
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;

protected:
    Singleton() = default;
    virtual ~Singleton() = default;

private:
    static std::unique_ptr<T> instance;
    static std::once_flag initFlag;
};

template <typename T, typename... Args>
std::unique_ptr<T> Singleton<T, Args...>::instance = nullptr;

template <typename T, typename... Args>
std::once_flag Singleton<T, Args...>::initFlag;
