# C++ Classes: A Comprehensive Guide

This document provides a structured overview of C++ classes, covering their definition, instantiation, member variables, member functions, and advanced features such as static members and sfriend functions. Each section builds upon the previous one, ensuring a smooth learning curve.

---

## 1. Classes and Objects

A **class** in C++ is a user-defined type that bundles data and functions, while an **object** is an instance of a class with its own state.

### 1.1 Basic Class Definition

To define a minimal class without any members, use:

```cpp
class Member {
    // empty body
};
```

* `Member` is the class name.
* A semicolon is required after the closing brace.

### 1.2 Creating an Object

When you declare an object, C++ uses the default constructor (generated if none is provided):

```cpp
Member member_one;   // allocated on the stack
Member* member_two = new Member(); // allocated on the heap
```

* `member_one` lives in automatic storage (stack).
* `member_two` is a pointer to a heap-allocated object (must be `delete`d later).

### 1.3 Constructors

Constructors initialize new objects. They have the same name as the class and no return type.

#### 1.3.1 Default and Parameterized Constructors

```cpp
class Member {
public:
    Member() {                 // default constructor
        std::cout << "New member created\n";
    }
    Member(std::string name, int age) : name(name), age(age) {}  // parameterized

private:
    std::string name;
    int age;
};
```

* The initializer list (`: name(name), age(age)`) initializes member variables more efficiently.
* If no constructor is declared, C++ provides an implicit default constructor.

### 1.4 The `this` Pointer

Within member functions, `this` is a pointer to the current object:

```cpp
class Member {
public:
    void setName(const std::string& name) {
        this->name = name;   // disambiguates member vs. parameter
    }
private:
    std::string name;
};
```

* Use `this->` to refer to members when names collide.

---

## 2. Member Variables and Member Functions

Once you understand how to define and instantiate classes, you can explore how to store data (member variables) and define behavior (member functions).

### 2.1 Member Variables

Member variables (data members) hold the state of each object.

```cpp
class Member {
public:
    Member(std::string name) : name(name) {}

private:
    std::string name;   // each object has its own `name`
};
```

* Private members are accessible only within the class.

### 2.2 Member Functions

Member functions (methods) operate on an object's data.

```cpp
class Member {
public:
    Member(std::string first, std::string last)
        : first_name(first), last_name(last) {}

    std::string fullName() const {
        return first_name + " " + last_name;
    }

private:
    std::string first_name;
    std::string last_name;
};

// Usage:
Member m("Amr", "Yasser");
std::cout << m.fullName(); // Amr Yasser
```

* The `const` after the method signature indicates it does not modify the object.

---

## 3. Static Members and Friend Functions

C++ offers static members shared by all instances, and friend functions/classes for controlled access.

### 3.1 Static Member Variables and Functions

Static members belong to the class rather than any object.

```cpp
class Member {
public:
    static int userCount;   // declaration

    Member() { ++userCount; }
    ~Member() { --userCount; }

    static void showUserCount() {
        std::cout << "Users: " << userCount << '\n';
    }

private:
    std::string name;
};

// Definition outside the class
int Member::userCount = 0;

// Usage:
Member a;
Member b;
Member::showUserCount(); // Users: 2
```

* Define and initialize static variables in a source file.

### 3.2 Friend Functions

Friend functions can access private members without being members themselves.

```cpp
class Member {
private:
    std::string name;

public:
    Member(std::string n) : name(n) {}
    friend void printName(const Member& m);
};

void printName(const Member& m) {
    std::cout << "Name: " << m.name << '\n';
}
```

* Use sparingly to maintain encapsulation.

---

## 4. Access Specifiers and Inheritance Note

* **public**: Accessible from anywhere.
* **protected**: Accessible in derived classes.
* **private**: Accessible only within the class.

<span style="color: gray;">(Inheritance details covered in its own file)</span>

---

## 5. Summary

* **Classes and Objects**: Define custom types and instantiate them.
* **Constructors**: Initialize objects, use initializer lists.
* **Member Variables & Functions**: Encapsulate state and behavior.
* **Static Members**: Share data and behavior at the class level.
* **Friend Functions**: Grant selective access to internals.

By following these guidelines and examples, you can structure your C++ classes to be clear, efficient, and maintainable.
