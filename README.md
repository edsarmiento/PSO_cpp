# PSO_cpp — Project analysis and run instructions

## What this project is

**PSO Comparator Algorithm V2013GUI** is a C++ application that uses **Particle Swarm Optimization (PSO)** to find good **sequence alignments** between two DNA/RNA sequences (e.g. in NCBI GenBank format).

- **Authors (from code):** E. David Sarmiento, V. Alejandro Herrera Magallanes  
- **Tech stack:** C++, **GTKmm 2.4** (GUI), Glib (threading).

### Main components

| Component        | Role |
|-----------------|------|
| `UserInterface.cpp` | Entry point: starts GTK and shows the main window. |
| `PSO_Interface.cpp/h` | Main window: file choosers, “Align” button, PSO parameters (population, iterations, c1, c2, w), output text area. |
| `PSOThread.cpp/h`     | Worker thread: loads two sequences with `scannADN()`, runs `alinear()` in background, sends result to GUI. |
| `pso.cpp/h`           | PSO core: `basicPSO()`, `alinear()`, NUC44 scoring matrix, fitness and population helpers. |
| `Scanner.cpp/h`       | Reads GenBank-style files; extracts sequence from lines after `ORIGIN` until `//`. |
| `main.cpp`            | **Fully commented out**; legacy CLI/experimental code. The real `main()` is in `UserInterface.cpp`. |

### Data files

- `H1N1-HM124380`, `H1N1-HM145748`: example sequence files (used for testing).
- `PSOGUI.glade`: Glade UI file (current code builds the UI in C++, so this may be unused).
- `Salida.txt`: likely a sample output file.

---

## Why the build failed

The project did **not** build because **GTKmm 2.4** is not installed (and on many current Linux distros it is not available by default):

- `pkg-config` cannot find `gtkmm-2.4`.
- The Makefile uses `pkg-config --cflags gtkmm-2.4` and `--libs gtkmm-2.4`, and hardcodes `/usr/include/glibmm-2.4/glibmm.h`, which is missing.

So the failure is **missing dependencies**, not a bug in the project code.

---

## How to build and run

### 1. Install GTKmm 2.4 (if your distro has it)

**Debian/Ubuntu:**

```bash
sudo apt install libgtkmm-2.4-dev
```

**Fedora (legacy):**

```bash
sudo dnf install gtkmm24-devel
```

If `gtkmm-2.4` is not available (e.g. Fedora 43), you have two options:

- Use a different environment (Docker, older distro, or VM) where `gtkmm-2.4` is still packaged, or  
- Port the app to **GTKmm 3** (e.g. `gtkmm30`) and adjust includes/API; this requires code and Makefile changes.

### 2. Build

From the project root:

```bash
cd "/home/davidst/Downloads/mic/MCIC/TODO tesis/PSO_cpp"
make build
```

Or:

```bash
make
```

The executable is produced at:

- **Debug:** `dist/Debug/GNU-Linux-x86/pso_cpp`

### 3. Run

```bash
./dist/Debug/GNU-Linux-x86/pso_cpp
```

You need a display (X11/Wayland); the app opens a window where you:

1. Select two “ADN” (sequence) files (GenBank-style).
2. Optionally adjust PSO parameters (population, iterations, c1, c2, w).
3. Click **Align** to run PSO alignment; results appear in the output area.

---

## Optional: Fix Makefile flags

In `nbproject/Makefile-Debug.mk`, **libs** should not be in the compiler flags. Prefer:

- **Compiler (CXXFLAGS):** only `pkg-config --cflags gtkmm-2.4` (and `-g`, `-I`, etc.).
- **Linker:** add `pkg-config --libs gtkmm-2.4` to the link line (e.g. `LDLIBSOPTIONS`) so that linking picks up the GTKmm libraries.

If your system has a different package (e.g. `gtkmm-3.0`), replace `gtkmm-2.4` with that and adjust any hardcoded include paths accordingly.

---

## Summary

- **Project:** PSO-based sequence alignment with a GTKmm 2.4 GUI.  
- **Run:** Install `gtkmm-2.4` (or port to gtkmm3), then `make build` and run `dist/Debug/GNU-Linux-x86/pso_cpp`.  
- **Build failure cause:** Missing `gtkmm-2.4` (and glibmm-2.4) on your system.
