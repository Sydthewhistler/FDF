# FDF — 3D Wireframe Renderer

A lightweight 3D wireframe visualization tool written in C. Reads a 2D height map and renders it as an interactive isometric projection in a native X11 window.

---

## Table of Contents

- [Overview](#overview)
- [Features](#features)
- [Project Structure](#project-structure)
- [Dependencies](#dependencies)
- [Build](#build)
- [Usage](#usage)
- [Controls](#controls)
- [Map Format](#map-format)
- [Architecture](#architecture)

---

## Overview

FDF (*Fil de Fer*, French for "wireframe") takes a plain-text height map as input and displays it as a real-time 3D isometric wireframe. The rendering pipeline applies a full 3D rotation matrix before projecting vertices onto the screen, allowing the user to rotate, translate, and zoom the scene interactively via keyboard.

The renderer is built on top of **MinilibX**, a minimal X11 graphics library, and uses direct pixel-buffer manipulation for performance.

---

## Features

- Isometric 3D projection with configurable angle
- Hypsometric color palette (geographic elevation tint): deep water → coast → plains → forest → uplands → rocky terrain → snow caps, smoothly interpolated along every edge
- Real-time keyboard-driven rotation on all three axes (X, Y, Z)
- Translation and zoom controls
- Bresenham-style line drawing connecting adjacent vertices
- Fully dynamic map loading — any grid size is supported
- Zero external runtime dependencies beyond X11

---

## Project Structure

```
FDF/
├── main.c          — Entry point, argument handling
├── FDF.c           — MLX window init, render loop
├── import_map.c    — Height map parser
├── put_pixel.c     — 3D→2D projection, pixel & line drawing
├── utils.c         — Keyboard hooks, memory cleanup
├── header.h        — Structures, constants, function prototypes
├── libft/          — Custom C utility library
│   ├── libft.h
│   ├── ft_printf.h
│   ├── get_next_line.h
│   └── *.c
├── minilibx-linux/ — X11 graphics library (fetched at setup)
├── maps/           — Sample height maps (fetched at setup)
└── Makefile
```

---

## Dependencies

| Dependency     | Purpose                              |
|----------------|--------------------------------------|
| `clang`        | C compiler                           |
| `MinilibX`     | X11 window & image management        |
| `libX11`       | X Window System protocol             |
| `libXext`      | X11 extensions                       |
| `libm`         | Math functions (`sin`, `cos`)        |
| `libz`         | Compression (MinilibX dependency)    |

On a Debian/Ubuntu system, install the required headers with:

```bash
sudo apt-get install clang libx11-dev libxext-dev zlib1g-dev
```

---

## Build

### First-time setup

Downloads and compiles MinilibX and sample maps, then compiles `libft`:

```bash
make start
```

### Compile the project

```bash
make
```

Produces the `fdf` executable in the project root.

### Rebuild from scratch

```bash
make re
```

### Clean object files

```bash
make clean
```

### Remove the binary and object files

```bash
make fclean
```

### Full reset (remove all generated files and libraries)

```bash
make superclean
```

> **Note:** `make superclean` removes `minilibx-linux/`, `libft/libft.a`, and any downloaded test maps. Run `make start` again afterwards to restore them.

---

### Makefile targets at a glance

| Target       | Description                                              |
|--------------|----------------------------------------------------------|
| `all`        | Build the `fdf` executable (default)                             |
| `debug`      | Build with `-g3` and AddressSanitizer (implies `re`)             |
| `start`      | Download dependencies and compile everything                     |
| `download`   | Fetch MinilibX and sample maps only                              |
| `clean`      | Remove `.o` object files                                         |
| `fclean`     | Remove `.o` files and the `fdf` binary                           |
| `re`         | Full rebuild (`fclean` + `all`)                                  |
| `superclean` | Remove all generated files including libraries and maps          |

### Compiler flags

| Flag           | Purpose                                    |
|----------------|--------------------------------------------|
| `-Wall`        | Enable all standard warnings               |
| `-Wextra`      | Enable extra warnings                      |
| `-Werror`      | Treat every warning as an error            |
| `-lXext -lX11` | Link against X11 and its extensions        |
| `-lm`          | Link against the math library              |
| `-lz`          | Link against zlib                          |
| `-g3`          | Include maximum debug symbols              |

---

## Usage

```bash
./fdf <map_file>
```

**Example:**

```bash
./fdf maps/42.fdf
./fdf maps/julia.fdf
./fdf maps/pyramide.fdf
```

---

## Controls

| Key              | Action                          |
|------------------|---------------------------------|
| `Arrow keys`     | Translate view (pan)            |
| `Z` / `X`        | Zoom in / Zoom out              |
| `A` / `Q`        | Rotate around X axis            |
| `S` / `W`        | Rotate around Y axis            |
| `D` / `E`        | Rotate around Z axis            |
| `ESC`            | Quit                            |
| Window close `×` | Quit                            |

---

## Map Format

Maps are plain-text files containing a grid of space-separated integers. Each integer represents the elevation (Z value) at that grid position.

```
0  0  0  0  0
0  5 10  5  0
0 10 20 10  0
0  5 10  5  0
0  0  0  0  0
```

- Positive values → raised terrain
- Negative values → lowered terrain (valleys, craters)
- All rows must have the same number of columns

---

## Architecture

```
main()
  └── import_map()        Parse height map file into a 2D int array
        └── ft_fdf()      Initialize MLX window (1920×1080), set default view params
              └── new_img()
                    └── create_img()
                          ├── put_pixel_iso()    Apply 3D rotation matrix → isometric projection → draw vertex
                          └── make_connections() Draw edges (Bresenham) between adjacent vertices

key_hook()                Keyboard events → update rotation/translation params → trigger new_img()
event_hook()              Window close event → clean exit
```

The 3D→2D transformation applies three successive rotation matrices (around X, Y, Z) followed by a parallel isometric projection. All rendering is done by writing directly into an MLX image buffer, which is then flushed to the window in a single call.
