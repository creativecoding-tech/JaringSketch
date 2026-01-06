## JaringSketch | OpenFrameworks Grid Animation

Eksperimen grid dengan animasi bezier yang smooth dan efek trails. Project ini adalah eksplorasi creative coding dengan openFrameworks untuk membuat pola grid yang dapat beranimasi dengan sistem easing yang halus.

[![OpenFrameworks](https://img.shields.io/badge/OpenFrameworks-0.12.1-blue)](https://openframeworks.cc/)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![License](https://img.shields.io/badge/License-Apache%202.0-green)
![Branch](https://img.shields.io/badge/Branch-sketch--basic-orange)

[![Fund The Experiments](https://img.shields.io/badge/Fund-The_Experiments-FF5722?style=for-the-badge&logo=buy-me-a-coffee)](https://sociabuzz.com/abdkdhni)

---

## 📺 Demo Video

Lihat hasilnya di YouTube: [Watch Demo](https://youtu.be/KFa9IZEcgQQ)

---

## 📺 Preview

Project ini menampilkan grid node dengan animasi transisi yang smooth menggunakan ease-in-ease-out interpolation.

---

## ✨ Fitur & Teknik

- **Grid Layout System** — 2D grid dengan node yang terkonfigurasi (cols & rows)
- **Smooth Animation** — Ease-in-ease-out interpolation untuk transisi posisi yang halus
- **Trails Effect** — Semi-transparent overlay untuk efek jejak visual yang menarik
- **Strategy Pattern** — Arsitektur yang fleksibel untuk animasi dan pewarnaan
- **Modular Design** — Terpisah dalam kategori: `anim/`, `clr/`, `shp/`, `strategy/`
- **Interactive Controls** — Keyboard shortcuts untuk kontrol realtime
- **Anti-Aliasing & Smoothing** — Garis dan kurva yang smooth untuk visual yang lebih baik

---

## 🎮 Controls

| Input | Action |
| --- | --- |
| **Key 'S'** | Toggle visibility shape grid (Show/Hide) |
| **Key 'R'** | Reset animasi ke posisi awal |
| **Key 'Q'** | Keluar dari aplikasi |
| **Right Click** | Toggle visibilitas kursor |

---

## 🛠️ Tech Stack

- **[OpenFrameworks 0.12.1](https://openframeworks.cc/)**
- **C++17**
- **Visual Studio 2022 Community** (v143 toolset)
- **Strategy Pattern** untuk arsitektur yang fleksibel
- **Bezier Curve Algorithms** untuk smooth animations

---

## 📦 Installation

### Prerequisites

1. Install **[OpenFrameworks](https://openframeworks.cc/)** untuk Windows
2. Install **Visual Studio 2022 Community** dengan workload "Desktop development with C++"

### Setup

```bash
# Clone repository ini
git clone https://github.com/username/JaringSketch.git

# Checkout branch sketch-basic
git checkout sketch-basic

# Buka Visual Studio
# Double-click: JaringSketch.sln

# Build & Run
# Press F5 atau klik "Local Windows Debugger"
```

---

## 🧬 Mathematics Behind

### Ease-In-Ease-Out Animation

Transisi posisi node menggunakan fungsi easing untuk smooth acceleration dan deceleration:

```cpp
// Ease-in-ease-out formula
t = progress / duration
if (t < 0.5) {
    value = 2 * t * t
} else {
    value = -1 + (4 - 2 * t) * t
}
```

### Grid System

Setiap node diposisikan berdasarkan:

```
x = margin + col * (cellSize + margin)
y = margin + row * (cellSize + margin)
```

### Trails Effect

Efek jejak dicapai dengan semi-transparent background clear:

```cpp
ofSetColor(0, 60);  // Alpha 60 untuk trails
ofDrawRectangle(0, 0, width, height);
```

---

## 📁 Project Structure

```
JaringSketch/
├── src/
│   ├── main.cpp              # Entry point aplikasi
│   ├── ofApp.cpp/h           # Main application class
│   ├── Node.cpp/h            # Node class (posisi & animasi)
│   ├── anim/
│   │   └── EaseInOutAnimation.cpp/h  # Easing strategy
│   ├── clr/
│   │   └── SolidColor.cpp/h          # Color strategy
│   ├── shp/
│   │   └── GridBezier.cpp/h          # Grid shape dengan bezier
│   └── strategy/
│       ├── AnimationStrategy.h       # Interface untuk animasi
│       ├── ColorStrategy.cpp/h       # Interface untuk warna
│       └── Shape.h                   # Base class untuk shapes
├── bin/                    # Compiled executable
├── dll/                    # OF dependencies
├── obj/                    # Intermediate files (gitignored)
└── JaringSketch.sln/.vcxproj  # Visual Studio project files
```

---

## 🎯 Purpose

Project ini adalah bagian dari eksplorasi **Creative Coding** dan pembelajaran:

- 🔬 Eksperimen grid systems dan geometric patterns
- 🎨 Belajar design patterns (Strategy Pattern) dalam C++
- ⚡ Implementasi smooth animations dengan easing functions
- 📚 Memahami arsitektur modular untuk visual programming
- 🌿 Fondasi untuk project visualisasi yang lebih kompleks

---

## 🚀 Performance

Dengan optimasi C++ modern dan openFrameworks:

- **Solid 120 FPS** pada resolusi bervariasi
- **Smooth easing** tanpa lag
- **Anti-aliased rendering** untuk kualitas visual tinggi
- **CPU-based rendering** (ideal untuk basic grid systems)

---

## 📝 Current Status: **sketch-basic**

Branch ini adalah **basic implementation** dari JaringSketch. Fitur yang tersedia:

✅ Grid layout system dengan konfigurasi cols/rows
✅ Ease-in-ease-out animation
✅ Trails effect
✅ Strategy pattern untuk animasi & warna
✅ Basic keyboard controls

🎨 **Creative Freedom**: Project ini terbuka untuk eksplorasi dan improvisasi tanpa batas. Seni digital adalah tentang ekspresi, bukan checklist.

---

## 🤝 Contributing

Ide, saran, dan improvement sangat welcome! Feel free to share your experiments!

---

## 📄 License

This project is licensed under the **Apache License 2.0** - see the LICENSE file for details.

---

## 🙏 Credits & References

- **OpenFrameworks** - Creative coding framework
- **Kuman** - Sister project untuk phyllotaxis patterns
- **Creative Coding Community** - Inspirasi dan resources

---

## 🔗 Links

- **[OpenFrameworks](https://openframeworks.cc/)** - openframeworks.cc
- **[ofxGui Addon](https://ofxaddons.com/categories/1-gui)** - ofxGui documentation
- **[Watch Demo](https://youtu.be/KFa9IZEcgQQ)** - YouTube demonstration
- **[Support Me](https://sociabuzz.com/abdkdhni)** - Fund the experiments ☕

---

**Made with ❤️ for learning and creative exploration**
