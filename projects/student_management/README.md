# Student Management System

A simple, object‑oriented Python CLI application to manage students, instructors, courses, enrollments, and grades. Data is persisted in JSON (`sms_data.json`), and the system exposes commands to add entities, enroll students, record grades, and generate transcripts with GPA calculations.

---

## Table of Contents

* [Features](#features)
* [Project Structure](#project-structure)
* [Installation](#installation)
* [Usage](#usage)

  * [Available Commands](#available-commands)
  * [Quick Start Script](#quick-start-script)
* [Configuration & Data Storage](#configuration--data-storage)
* [Testing](#testing)
* [Contributing](#contributing)
* [License](#license)

---

## Features

* **OOP Design**: `Student`, `Instructor`, `Course`, `Transcript`, and `Person` classes with clear responsibilities.
* **Persistence**: Data stored in `sms_data.json` via `sms_data.py` helper functions.
* **CLI Interface**: Add instructors, students, courses; enroll students; record grades; generate student reports.
* **Serialization**: `to_dict` / `from_dict` methods on models to convert between instances and JSON.
* **Testing**: 11 pytest unit tests cover all core functionality.

---

## Project Structure

```text
├── pyproject.toml              # Project metadata & dependencies
├── README.md                   # This documentation
├── sms_data.json               # JSON datastore
├── student_management/         # Package source
│   ├── course.py               # Course model
│   ├── instructor.py           # Instructor model
│   ├── person.py               # Abstract Person base class
│   ├── sms_cli.py              # CLI entrypoint & command handlers
│   ├── sms_data.py             # JSON load/save helpers
│   ├── student.py              # Student model & transcript delegation
│   └── transcript.py           # Grade recording & GPA logic
├── student_management.egg-info # Editable installation metadata
├── test_cli.sh                 # Integration script for demo/testing
└── tests/                      # pytest unit tests
    ├── test_course.py
    ├── test_instructor.py
    ├── test_person.py
    ├── test_student.py
    └── test_transcript.py
```

*Note: `.gitignore` excludes virtual environment files, compiled Python files, and other local artifacts.*

---

## Installation

1. **Clone the repository**

   ```bash
   git clone https://github.com/yourusername/student_management.git
   cd student_management
   ```

2. **Create and activate a virtual environment**

   ```bash
   python3 -m venv .venv
   source .venv/bin/activate
   ```

3. **Install dependencies in editable mode**

   ```bash
   pip install -e .
   ```

You now have the `sms` command available in your shell.

---

## Usage

### Available Commands

```bash
sms [-h] [-v]
    {add-instructor, add-student, add-course, enroll, record-grade, report-student} …
```

**Global Options**

* `-h, --help`   Show help message
* `-v, --verbose`  Enable debug logging

**Subcommands**

| Command          | Arguments                        | Description                                      |
| ---------------- | -------------------------------- | ------------------------------------------------ |
| `add-instructor` | `--id` `--name` `--email`        | Register a new instructor                        |
| `add-student`    | `--id` `--name` `--email`        | Register a new student                           |
| `add-course`     | `--code` `--title` `--capacity`  | Add a new course                                 |
| `enroll`         | `--student` `--course`           | Enroll a student in a course                     |
| `record-grade`   | `--student` `--course` `--grade` | Record a numeric grade for a student in a course |
| `report-student` | `--id`                           | Print student's transcript and calculated GPA    |

Example:

```bash
sms add-student --id 1 --name "Alice Smith" --email alice@example.com
sms add-course --code MATH101 --title "Math 101" --capacity 30
sms enroll --student 1 --course MATH101
sms record-grade --student 1 --course MATH101 --grade 92
sms report-student --id 1
```

### Quick Start Script

A sample integration script `test_cli.sh` walks through all commands end‑to‑end:

```bash
chmod +x test_cli.sh
./test_cli.sh
```

It will:

1. Reset `sms_data.json`
2. Add an instructor & a student
3. Add a course
4. Enroll the student
5. Record a grade
6. Generate and display the transcript & GPA

---

## Configuration & Data Storage

* All data is stored in `sms_data.json` at the project root.
* The JSON schema:

  ```json
  {
    "instructors": { "<id>": {…} },
    "students": { "<id>": {…} },
    "courses": { "<code>": {…} }
  }
  ```
* Models implement `to_dict()`/`from_dict()` for JSON (de)serialization.

---

## Testing

Run unit tests with pytest:

```bash
pytest -v
```

All tests under `tests/` should pass, covering edge cases and model behaviors.

---

## Contributing

1. Fork the repository
2. Create a feature branch: `git checkout -b feature/YourFeature`
3. Commit your changes: `git commit -m "Add feature X"`
4. Push to your fork: `git push origin feature/YourFeature`
5. Open a Pull Request

Please ensure all tests pass and follow the existing code style (PEP8, docstrings).

---

## License

This project is released under the [MIT License](LICENSE). Feel free to use and modify as needed.
