import pytest
from student_management.person import Person
from abc import ABC

def test_person_is_abstract():
    with pytest.raises(TypeError):
        Person(1, "Name", "email@example.com")  # Cannot instantiate ABC directly
