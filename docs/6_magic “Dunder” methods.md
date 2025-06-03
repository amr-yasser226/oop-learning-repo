# Python Objects and Special (“Dunder”) Methods

In Python, **everything is an object**. Classes, instances, strings, integers—every value belongs to some class and supports various built-in methods. Special methods (often called “dunder” methods because they begin and end with double underscores) let you customize how your classes behave with built-in functions and operators.

---

## Table of Contents

1. [Overview of Special Methods](#overview-of-special-methods)  
2. [Key “Dunder” Methods](#key-dunder-methods)  
   - [`__init__`](#init)  
   - [`__str__`](#str)  
   - [`__len__`](#len)  
   - [`__class__`](#class)  
3. [Example: A `Skill` Class](#example-a-skill-class)  
4. [Example Output](#example-output)  
5. [Inspecting Built-in Types](#inspecting-built-in-types)  
   - [Strings (`str`)](#strings-str)  
   - [Integers (`int`)](#integers-int)  

---

## Overview of Special Methods

Special methods (also known as “magic” or “dunder” methods) are predefined method names you can implement to make your objects work with Python’s built-in functions and operators. Examples include:

- `__init__(self, …)`: Called automatically when an instance is created.
- `__str__(self)`: Defines the “informal” or human-readable string representation.
- `__len__(self)`: Called by the built-in `len()` function to determine the “length” of an object.
- `__class__`: A standard attribute (not a method) that tells you which class an instance belongs to.

---

## Key “Dunder” Methods

### `__init__`

- Automatically invoked when a new instance of the class is created.
- Often used to initialize instance attributes.

```python
class MyClass:
    def __init__(self, value):
        self.value = value
````

### `__str__`

* Returns a human-readable (informal) string representation of the object.
* Used by `print(obj)` and `str(obj)`.

```python
class MyClass:
    def __str__(self):
        return f"MyClass with value: {self.value}"
```

### `__len__`

* Returns an integer representing the “length” of the object.
* Invoked when you call `len(obj)`.

```python
class MyClass:
    def __len__(self):
        return len(self.value)  # if self.value is a sequence
```

### `__class__`

* Not actually a method, but a built-in attribute.
* Every object has a `__class__` attribute that points to the class to which it belongs.

```python
instance = MyClass("hello")
print(instance.__class__)        # <class '__main__.MyClass'>
print(instance.__class__.__name__)  # "MyClass"
```

---

## Example: A `Skill` Class

Below is a simple example that demonstrates how `__init__`, `__str__`, and `__len__` work in practice. This `Skill` class maintains a list of skills and shows how Python treats it as an object.

```python
class Skill:
    def __init__(self):
        """
        Initialize the Skill instance with a default list of skills.
        """
        self.skills = ["ML", "AI", "Python", "Deep Learning", "C++"]

    def __str__(self):
        """
        Return a human-readable string when the object is printed.
        """
        return f"This is my Skills => {self.skills}."

    def __len__(self):
        """
        Return the number of skills in the list
        when len() is called on the instance.
        """
        return len(self.skills)

# Instantiate the class
profile = Skill()

# Display the string representation
print(profile)

# Display the initial length of the skills list
print(len(profile))

# Show the class of the instance
print(profile.__class__)         # Which class does this instance belong to?
print(profile.__class__.__name__)  # The class’s name

# Add more skills
profile.skills.append("JavaScript")
profile.skills.append("MySQL")

# Display the updated length
print(len(profile))              # Now the list has 7 items
```

---

## Example Output

```text
This is my Skills => ['ML', 'AI', 'Python', 'Deep Learning', 'C++'].
5
<class '__main__.Skill'>
Skill
7
```

* The first line shows the result of `print(profile)`.
* `5` is printed because the original list has 5 items.
* `<class '__main__.Skill'>` and `Skill` show how `__class__` and `__class__.__name__` work.
* After adding two more skills, `len(profile)` is `7`.

---

## Inspecting Built-in Types

Since **everything** in Python is an object, you can inspect built-in types in exactly the same way.

### Strings (`str`)

```python
my_string1 = "Amr"
print(type(my_string1))          # <class 'str'>
print(my_string1.__class__)      # <class 'str'>
print(dir(str))                  # List all methods and attributes of the str class
```

* `type(my_string1)` and `my_string1.__class__` both show that the variable is a `str`.
* `dir(str)` shows all special and regular methods on strings, including `__add__`, `__len__`, `__str__`, `split`, `join`, and many more.

### Integers (`int`)

```python
my_string2 = 12
print(type(my_string2))          # <class 'int'>
print(my_string2.__class__)      # <class 'int'>
print(dir(int))                  # List all methods and attributes of the int class
```

* Similarly, integers are instances of the `int` class.
* `dir(int)` lists methods such as `__add__`, `__mul__`, `__str__`, `bit_length`, `to_bytes`, and so on.

---

## Summary

* **Everything in Python is an object**—including numbers, strings, lists, and your custom classes.
* Special methods (dunder methods) allow you to define or override built-in behaviors:

  * `__init__` for initialization
  * `__str__` for the string representation
  * `__len__` for length
  * `__class__` as an attribute that always points to the object’s class
* You can inspect any object’s class with `obj.__class__`, and see available methods with `dir(obj.__class__)`.

By implementing and exploring these special methods, you can make your classes integrate seamlessly with Python’s syntax and built-in functions.
