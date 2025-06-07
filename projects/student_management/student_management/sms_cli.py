#!/usr/bin/env python3
import argparse
import logging
from student_management.sms_data import load_data, save_data
from student_management.student import Student
from student_management.instructor import Instructor
from student_management.course import Course

log = logging.getLogger(__name__)

# Command handlers

def add_instructor(args, ctx):
    inst = Instructor(args.id, args.name, args.email)
    ctx['instructors'][args.id] = inst
    log.info(f"Added instructor {args.id}")

def add_student(args, ctx):
    student = Student(args.id, args.name, args.email)
    ctx['students'][args.id] = student
    log.info(f"Added student {args.id}")

def add_course(args, ctx):
    course = Course(args.code, args.title, args.capacity)
    ctx['courses'][args.code] = course
    log.info(f"Added course {args.code}")

def enroll(args, ctx):
    student = ctx['students'].get(args.student)
    course = ctx['courses'].get(args.course)
    if not student:
        log.error(f"Student ID {args.student} not found")
        return
    if not course:
        log.error(f"Course code {args.course} not found")
        return
    try:
        student.enroll(course.code)
        course._students.append(student)  # keep course's student list in sync
        log.info(f"Enrolled student {args.student} in course {args.course}")
    except ValueError as e:
        log.error(str(e))

def record_grade(args, ctx):
    student = ctx['students'].get(args.student)
    course = ctx['courses'].get(args.course)
    if not student:
        log.error(f"Student ID {args.student} not found")
        return
    if not course:
        log.error(f"Course code {args.course} not found")
        return
    try:
        student.record_grade(course.code, args.grade)
        log.info(f"Recorded grade {args.grade} for student {args.student} in course {args.course}")
    except Exception as e:
        log.error(str(e))

def report_student(args, ctx):
    student = ctx['students'].get(args.id)
    if not student:
        log.error(f"Student ID {args.id} not found")
        return
    print(f"Transcript for {student.name} (ID: {student.id}):")
    for course_code, grade in student.get_transcript().items():
        course = ctx['courses'].get(course_code)
        if course:
            print(f"  {course.code} - {course.title}: Grade {grade}")
        else:
            print(f"  {course_code}: Grade {grade}")
    gpa = student.calculate_gpa()
    print(f"GPA: {gpa:.2f}")

# Main CLI setup

def main():
    parser = argparse.ArgumentParser(prog="sms", description="Student Management System CLI")
    parser.add_argument("-v", "--verbose", action="store_true", help="enable debug logging")
    sub = parser.add_subparsers(dest="cmd")

    # add-instructor
    p = sub.add_parser("add-instructor", help="Register a new instructor")
    p.add_argument("--id", required=True, type=int, help="Unique instructor ID")
    p.add_argument("--name", required=True, help="Instructor's full name")
    p.add_argument("--email", required=True, help="Instructor's email address")
    p.set_defaults(func=add_instructor)

    # add-student
    p = sub.add_parser("add-student", help="Register a new student")
    p.add_argument("--id", required=True, type=int, help="Unique student ID")
    p.add_argument("--name", required=True, help="Student's full name")
    p.add_argument("--email", required=True, help="Student's email address")
    p.set_defaults(func=add_student)

    # add-course
    p = sub.add_parser("add-course", help="Add a new course")
    p.add_argument("--code", required=True, help="Course code (unique)")
    p.add_argument("--title", required=True, help="Course title")
    p.add_argument("--capacity", required=True, type=int, help="Max capacity of the course")
    p.set_defaults(func=add_course)

    # enroll
    p = sub.add_parser("enroll", help="Enroll a student in a course")
    p.add_argument("--student", required=True, type=int, help="Student ID")
    p.add_argument("--course", required=True, help="Course code")
    p.set_defaults(func=enroll)

    # record-grade
    p = sub.add_parser("record-grade", help="Record a student's grade for a course")
    p.add_argument("--student", required=True, type=int, help="Student ID")
    p.add_argument("--course", required=True, help="Course code")
    p.add_argument("--grade", required=True, type=float, help="Grade (numeric)")
    p.set_defaults(func=record_grade)

    # report-student
    p = sub.add_parser("report-student", help="Show student's transcript and GPA")
    p.add_argument("--id", required=True, type=int, help="Student ID")
    p.set_defaults(func=report_student)

    args = parser.parse_args()
    logging.basicConfig(level=logging.DEBUG if args.verbose else logging.INFO)

    # Load data
    data = load_data()

    # Deserialize objects
    ctx = {
        'instructors': {int(k): Instructor.from_dict(v) for k, v in data.get('instructors', {}).items()},
        'students': {int(k): Student.from_dict(v) for k, v in data.get('students', {}).items()},
        'courses': {k: Course.from_dict(v) for k, v in data.get('courses', {}).items()},
    }

    # Re-link instructor and students to courses
    for code, course in ctx['courses'].items():
        course_data = data['courses'][code]
        instr_id = course_data.get('instructor_id')
        if instr_id is not None:
            course.instructor = ctx['instructors'].get(instr_id)
        student_ids = course_data.get('students_ids', [])
        course._students = [ctx['students'][sid] for sid in student_ids if sid in ctx['students']]

    if hasattr(args, 'func'):
        args.func(args, ctx)

        # Serialize back to dicts
        data_to_save = {
            'instructors': {str(k): v.to_dict() for k, v in ctx['instructors'].items()},
            'students': {str(k): v.to_dict() for k, v in ctx['students'].items()},
            'courses': {k: v.to_dict() for k, v in ctx['courses'].items()},
        }
        save_data(data_to_save)
    else:
        parser.print_help()

if __name__ == "__main__":
    main()
