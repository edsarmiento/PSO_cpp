# PSO_cpp — Project analysis and run instructions

## What this project is

**PSO Comparator Algorithm V2013GUI** is a C++ application that uses **Particle Swarm Optimization (PSO)** to find good **sequence alignments** between two DNA/RNA sequences (e.g. in NCBI GenBank format).

- **Authors (from code):** E. David Sarmiento, V. Alejandro Herrera Magallanes  
- **Tech stack:** C++, **GTKmm 3.0** (GUI), glibmm (threading via `std::thread` + `Glib::Dispatcher`).

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

## How to build and run

### 1. Install GTKmm 3.0

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

The Makefile looks for `gtkmm-3.0` or `gtkmm3.0` via `pkg-config`.

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

## Port from GTKmm 2.4 to 3.0 (summary of changes)

- **Makefiles:** Use `pkg-config gtkmm-3.0` (or `gtkmm3.0`); compiler gets `--cflags`, linker gets `--libs`. No hardcoded includes.
- **Widgets:** `Gtk::Table` → `Gtk::Grid`; `Gtk::HBox`/`Gtk::VBox` → `Gtk::Box` with `Gtk::ORIENTATION_*`; `Gtk::Alignment` removed (margins on `Gtk::ScrolledWindow`).
- **API:** `Gtk::Label::set_alignment(x, y)` now uses floats 0.0–1.0; `set_position(Gtk::WindowPosition::WIN_POS_CENTER)`; `modify_font()` → `override_font()`.
- **Threading:** `Glib::Thread` replaced by `std::thread`; `Glib::Dispatcher` used to emit `signal_finished_()` on the main thread (GTK-safe).

---

## Summary

- **Project:** PSO-based sequence alignment with a **GTKmm 3.0** GUI.  
- **Run:** Install `gtkmm-3.0` (e.g. `gtkmm30-devel` on Fedora, `libgtkmm-3.0-dev` on Debian/Ubuntu), then `make build` and run `dist/Debug/GNU-Linux-x86/pso_cpp`.
