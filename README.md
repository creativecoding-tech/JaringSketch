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
- **Random Initialization Direction** — 4 arah pertumbuhan grid: TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT
- **Multiple Animation Strategies** — 5 jenis easing: Linear, Quadratic, Cubic, Wobble, dan Wave
- **Multiple Color Strategies** — 6 jenis pewarnaan: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
- **Strategy Pattern** — Arsitektur yang fleksibel untuk animasi dan pewarnaan
- **Modular Design** — Terpisah dalam kategori: `anim/`, `clr/`, `shp/`, `strategy/`
- **Smooth Easing Functions** — Power-based easing (1, 2, 3) untuk tingkat smoothness berbeda
- **Special Effects** — Wobble (spring) dan Wave (gelombang) untuk creative animations
- **Dynamic Line Width** — Ketebalan garis berubah mengikuti gelombang (WAVE, RADIALWAVE & WOBBLE mode)
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
| **VARYING** | Varying bezier curves | Grid statis dengan semua nodes visible dari awal. Curve intensity bervariasi secara random (0-5) setiap reset, menciptakan pola kurva yang unik. |
| **MULURLR** | Growing grid animation | Grid tumbuh dari (0,0) dengan animasi easing. Nodes bertambah secara gradual hingga penuh. |
| **WOBBLE** | Perlin noise wobble | Setiap node bergoyang dengan Perlin noise untuk efek organik "bernapas". Gerakan acak halus seperti cairan. **Termasuk hybrid dynamic line width (noise + pulse)!** |
| **WAVE** | Diagonal wave effect | Kurva bernapas dengan pola gelombang diagonal yang merambat. Menggunakan fungsi sinus untuk pattern teratur. **Termasuk dynamic line width!** |
| **RADIALWAVE** | Radial wave effect | Gelombang melinglar merambat dari tengah grid ke luar seperti efek ripple di air. Menggunakan distance-based sinus wave. **Termasuk dynamic line width!** |

### Technical Details:

**VARYING Mode:**
```cpp
// Grid langsung tampil penuh
// Curve intensity: ofRandom(0, 5) - bervariasi setiap reset!
// Loop hingga maxCols dan maxRows
```

**MULURLR Mode:**
```cpp
// Grid tumbuh dengan animasi easing
// currentCols/Rows bertambah secara gradual
// Arah pertumbuhan ditentukan oleh random initialization direction
// Loop hingga currentCols dan currentRows
```

**Random Initialization Direction:**
```cpp
// 4 Arah pertumbuhan grid yang di-random saat constructor:
enum initDirection { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT };

// TOP_LEFT:    Atas → Bawah, Kiri → Kanan (default)
// TOP_RIGHT:   Atas → Bawah, Kanan → Kiri
// BOTTOM_LEFT: Bawah → Atas, Kiri → Kanan
// BOTTOM_RIGHT:Bawah → Atas, Kanan → Kiri

// Arah ditentukan sekali di constructor dan berlaku untuk SEMUA mode
int randomDir = (int)ofRandom(0, 4);
this->currentInitDir = static_cast<initDirection>(randomDir);
```

**Fitur Spesial Random Initialization:**
- 🎲 **4 Arah Berbeda**: Setiap reset memberikan arah pertumbuhan yang random
- 🌱 **Growing Animation**: MULURLR mode akan tumbuh dari arah yang berbeda-beda
- 🎯 **All Modes**: Berlaku untuk SEMUA GridBezier modes (VARYING, MULURLR, WOBBLE, WAVE, RADIALWAVE)
- 🔄 **Consistent Direction**: Arah tetap sama selama lifecycle object, berubah saat reset ('R')

**WOBBLE Mode:**
```cpp
// Hitung Perlin noise untuk node position
float noise1 = ofNoise(time + n1.noiseOffset);
float wobble1 = ofMap(noise1, 0, 1, -10, 10);

// Hybrid dynamic line width: noise + global pulse
float pulse = cos(ofGetFrameNum() * 0.05f);  // cos() untuk vertikal
float combined = ((noise1 + noise2) / 2.0f + pulse) / 2.0f;
float lineWidth = ofMap(combined, 0, 1, 3, 6);
ofSetLineWidth(lineWidth);
```

