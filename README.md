## JaringSketch | OpenFrameworks Grid Animation

Eksperimen grid dengan animasi bezier yang smooth dan efek trails. Project ini adalah eksplorasi creative coding dengan openFrameworks untuk membuat pola grid yang dapat beranimasi dengan sistem easing yang halus.

[![OpenFrameworks](https://img.shields.io/badge/OpenFrameworks-0.12.1-blue)](https://openframeworks.cc/)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![License](https://img.shields.io/badge/License-Apache%202.0-green)
![Branch](https://img.shields.io/badge/Branch-sketch--GridBezier-orange)

[![Fund The Experiments](https://img.shields.io/badge/Fund-The_Experiments-FF5722?style=for-the-badge&logo=buy-me-a-coffee)](https://sociabuzz.com/abdkdhni)

---

## 📺 Demo Video

Lihat hasilnya di YouTube: [Watch Demo](https://youtu.be/XwEZjz_YhQg)

---

## 📺 Preview

Project ini menampilkan grid node dengan animasi transisi yang smooth menggunakan ease-in-ease-out interpolation.

---

## ✨ Fitur & Teknik

- **Grid Layout System** — 2D grid dengan node yang terkonfigurasi (cols & rows)
- **Multiple Animation Strategies** — 5 jenis easing: Linear, Quadratic, Cubic, Wobble, dan Wave
- **Multiple Color Strategies** — 6 jenis pewarnaan: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
- **Strategy Pattern** — Arsitektur yang fleksibel untuk animasi dan pewarnaan
- **Modular Design** — Terpisah dalam kategori: `anim/`, `clr/`, `shp/`, `strategy/`
- **Smooth Easing Functions** — Power-based easing (1, 2, 3) untuk tingkat smoothness berbeda
- **Special Effects** — Wobble (spring) dan Wave (gelombang) untuk creative animations
- **HSB Color System** — Hue-Saturation-Brightness untuk vivid colors dan smooth gradients
- **Animated Colors** — Time-based color transitions untuk dynamic visual effects
- **Trails Effect** — Semi-transparent overlay untuk efek jejak visual yang menarik
- **Interactive Controls** — Keyboard shortcuts untuk kontrol realtime
- **Anti-Aliasing & Smoothing** — Garis dan kurva yang smooth untuk visual yang lebih baik

---

## 🎮 Controls

| Input | Action |
| --- | --- |
| **Key 'S'** | Toggle visibility shape grid (Show/Hide) |
| **Key 'R'** | Reset animasi dengan strategi baru (random) |
| **Key 'Q'** | Keluar dari aplikasi |
| **Right Click** | Toggle visibilitas kursor |
| **Key 'Z'** | Set Horizontal Gradient color |
| **Key 'X'** | Set Rainbow Spiral color |
| **Key 'C'** | Set Radial Gradient color |
| **Key 'V'** | Set Vertical Gradient color |
| **Key 'B'** | Set Time-Based (WAVE mode) color |
| **Key '1'** | Set EaseInOut (Quadratic) animation |
| **Key '2'** | Set Linear animation |
| **Key '3'** | Set CubicEaseInOut animation |
| **Key '4'** | Set Wobble animation |
| **Key '5'** | Set Wave animation |

---

## 🎨 GridBezier Rendering Modes

GridBezier mendukung **5 mode rendering** berbeda untuk efek visual yang bervariasi:

| Mode | Deskripsi | Karakteristik |
|------|-----------|---------------|
| **NORMAL** | Standard bezier curves | Grid statis dengan semua nodes visible dari awal. Cocok untuk base grid display. |
| **MULURLR** | Growing grid animation | Grid tumbuh dari (0,0) dengan animasi easing. Nodes bertambah secara gradual hingga penuh. |
| **WOBBLE** | Perlin noise wobble | Setiap node bergoyang dengan Perlin noise untuk efek organik "bernapas". Gerakan acak halus seperti cairan. |
| **WAVE** | Diagonal wave effect | Kurva bernapas dengan pola gelombang diagonal yang merambat. Menggunakan fungsi sinus untuk pattern teratur. |
| **RADIALWAVE** | Radial wave effect | Gelombang melinglar merambat dari tengah grid ke luar seperti efek ripple di air. Menggunakan distance-based sinus wave. |

### Technical Details:

**NORMAL Mode:**
```cpp
// Grid langsung tampil penuh
// Loop hingga maxCols dan maxRows
```

**MULURLR Mode:**
```cpp
// Grid tumbuh dari 0,0 ke target
// currentCols/Rows bertambah dengan animasi easing
// Loop hingga currentCols dan currentRows
```

**WOBBLE Mode:**
```cpp
// Posisi node digeser dengan Perlin noise
float wobble = ofMap(ofNoise(time + node.noiseOffset), 0, 1, -10, 10);
float x = node.x + wobble;
float y = node.y + wobble;
```

**WAVE Mode:**
```cpp
// Curve amount dinamis dengan sinus wave
float wave = sin(i * frequency + j * frequency + time * speed);
float curveAmount = baseCurve + (wave * amplitude);
```

**RADIALWAVE Mode:**
```cpp
// Hitung jarak dari center
float centerX = currentCols / 2.0f;
float centerY = currentRows / 2.0f;
float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

// Curve amount dengan radial wave (ripple effect)
float wave = sin(distFromCenter * frequency - time * speed);
float curveAmount = baseCurve + (wave * amplitude);
```

Mode dipilih secara **random** saat aplikasi start atau saat tekan tombol 'R'.

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

# Checkout branch sketch-GridBezier
git checkout sketch-GridBezier

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

#### ⚠️ Peringatan Penting: WaveAnimation vs Wave Modes

**PENTING: Bedakan antara WaveAnimation strategy dan Wave rendering modes!**

**1. WaveAnimation (Animation Strategy)**
- Ini adalah **strategi animasi** yang mengontrol `currentCols/rows`
- **HANYA AMAN untuk mode NORMAL** (karena NORMAL pakai `maxCols/maxRows` yang statis)
- **TIDAK COCOK** untuk mode MULURLR, WOBBLE, WAVE, dan RADIALWAVE karena menyebabkan:
  - **Vector Out of Range** - Wave membuat nilai naik-turun drastis
  - **Index Calculation Error** - Node index bergantung pada `currentCols/rows` yang dinamis
  - **Visual Glitch** - Grid berkedip secara chaotic

**2. Wave Rendering Modes (GridBezier Rendering Modes)**
- **WAVE Mode**: Efek diagonal wave, **AMAN** karena hanya mempengaruhi curve amount
- **RADIALWAVE Mode**: Efek radial ripple, **AMAN** karena hanya mempengaruhi curve amount
- Kedua mode ini membuat efek bernapas dengan pola gelombang yang merambat

**System Implementation:**
```cpp
// Otomatis exclude WaveAnimation untuk mode yang tidak aman
if (currentBzMode == MULURLR || currentBzMode == WOBBLE
    || currentBzMode == WAVE || currentBzMode == RADIALWAVE) {
    // Hanya pilih dari: Linear, EaseInOut, Cubic, Wobble (0-3)
    randomAnim = ofRandom(0, 4);
} else {
    // NORMAL mode: WaveAnimation BOLEH dipakai (0-4)
    randomAnim = ofRandom(0, 5);
}
```

**Untuk GridBezier Animation Strategy:**
- Mode **NORMAL**: Linear, Quadratic, Cubic, Wobble, atau Wave ✅
- Mode **MULURLR/WOBBLE/WAVE/RADIALWAVE**: Linear, Quadratic, Cubic, atau Wobble saja (NO WaveAnimation!) ⚠️

**Untuk GridBezier Visual Effect:**
Gunakan mode: NORMAL, MULURLR, WOBBLE, WAVE, atau RADIALWAVE (rendering mode).

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

### Color System dengan HSB

Project ini menggunakan **HSB (Hue-Saturation-Brightness)** color system untuk vivid colors dan smooth gradients. Berbeda dengan RGB, HSB lebih intuitif untuk color transitions.

#### HSB vs RGB

| Aspect | RGB | HSB |
|--------|-----|-----|
| **Range** | 0-255 per channel | H: 0-255, S: 0-255, B: 0-255 |
| **Intuitif** | ❌ Tidak mudah untuk gradients | ✅ Mudah membuat color transitions |
| **Use Case** | Technical colors | Artistic gradients |

#### Color Strategy Implementation

```cpp
// Set HSB color di openFrameworks
ofColor color;
color.setHsb(hue, saturation, brightness);
// hue: 0-255 (0=red, 85=green, 170=blue, 255=red again)
// saturation: 0-255 (0=grayscale, 255=vivid)
// brightness: 0-255 (0=black, 255=brightest)
```

#### Tipe Color Strategies Tersedia

| Strategy | Deskripsi | Arah/Pattern | Use Case |
|----------|-----------|--------------|----------|
| **SolidColor** | Warna solid tunggal | - | Base grid, simple visuals |
| **HorizontalGradient** | Gradient kiri-kanan | Kiri → Kanan | Sunsets, horizons |
| **VerticalGradient** | Gradient atas-bawah | Atas → Bawah | Sky effects |
| **RadialGradient** | Gradient dari center | Center → Luar | Glows, spotlights |
| **RainbowSpiral** | Spiral dengan rotasi animasi | Circular + Angle | Psychedelic effects |
| **TimeBasedColor** | Berubah seiring waktu | Frame-based animation | Dynamic ambient colors |

#### Gradient Formula

**Horizontal Gradient:**
```cpp
float pos = (float)i / cols;  // 0.0 - 1.0 (kiri ke kanan)
float hue = ofMap(pos, 0, 1, startHue, endHue);
```

**Vertical Gradient:**
```cpp
float pos = (float)j / rows;  // 0.0 - 1.0 (atas ke bawah)
float hue = ofMap(pos, 0, 1, startHue, endHue);
```

**Radial Gradient:**
```cpp
float distFromCenter = ofDist(i, j, cols/2.0, rows/2.0);
float maxDist = ofDist(0, 0, cols/2.0, rows/2.0);
float pos = distFromCenter / maxDist;  // 0.0 - 1.0 (center ke luar)
float hue = ofMap(pos, 0, 1, startHue, endHue);
```

**Rainbow Spiral:**
```cpp
float angle = atan2(j - rows/2.0f, i - cols/2.0f);
float distFromCenter = ofDist(i, j, cols/2.0f, rows/2.0f);
float hue = fmod(ofRadToDeg(angle) + distFromCenter * 10 + ofGetFrameNum() * speed, 360);
```

**Time-Based Color:**
```cpp
// Mode NORMAL: semua cell berubah sama
float hue = fmod(ofGetFrameNum() * speed, 360);

// Mode WAVE: gradient bergerak
float pos = (float)i / cols;
float hue = fmod((pos * 360) + ofGetFrameNum() * speed, 360);
```

#### Perbandingan Visual Gradient

```
Horizontal:  ░▒▓█▓▒░  (Kiri → Kanan)

Vertical:    ░     ░
              ▒     ▒
              ▓     ▓
              █     █  (Atas → Bawah)

Radial:      ▓▓▓▓▓
              ▓███▓
              ▓█░█▓  (Center → Luar)
              ▓███▓
              ▓▓▓▓▓

Rainbow:     ╱╲╱╲╱╲  (Spiral berputar)
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
│   │   ├── SolidColor.cpp/h              # Solid color implementation
│   │   ├── HorizontalGradient.cpp/h      # Horizontal gradient (left to right)
│   │   ├── VerticalGradient.cpp/h        # Vertical gradient (top to bottom)
│   │   ├── RadialGradient.cpp/h          # Radial gradient (center outward)
│   │   ├── RainbowSpiral.cpp/h           # Rainbow spiral with rotation
│   │   └── TimeBasedColor.cpp/h           # Time-based animated colors
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

## 📝 Current Status: **sketch-GridBezier**

Branch ini adalah **pengembangan lanjut** dari JaringSketch dengan fokus pada **multi-mode rendering system** untuk GridBezier. Fitur yang tersedia:

✅ Grid layout system dengan konfigurasi cols/rows
✅ **5 Rendering Modes**: NORMAL, MULURLR, WOBBLE, WAVE, RADIALWAVE
✅ **5 Animation Strategies**: Linear, Quadratic, Cubic, Wobble, Wave
✅ **6 Color Strategies**: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
✅ **Multi-mode rendering** dengan efek visual bervariasi
✅ **Dynamic mode selection** (random pada startup/reset)
✅ **Interactive strategy switching** via keyboard (1-5 untuk animasi, Z-X-C-V-B untuk color)
✅ Trails effect untuk visual impact
✅ Strategy pattern untuk animasi & warna
✅ Bezier curve rendering dengan curve intensity dinamis
✅ Perlin noise untuk organik wobble effects
✅ Sinusoidal wave untuk diagonal & radial wave patterns
✅ Distance-based radial ripple effects
✅ HSB color system untuk vivid gradients
✅ Delta time-based animation (FPS independent)
✅ Memory-safe implementation dengan `std::unique_ptr`

### Mode Highlights:
- **WOBBLE Mode**: Perlin noise-based organic movement
- **WAVE Mode**: Diagonal wave pattern untuk "breathing" curves
- **RADIALWAVE Mode**: Radial ripple effect dari tengah ke luar
- **MULURLR Mode**: Growing grid dengan smooth easing
- **NORMAL Mode**: Classic static grid display

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
- **[Watch Demo](https://youtu.be/XwEZjz_YhQg)** - YouTube demonstration
- **[Support Me](https://sociabuzz.com/abdkdhni)** - Fund the experiments ☕

---

**Made with ❤️ for learning and creative exploration**
