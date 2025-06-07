from typing import List
from .person import Person

class Instructor(Person):
    def __init__(self, id_: int, name: str, email: str):
        super().__init__(id_, name, email)
        self._courses: List[str] = []

    @property
    def courses_taught(self) -> List[str]:
        return list(self._courses)

    def assign_course(self, code: str):
        if code in self._courses:
            raise ValueError("Already teaching")
        self._courses.append(code)

    def remove_course(self, code: str):
        try:
            self._courses.remove(code)
        except ValueError:
            raise ValueError("Not teaching")

    def get_profile(self) -> str:
        return (
            f"Instructor {self.id}: {self.name}\n"
            f"Email: {self.email}\n"
            f"Courses: {', '.join(self._courses) or 'None'}"
        )
    
    @classmethod
    def from_dict(cls, data):
        instructor = cls(data['id_'], data['name'], data['email'])
        instructor._courses = data.get('courses', [])
        return instructor


    def to_dict(self):
        return {
            'id_': self.id,
            'name': self.name,
            'email': self.email,
            'courses': self._courses,
        }
