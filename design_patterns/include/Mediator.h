#ifndef MEDIATOR_H
#define MEDIATOR_H

#include <vector>
#include <iostream>

// Forward declaration of the Component template class
template<typename T>
class Component;

// Mediator interface
template<typename T>
class Mediator {
public:
    virtual void send(T message, Component<T>* sender) = 0;
    virtual ~Mediator() {}
};

// Component base class
template<typename T>
class Component {
protected:
    Mediator<T>* mediator;
public:
    explicit Component(Mediator<T>* mediator) : mediator(mediator) {}
    virtual void send(T message) {
        mediator->send(message, this);
    }
    virtual void receive(T message) = 0;
    virtual ~Component() {}
};

// Concrete Mediator
template<typename T>
class ConcreteMediator : public Mediator<T> {
private:
    std::vector<Component<T>*> components;
public:
    void addComponent(Component<T>* component) {
        components.push_back(component);
    }
    void send(T message, Component<T>* sender) override {
        for (auto comp : components) {
            if (comp != sender) {
                comp->receive(message);
            }
        }
    }
};

// Concrete Component A
template<typename T>
class ConcreteComponentA : public Component<T> {
public:
    using Component<T>::Component; // Inherit constructor
    void receive(T message) override {
        std::cout << "Component A received: " << message << std::endl;
    }
};

// Concrete Component B
template<typename T>
class ConcreteComponentB : public Component<T> {
public:
    using Component<T>::Component; // Inherit constructor
    void receive(T message) override {
        std::cout << "Component B received: " << message << std::endl;
    }
};

#endif // MEDIATOR_H

