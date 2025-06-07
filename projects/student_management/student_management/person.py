from abc import ABC, abstractmethod

class Person(ABC):
    def __init__(self, id_: int, name: str, email: str):
        self._id = id_
        self._name = name
        self._email = email

    @property
    def id(self) -> int:
        return self._id

    @property
    def name(self) -> str:
        return self._name

    @name.setter
    def name(self, new: str):
        if not new:
            raise ValueError("Name cannot be empty")
        self._name = new

    @property
    def email(self) -> str:
        return self._email

    @email.setter
    def email(self, new: str):
        if "@" not in new:
            raise ValueError("Invalid email")
        self._email = new

    @abstractmethod
    def get_profile(self) -> str:
        pass