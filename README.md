# 🏰 Cub3D - 125/100 Project

A 3D graphical game engine inspired by the legendary **Wolfenstein 3D**. This project explores the fundamentals of computer graphics using the **Raycasting** technique, developed in C from scratch.

![Score](https://img.shields.io/badge/Score-125%2F100-brightgreen?style=for-the-badge)

---

## 🚀 Overview
The goal was to create a dynamic 3D perspective inside a 2D map. This version includes the **full bonus set**, extending the engine with advanced features like minimaps, and wall collisions.

### 🛠 Tech Stack
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![MiniLibX](https://img.shields.io/badge/Library-MiniLibX-orange)
![Math](https://img.shields.io/badge/Logic-Trigonometry%20%26%20DDA-red)

---

## ✨ Features & Bonus (125/100)
* **DDA Raycasting Engine:** Fast and efficient rendering with wall texture mapping.
* **🎯 Wall Collisions:** Realistic movement that prevents passing through walls.
* **🗺️ Interactive Minimap:** Real-time top-down view of the player's position and orientation.
* **🖱️ Mouse Look:** Smooth camera rotation using the mouse (360°).
* **🎨 Floor & Ceiling Textures:** Beyond simple colors, supporting full texture mapping for all surfaces.

---

## 🧠 Technical Deep Dive
Cub3D was my first real challenge with **Computer Graphics**. It taught me:
* **Rotation Matrices:** To rotate the player's direction and camera plane vectors.
* **DDA Algorithm:** Precise calculation of the distance to the next wall to avoid fish-eye distortion.
* **Buffer Management:** Writing directly to a pixel buffer for high-performance rendering.

---

## 🛠 Installation & Usage

### Prerequisites
* **X11** and **AppKit** (depending on your OS).
* **MiniLibX** (included in the repo).

### Compilation & Running
```bash
make
./cub3d maps/map.cub
```

### Bonus
```bash
make bonus
./cub3d_bonus maps/map.cub
```
---
## 🧪 Automated Testing & QA
To ensure the robustness of the map parser, I developed a **custom Bash Testing Suite**. This allowed us to validate the engine against hundreds of edge cases and ensure 100% stability before the final evaluation.

### Features of the Tester:
* **Validation Categories:** Separate tests for file naming, texture paths, color gradients, and complex map geometries.
* **Expected Output Comparison:** Automatically compares the engine's error messages with expected logs using `diff`.
* **Memory Leak Detection:** Integrated **Valgrind** support to ensure every parsing error is handled without memory leaks (Exit code 42 on failure).
* **Regression Safety:** Allows for rapid testing of the entire codebase after any architectural change.

### How to run tests:
```bash
# Standard test
./tester.sh

# Test with Valgrind leak detection
./tester.sh valgrind
```
---
## 👥 The Team
This project was developed in collaboration with:
* **Giulia Viganò** - [@giuliavigano](https://github.com/giuliavigano/giuliavigano)
* **Manuel Chiaramello** - [@chiaramellomanuel](https://github.com/chiaramellomanuel)
