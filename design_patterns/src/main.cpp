#include "Mediator.h"
#include "Singleton.h"

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

    return 0;
}

