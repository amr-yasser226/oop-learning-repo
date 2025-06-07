from typing import Dict, Optional

class Transcript:
    _scale = [(90, 4.0), (80, 3.0), (70, 2.0), (60, 1.0), (0, 0.0)]

    def __init__(self, student):
        self._student = student
        self._grades: Dict[str, float] = {}

    def record_grade(self, code: str, grade: float):
        if not (0 <= grade <= 100):
            raise ValueError("Invalid grade")
        if code not in self._student.enrolled_courses:
            raise ValueError("Not enrolled")
        self._grades[code] = grade

    def remove_grade(self, code: str):
        self._grades.pop(code, None)

    def calculate_gpa(self) -> float:
        if not self._grades:
            return 0.0
        total = 0
        for g in self._grades.values():
            for th, pts in self._scale:
                if g >= th:
                    total += pts
                    break
        return round(total / len(self._grades), 2)

    def generate_transcript(self) -> str:
        lines = [f"Transcript for {self._student.name} ({self._student.id}):"]
        for c, g in self._grades.items():
            lines.append(f"{c}: {g}")
        lines.append(f"GPA: {self.calculate_gpa()}")
        return "\n".join(lines)

    @property
    def courses(self) -> Dict[str, float]:
        return self._grades