**WAVE Mode:**
```cpp
// Diagonal wave untuk curve dan line width (dynamic!)
float wave = sin(i * frequency + j * frequency + time * speed);

// Dynamic line width: wave mempengaruhi ketebalan garis
float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Wave tinggi → Line tebal
ofSetLineWidth(lineWidth);

// Curve amount dengan diagonal wave
float curveAmount = baseCurve + (wave * amplitude);
```

**RADIALWAVE Mode:**
```cpp
// Hitung jarak dari center
float centerX = currentCols / 2.0f;
float centerY = currentRows / 2.0f;
float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

// Radial wave untuk curve dan line width (dynamic!)
float wave = sin(distFromCenter * frequency - time * speed);

// Dynamic line width: wave mempengaruhi ketebalan garis
float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Wave tinggi → Line tebal
ofSetLineWidth(lineWidth);

// Curve amount dengan radial wave (ripple effect)
float curveAmount = baseCurve + (wave * amplitude);
```

**Fitur Spesial RADIALWAVE:**
- ✨ **Dynamic Line Width** - Ketebalan garis berubah mengikuti gelombang
  - Wave tinggi (1) → Line tebal (6px)
  - Wave rendah (-1) → Line tipis (3px)
  - Menciptakan efek "berdenyut" yang dramatis

Mode dipilih secara **random** saat aplikasi start atau saat tekan tombol 'R'.

---

## ✨ Dynamic Line Width Feature

**WAVE**, **RADIALWAVE**, dan **WOBBLE** mode memiliki fitur spesial **Dynamic Line Width** yang membuat ketebalan garis berubah mengikuti gelombang atau noise.

### How It Works

**Diagonal Wave (WAVE Mode):**
```cpp
// Hitung diagonal wave value (-1 sampai 1)
float wave = sin(i * frequency + j * frequency + time * speed);

// Mapping wave ke line width (3px sampai 6px)
float lineWidth = ofMap(wave, -1, 1, 3, 6);
ofSetLineWidth(lineWidth);
```

**Radial Wave (RADIALWAVE Mode):**
```cpp
// Hitung radial wave value (-1 sampai 1)
float wave = sin(distFromCenter * frequency - time * speed);

// Mapping wave ke line width (3px sampai 6px)
float lineWidth = ofMap(wave, -1, 1, 3, 6);
ofSetLineWidth(lineWidth);
```

**Hybrid Approach (WOBBLE Mode):**
```cpp
// Perlin noise untuk local variation (0 sampai 1)
float noise1 = ofNoise(time + n1.noiseOffset);
float noise2 = ofNoise(time + n2.noiseOffset);

// Sinusoidal pulse untuk global pulsing (-1 sampai 1)
float pulse = cos(ofGetFrameNum() * 0.05f);  // cos() untuk vertikal
// float pulse = sin(ofGetFrameNum() * 0.05f);  // sin() untuk horizontal

// Gabungan noise + pulse
float combined = ((noise1 + noise2) / 2.0f + pulse) / 2.0f;

// Mapping combined value ke line width (3px sampai 6px)
float lineWidth = ofMap(combined, 0, 1, 3, 6);
ofSetLineWidth(lineWidth);
```

**Visual Effect:**
- Gelombang tinggi → Garis tebal (6px)
- Gelombang rendah → Garis tipis (3px)
- Menciptakan efek **"berdenyut"** seperti pulsating light
- **WAVE**: Pola diagonal teratur
- **RADIALWAVE**: Pola radial melingkar
- **WOBBLE**: Pola chaotic dengan local variation + global pulse

**Parameter Mapping:**
```cpp
ofMap(wave, -1, 1, 3, 6);
//         ^   ^  ^ ^
//         |   |  | +-- Max line width (6px)
//         |   |  +----- Min line width (3px)
//         |   +-------- Input max (wave tertinggi)
//         +------------ Input min (wave terendah)
```

**Customization:**
Ubah range line width untuk efek yang berbeda:
- `ofMap(wave, -1, 1, 2, 4)` - Lebih halus
- `ofMap(wave, -1, 1, 3, 6)` - Medium (current)
- `ofMap(wave, -1, 1, 1, 10)` - Ekstrem dramatis

