# PSO_cpp — Project analysis and run instructions

## What this project is

**PSO Comparator Algorithm V2013GUI** is a C++ application that uses **Particle Swarm Optimization (PSO)** to find good **sequence alignments** between two DNA/RNA sequences (e.g. in NCBI GenBank format).

- **Authors (from code):** E. David Sarmiento
- **Tech stack:** C++, **GTKmm 3.0** (GUI), glibmm (threading via `std::thread` + `Glib::Dispatcher`).

### Source layout (refactored)

Code is split by responsibility with namespaces `pso::core`, `pso::io`, `pso::gui`:

| Directory / file | Role |
|------------------|------|
| **src/main.cpp** | Entry point: starts GTK, runs `pso::gui::MainWindow`. |
| **src/core/** | PSO algorithm and alignment (no GUI). |
| `scoring.h/cpp` | NUC44 matrix, `nucleotide_to_int()`, `drandom()`. |
| `pso_algorithm.h/cpp` | `get_initial_population()`, `basic_pso()`, `fitness_nuc44()`. |
| `pairwise_align.h/cpp` | Smith–Waterman local alignment **with gaps** (affine gap penalty), NUC44. |
| `alignment.h/cpp` | `align_sequences()`: PSO finds best region, then Smith–Waterman with gaps produces the final alignment. |
| **src/io/** | File I/O. |
| `genbank_reader.h/cpp` | `load_sequence_from_genbank()` — reads sequence from NCBI GenBank-style files. |
| **src/gui/** | GTK UI. |
| `main_window.h/cpp` | Main window: file choosers, PSO parameters, output text area. |
| `alignment_worker.h/cpp` | Background thread: loads sequences, calls `align_sequences()`, signals when done. |

### Data files

- `H1N1-HM124380`, `H1N1-HM145748`: example sequence files (used for testing).
- `PSOGUI.glade`: Glade UI file (current code builds the UI in C++, so this may be unused).
- `Salida.txt`: likely a sample output file.

---

## How to build and run

### Quick start (after installing GTKmm 3.0)

From the project root directory:

```bash
make
./dist/Debug/GNU-Linux-x86/pso_cpp
```

- **`make`** — compiles the project and produces the executable.
- **`./dist/Debug/GNU-Linux-x86/pso_cpp`** — runs the GUI application.

To do a clean rebuild:

```bash
make clean
make
./dist/Debug/GNU-Linux-x86/pso_cpp
```

---

### 1. Install GTKmm 3.0 (first time only)

The project is ported to **GTKmm 3.0**. Install the development package:

**Fedora / RHEL:**

```bash
sudo dnf install gtkmm30-devel
```

**Debian / Ubuntu:**

```bash
sudo apt install libgtkmm-3.0-dev
```

**Arch:**

```bash
sudo pacman -S gtkmm-3.0
```

The project uses a **standalone Makefile** (no NetBeans/IDE project files). The Makefile looks for `gtkmm-3.0` or `gtkmm3.0` via `pkg-config`.

### 2. Build

From the project root:

```bash
make
```

(or `make build`). The executable is created at **`dist/Debug/GNU-Linux-x86/pso_cpp`**.

To remove build artifacts and the executable:

```bash
make clean
```

### 3. Run

```bash
./dist/Debug/GNU-Linux-x86/pso_cpp
```

You need a display (X11/Wayland). The app opens a window where you:

1. Select two “ADN” (sequence) files (GenBank-style).
2. Optionally adjust PSO parameters (population, iterations, c1, c2, w).
3. Click **Align** to run PSO alignment; results appear in the output area.

---

## Port from GTKmm 2.4 to 3.0 (summary of changes)

- **Makefiles:** Use `pkg-config gtkmm-3.0` (or `gtkmm3.0`); compiler gets `--cflags`, linker gets `--libs`. No hardcoded includes.
- **Widgets:** `Gtk::Table` → `Gtk::Grid`; `Gtk::HBox`/`Gtk::VBox` → `Gtk::Box` with `Gtk::ORIENTATION_*`; `Gtk::Alignment` removed (margins on `Gtk::ScrolledWindow`).
- **API:** `Gtk::Label::set_alignment(x, y)` now uses floats 0.0–1.0; `set_position(Gtk::WindowPosition::WIN_POS_CENTER)`; `modify_font()` → `override_font()`.
- **Threading:** `Glib::Thread` replaced by `std::thread`; `Glib::Dispatcher` used to emit `signal_finished_()` on the main thread (GTK-safe).

---

## Summary

- **Project:** PSO-based sequence alignment with a **GTKmm 3.0** GUI.  
- **Run:** Install `gtkmm-3.0` (e.g. `gtkmm30-devel` on Fedora, `libgtkmm-3.0-dev` on Debian/Ubuntu), then `make build` and run `dist/Debug/GNU-Linux-x86/pso_cpp`.
