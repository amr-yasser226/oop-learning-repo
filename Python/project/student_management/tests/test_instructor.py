from student_management.instructor import Instructor

def test_instructor_creation():
    inst = Instructor(1, "Dr. Alice", "alice@example.edu")
    assert inst.id == 1
    assert inst.name == "Dr. Alice"
    assert inst.email == "alice@example.edu"
    assert inst.courses_taught == []

def test_assign_course():
    inst = Instructor(1, "Dr. Alice", "alice@example.edu")
    inst.assign_course("MATH101")
    assert "MATH101" in inst.courses_taught
