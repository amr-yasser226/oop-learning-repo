# Encapsulation, Getters & Setters, and `@property` in Python

This document covers three related topics—Encapsulation, traditional Getters & Setters, and computed-property patterns using `@property`—organized in a single file with one unified Table of Contents and a combined Summary at the end.

---

## Table of Contents

1. [Encapsulation](#encapsulation)  
   1. [Overview of Encapsulation](#overview-of-encapsulation)  
   2. [Access Levels](#access-levels)  
      - [Public Attributes and Methods](#public-attributes-and-methods)  
      - [Protected Attributes and Methods](#protected-attributes-and-methods)  
      - [Private Attributes and Methods](#private-attributes-and-methods)  
   3. [Encapsulation Examples](#encapsulation-examples)  
      - [Public Example](#public-example)  
      - [Protected Example](#protected-example)  
      - [Private Example](#private-example)  
   4. [Encapsulation: Example Output and Notes](#encapsulation-example-output-and-notes)  
2. [Getters & Setters (Traditional)](#getters--setters-traditional)  
   1. [Overview of Getters & Setters](#overview-of-getters--setters)  
   2. [Defining a Class with Private Attribute](#defining-a-class-with-private-attribute)  
   3. [Implementing Getter and Setter Methods](#implementing-getter-and-setter-methods)  
   4. [Example Usage](#example-usage)  
   5. [Example Output](#example-output)  
3. [Getters & Setters with `@property`](#getters--setters-with-property)  
   1. [Overview of `@property`](#overview-of-property)  
   2. [Defining a Class with a Computed Property](#defining-a-class-with-a-computed-property)  
   3. [How `@property` Works](#how-property-works)  
   4. [Example Usage](#example-usage-1)  
   5. [Example Output](#example-output-1)  
4. [Summary](#summary)  

---

## Encapsulation

### Overview of Encapsulation

- **Encapsulation** bundles data (attributes) and the methods that operate on that data into a single unit (a class).  
- It restricts access to certain components, preventing accidental modification or misuse.  
- Python does not enforce strict access control. Instead, it relies on naming conventions:  
  - **Public** (no underscores): accessible everywhere.  
  - **Protected** (single underscore `_`): intended for internal use (class and subclasses).  
  - **Private** (double underscore `__`): name-mangled to minimize accidental external access.

---

### Access Levels

#### Public Attributes and Methods

- By default, all Python attributes and methods are **public**.  
- No leading underscores means anyone in the code can read, write, or call them.

```python
class Member:
    def __init__(self, name):
        self.name = name  # Public attribute

# Example usage:
one = Member("Amr")
print(one.name)            # Allowed: prints "Amr"

one.name = "Amr Yasser"    # Allowed: modify freely
print(one.name)            # Prints "Amr Yasser"
````

* **Key Point**: There is no restriction—any code that has a reference to `Member` can change `name`.

---

#### Protected Attributes and Methods

* A **protected** attribute or method is prefixed with a single underscore (`_`).
* This signals “internal use.” By convention, external code should not access or modify these attributes, but Python will not stop you.

```python
class Member:
    def __init__(self, name):
        self._name = name  # Protected attribute

# Example usage:
one = Member("Amr")

# Accessing or modifying a protected attribute is possible, but discouraged:
print(one._name)           # Prints "Amr" (allowed, but not recommended)

one._name = "Amr Yasser"   # Allowed, but breaks the encapsulation intent
print(one._name)           # Prints "Amr Yasser"
```

* **By Convention**:

  * A single underscore is a hint to other developers: “This is internal; handle with care.”
  * There is no runtime enforcement—Python treats `_name` the same as any other attribute.

---

#### Private Attributes and Methods

* A **private** attribute or method is prefixed with a double underscore (`__`).
* Python name-mangles these names internally to `_ClassName__attribute`, making accidental access harder (but not impossible).

```python
class Member:
    def __init__(self, name):
        self.__name = name  # Private attribute

    def hello(self):
        # Accessing the private attribute from within the class is allowed:
        return f"Hello {self.__name}"
```

* **Attempting external access** to `__name` will fail:

  ```python
  one = Member("Amr")

  print(one.__name)
  # AttributeError: 'Member' object has no attribute '__name'
  ```

* **Workaround** (name mangling):

  * Internally, Python renames `__name` to `_Member__name`.
  * If you really want to access it (discouraged), you can do `one._Member__name`, but this defeats the purpose of privacy.

---

### Encapsulation Examples

#### Public Example

```python
class Member:
    def __init__(self, name):
        self.name = name  # Public attribute

# Creating an object of Member
one = Member("Amr")

# Because 'name' is public, we can read and modify it freely:
print(one.name)         # Output: Amr

one.name = "Amr Yasser"
print(one.name)         # Output: Amr Yasser
```

* Nothing prevents external code from modifying `name`.

---

#### Protected Example

```python
class Member:
    def __init__(self, name):
        self._name = name  # Protected attribute

# Creating an object of Member
one = Member("Amr")

# Conventions suggest this is “for internal use,” but:
print(one._name)        # Output: Amr  (Allowed, but discouraged)

one._name = "Amr Yasser"
print(one._name)        # Output: Amr Yasser
```

* Although `_name` is intended for internal or subclass use, Python does not enforce it.

---

#### Private Example

```python
class Member:
    def __init__(self, name):
        self.__name = name  # Private attribute

    def hello(self):
        # Correct way to access private attribute internally
        return f"Hello {self.__name}"

# Creating an object of Member
one = Member("Amr")

# Attempting to access the private attribute from outside:
print(one.__name)
# Raises: AttributeError: 'Member' object has no attribute '__name'

# Attempting to modify the private attribute directly:
one.__name = "Amr Yasser"
print(one.__name)
# This simply creates a new attribute called '__name' in the instance’s __dict__,
# but does not override the private __name. The real private attribute is still hidden.

# Correct way to access the private attribute is through a public method:
print(one.hello())      # Output: Hello Amr

# Name mangling allows forced access (not recommended):
print(one._Member__name)  
# Output: Amr
# But this goes against encapsulation principles.
```

* **Key Points**:

  1. `print(one.__name)` ⇒ `AttributeError` because `__name` is name-mangled.
  2. Assigning to `one.__name` does not change the private attribute; it merely creates a new public attribute.
  3. `one.hello()` works because the method is part of the class and can access the private attribute.
  4. `one._Member__name` bypasses the privacy guard, but should be avoided unless absolutely necessary.

---

### Encapsulation: Example Output and Notes

```text
# Public Example
Amr
Amr Yasser

# Protected Example
Amr
Amr Yasser

# Private Example
Traceback (most recent call last):
  File "script.py", line X, in <module>
    print(one.__name)
AttributeError: 'Member' object has no attribute '__name'

# After setting one.__name = "Amr Yasser"
# It creates a new, unrelated attribute named __name:
Amr Yasser

# Accessing via hello():
Hello Amr

# Accessing via name-mangled attribute (not recommended):
Amr
```

* In the **public** and **protected** examples, there are no runtime errors.
* In the **private** example, `print(one.__name)` raises an `AttributeError` because `__name` is truly private.
* After assigning `one.__name = "Amr Yasser"`, Python creates a distinct public attribute named `__name`, but the original private attribute remains untouched.
* Calling `one.hello()` correctly returns “Hello Amr.”
* Using `one._Member__name` displays the actual private attribute (“Amr”), but this circumvents encapsulation.

---

## Getters & Setters (Traditional)

Getters and setters are methods that allow controlled access to private attributes of a class. A **getter** retrieves the value of a private attribute, and a **setter** modifies it. This promotes encapsulation by preventing direct external manipulation of sensitive data.

---

### Overview of Getters & Setters

* **Private Attributes**: Attributes prefixed with double underscores (`__`) are name-mangled and cannot be accessed directly from outside the class.
* **Getter Method** (`get_…`): Returns the value of a private attribute.
* **Setter Method** (`set_…`): Validates and/or assigns a new value to a private attribute.
* By using getters and setters, we adhere to encapsulation principles—external code interacts with attributes only through controlled interfaces.

---

### Defining a Class with Private Attribute

Below is a class `Member` with a private attribute `__name`. By itself, this attribute cannot be accessed or modified directly from outside the class.

```python
class Member:
    def __init__(self, name):
        self.__name = name  # Private attribute

    def hello(self):
        """
        Public method that uses the private attribute __name.
        """
        print(f"Hello {self.__name}")
```

* `self.__name` is private.
* Calling `one = Member("Amr")` stores `"Amr"` in `one._Member__name` internally, but there is no direct way to read or modify `__name` from outside.

---

### Implementing Getter and Setter Methods

To safely access and update `__name`, define:

1. **Getter**: `get_name(self)`
2. **Setter**: `set_name(self, new_name)`

```python
class Member:
    def __init__(self, name):
        self.__name = name  # Private attribute

    def hello(self):
        """
        Public method to greet using the private attribute.
        """
        print(f"Hello {self.__name}")

    def get_name(self):
        """
        Getter method to access the private variable __name.
        """
        return self.__name

    def set_name(self, new_name):
        """
        Setter method to modify the private variable __name.
        """
        self.__name = new_name
```

* `get_name()` returns the value of `__name`.
* `set_name(new_name)` assigns `new_name` to `__name`.
* External code must use these methods rather than touching `__name` directly.

---

### Example Usage

```python
one = Member("Amr")

# Attempting direct assignment to __name would not affect the private attribute:
# one.__name = "Ahmed"
# one.hello()  # Still prints "Hello Amr"

# Accessing the private attribute via name mangling (not recommended):
# print(one._Member__name)  # Possible but breaks encapsulation

# Correct use of getter and setter:
print(one.get_name())       # Output: Amr

one.set_name("Amr Yasser")  # Updates the private attribute
print(one.get_name())       # Output: Amr Yasser

one.hello()                 # Output: Hello Amr Yasser
```

* `one.get_name()` prints `"Amr"`.
* After `one.set_name("Amr Yasser")`, `get_name()` returns `"Amr Yasser"`.
* `one.hello()` reflects the updated private attribute.

---

### Example Output

```text
Amr
Amr Yasser
Hello Amr Yasser
```

1. **“Amr”** is printed by `print(one.get_name())` initially.
2. **“Amr Yasser”** prints after calling `one.set_name("Amr Yasser")`.
3. **“Hello Amr Yasser”** prints when `one.hello()` is called, demonstrating that the private attribute was successfully updated.

---

## Getters & Setters with `@property`

Python’s `@property` decorator provides a Pythonic way to create getters (and optionally setters) for computed or derived attributes. This allows us to access methods like attributes, improving readability while maintaining encapsulation and data validation.

---

### Overview of `@property`

* **Traditional getters/setters**: Define explicit methods like `get_age()` and `set_age(new_age)`.
* **`@property` decorator**: Allows you to define a method that is accessed like an attribute.
* Benefits:

  * Cleaner syntax—no need to call the method with parentheses.
  * Keeps computing logic hidden behind an attribute name.
  * Supports read-only or read/write computed properties.

---

### Defining a Class with a Computed Property

Below is a class `Member` with two instance attributes (`name` and `age`) and one computed property `age_in_days`. We calculate `age_in_days` by multiplying `age` by 365.

```python
class Member:
    def __init__(self, name, age):
        """
        Initialize the Member instance with public attributes 'name' and 'age'.
        """
        self.name = name
        self.age = age

    def hello(self):
        """
        A simple method that returns a greeting using the member’s name.
        """
        return f"Hello {self.name}"

    @property
    def age_in_days(self):
        """
        Compute the member’s age in days.
        Because of the @property decorator, this method can be accessed
        like an attribute (without parentheses).
        """
        return self.age * 365
```

* `name` and `age`: Public attributes, accessible directly.
* `hello()`: Regular method that returns a greeting string.
* `age_in_days`: Method decorated with `@property`, so `one.age_in_days` will call this method behind the scenes.

---

### How `@property` Works

1. **Definition**:

   ```python
   @property
   def age_in_days(self):
       return self.age * 365
   ```

   * The method name (`age_in_days`) becomes the attribute name.
   * No parentheses needed at access time.

2. **Access**:

   * When you write `one.age_in_days`, Python invokes `Member.age_in_days(one)` and returns the result.
   * If you tried `one.age_in_days()`, it raises a `TypeError` because `age_in_days` is now a property, not a regular method.

3. **Use Cases**:

   * Computed values that shouldn’t be stored as separate attributes.
   * Lazy evaluation—compute on demand.
   * Read-only attributes by omitting a setter.

---

### Example Usage

```python
one = Member("Amr", 20)

# Accessing public attributes directly:
print(one.name)   # Output: Amr
print(one.age)    # Output: 20

# Calling the hello() method:
print(one.hello())  # Output: Hello Amr

# Accessing the computed property age_in_days:
# Note: No parentheses needed!
print(one.age_in_days)  
# Output: 7300  (because 20 * 365 = 7300)

# Attempting to call age_in_days as a method would be incorrect:
# print(one.age_in_days())  # TypeError: 'int' object is not callable
```

* `one.name` and `one.age` print their stored values.
* `one.hello()` prints the greeting.
* `one.age_in_days` returns the computed integer `7300` without requiring parentheses.

---

### Example Output

```text
Amr
20
Hello Amr
7300
```

1. **“Amr”** comes from `print(one.name)`.
2. **“20”** comes from `print(one.age)`.
3. **“Hello Amr”** comes from `print(one.hello())`.
4. **“7300”** comes from `print(one.age_in_days)` (20 years × 365 days/year).

---

## Summary

* **Encapsulation** hides an object’s internal state and only exposes what is necessary. Python relies on naming conventions:

  * **Public (no underscore)**: accessible anywhere.
  * **Protected (single underscore `_`)**: intended for class/subclass; accessible externally but discouraged.
  * **Private (double underscore `__`)**: name-mangled to `_ClassName__attribute`, preventing accidental external access.

* **Getters & Setters (Traditional)**:

  * Use `get_…` and `set_…` methods to expose private attributes safely.
  * Private attributes (prefixed with `__`) cannot be accessed directly, so getters return the value and setters update it while preserving encapsulation.

* **`@property` Decorator**:

  * Allows a method to be accessed like an attribute, hiding computed or derived logic.
  * Eliminates the need for explicit getter calls (`obj.property` instead of `obj.get_property()`).
  * Read-only computed attributes are possible by omitting a corresponding setter.

By combining encapsulation principles with getters/setters (traditional or `@property`), you can write more maintainable, readable, and robust Python classes that protect internal data and expose only what’s intended.

