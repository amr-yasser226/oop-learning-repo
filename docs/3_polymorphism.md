# Polymorphism in Python

Polymorphism is the ability of a single function or operator to work with different types of data. In Python, you’ll see polymorphism in:

- **Operator Overloading**: The same operator behaves differently depending on operand types (e.g., `+` for numbers vs. strings).
- **Function Polymorphism**: Built-in functions like `len()` can accept lists, strings, dictionaries, etc., and return the appropriate “length.”
- **Method Overriding in Classes**: A base class defines a method signature; derived classes provide their own implementation.

---

## Table of Contents

1. [Overview of Polymorphism](#overview-of-polymorphism)  
2. [Operator Overloading (Built-in Polymorphism)](#operator-overloading-built-in-polymorphism)  
3. [Function Polymorphism (`len` Example)](#function-polymorphism-len-example)  
4. [Polymorphism with Custom Classes](#polymorphism-with-custom-classes)  
   - [Base Class `A`](#base-class-a)  
   - [Derived Classes `B` and `C`](#derived-classes-b-and-c)  
5. [Example Output](#example-output)  
6. [Summary](#summary)  

---

## Overview of Polymorphism

- **Definition**: Polymorphism comes from the Greek words “poly” (many) and “morph” (form). It means “many forms.”  
- In Python, the same operator or function name can be “overloaded” to work on different data types.  
- At the class level, polymorphism often appears when a base class declares a method (or an abstract method), and each derived class implements it in its own way.  

---

## Operator Overloading (Built-in Polymorphism)

Python’s `+` operator behaves differently depending on operand types:

```python
n1 = 10
n2 = 20

# When both operands are integers, '+' performs numeric addition:
print("n1 + n2 =", n1 + n2)    # Output: n1 + n2 = 30

s1 = "Hello"
s2 = "Python"

# When both operands are strings, '+' performs concatenation:
print("s1 + s2 =", s1 + " " + s2)   # Output: s1 + s2 = Hello Python
````

* **Integers**: `10 + 20` → `30`.
* **Strings**: `"Hello" + " Python"` → `"Hello Python"`.
* The operator `+` is “polymorphic” because it adapts based on operand types.

---

## Function Polymorphism (`len` Example)

The built-in `len()` function can accept any sequence or collection type and return its length. Examples:

```python
# 1. len() on a list
print(len([1, 2, 3, 4, 5, 6]))      
# Output: 6

# 2. len() on a string
print(len("Amr Yasser"))             
# Output: 10

# 3. len() on a dictionary
print(len({"Key_one": 1, "Key_two": 2}))  
# Output: 2
```

* `len([1,2,3,4,5,6])` returns `6` because there are 6 elements in the list.
* `len("Amr Yasser")` returns `10` (including the space).
* `len({"Key_one": 1, "Key_two": 2})` returns `2` (two keys in the dictionary).

> **Note:** If you try to call `len()` without any argument, or with multiple separate arguments (e.g., `len(1, 2, 3)`), Python will raise a `TypeError`, because `len()` expects exactly one argument that is a sequence or collection.

---

## Polymorphism with Custom Classes

User-defined classes can implement polymorphism via method overriding. A common pattern is:

1. **Define a base class** with a method that raises `NotImplementedError`.
2. **Derived classes** override that method and provide specific behavior.
3. At runtime, a reference to the base class can hold any derived-class instance, and calling the overridden method invokes the derived version.

### Base Class `A`

```python
class A:
    def do_something(self):
        """
        Base method signature. Raises an exception if not overridden.
        """
        print("From Class A")
        raise NotImplementedError("Derived classes must implement do_something()")
```

* `A` defines a method `do_something()`, but it always raises `NotImplementedError`.
* This signals that **every subclass** should provide its own implementation of `do_something()`.

### Derived Classes `B` and `C`

```python
class B(A):
    def do_something(self):
        """
        B’s implementation of do_something().
        """
        print("From Class B")

class C(A):
    def do_something(self):
        """
        C’s implementation of do_something().
        """
        print("From Class C")
```

* `B` and `C` both inherit from `A`.
* Each class provides its own version of `do_something()`.
* If you try to instantiate `A` directly and call `do_something()`, you’ll get the `NotImplementedError`. But if you instantiate `B` or `C`, their `do_something()` runs instead.

```python
# Instantiate C, but store it in a variable of type A:
my_instance = C()

# Even though the reference is “A-like,” the actual object is a C.
# Calling do_something() invokes C’s version (dynamic dispatch).
my_instance.do_something()  # Output: From Class C
```

* The variable `my_instance` has type `C`, which is a subclass of `A`.
* Calling `my_instance.do_something()` runs the `C` implementation.
* This demonstrates polymorphism: **the same method name** (`do_something`) behaves differently depending on the object’s class.

---

## Example Output

Putting all of the above together, here is what you would see when running the code:

```text
# Operator Overloading
n1 + n2 = 30
s1 + s2 = Hello Python

# Function Polymorphism (len)
6
10
2

# Polymorphism with Custom Classes
From Class C
```

1. **“30”** → result of `10 + 20`.
2. **“Hello Python”** → result of string concatenation.
3. **“6”**, **“10”**, **“2”** → lengths of the list, string, and dictionary, respectively.
4. **“From Class C”** → `C`’s override of `do_something()`.

---

## Summary

* **Polymorphism** allows the same operator or function to act on different data types.
* **Operator Overloading**: `+` adds numbers or concatenates strings.
* **Function Polymorphism**: `len()` works on lists, strings, dictionaries, etc.
* **Class-Level Polymorphism** (Method Overriding): A base class declares a method signature; derived classes implement it differently.
* Use polymorphism to write more flexible, reusable code that can operate uniformly on different types of objects.

```python
# Complete Code for Reference

# 1. Operator Overloading
n1 = 10
n2 = 20
print("n1 + n2 =", n1 + n2)

s1 = "Hello"
s2 = "Python"
print("s1 + s2 =", s1 + " " + s2)

# 2. Function Polymorphism (len)
print(len([1, 2, 3, 4, 5, 6]))      # 6
print(len("Amr Yasser"))             # 10
print(len({"Key_one": 1, "Key_two": 2}))  # 2

# 3. Class-Level Polymorphism

class A:
    def do_something(self):
        print("From Class A")
        raise NotImplementedError("Derived classes must implement do_something()")

class B(A):
    def do_something(self):
        print("From Class B")

class C(A):
    def do_something(self):
        print("From Class C")

my_instance = C()
my_instance.do_something()  # Output: From Class C
```
