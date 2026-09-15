# Advanced C – Homework Assignments

This folder contains homework assignments for **Advanced C (Fall 2025)**.
Each assignment corresponds to lecture notes and has been structured with CMake for easy build and testing.

---

## 📂 Assignments

### 🔹 Error Handling – *September 10, 2025*

**File:** `src/errorHandler.c`

* Demonstrates runtime error handling using **assertions** and **errno**.
* Example: catching division by zero and failing gracefully.

---

### 🔹 Unit Testing – *September 11, 2025*

**Files:**

* `src/name_length.c`, `src/main.c`
* `tests/test_name_length.c` (with `third_party/utest.h`)
* `include/name_length.h`

Implements a small library (`name_length`) and validates it with **unit tests** using `utest.h` and **CTest**.

---

### 🔹 Pointers Exercises – *September 23–24, 2025*

**Files:** `pointers_1.c`, `pointersQuestions.c`

* Practice with **pointers, pointer arithmetic, null pointers, passing by value/pointer**, and memory safety.
* Based on lessons on pointers and memory management.

---

## ⚙️ Build & Run

From the `homeWork/` root:

```bash
conda activate myenv
cmake -B build
cmake --build build
```

Run executables:

```bash
./build/src/errorHandler          # Error handling assignment
./build/src/main                  # Unit testing assignment (name_length)
./build/pointers_1                # Pointers exercise 1
./build/pointersQuestions         # Pointers exercise 2
```

Run tests:

```bash
ctest --test-dir build -V
```

---

## 📝 Notes

Assignments are based on the following lecture notes:

* **Error Handling** – Sept 10, 2025
* **Error Handling II: Unit Testing** – Sept 25, 2025
* **Pointers** – Sept 29, 2025
* **Structs & Unions** – Sept 29, 2025
