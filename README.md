## JaringSketch | OpenFrameworks Grid Animation

Eksperimen grid dengan animasi bezier yang smooth dan efek trails. Project ini adalah eksplorasi creative coding dengan openFrameworks untuk membuat pola grid yang dapat beranimasi dengan sistem easing yang halus.

[![OpenFrameworks](https://img.shields.io/badge/OpenFrameworks-0.12.1-blue)](https://openframeworks.cc/)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![License](https://img.shields.io/badge/License-Apache%202.0-green)
![Branch](https://img.shields.io/badge/Branch-sketch--basic--anim--color-orange)

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
- **Multiple Animation Strategies** — 5 jenis easing: Linear, Quadratic, Cubic, Wobble, dan Wave
- **Strategy Pattern** — Arsitektur yang fleksibel untuk animasi dan pewarnaan
- **Modular Design** — Terpisah dalam kategori: `anim/`, `clr/`, `shp/`, `strategy/`
- **Smooth Easing Functions** — Power-based easing (1, 2, 3) untuk tingkat smoothness berbeda
- **Special Effects** — Wobble (spring) dan Wave (gelombang) untuk creative animations
- **Trails Effect** — Semi-transparent overlay untuk efek jejak visual yang menarik
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

### Animation System dengan Strategy Pattern

Project ini menggunakan **Strategy Pattern** untuk sistem animasi yang fleksibel. Base class `AnimationStrategy` mendefinisikan interface, dan berbagai implementasi menyediakan easing functions yang berbeda.

#### Tipe Animasi Tersedia

| Animasi | File | Power | Karakteristik | Cocok Untuk |
|---------|------|-------|---------------|-------------|
| **Linear** | `LinearAnimation.cpp` | 1 | Kecepatan konstan | Loading bars, counters |
| **Quadratic** | `EaseInOutAnimation.cpp` | 2 | Mulai & akhir lambat | UI transitions, general use |
| **Cubic** | `CubicEaseInOutAnimation.cpp` | 3 | Paling ekstrem & smooth | Premium feel, dramatic reveals |
| **Wobble** | `WobbleAnimation.cpp` | - | Spring/oscillation effect | Playful animations |
| **Wave** | `WaveAnimation.cpp` | - | Gelombang merambat | ⚠️ **TIDAK untuk GridBezier** |

#### Ease Functions Formula

```cpp
// Linear (Power 1)
value = progress * target

// Quadratic Ease-In-Out (Power 2)
if (progress < 0.5) {
    easeProgress = 2 * progress * progress
} else {
    easeProgress = 1 - pow(-2 * progress + 2, 2) / 2
}

// Cubic Ease-In-Out (Power 3)
if (progress < 0.5) {
    easeProgress = 4 * progress * progress * progress
} else {
    easeProgress = 1 - pow(-2 * progress + 2, 3) / 2
}

// Wobble (Sinusoidal dengan decay)
decay = 1.0 - progress
wobble = sin(progress * PI * 2 * frequency) * amplitude * decay
easeProgress = progress + wobble

// Wave (Dengan offset)
shiftedProgress = progress - offset
wave = sin(shiftedProgress * PI * 2 / waveLength) * amplitude
easeProgress = shiftedProgress + wave
```

#### Perbandingan Visual

```
Kecepatan Relatif:

Cubic      ╱───╲    (Paling ekstrem)
           ╱     ╲

Quadratic  ╱──╲     (Moderate)
          ╱    ╲

Linear    ─────     (Konsisten)

Wobble    ╰╯╰╯     (Spring effect)

Wave      ~~~      (Gelombang merambat)
```

#### ⚠️ Peringatan Penting: WaveAnimation & GridBezier

**WaveAnimation TIDAK COCOK untuk GridBezier!** Menggunakan WaveAnimation pada `GridBezier::currentCols/rows` dapat menyebabkan:

- **Vector Out of Range** - Wave membuat nilai naik-turun drastis
- **Index Calculation Error** - Node index bergantung pada `currentCols`
- **Visual Glitch** - Grid berkedip secara chaotic

**Gunakan WaveAnimation HANYA untuk:**
- Animasi posisi individual (bukan jumlah kolom/rows)
- Visual effects di luar grid layout
- Custom implementations dengan proper bounds checking

**Untuk GridBezier, gunakan:** Linear, Quadratic, atau Cubic animation.

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
│   ├── anim/                 # Animation strategies
│   │   ├── LinearAnimation.cpp/h          # Linear easing (Power 1)
│   │   ├── EaseInOutAnimation.cpp/h       # Quadratic easing (Power 2)
│   │   ├── CubicEaseInOutAnimation.cpp/h  # Cubic easing (Power 3)
│   │   ├── WobbleAnimation.cpp/h          # Spring/oscillation effect
│   │   └── WaveAnimation.cpp/h            # Wave dengan offset
│   ├── clr/                 # Color strategies
│   │   └── SolidColor.cpp/h              # Solid color implementation
│   ├── shp/                 # Shape implementations
│   │   └── GridBezier.cpp/h              # Grid shape dengan bezier curves
│   └── strategy/            # Base strategies & interfaces
│       ├── AnimationStrategy.h           # Interface untuk animasi
│       ├── ColorStrategy.cpp/h           # Interface untuk warna
│       └── Shape.h                       # Base class untuk shapes
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

## 📝 Current Status: **sketch-basic-anim-color**

Branch ini adalah **implementation lengkap** dari JaringSketch dengan sistem animasi berbasis Strategy Pattern. Fitur yang tersedia:

✅ Grid layout system dengan konfigurasi cols/rows
✅ **5 Animation Strategies**: Linear, Quadratic, Cubic, Wobble, Wave
✅ Trails effect untuk visual impact
✅ Strategy pattern untuk animasi & warna
✅ Bezier curve rendering untuk smooth lines
✅ Basic keyboard controls
✅ Delta time-based animation (FPS independent)

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
