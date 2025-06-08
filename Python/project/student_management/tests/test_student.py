from student_management.student import Student

def test_student_creation():
    student = Student(1001, "Charlie Brown", "charlie.brown@student.edu")
    assert student.id == 1001
    assert student.name == "Charlie Brown"
    assert student.email == "charlie.brown@student.edu"

def test_enroll_and_transcript():
    student = Student(1002, "Dana White", "dana.white@student.edu")
    student.enroll("MATH101")
    student.transcript.record_grade("MATH101", 90)

    assert "MATH101" in student.enrolled_courses
    assert student.transcript.courses["MATH101"] == 90
    assert student.transcript.calculate_gpa() == 4.0
