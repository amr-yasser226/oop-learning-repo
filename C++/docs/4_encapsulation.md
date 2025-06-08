# Encapsulation, Getters & Setters, and Computed Properties in C++

This document covers three related topics—Encapsulation, traditional Getters & Setters, and computed-property patterns via inline methods—organized in a single file with one unified Table of Contents and a combined Summary at the end.

---

## Table of Contents

1. [Encapsulation](#encapsulation)

   1. [Overview of Encapsulation](#overview-of-encapsulation)
   2. [Access Specifiers](#access-specifiers)

      * [Public Members](#public-members)
      * [Protected Members](#protected-members)
      * [Private Members](#private-members)
   3. [Encapsulation Examples](#encapsulation-examples)

      * [Public Example](#public-example)
      * [Protected Example](#protected-example)
      * [Private Example](#private-example)
   4. [Example Output and Notes](#example-output-and-notes)
2. [Getters & Setters (Traditional)](#getters--setters-traditional)

   1. [Overview of Getters & Setters](#overview-of-getters--setters)
   2. [Defining a Class with Private Member](#defining-a-class-with-private-member)
   3. [Implementing Getter and Setter Methods](#implementing-getter-and-setter-methods)
   4. [Example Usage](#example-usage)
   5. [Example Output](#example-output)
3. [Computed Properties via Inline Methods](#computed-properties-via-inline-methods)

   1. [Overview of Computed Properties](#overview-of-computed-properties)
   2. [Defining a Class with a Computed Method](#defining-a-class-with-a-computed-method)
   3. [How Inline Computation Works](#how-inline-computation-works)
   4. [Example Usage](#example-usage-1)
   5. [Example Output](#example-output-1)
4. [Summary](#summary)

---

## Encapsulation

### Overview of Encapsulation

* **Encapsulation** bundles data (member variables) and the functions that operate on that data into a single unit (a class).
* It restricts access to implementation details, exposing only what is necessary through public interfaces.
* C++ enforces access control via **access specifiers**: `public`, `protected`, and `private`.

---

### Access Specifiers

#### Public Members

* Declared under the `public:` label.
* Accessible from anywhere the object is visible.

```cpp
class Member {
public:
    std::string name;  // Public member variable
    void greet() const { std::cout << "Hello " << name << std::endl; }
};
```

#### Protected Members

* Declared under the `protected:` label.
* Accessible within the class and its derived classes, but not from outside.

```cpp
class Member {
protected:
    std::string name;  // Protected member variable
};

class Derived : public Member {
public:
    void showName() const { std::cout << name << std::endl; }
};
```

#### Private Members

* Declared under the `private:` label.
* Accessible only within the class itself (and friends).

```cpp
class Member {
private:
    std::string name;  // Private member variable
public:
    Member(const std::string& n) : name(n) {}
    void greet() const { std::cout << "Hello " << name << std::endl; }
};
```

---

### Encapsulation Examples

#### Public Example

```cpp
Member one("Amr");
std::cout << one.name << std::endl;   // Allowed: prints "Amr"
one.name = "Amr Yasser";            // Allowed: modify freely
std::cout << one.name << std::endl;   // Prints "Amr Yasser"
```

#### Protected Example

```cpp
Derived d;
// d.name = "Test";                // Error: 'name' is protected
// Instead, derived class can access it internally:
d.showName();                     // Prints inherited 'name' value
```

#### Private Example

```cpp
Member one("Amr");
// std::cout << one.name;          // Error: 'name' is private
one.greet();                        // Allowed: prints "Hello Amr"
```

---

### Example Output and Notes

```text
Amr
Amr Yasser
Hello Amr
```

* Public members can be read and modified anywhere.
* Protected members are hidden from external code but available to subclasses.
* Private members are accessible only through public member functions or friends.

---

## Getters & Setters (Traditional)

### Overview of Getters & Setters

* **Getter**: A public member function that returns the value of a private member.
* **Setter**: A public member function that validates and/or modifies a private member.
* They preserve encapsulation by preventing direct external access to private data.

---

### Defining a Class with Private Member

```cpp
class Member {
private:
    std::string name;
public:
    Member(const std::string& n) : name(n) {}
    void greet() const { std::cout << "Hello " << name << std::endl; }
};
```

---

### Implementing Getter and Setter Methods

```cpp
class Member {
private:
    std::string name;
public:
    Member(const std::string& n) : name(n) {}
    // Getter
    std::string getName() const { return name; }
    // Setter
    void setName(const std::string& newName) { name = newName; }
    void greet() const { std::cout << "Hello " << name << std::endl; }
};
```

---

### Example Usage

```cpp
Member one("Amr");
std::cout << one.getName() << std::endl;   // Output: Amr
one.setName("Amr Yasser");
std::cout << one.getName() << std::endl;   // Output: Amr Yasser
one.greet();                                // Output: Hello Amr Yasser
```

---

### Example Output

```text
Amr
Amr Yasser
Hello Amr Yasser
```

---

## Computed Properties via Inline Methods

### Overview of Computed Properties

* C++ does not have a `@property` decorator, but provides **inline member functions** to compute values on the fly.
* These methods behave like computed properties: no separate storage, computed each call.

---

### Defining a Class with a Computed Method

```cpp
class Member {
private:
    std::string name;
    int age;
public:
    Member(const std::string& n, int a) : name(n), age(a) {}
    // Computed property: age in days
    int ageInDays() const { return age * 365; }
    std::string greet() const { return "Hello " + name; }
};
```

---

### How Inline Computation Works

* `ageInDays()` is defined inside the class, making it implicitly `inline`.
* Each call computes `age * 365` at run time; no extra member variable needed.
* You call it like any other method: `obj.ageInDays()`.

---

### Example Usage

```cpp
Member one("Amr", 20);
std::cout << one.greet() << std::endl;       // Output: Hello Amr
std::cout << one.ageInDays() << std::endl;   // Output: 7300
```

---

### Example Output

```text
Hello Amr
7300
```

---

## Summary

* **Encapsulation**: Use `public`, `protected`, and `private` to control access to members.
* **Getters & Setters**: Provide `getX()`/`setX()` to access or modify private data while enforcing invariants.
* **Computed Properties**: Use inline methods to compute values on demand, emulating property-like behavior.

By applying these patterns in C++, you ensure robust, maintainable classes that hide implementation details and expose only the intended interface.
