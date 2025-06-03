# Abstract Base Classes (ABC) 

An **Abstract Base Class (ABC)** is a class that cannot be instantiated on its own and is meant to serve as a blueprint for other classes. ABCs define methods that must be implemented by any concrete (non-abstract) subclass. In Python, the `abc` module provides the infrastructure to create and use abstract base classes.

---

## Table of Contents

1. [Overview of Abstract Base Classes](#overview-of-abstract-base-classes)  
2. [Key Components: `ABCMeta` and `@abstractmethod`](#key-components-abcmeta-and-abstractmethod)  
3. [Defining an Abstract Base Class](#defining-an-abstract-base-class)  
4. [Implementing Concrete Subclasses](#implementing-concrete-subclasses)  
5. [Example Code](#example-code)  
6. [Example Output](#example-output)  
7. [Summary](#summary)  

---

## Overview of Abstract Base Classes

- An **Abstract Base Class** (ABC) is a class that cannot be instantiated directly.  
- It can contain one or more **abstract methods**—methods declared but not implemented (i.e., their body is `pass` or raises `NotImplementedError`).  
- Subclasses of an ABC are **required** to implement all abstract methods before they can be instantiated.  
- ABCs ensure a consistent interface for a family of classes, preventing instantiation of incomplete subclasses.

---

## Key Components: `ABCMeta` and `@abstractmethod`

1. **`ABCMeta` (Metaclass)**  
   - A metaclass is “a class of a class.” In this case, `ABCMeta` is used to tell Python that a class is abstract.  
   - By specifying `metaclass=ABCMeta` in the class definition, the class becomes an abstract base class.  
   - The `abc` module also provides a convenience base class `ABC` that already uses `ABCMeta`.

2. **`@abstractmethod` (Decorator)**  
   - Decorate any method that must be implemented by concrete subclasses.  
   - If a subclass does not override all abstract methods, trying to instantiate it raises a `TypeError`.  
   - Even if a subclass provides an implementation that simply returns `None` or does nothing, it still counts as “implemented” for ABC purposes.

---

## Defining an Abstract Base Class

Below, we define an abstract base class `Programming` with one abstract method `has_oop()`—designed to check if a programming language supports object-oriented programming (OOP).

```python
from abc import ABCMeta, abstractmethod

class Programming(metaclass=ABCMeta):
    """
    Abstract Base Class for programming languages.
    Any subclass must implement has_oop().
    """

    @abstractmethod
    def has_oop(self):
        """
        Method to check whether the language supports OOP.
        Must be implemented by all concrete subclasses.
        """
        pass

    # Example of a second abstract method (commented out):
    # @abstractmethod
    # def has_name(self):
    #     pass
````

* **`metaclass=ABCMeta`**: Declares that `Programming` is abstract.
* **`@abstractmethod def has_oop(self): pass`**: Marks `has_oop()` as abstract. Subclasses must override it.

---

## Implementing Concrete Subclasses

### Subclass: `Python`

```python
class Python(Programming):
    """
    Concrete subclass that implements has_oop() by returning "Yes".
    """

    def has_oop(self):
        return "Yes"
```

* `Python` inherits from `Programming` and **provides** the required `has_oop()` method.
* Because `Python` implements `has_oop()`, it can be instantiated.

---

### Subclass: `Pascal`

```python
class Pascal(Programming):
    """
    Concrete subclass that implements has_oop() but leaves the body empty.
    """

    def has_oop(self):
        """
        Although this method has a body (even if it simply `pass`es),
        Python considers it “implemented,” so `Pascal` is instantiable.
        """
        pass

    # If Pascal did not define has_oop(), instantiating Pascal would raise an error.
    # Example of implementing a second abstract method (commented out):
    # def has_name(self):
    #     return "Pascal"
```

* `Pascal` also inherits from `Programming` and overrides `has_oop()`.
* Even though `has_oop()` merely executes `pass`, it counts as an implementation from the ABC’s perspective.
* Therefore, `Pascal` can be instantiated despite not returning a meaningful value.

---

## Example Code

Below is the complete code combining the abstract base class and its two subclasses. We then create instances of `Pascal` and `Python` and call their `has_oop()` methods.

```python
from abc import ABCMeta, abstractmethod

# Abstract Base Class
class Programming(metaclass=ABCMeta):
    """
    Abstract Base Class for programming languages.
    """

    @abstractmethod
    def has_oop(self):
        """
        Abstract method that must be implemented by subclasses:
        Check if the language supports object-oriented programming.
        """
        pass

    # Optional second abstract method (commented out):
    # @abstractmethod
    # def has_name(self):
    #     pass


# Concrete subclass: Python
class Python(Programming):
    """
    Python supports OOP, so return 'Yes'.
    """
    def has_oop(self):
        return "Yes"


# Concrete subclass: Pascal
class Pascal(Programming):
    """
    Pascal’s OOP support is not implemented here (method body is pass).
    """
    def has_oop(self):
        pass

    # If Pascal needed to implement a second abstract method, it would go here:
    # def has_name(self):
    #     return "Pascal"


# Instantiate and test
one = Pascal()    # Pascal can be instantiated because has_oop() is “implemented”
two = Python()    # Python can be instantiated because has_oop() returns "Yes"

print(one.has_oop())  # Output will be None, since Pascal.has_oop() does not return a value
print(two.has_oop())  # Output: Yes
```

* **`one = Pascal()`**: Succeeds because `Pascal.has_oop()` exists (even though it does nothing).
* **`two = Python()`**: Succeeds because `Python.has_oop()` returns `"Yes"`.
* Calling `one.has_oop()` prints `None` (implicit return), and `two.has_oop()` prints `"Yes"`.

---

## Example Output

```text
None
Yes
```

1. **`None`**

   * Comes from `print(one.has_oop())`. Since `Pascal.has_oop()` uses `pass`, it implicitly returns `None`.
2. **`Yes`**

   * Comes from `print(two.has_oop())`. `Python.has_oop()` explicitly returns the string `"Yes"`.

---

## Summary

* **Abstract Base Classes (ABCs)** enforce that certain methods are implemented in subclasses before instantiation.
* Use `metaclass=ABCMeta` (or inherit from `abc.ABC`) to declare a class as abstract.
* Mark methods with `@abstractmethod` to require overriding in concrete subclasses.
* A subclass that provides at least empty implementations for all abstract methods can be instantiated.
* Attempting to instantiate a subclass that does not override all abstract methods raises a `TypeError`.

By leveraging ABCs, you can design clear interfaces for related classes, ensuring that all implementations adhere to a consistent contract.

