# Polymorphism in C++

Polymorphism is the ability of the same interface (function or operator) to work with different types or classes. In C++, you’ll see polymorphism in:

* **Operator Overloading**: Defining how operators (e.g., `+`) behave for user-defined types.
* **Function Overloading**: Multiple functions with the same name but different parameter lists.
* **Compile-Time Polymorphism**: Achieved via templates and inline functions.
* **Run-Time Polymorphism**: Achieved via inheritance, virtual functions, and pointers or references.

---

## Table of Contents

1. [Overview of Polymorphism](#overview-of-polymorphism)
2. [Operator Overloading](#operator-overloading)
3. [Function Overloading](#function-overloading)
4. [Compile-Time Polymorphism (Templates)](#compile-time-polymorphism-templates)
5. [Run-Time Polymorphism with Virtual Functions](#run-time-polymorphism-with-virtual-functions)

   * [Base Class `A`](#base-class-a)
   * [Derived Classes `B` and `C`](#derived-classes-b-and-c)
6. [Example Output](#example-output)
7. [Summary](#summary)

---

## Overview of Polymorphism

* **Polymorphism** (many forms) lets code operate on objects of different types through a unified interface.
* In C++, polymorphism appears at both compile time (overloading, templates) and run time (virtual functions).
* It enhances flexibility and extensibility of code, reducing duplication.

---

## Operator Overloading

Operator overloading lets you define custom behavior for built-in operators when applied to user-defined types.

```cpp
#include <iostream>

class Point {
public:
    int x, y;
    Point(int x, int y) : x(x), y(y) {}

    // Overload + operator to add two Point objects
    Point operator+(const Point& other) const {
        return Point(x + other.x, y + other.y);
    }
};

int main() {
    Point p1(1, 2);
    Point p2(3, 4);
    Point sum = p1 + p2;  // Calls overloaded operator+
    std::cout << "Sum: (" << sum.x << ", " << sum.y << ")\n";
}
```

* Defines `operator+` to add coordinates of two `Point` objects.
* Enables using `p1 + p2` just like built-in types.

---

## Function Overloading

Function overloading allows multiple functions with the same name but different parameter types or counts.

```cpp
#include <iostream>

// Overloaded functions named print
void print(int value) {
    std::cout << "Int: " << value << '\n';
}

void print(double value) {
    std::cout << "Double: " << value << '\n';
}

void print(const std::string& value) {
    std::cout << "String: " << value << '\n';
}

int main() {
    print(42);
    print(3.14);
    print("Hello C++");
}
```

* Compiler selects the correct overload based on argument types.

---

## Compile-Time Polymorphism (Templates)

Templates let you write generic functions or classes that work with any data type.

```cpp
#include <iostream>

template<typename T>
T add(T a, T b) {
    return a + b;
}

int main() {
    std::cout << add<int>(2, 3) << '\n';        // 5
    std::cout << add<double>(2.5, 4.1) << '\n'; // 6.6
}
```

* The `add` function is instantiated for each type used, enabling type-safe polymorphism at compile time.

---

## Run-Time Polymorphism with Virtual Functions

Run-time polymorphism uses base-class pointers or references and virtual functions to invoke derived-class behavior.

### Base Class `A`

```cpp
#include <iostream>

class A {
public:
    virtual void doSomething() const {
        std::cout << "Doing something in A" << std::endl;
    }
    virtual ~A() = default;  // virtual destructor for proper cleanup
};
```

* Declares `doSomething()` as `virtual`, enabling override in derived classes.
* Virtual destructor ensures correct destruction through base pointers.

### Derived Classes `B` and `C`

```cpp
#include <iostream>

class B : public A {
public:
    void doSomething() const override {
        std::cout << "Doing something in B" << std::endl;
    }
};

class C : public A {
public:
    void doSomething() const override {
        std::cout << "Doing something in C" << std::endl;
    }
};

int main() {
    A* ptr = new C();  // pointer of type A pointing to C
    ptr->doSomething();  // Calls C::doSomething()
    delete ptr;
}
```

* `override` keyword enforces correct overriding.
* Dynamic dispatch ensures the call to `doSomething()` uses the actual object’s implementation.

---

## Example Output

```text
Sum: (4, 6)
Int: 42
Double: 3.14
String: Hello C++
5
6.6
Doing something in C
```

---

## Summary

* **Operator Overloading**: Customize operators for user-defined types.
* **Function Overloading**: Same function name, different signatures.
* **Templates**: Generic code instantiated per type (compile-time polymorphism).
* **Virtual Functions**: Enable run-time polymorphism via dynamic dispatch.

By leveraging these forms of polymorphism in C++, you can write flexible, reusable, and type-safe code.