---

### 🔥 WOBBLE Mode: Hybrid Dynamic Line Width

WOBBLE mode menggunakan pendekatan **hybrid** yang menggabungkan dua sumber nilai:

**1. Perlin Noise (Local Variation):**
- Setiap bezier punya noise value berbeda (0 sampai 1)
- Menciptakan variasi **local** yang unik per garis
- Bersifat chaotic dan unpredictable

**2. Sinusoidal Pulse (Global Pulsing):**
- Semua bezier berdenyut **bersamaan** (-1 sampai 1)
- Menggunakan `cos()` untuk vertikal, `sin()` untuk horizontal
- Menciptakan pola **global** yang teratur

**Combination Formula:**
```cpp
float combined = ((noise1 + noise2) / 2.0f + pulse) / 2.0f;
```

**Kenapa Hybrid Lebih Menarik:**
- ✨ **Best of both worlds**: Variasi chaotic + rhythm teratur
- 🎭 **Phase difference**: `cos()` vs `sin()` untuk cross-fading antara vertikal & horizontal
- 💫 **Organic complexity**: Lebih natural daripada hanya noise atau hanya pulse
- 🌊 **Chaotic breathing**: Efek "bernapas" tapi tidak monoton

**Phase Difference Magic:**
```cpp
float pulse = cos(frame * 0.05);  // Vertikal curves
float pulse = sin(frame * 0.05);  // Horizontal curves
```
- `cos()` dan `sin()` beda 90° fase
- Saat vertikal tebal → horizontal sedang (dan sebaliknya)
- Menciptakan pola berputar yang dynamic!

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
- **HANYA AMAN untuk mode VARYING** (karena VARYING pakai `maxCols/maxRows` yang statis)
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
    // VARYING mode: WaveAnimation BOLEH dipakai (0-4)
    randomAnim = ofRandom(0, 5);
}
```

**Untuk GridBezier Animation Strategy:**
- Mode **VARYING**: Linear, Quadratic, Cubic, Wobble, atau Wave ✅
- Mode **MULURLR/WOBBLE/WAVE/RADIALWAVE**: Linear, Quadratic, Cubic, atau Wobble saja (NO WaveAnimation!) ⚠️

**Untuk GridBezier Visual Effect:**
Gunakan mode: VARYING, MULURLR, WOBBLE, WAVE, atau RADIALWAVE (rendering mode).

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
// Mode VARYING: semua cell berubah sama
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
✅ **5 Rendering Modes**: VARYING, MULURLR, WOBBLE, WAVE, RADIALWAVE
✅ **5 Animation Strategies**: Linear, Quadratic, Cubic, Wobble, Wave
✅ **6 Color Strategies**: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
✅ **4 Initialization Directions**: TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT (random!)
✅ **Multi-mode rendering** dengan efek visual bervariasi
✅ **Dynamic mode selection** (random pada startup/reset)
✅ **Interactive strategy switching** via keyboard (1-5 untuk animasi, Z-X-C-V-B untuk color)
✅ Trails effect untuk visual impact
✅ Strategy pattern untuk animasi & warna
✅ Bezier curve rendering dengan curve intensity dinamis
✅ Perlin noise untuk organik wobble effects
✅ Sinusoidal wave untuk diagonal & radial wave patterns
✅ Distance-based radial ripple effects
✅ **Dynamic line width** yang mengikuti gelombang (WAVE, RADIALWAVE & WOBBLE mode)
✅ **Hybrid dynamic line width** dengan noise + pulse combination (WOBBLE mode)
✅ HSB color system untuk vivid gradients
✅ Delta time-based animation (FPS independent)
✅ Memory-safe implementation dengan `std::unique_ptr`

### Mode Highlights:
- **WOBBLE Mode**: Perlin noise-based organic movement dengan **hybrid dynamic line width** (noise + pulse)
- **WAVE Mode**: Diagonal wave pattern dengan **dynamic line width** yang berdenyut
- **RADIALWAVE Mode**: Radial ripple effect dengan **dynamic line width** yang berdenyut
- **MULURLR Mode**: Growing grid dengan smooth easing
- **VARYING Mode**: Static grid dengan **random curve intensity** yang bervariasi setiap reset

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
