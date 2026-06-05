<div align="center">

# 🎯 Monte Carlo PI Estimator

**A real-time visual simulation that approximates π using randomness and geometry**

![C++](https://img.shields.io/badge/C++-17-00599C?style=for-the-badge&logo=cplusplus&logoColor=white)
![Raylib](https://img.shields.io/badge/Raylib-4.0+-FF4500?style=for-the-badge&logo=raylib&logoColor=white)
![Platform](https://img.shields.io/badge/Platform-Linux%20%7C%20Windows-informational?style=for-the-badge)
![License](https://img.shields.io/badge/License-MIT-green?style=for-the-badge)

</div>

---

## 📖 What Is This?

This project uses the **Monte Carlo method** to estimate the value of **π (pi)** in real time with a visual simulation. Random points are scattered across a square, and the ratio of those landing inside an inscribed circle is used to compute π — all rendered live with Raylib.

> **The idea:** If you randomly throw darts at a square with an inscribed circle, the fraction that land inside the circle ≈ π/4. Scale by 4 and you get π.

---

## 🎬 How It Works

```
┌──────────────────────────┐
│      ·  ·   · (red)      │
│   ·  ╭──────────╮  ·     │
│    · │ · (green)│ ·      │
│      │    ●     │        │
│    · │  (green) │ ·      │
│      ╰──────────╯        │
│  ·      ·    ·  (red)    │
└──────────────────────────┘
   π ≈ 4 × (inside / total)
```

1. A **circle** is inscribed inside a **square**
2. **N random points** are generated uniformly across the square each frame
3. Points **inside** the circle → 🟢 green | Points **outside** → 🔴 red
4. **π ≈ 4 × (green points) / (total points)**

The more points, the closer the estimate converges to **3.14159...**

---

## ✨ Features

- 🔴🟢 **Live visual rendering** of random point distribution
- 🎚️ **Interactive slider** — adjust iterations from 100 to 20,000 per frame
- 📊 **Real-time π estimate** displayed on screen, updated every frame
- ⚡ **Lightweight** — single C++ file, no heavy dependencies

---

## 📁 Project Structure

```
Monte-Carlo-main/
├── src/
│   ├── main.cpp       # Simulation logic + Raylib rendering
│   └── raygui.h       # Single-header GUI library (slider UI) — bundled, no install needed
├── Makefile           # Linux/macOS build script
├── app                # Pre-compiled Linux binary
└── .gitignore
```

---

## 🛠️ Building & Running

### 🐧 Linux / macOS

**Install Raylib:**

```bash
# Ubuntu/Debian
sudo apt install libraylib-dev

# macOS (Homebrew)
brew install raylib
```

**Build and run:**

```bash
make run
```

Or manually:

```bash
g++ src/main.cpp -o app -Isrc -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -std=c++17
./app
```

---

### 🪟 Windows (MSYS2 — Recommended)

> ⚠️ The `Makefile` links Linux-only libraries and **will not work on Windows**. Use the steps below instead.

**Step 1 — Install [MSYS2](https://www.msys2.org)** and open the **MinGW64** terminal

**Step 2 — Install dependencies:**

```bash
pacman -Syu
pacman -S mingw-w64-x86_64-gcc mingw-w64-x86_64-raylib
```

**Step 3 — Navigate to the project folder:**

```bash
cd Monte-Carlo-main
```

**Step 4 — Compile:**

```bash
g++ src/main.cpp -o MonteCarloPI -Isrc -lraylib -lopengl32 -lgdi32 -lwinmm -std=c++17
```

**Step 5 — Run:**

```bash
./MonteCarloPI.exe
```

> **Why different flags?** On Windows, `-lGL -lX11` are replaced with `-lopengl32 -lgdi32 -lwinmm` — the Windows equivalents for OpenGL and windowing.

---

### 🪟 Windows (Visual Studio + vcpkg)

```bash
vcpkg install raylib
```

Then create a project, add `src/main.cpp`, and link against raylib via vcpkg integration.

---

## 🎮 Controls

| Control | Description |
|---|---|
| **Slider** (top-left) | Drag to set iterations per frame (100 – 20,000) |
| **PI display** (top-left) | Live π estimate, updates every frame |
| **Iterations display** | Shows current iteration count |
| **Close / `Esc`** | Exit the simulation |

---

## 🔧 Compiler Flags Reference

| Flag | Purpose |
|---|---|
| `-Isrc` | Include path for `raygui.h` |
| `-lraylib` | Link Raylib graphics library |
| `-lGL` / `-lopengl32` | OpenGL backend (Linux / Windows) |
| `-lX11` / `-lgdi32` | Window management (Linux / Windows) |
| `-lwinmm` | Windows multimedia (timing/audio) |
| `-std=c++17` | Enable C++17 features |

---

## ❓ Troubleshooting

<details>
<summary><b>raylib.h: No such file or directory</b></summary>

Raylib is not installed or not on the include path.

- **MSYS2:** `pacman -S mingw-w64-x86_64-raylib`
- **Ubuntu:** `sudo apt install libraylib-dev`
- Make sure you're in the **MinGW64** terminal (not plain MSYS2) on Windows

</details>

<details>
<summary><b>Linker errors (undefined reference)</b></summary>

Ensure all `-l` flags are present and in the correct order. Keep `-lraylib` before the system libraries:

```bash
-lraylib -lopengl32 -lgdi32 -lwinmm   # Windows
-lraylib -lGL -lm -lpthread -ldl -lrt -lX11   # Linux
```

</details>

<details>
<summary><b>Window is blank or crashes immediately</b></summary>

Your GPU drivers may not support the required OpenGL version. Try:
1. Update your graphics drivers
2. Add `-DGRAPHICS_API_OPENGL_21` to force OpenGL 2.1 compatibility mode

</details>

<details>
<summary><b>make doesn't work on Windows</b></summary>

Expected — the `Makefile` uses Linux-only library flags. Use the manual `g++` command in the Windows section above.

</details>

---

## 📚 Dependencies

| Dependency | Version | Notes |
|---|---|---|
| **g++ / MinGW-w64** | ≥ 9.0 | C++17 support required |
| **Raylib** | ≥ 4.0 | Graphics & windowing |
| **raygui.h** | Bundled | Already in `src/` — no install needed |

---

## 🧮 The Math

The Monte Carlo method exploits a geometric probability:

$$\frac{\text{Area of circle}}{\text{Area of square}} = \frac{\pi r^2}{(2r)^2} = \frac{\pi}{4}$$

So:

$$\pi \approx 4 \times \frac{\text{points inside circle}}{\text{total points}}$$

As the number of random samples → ∞, the estimate → π.

---

<div align="center">

Made with ❤️ and randomness &nbsp;|&nbsp; Built with [Raylib](https://www.raylib.com)

</div>
