# Python Classes: A Comprehensive Guide

This document provides a structured overview of Python classes, covering their definition, instantiation, attributes, methods, and advanced features such as class methods and static methods. Each section builds upon the previous one, ensuring a smooth learning curve.

---

## 1. Classes and Instances

A **class** in Python is a blueprint for creating objects, while an **instance** (or object) is created from a class and has its own methods and attributes.

### 1.1 Basic Class Definition

To define a minimal class without any attributes or methods, use:

```python
class Member:
    pass
```

* `Member` is the class name.
* The `pass` statement ensures no syntax errors while defining an empty class.

### 1.2 Creating an Instance

When you create a new object (instance) from a class, Python looks for the built-in `__init__` method:

```python
member_one = Member()
member_two = Member()
```

* Here, `member_one` and `member_two` are two separate instances of the `Member` class.
* If `__init__` is not defined, Python automatically uses a default constructor that does nothing.

### 1.3 The `__init__` Method (Constructor)

The `__init__` method is called every time an instance is created. It is responsible for initializing instance attributes.

#### 1.3.1 Syntax

```python
class Member:
    def __init__(self, p1, p2, p3):
        # Initialize instance attributes here
        self.param1 = p1
        self.param2 = p2
        self.param3 = p3
```

* `__init__` is often referred to as the **constructor**.
* Any method whose name begins and ends with double underscores (e.g., `__init__`, `__str__`) is called a **dunder** or **magic method**.
* The first parameter of `__init__` (conventionally named `self`) refers to the new instance being created. Although you can name it anything, `self` is the widely accepted convention.

#### 1.3.2 Example with No Initialization Arguments

```python
class Member:
    def __init__(self):
        print("A new member has been added")

# Creating instances
member_one = Member()
member_two = Member()

# Output:
# A new member has been added
# A new member has been added
```

* Since no parameters are passed to `__init__`, each instantiation simply prints a message.

### 1.4 Understanding `self`

* The name `self` refers to the current instance of the class.
* It must be the first parameter in any instance method, including `__init__`.
* Through `self`, you assign or access instance attributes:

```python
class Member:
    def __init__(self, name, age):
        self.name = name
        self.age = age

# Creating an instance with attributes "Alice" and 30
member = Member("Alice", 30)

print(member.name)  # Output: Alice
print(member.age)   # Output: 30
```

### 1.5 Inspecting an Instance’s Class

To verify the class of an instance, use the built-in `__class__` attribute:

```python
member_one = Member("Bob", 25)
print(member_one.__class__)
```

* This prints:

  ```
  <class '__main__.Member'>
  ```

* It confirms that `member_one` is an instance of the `Member` class.

---

## 2. Attributes and Methods

Once you understand how to create classes and instances, the next step is to explore how to store data (attributes) and define behaviors (methods).

### 2.1 Instance Attributes

Instance attributes are defined inside the constructor (`__init__` method).

```python
class Member:
    def __init__(self):
        self.name = "Amr"

member_one   = Member()
member_two   = Member()
member_three = Member()

print(member_one.name)    # Amr
print(member_two.name)    # Amr
print(member_three.name)  # Amr
```

* All three instances print the default name `"Amr"`.

#### 2.1.1 Default Value vs. Parameterized Value

##### Default Name (Hardcoded)

```python
class Member:
    def __init__(self, first_name):
        self.name = "Amr"

member_one   = Member("Amr")
member_two   = Member("Mark")
member_three = Member("Elon")

print(member_one.name)    # Amr
print(member_two.name)    # Amr
print(member_three.name)  # Amr
```

* Although different values are passed to `first_name`, `self.name` is hardcoded to `"Amr"`.
* All instances still show `"Amr"` because the passed-in value is not used.

##### Using the Passed-in Argument

```python
class Member:
    def __init__(self, first_name):
        self.name = first_name

member_one   = Member("Amr")
member_two   = Member("Mark")
member_three = Member("Elon")

print(member_one.name)    # Amr
print(member_two.name)    # Mark
print(member_three.name)  # Elon
```

* Now, `self.name` is assigned to `first_name`, so each instance shows its own `name`.

### 2.2 Multiple Attributes

You can define more than one attribute per instance:

```python
class Member:
    def __init__(self, first_name, middle_name, last_name):
        self.fname = first_name
        self.mname = middle_name
        self.lname = last_name

member_one   = Member("Amr",  "Yasser", "Anwar")
member_two   = Member("Mark", "Adam",   "Ali")
member_three = Member("Elon", "Mask",   "IDK")

print(member_one.fname, member_one.mname, member_one.lname)
# Amr Yasser Anwar
print(member_two.fname, member_two.mname, member_two.lname)
# Mark Adam Ali
print(member_three.fname, member_three.mname, member_three.lname)
# Elon Mask IDK
```

* Each instance stores three separate attributes: `fname`, `mname`, and `lname`.

### 2.3 Instance Methods

You can define methods that operate on instance attributes. For example, a method to return the full name:

```python
class Member:
    def __init__(self, first_name, middle_name, last_name):
        self.fname = first_name
        self.mname = middle_name
        self.lname = last_name

    def full_name(self):
        return f"{self.fname} {self.mname} {self.lname}"

member_one   = Member("Amr",  "Yasser", "Anwar")
member_two   = Member("Mark", "Adam",   "Ali")
member_three = Member("Elon", "Mask",   "IDK")

print(member_one.full_name())    # Amr Yasser Anwar
print(member_two.full_name())    # Mark Adam Ali
print(member_three.full_name())  # Elon Mask IDK
```

