//
// Created by shivan on 8/10/24.
//

#ifndef CRTP_H
#define CRTP_H

template <template <typename, typename...> class Base, typename Derived, typename... Args>
struct CRTP {
private:
    // Private constructor to prevent direct instantiation
    CRTP() = default;
    friend Base<Derived, Args...>; // Allow only the correct instantiation of Base

public:
    // Deleted copy and move constructors to further enforce correct usage
    // Deleting these functions prevents accidental copying or moving of the CRTPBase object,
    // which reinforces the idea that CRTP base struct should only be used in the
    // context of inheritance and not as a standalone object.
    CRTP(const CRTP&) = delete;
    CRTP(CRTP&&) = delete;
    CRTP& operator=(const CRTP&) = delete;
    CRTP& operator=(CRTP&&) = delete;

    Derived& derived() {
        return static_cast<Derived&>(*this);
    }

    const Derived& derived() const {
        return static_cast<const Derived&>(*this);
    }
};
#endif //CRTP_H
