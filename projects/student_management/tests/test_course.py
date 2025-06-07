import pytest
from student_management.course import Course
from student_management.student import Student
from student_management.instructor import Instructor

def test_course_creation():
    course = Course("CS101", "Intro to CS", 2)
    assert course.code == "CS101"
    assert course.title == "Intro to CS"
    assert course.capacity == 2
    assert course.instructor is None
    assert course._students == []

def test_assign_instructor():
    course = Course("CS101", "Intro to CS", 2)
    inst = Instructor(1, "Dr. Alice", "alice@example.edu")
    course.assign_instructor(inst)
    assert course.instructor == inst

def test_enroll_student():
    course = Course("CS101", "Intro to CS", 1)
    student = Student(1001, "Charlie", "charlie@student.edu")
    course.enroll(student)
    assert student in course._students

def test_enroll_over_capacity():
    course = Course("CS101", "Intro to CS", 1)
    s1 = Student(1001, "Charlie", "charlie@student.edu")
    s2 = Student(1002, "Dana", "dana@student.edu")
    course.enroll(s1)
    
    with pytest.raises(ValueError, match="Course full"):
        course.enroll(s2)