* The `full_name` method concatenates the three attributes and returns the full name string.

---

## 3. Class Attributes and Instance Methods

Class attributes are defined outside the constructor (`__init__`) and are shared by all instances of the class.

### 3.1 Defining a Class Attribute

```python
class Member:
    # Class attribute defined at the class level
    not_allowed_names = ["admin", "root", "user"]
    
    def __init__(self, name, age):
        self.name = name
        self.age = age

    def greet(self):
        if self.name in Member.not_allowed_names:
            raise ValueError(f"Name '{self.name}' is not allowed.")
        return f"Hello, my name is {self.name} and I am {self.age} years old."
```

* `not_allowed_names` is a **class attribute**:

  * It belongs to the class itself, not to any single instance.
  * All instances of `Member` see the same `not_allowed_names` list.
* Inside methods, you can reference this attribute as `Member.not_allowed_names` (or `self.__class__.not_allowed_names`).

### 3.2 How the `greet` Method Uses the Class Attribute

```python
def greet(self):
    if self.name in Member.not_allowed_names:
        raise ValueError(f"Name '{self.name}' is not allowed.")
    return f"Hello, my name is {self.name} and I am {self.age} years old."
```

1. When `greet()` is called on an instance, it checks whether `self.name` appears in the shared `not_allowed_names` list.
2. If the name is not allowed, it raises a `ValueError`.
3. Otherwise, it returns a greeting string using the instance’s `name` and `age`.

### 3.3 Example Usage

```python
member_one = Member("admin", 30)
print(member_one.greet())
```

* Since `"admin"` is in `Member.not_allowed_names`, calling `member_one.greet()` raises:

  ```
  ValueError: Name 'admin' is not allowed.
  ```

If you use a name that is not blacklisted:

```python
member_two = Member("Amr", 20)
print(member_two.greet())  
# Output: Hello, my name is Amr and I am 20 years old.
```

### 3.4 Inspecting an Instance (`dir()`)

To see the attributes and methods available on an instance:

```python
member_one = Member("admin", 30)
print(dir(member_one))
```

* `dir(member_one)` lists:

  * Instance attributes (`name`, `age`)
  * Methods (`greet`, plus all inherited methods like `__init__`, `__repr__`, etc.)
  * Class attribute accessible through the class or instance (`not_allowed_names` will appear under its class, not directly in `member_one.__dict__`).

Example output snippet (keys may vary):

```
['__class__', '__delattr__', '__dict__', ..., 'age', 'greet', 'name', 'not_allowed_names', ...]
```

* Notice that `not_allowed_names` appears in the list of accessible attributes, even though it’s a class attribute.

---

## 4. Class Methods and Static Methods

Beyond instance methods and class attributes, Python classes support **class methods** and **static methods** for functionality related to the class itself or utility functions that do not need access to class or instance data.

### 4.1 Class Methods

* Marked with the `@classmethod` decorator.
* Takes `cls` (the class) as the first parameter, not `self` (the instance).
* Can be called on the class itself without creating an instance.
* Commonly used when you want to perform actions related to the class as a whole (e.g., updating or accessing class-level data).

```python
class Member:
    user_num = 0

    @classmethod
    def show_users_count(cls):
        print(f"We have {cls.user_num} users in the system.")
```

* `user_num` is a **class attribute** tracking the number of users.
* `show_users_count` is a **class method** that prints the current value of `user_num` by referencing `cls.user_num`.
* You can call it directly on the class:

```python
Member.show_users_count()
```

```plaintext
We have 0 users in the system.
```

### 4.2 Static Methods

* Marked with the `@staticmethod` decorator.
* Takes no `self` or `cls` parameter.
* Bound to the class namespace but does not access class or instance data.
* Used when the method’s logic is related to the class conceptually but does not need to read or modify class/instance attributes.

```python
class Member:
    @staticmethod
    def say_hello():
        print("Hello, welcome to the system!")
```

* `say_hello` is a **static method** that simply prints a welcome message.
* It can be called on the class itself:

```python
Member.say_hello()
```

```plaintext
Hello, welcome to the system!
```

### 4.3 Combined Example

```python
class Member:
    user_num = 0

    @classmethod
    def show_users_count(cls):
        print(f"We have {cls.user_num} users in the system.")

    @staticmethod
    def say_hello():
        print("Hello, welcome to the system!")

# Calling class method without creating an instance
Member.show_users_count()

# Calling static method directly on the class
Member.say_hello()
```

```plaintext
We have 0 users in the system.
Hello, welcome to the system!
```

---

## 5. Summary

* **Classes and Instances**: A class is a blueprint; an instance is a concrete object created from that blueprint. The `__init__` method initializes new instances.
* **Instance Attributes and Methods**: Store data specific to each instance and define behaviors that operate on that data.
* **Class Attributes**: Shared across all instances; used for data or behavior relevant to the class as a whole.
* **Class Methods**: Operate on class-level data and are marked with `@classmethod`.
* **Static Methods**: Utility functions related to the class but not dependent on class or instance data, marked with `@staticmethod`.

By following these guidelines and examples, you can structure your Python classes to be clean, maintainable, and effective.
