#include "Mediator.h"
#include "Singleton.h"
#include "CRTP.h"

// Example class to be managed by the singleton
class Example
{
public:
    Example(int a, double b) : a_(a), b_(b) {}

    void Display() const
    {
        std::cout << "Example instance with a = " << a_ << " and b = " << b_ << std::endl;
    }

private:
    int a_;
    double b_;
};

template <typename Derived>
class BaseClass : public CRTP<BaseClass, Derived> {
public:
    void DoSomethingImpl() {
        this->derived().DoSomething();
    }

    BaseClass() = default;
    virtual ~BaseClass() = default;
    virtual void DoSomething() = 0;
};

class Derived1 : public BaseClass<Derived1> {
public:
    Derived1() = default;
private:
    void DoSomething() override {
        std::cout << "Derived1 class" << std::endl;
    };
    friend class BaseClass<Derived1>;
};

class Derived2 : public BaseClass<Derived2> {
public:
    void DoSomething() override {
        std::cout << "Derived2 class" << std::endl;
    };
};

class Derived3 : public BaseClass<Derived3> {
public:
    void DoSomething() override {
        std::cout << "Derived3 class" << std::endl;
    }
};


int main() {
    ConcreteMediator<std::string> mediator;
    ConcreteComponentA<std::string> compA(&mediator);
    ConcreteComponentB<std::string> compB(&mediator);

    mediator.addComponent(&compA);
    mediator.addComponent(&compB);

    compA.send("Hello from A");
    compB.send("Hello from B");

    // Get the singleton instance of std::vector<int>
    auto& vec = Singleton<std::vector<int>>::getInstance();

    // Add some values to the vector
    vec.push_back(1);
    vec.push_back(2);
    vec.push_back(3);

    // Print the values in the vector
    for (const auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    // Ensure that we get the same instance
    auto& sameVec = Singleton<std::vector<int>>::getInstance();
    sameVec.push_back(4);

    // Print the values again to confirm it's the same instance
    for (const auto& value : vec) {
        std::cout << value << " ";
    }
    std::cout << std::endl;

    Derived1 obj1;
    Derived2 obj2;
    Derived3 obj3;
    obj1.DoSomethingImpl(); // Calls Derived1's DoSomething
    obj2.DoSomethingImpl(); // Calls Derived2's DoSomething
    obj3.DoSomethingImpl(); // Calls Derived3's DoSomething
    return 0;
}

