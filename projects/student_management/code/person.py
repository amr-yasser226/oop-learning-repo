from abc import ABC, abstractmethod

class Person(ABC):

    def __init__(self, name: str, email: str):
        self._name = name
        self._email = email

    @abstractmethod
    def get_profile(self) -> str:
        """Return a string representation of the person's profile."""
        pass