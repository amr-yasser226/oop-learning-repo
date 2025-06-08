# Abstract Base Classes in C++

An **Abstract Base Class (ABC)** in C++ is a class that cannot be instantiated on its own and serves as a blueprint for derived classes. ABCs define **pure virtual functions** that must be implemented by any concrete subclass. This enforces a consistent interface across related classes.

---

## Table of Contents

1. [Overview of Abstract Base Classes](#overview-of-abstract-base-classes)
2. [Key Components: Pure Virtual Functions](#key-components-pure-virtual-functions)
3. [Defining an Abstract Base Class](#defining-an-abstract-base-class)
4. [Implementing Concrete Subclasses](#implementing-concrete-subclasses)
5. [Example Code](#example-code)
6. [Example Output](#example-output)
7. [Summary](#summary)

---

## Overview of Abstract Base Classes

* An **Abstract Base Class** cannot be instantiated directly because it contains at least one **pure virtual function**.
* Pure virtual functions declare an interface without providing an implementation.
* Any subclass must override all pure virtual functions before it becomes a concrete class that can be instantiated.
* ABCs ensure a uniform interface for a family of related classes.

---

## Key Components: Pure Virtual Functions

1. **Pure Virtual Function**

   * Declared by assigning `= 0` in the member function declaration.
   * Example: `virtual void doSomething() = 0;`
   * Makes the class abstract.
2. **Abstract Class**

   * A class with one or more pure virtual functions.
   * Cannot be instantiated directly.
3. **Concrete Subclass**

   * A derived class that overrides all inherited pure virtual functions.
   * Can be instantiated.

---

## Defining an Abstract Base Class

```cpp
#include <iostream>

class Programming {
public:
    // Pure virtual function: must be implemented by subclasses
    virtual bool hasOOP() const = 0;

    // Virtual destructor for proper cleanup of derived objects
    virtual ~Programming() = default;
};
```

* `Programming` is abstract because `hasOOP()` is declared `= 0`.
* The virtual destructor ensures derived destructors run correctly.

---

## Implementing Concrete Subclasses

### Subclass: Python

```cpp
#include <iostream>
#include <string>

class Python : public Programming {
public:
    bool hasOOP() const override {
        return true;
    }
};
```

* `Python` overrides `hasOOP()` and returns `true`.
* `Python` can be instantiated because it implements the pure virtual function.

### Subclass: Pascal

```cpp
#include <iostream>
#include <string>

class Pascal : public Programming {
public:
    bool hasOOP() const override {
        // No meaningful return; still counts as implementation
        return false;
    }
};
```

* `Pascal` also overrides `hasOOP()`, returning `false`.
* Even a trivial implementation makes `Pascal` concrete.

---

## Example Code

```cpp
#include <iostream>

int main() {
    // Programming prog;                // Error: cannot instantiate abstract class

    Pascal pascal;
    Python python;

    std::cout << std::boolalpha;
    std::cout << "Pascal supports OOP? " << pascal.hasOOP() << std::endl;
    std::cout << "Python supports OOP? " << python.hasOOP() << std::endl;

    return 0;
}
```

* Attempting to instantiate `Programming` directly causes a compilation error.
* `pascal.hasOOP()` prints `false`, and `python.hasOOP()` prints `true`.

---

## Example Output

```text
Pascal supports OOP? false
Python supports OOP? true
```

1. **`false`** comes from `pascal.hasOOP()`.
2. **`true`** comes from `python.hasOOP()`.

---

## Summary

* **Abstract Base Classes** in C++ define interfaces via pure virtual functions (methods declared with `= 0`).
* A class with at least one pure virtual function cannot be instantiated.
* **Concrete subclasses** must override all pure virtual functions to become instantiable.
* Virtual destructors in ABCs ensure proper resource cleanup when deleting derived objects via base pointers.

By using ABCs, you design clear, enforceable interfaces for related classes, ensuring consistency and preventing incomplete implementations.
