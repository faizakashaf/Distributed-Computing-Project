# 🗳️ Leader Election Using Bully Algorithm (C Project)

This project is a simulation of the **Bully Algorithm** for leader election in distributed systems, implemented in the C programming language. It demonstrates how processes (nodes) can elect a coordinator dynamically, especially in the event of a node failure.

---

## 📌 Features

- Terminal-based UI with color-coded output using ANSI escape codes.
- Simulates activation and failure of nodes.
- Handles election process dynamically with recursive logic.
- Displays current status of nodes and coordinator.
- Easy to compile and run on any system with a C compiler.

---

## 🛠️ Requirements

- GCC Compiler (or any standard C compiler)
- Linux/macOS/WSL terminal (for color support)

---

## 📁 Files

- `bully.c` – Main C file containing the simulation code.
- `README.md` – Project documentation.
- `Bully_Algorithm_Project_Report.pdf` – Brief description/report for submission.

---

## 🚀 How to Compile and Run

```bash
gcc bully.c -o bully
./bully
