# 🏰 Cub3D - My first Raycaster Engine

A 3D graphical game engine inspired by the legendary **Wolfenstein 3D**. This project explores the fundamentals of computer graphics using the **Raycasting** technique, developed in C from scratch.

---

## 🚀 Overview
The goal was to create a dynamic 3D perspective inside a 2D map. Every "wall" you see is the result of mathematical calculations (DDA algorithm) that determine the distance to the nearest obstacle and render it in real-time.

### 🛠 Tech Stack
![C](https://img.shields.io/badge/c-%2300599C.svg?style=for-the-badge&logo=c&logoColor=white)
![MiniLibX](https://img.shields.io/badge/Library-MiniLibX-orange)
![Math](https://img.shields.io/badge/Logic-Trigonometry%20%26%20DDA-red)

---

## ✨ Key Features
* **Real-time Raycasting:** Fast and efficient rendering using the **DDA (Digital Differential Analyzer)** algorithm.
* **Texture Mapping:** Different textures for North, South, East, and West walls.
* **Movement System:** Smooth movement with WASD and 360° camera rotation (rotation matrices).
* **Map Parsing:** Robust `.cub` file parser with error handling for invalid maps, missing textures, or open boundaries.
* **Floor/Ceiling:**

---

## 🧠 Technical Deep Dive
Cub3D was my first real challenge with **Computer Graphics**. It taught me:
* **Linear Algebra & Trig:** Using vectors and angles to project a 2D environment into 3D.
* **Buffer Management:** Writing directly to a pixel buffer for high-performance rendering instead of drawing pixel by pixel.
* **Event Handling:** Managing keyboard and mouse inputs efficiently via hooks.

---

## 🛠 Installation & Usage

### Prerequisites
* **X11** and **AppKit** (depending on your OS).
* **MiniLibX** (included in the repo).

### Compilation
```bash
make
```

### Running
```bash
./cub3d maps/map.cub
```
---
## 👥 The Team
This project was developed in collaboration with:
* **Giulia Viganò** - [@giuliavigano](https://github.com/giuliavigano/giuliavigano)
* **Manuel Chiaramello** - [@chiaramellomanuel](https://github.com/chiaramellomanuel)
