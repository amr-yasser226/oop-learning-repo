from typing import List, Dict, Any
from .person import Person
from .transcript import Transcript

class Student(Person):
    def __init__(self, id_: int, name: str, email: str):
        super().__init__(id_, name, email)
        self._transcript = Transcript(self)
        self._courses: List[str] = []

    @property
    def transcript(self) -> Transcript:
        return self._transcript

    @property
    def enrolled_courses(self) -> List[str]:
        return list(self._courses)

    def enroll(self, course_code: str):
        if course_code in self._courses:
            raise ValueError("Already enrolled")
        self._courses.append(course_code)

    def drop(self, course_code: str):
        try:
            self._courses.remove(course_code)
            self._transcript.remove_grade(course_code)
        except ValueError:
            raise ValueError("Not enrolled")

    def record_grade(self, course_code: str, grade: float):
        """
        Record a numeric grade for the given course code.
        Delegates to the Transcript object.
        """
        self._transcript.record_grade(course_code, grade)

    def get_transcript(self) -> Dict[str, float]:
        """
        Returns the mapping of course codes to grades.
        """
        return self._transcript.courses

    def calculate_gpa(self) -> float:
        """
        Delegate GPA calculation to the Transcript object.
        """
        return self._transcript.calculate_gpa()

    def get_profile(self) -> str:
        return (
            f"Student {self.id}: {self.name}\n"
            f"Email: {self.email}\n"
            f"Courses: {', '.join(self._courses) or 'None'}"
        )
    
    @classmethod
    def from_dict(cls, data: Dict[str, Any]) -> "Student":
        student = cls(data['id_'], data['name'], data['email'])
        student._courses = data.get('courses', [])
        # restore transcript if serialized
        grades = data.get('transcript', {})
        for code, grade in grades.items():
            # directly set into Transcript
            student._transcript._grades[code] = grade
        return student

    def to_dict(self) -> Dict[str, Any]:
        return {
            'id_': self.id,
            'name': self.name,
            'email': self.email,
            'courses': self._courses,
            'transcript': self._transcript.courses,
        }
