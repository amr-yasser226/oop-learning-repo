from typing import List, Optional
from .instructor import Instructor
from .student import Student

class Course:
    def __init__(self, code: str, title: str, capacity: int):
        self.code = code
        self.title = title
        self.capacity = max(1, capacity)
        self.instructor: Optional[Instructor] = None
        self._students: List[Student] = []

    def assign_instructor(self, inst: Instructor):
        if self.instructor:
            self.instructor.remove_course(self.code)
        self.instructor = inst
        inst.assign_course(self.code)

    def enroll(self, stu: Student):
        if len(self._students) >= self.capacity:
            raise ValueError("Course full")
        self._students.append(stu)
        stu.enroll(self.code)

    def enroll_student(self, stu: Student):
        # Alias method for testing compatibility
        self.enroll(stu)

        return True

    def drop(self, stu: Student):
        if stu not in self._students:
            raise ValueError("Not enrolled")
        self._students.remove(stu)
        stu.drop(self.code)

    @property
    def enrolled_students(self):
        return self._students

    def get_details(self) -> str:
        return (
            f"{self.code} - {self.title}\n"
            f"Instructor: {self.instructor.name if self.instructor else 'TBD'}\n"
            f"Enrolled: {len(self._students)}/{self.capacity}"
        )
    
    @classmethod
    def from_dict(cls, data):
        course = cls(data['code'], data['title'], data['capacity'])
        # instructor and students are resolved later
        return course

    
    def to_dict(self):
        return {
            'code': self.code,
            'title': self.title,
            'capacity': self.capacity,
            'instructor_id': self.instructor.id if self.instructor else None,
            'students_ids': [s.id for s in self._students],
        }

