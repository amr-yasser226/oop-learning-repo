# Inheritance in Python

Inheritance allows us to define a class (the **derived** or **child** class) that inherits attributes and methods from another class (the **base** or **parent** class). This is a fundamental concept in object-oriented programming (OOP) that promotes code reuse and hierarchical relationships.

---

## Table of Contents

1. [Overview of Inheritance](#overview-of-inheritance)  
2. [Single Inheritance Example](#single-inheritance-example)  
   - [Base Class: `Food`](#base-class-food)  
   - [Derived Class: `Apple`](#derived-class-apple)  
   - [How `super()` Works](#how-super-works)  
3. [Method Overriding](#method-overriding)  
4. [Multiple Inheritance Example](#multiple-inheritance-example)  
   - [Base Classes: `BaseOne` and `BaseTwo`](#base-classes-baseone-and-basetwo)  
   - [Derived Class: `Derived`](#derived-class-derived)  
   - [Method Resolution Order (MRO)](#method-resolution-order-mro)  
5. [Inheritance Hierarchy With Empty Classes](#inheritance-hierarchy-with-empty-classes)  
6. [Example Output](#example-output)  
7. [Summary](#summary)  

---

## Overview of Inheritance

- **Base (Parent) Class**: Defines attributes and methods that are common to all derived classes.  
- **Derived (Child) Class**: Inherits from one or more base classes and can add new attributes/methods or override existing ones.  
- Inheritance promotes **code reuse**—you don’t have to rewrite functionality that already exists in the parent class.  
- Python supports:  
  - **Single Inheritance** (one base class)  
  - **Multiple Inheritance** (multiple base classes)  
  - **Method Overriding** (derived class changes behavior of an inherited method)  
  - **`super()`** for calling base-class methods  

---

## Single Inheritance Example

### Base Class: `Food`

```python
class Food:  # Base class
    def __init__(self, name, price):
        """
        Initialize the Food instance with a name and price.
        This runs when an object of type Food (or its subclasses) is created.
        """
        self.name = name
        self.price = price
        print(f"{self.name} is created from base class")

    def eat(self):
        """
        A simple method that all Food objects can use to simulate eating.
        """
        print("Eat method from base class")
````

* The `Food` class has two attributes:

  1. `name` (e.g., `"Pizza"`)
  2. `price` (e.g., `150`)
* Its constructor (`__init__`) prints a message when an instance is created.
* The `eat()` method belongs to every instance of `Food`.

---

### Derived Class: `Apple`

```python
class Apple(Food):  # Derived class inherits from Food
    def __init__(self, name, price, amount):
        """
        Initialize the Apple instance. We want to reuse Food’s __init__ logic,
        so we call super().__init__(name, price).
        """
        # Call the base class constructor to set name and price
        super().__init__(name, price)

        # Now add the extra attribute specific to Apple
        self.amount = amount
        print(f"{self.name} is created from derived class "
              f"and price is {self.price} and amount is {self.amount}")

    def get_from_tree(self):
        """
        A method unique to Apple that simulates picking apples from a tree.
        """
        print("Get from tree from derived class")
```

* `Apple` inherits all attributes and methods of `Food`.
* By calling `super().__init__(name, price)`, we invoke `Food`’s constructor to set `name` and `price`.
* We then add an extra attribute: `amount`.
* Finally, we define a new method `get_from_tree()` that belongs only to `Apple`.

---

### How `super()` Works

* `super()` returns a temporary object that allows you to call the base class’s methods.
* In this example:

  ```python
  super().__init__(name, price)
  ```

  executes `Food.__init__(self, name, price)` behind the scenes.
* Using `super()` is preferred over directly calling `Food.__init__(...)` because it supports cooperative multiple inheritance (see next section) and maintains the correct Method Resolution Order (MRO).

---

## Method Overriding

* A derived class can **override** (replace) a method inherited from its base class by defining a method with the same name.
* When you call the method on the derived-class instance, Python uses the derived-class version instead of the base-class version.

```python
class Apple(Food):
    # ... (existing __init__ and get_from_tree methods)

    def eat(self):
        """
        Override the eat() method from Food.
        Now, when eat() is called on an Apple instance, this version runs.
        """
        print("Eat method from derived class")
```

* Even though `Food` had its own `eat()`, this new `eat()` in `Apple` “overrides” it.
* If you want to use the base-class version inside the overriding method, you could do:

  ```python
  def eat(self):
      super().eat()      # Call the base-class eat()
      print("Additional steps in derived class’s eat()")
  ```

---

## Multiple Inheritance Example

Python allows a class to inherit from more than one base class. This is called **multiple inheritance**. The derived class gets attributes and methods from all of its parent classes.

### Base Classes: `BaseOne` and `BaseTwo`

```python
class BaseOne:
    def __init__(self):
        """
        When an object of Derived is created,
        BaseOne’s constructor will run first (per MRO).
        """
        print("Base One Constructor")

    def func_one(self):
        """
        A method specific to BaseOne.
        """
        print("One")

class BaseTwo:
    def __init__(self):
        """
        When an object of Derived is created,
        BaseTwo’s constructor will run after BaseOne (per MRO).
        """
        print("Base Two Constructor")

    def func_two(self):
        """
        A method specific to BaseTwo.
        """
        print("Two")
```

* `BaseOne` and `BaseTwo` each have their own `__init__()` and a single method (`func_one()` or `func_two()`).
* When a class inherits from both, both constructors will execute (in MRO order) unless overridden.

---

### Derived Class: `Derived`

```python
class Derived(BaseOne, BaseTwo):  # Multiple inheritance
    pass
```

* `Derived` inherits from both `BaseOne` and `BaseTwo`.
* Since `Derived` does not define its own `__init__()`, Python calls parent constructors in the order defined by the MRO:

  1. `BaseOne.__init__()`
  2. `BaseTwo.__init__()`

```python
# Create an object of Derived
my_var = Derived()

# Call methods inherited from each base class:
my_var.func_one()  # Should print "One"
my_var.func_two()  # Should print "Two"
```

---

### Method Resolution Order (MRO)

* The **MRO** determines the order in which base classes are searched when looking for a method or attribute.
* For `Derived(BaseOne, BaseTwo)`, the MRO is:

  ```
  Derived → BaseOne → BaseTwo → object
  ```
* You can inspect the MRO using either property:

  ```python
  print(Derived.mro())
  # or
  print(Derived.__mro__)
  ```
* This ensures that if multiple base classes define the same method, Python knows which one to call first.

---

## Inheritance Hierarchy With Empty Classes

Sometimes you may have a chain of classes where each one inherits from the previous, even if they add no new behavior. This can be used in frameworks or type hierarchies to create specialized versions later.

```python
class Base:
    pass

class DerivedOne(Base):
    pass

class DerivedTwo(DerivedOne):
    pass
```

* `DerivedOne` inherits everything from `Base`, but adds no new attributes or methods.
* `DerivedTwo` inherits from `DerivedOne`, forming a linear inheritance chain:

  ```
  DerivedTwo → DerivedOne → Base → object
  ```

---

## Example Output

Putting it all together—single inheritance, method overriding, and multiple inheritance—here is what happens when you run the code:

```text
# Single Inheritance
Pizza is created from base class
Pizza is created from derived class and price is 150 and amount is 500
Eat method from base class
Get from tree from derived class

# Method Overriding (if uncommented)
# Eat method from derived class

# Multiple Inheritance
Base One Constructor
Base Two Constructor
One
Two
```

1. **“Pizza is created from base class”** comes from `Food.__init__` inside `Apple.__init__`.
2. **“Pizza is created from derived class and price is 150 and amount is 500”** comes from the last print in `Apple.__init__`.
3. Calling `food_two.eat()` (before overriding) invokes `Food.eat()`.
4. Calling `food_two.get_from_tree()` invokes the derived-class method.
5. If you override `eat()` in `Apple`, then `food_two.eat()` prints “Eat method from derived class.”
6. Creating `Derived()` prints:

   * “Base One Constructor” (from `BaseOne.__init__`)
   * “Base Two Constructor” (from `BaseTwo.__init__`)
7. Calling `my_var.func_one()` prints “One”.
8. Calling `my_var.func_two()` prints “Two”.

---

## Summary

* **Inheritance** enables classes to reuse code and establish “is-a” relationships.
* **Single Inheritance**: A derived class inherits from one base class.
* **Multiple Inheritance**: A derived class inherits from two or more base classes.
* Use `super()` to call the base-class constructor or other methods, which simplifies code and respects the MRO.
* **Method Overriding** lets a derived class replace or extend behavior defined in its base class.
* **MRO** guarantees a consistent lookup order when multiple classes define the same attribute or method.

By leveraging inheritance, you can create clear hierarchies, reduce code duplication, and design more maintainable object-oriented systems in Python.

