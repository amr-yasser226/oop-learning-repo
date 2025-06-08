#!/usr/bin/env bash
set -e

# ——————————————————————————————————————
# 1) Backup or wipe any existing data
# ——————————————————————————————————————
cp sms_data.json sms_data.json.bak 2>/dev/null || true
echo '{"instructors":{},"students":{},"courses":{}}' > sms_data.json

# ——————————————————————————————————————
# 2) Add an instructor
# ——————————————————————————————————————
echo ">> Adding instructor Dr. Einstein"
python -m student_management.sms_cli add-instructor \
    --id 1 \
    --name "Dr. Einstein" \
    --email "einstein@university.edu"

# ——————————————————————————————————————
# 3) Add a student
# ——————————————————————————————————————
echo ">> Adding student Alice Smith"
python -m student_management.sms_cli add-student \
    --id 1 \
    --name "Alice Smith" \
    --email "alice.smith@student.edu"

# ——————————————————————————————————————
# 4) Add a course (no instructor flag here)
# ——————————————————————————————————————
echo ">> Adding course Relativity101 (capacity 30)"
python -m student_management.sms_cli add-course \
    --code Relativity101 \
    --title "Relativity 101" \
    --capacity 30

# ——————————————————————————————————————
# 5) Enroll student #1 in course Relativity101
# ——————————————————————————————————————
echo ">> Enrolling student 1 in course Relativity101"
python -m student_management.sms_cli enroll \
    --student 1 \
    --course Relativity101

# ——————————————————————————————————————
# 6) Record a grade “95” for that enrollment
# ——————————————————————————————————————
echo ">> Recording grade 95 for student 1, course Relativity101"
python -m student_management.sms_cli record-grade \
    --student 1 \
    --course Relativity101 \
    --grade 95

# ——————————————————————————————————————
# 7) Print the transcript & GPA for student #1
# ——————————————————————————————————————
echo ">> Generating report for student 1"
python -m student_management.sms_cli report-student \
    --id 1

# ——————————————————————————————————————
# 8) Restore original data
# ——————————————————————————————————————
echo
echo ">> Restoring original sms_data.json (if any)"
mv sms_data.json.bak sms_data.json 2>/dev/null || true
