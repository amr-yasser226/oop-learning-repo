"""
student_management

A small school backend for managing Students, Instructors, Courses, and Transcripts.
"""

__version__ = "0.1.0"

# Expose core classes for easier imports:
from .person import Person
from .student import Student
from .instructor import Instructor
from .course import Course
from .transcript import Transcript
