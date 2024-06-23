#include "Mediator.h"

int main() {
    ConcreteMediator<std::string> mediator;
    ConcreteComponentA<std::string> compA(&mediator);
    ConcreteComponentB<std::string> compB(&mediator);

    mediator.addComponent(&compA);
    mediator.addComponent(&compB);

    compA.send("Hello from A");
    compB.send("Hello from B");

    return 0;
}

