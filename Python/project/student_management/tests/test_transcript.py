import pytest
from student_management.transcript import Transcript
from student_management.student import Student

def test_transcript_record_and_calculate_gpa():
    student = Student(1001, "Test Student", "test@student.com")
    student.enroll("MATH101")
    student.enroll("PHYS101")
    transcript = Transcript(student)

    transcript.record_grade("MATH101", 95)
    transcript.record_grade("PHYS101", 85)
    
    gpa = transcript.calculate_gpa()

    assert isinstance(gpa, float)
    assert 0.0 <= gpa <= 4.0
    assert transcript._grades["MATH101"] == 95
    assert transcript._grades["PHYS101"] == 85

def test_invalid_grade():
    student = Student(1002, "Another Student", "another@student.com")
    student.enroll("CS101")
    transcript = Transcript(student)

    # Invalid grades out of range
    with pytest.raises(ValueError, match="Invalid grade"):
        transcript.record_grade("CS101", 105)

    with pytest.raises(ValueError, match="Invalid grade"):
        transcript.record_grade("CS101", -10)

    # Not enrolled in HIST101
    with pytest.raises(ValueError, match="Not enrolled"):
        transcript.record_grade("HIST101", 90)
