# Inheritance in C++

Inheritance allows us to define a class (the **derived** or **child** class) that inherits member variables and member functions from another class (the **base** or **parent** class). This fundamental OOP concept promotes code reuse and hierarchical relationships.

---

## Table of Contents

1. [Overview of Inheritance](#overview-of-inheritance)
2. [Single Inheritance Example](#single-inheritance-example)

   * [Base Class: `Food`](#base-class-food)
   * [Derived Class: `Apple`](#derived-class-apple)
   * [How `Base` Constructor Is Called](#how-base-constructor-is-called)
3. [Method Overriding](#method-overriding)
4. [Multiple Inheritance Example](#multiple-inheritance-example)

   * [Base Classes: `BaseOne` and `BaseTwo`](#base-classes-baseone-and-basetwo)
   * [Derived Class: `Derived`](#derived-class-derived)
   * [Order of Constructor Calls](#order-of-constructor-calls)
5. [Inheritance Hierarchy With Empty Classes](#inheritance-hierarchy-with-empty-classes)
6. [Example Output](#example-output)
7. [Summary](#summary)

---

## Overview of Inheritance

* **Base (Parent) Class**: Defines data members and member functions common to all derived classes.
* **Derived (Child) Class**: Inherits from one or more base classes and can add new members or override existing functions.
* Inheritance promotes **code reuse**—you don’t rewrite functionality present in the base class.
* C++ supports:

  * **Single Inheritance** (one base class)
  * **Multiple Inheritance** (multiple base classes)
  * **Method Overriding** (derived class replaces a virtual function)
  * **Access Specifiers** (`public`, `protected`, `private`) to control inheritance visibility

---

## Single Inheritance Example

### Base Class: `Food`

```cpp
#include <iostream>
#include <string>

class Food {  // Base class
public:
    Food(const std::string& name, double price)
        : name(name), price(price) {
        std::cout << name << " constructed as Food" << std::endl;
    }

    void eat() const {
        std::cout << "Eating " << name << " from Food" << std::endl;
    }

protected:
    std::string name;
    double price;
};
```

* `Food` holds `name` and `price`, and provides `eat()`.
* Constructor prints when a `Food` object is created.

### Derived Class: `Apple`

```cpp
#include <iostream>
#include <string>

class Apple : public Food {  // Derived class
public:
    Apple(const std::string& name, double price, int quantity)
        : Food(name, price), quantity(quantity) {
        std::cout << name << " constructed as Apple (quantity: "
                  << quantity << ")" << std::endl;
    }

    void getFromTree() const {
        std::cout << "Picked " << quantity << " " << name << "(s) from the tree" << std::endl;
    }

private:
    int quantity;
};
```

* `Apple` reuses `Food`’s constructor via the initializer list.
* Adds `quantity` and a new method `getFromTree()`.

### How Base Constructor Is Called

* In the initializer list of `Apple`, `Food(name, price)` invokes the base-class constructor.
* Ensures `name` and `price` are initialized before `Apple`’s own members.

---

## Method Overriding

* To override behavior, declare the base function `virtual` and redefine it in the derived class.

```cpp
class Food {
public:
    virtual void eat() const {
        std::cout << "Eating " << name << " from Food" << std::endl;
    }
    // ...
};

class Apple : public Food {
public:
    void eat() const override {
        std::cout << "Eating " << name << " from Apple" << std::endl;
    }
    // ...
};
```

* Calling `eat()` on a `Food*` or `Food&` that actually refers to an `Apple` invokes the overridden version.

---

## Multiple Inheritance Example

### Base Classes: `BaseOne` and `BaseTwo`

```cpp
#include <iostream>

class BaseOne {
public:
    BaseOne() { std::cout << "BaseOne constructed" << std::endl; }
    void funcOne() const { std::cout << "Function One" << std::endl; }
};

class BaseTwo {
public:
    BaseTwo() { std::cout << "BaseTwo constructed" << std::endl; }
    void funcTwo() const { std::cout << "Function Two" << std::endl; }
};
```

### Derived Class: `Derived`

```cpp
class Derived : public BaseOne, public BaseTwo {
    // inherits both BaseOne and BaseTwo
};
```

* `Derived` gets `funcOne()` and `funcTwo()`.

### Order of Constructor Calls

* Constructors are called in the order of declaration in the class definition:

  1. `BaseOne()`
  2. `BaseTwo()`
  3. `Derived()` (implicit default)

```cpp
Derived d;
d.funcOne();  // Function One
d.funcTwo();  // Function Two
```

---

## Inheritance Hierarchy With Empty Classes

```cpp
class Base {};
class DerivedOne : public Base {};
class DerivedTwo : public DerivedOne {};
```

* Forms a linear chain: `DerivedTwo → DerivedOne → Base → object`.
* Useful for type hierarchies and future expansions.

---

## Example Output

```text
// Single Inheritance
Pizza constructed as Food
Pizza constructed as Apple (quantity: 5)
Eating Pizza from Food
Picked 5 Pizza(s) from the tree

// Method Overriding
Eating Pizza from Apple

// Multiple Inheritance
BaseOne constructed
BaseTwo constructed
Function One
Function Two
```

---

## Summary

* **Inheritance** enables code reuse and “is-a” relationships.
* **Single Inheritance**: Derive one class from another.
* **Multiple Inheritance**: Derive from multiple base classes; watch constructor order.
* **Method Overriding**: Use `virtual` and `override` to customize behavior.
* **Initializer Lists**: Call base constructors before initializing derived members.

By leveraging inheritance in C++, you can build clear, maintainable, and reusable class hierarchies.
