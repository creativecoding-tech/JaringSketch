## JaringSketch | OpenFrameworks Grid Animation

Eksperimen grid dengan animasi bezier yang smooth dan efek trails. Project ini adalah eksplorasi creative coding dengan openFrameworks untuk membuat pola grid yang dapat beranimasi dengan sistem easing yang halus.

[![OpenFrameworks](https://img.shields.io/badge/OpenFrameworks-0.12.1-blue)](https://openframeworks.cc/)
![C++](https://img.shields.io/badge/C++-17-blue)
![Platform](https://img.shields.io/badge/Platform-Windows-lightgrey)
![License](https://img.shields.io/badge/License-Apache%202.0-green)
![Branch](https://img.shields.io/badge/Branch-master-green)

[![Fund The Experiments](https://img.shields.io/badge/Fund-The_Experiments-FF5722?style=for-the-badge&logo=buy-me-a-coffee)](https://sociabuzz.com/abdkdhni)

---

## 📺 Demo Video

Lihat hasilnya di YouTube: [Watch Demo](https://youtu.be/R_g6W-CVu7A)

---

## 📺 Preview

Project ini menampilkan grid node dengan animasi bezier yang dinamis dalam **2D dan 3D** dengan 7 mode rendering berbeda:

- **VARYING**: Grid statis dengan curve intensity yang bervariasi
- **MULURLR**: Grid tumbuh dengan animasi easing dari 6 arah pertumbuhan yang berbeda
- **WOBBLE**: Grid bernapas dengan efek Perlin noise yang organik
- **WAVE**: Grid dengan pola gelombang diagonal yang berdenyut
- **RADIALWAVE**: Grid dengan efek ripple radial dari tengah ke luar
- **HORIZONTALWAVE**: Grid dengan gelombang horizontal dari kiri ke kanan
- **VERTICALWAVE**: Grid dengan gelombang vertikal dari atas ke bawah

Setiap mode memiliki karakteristik visual yang unik dengan dynamic line width dan smooth color transitions.

### 2D vs 3D Rendering

Project ini mendukung **2 mode rendering** yang dipilih secara random saat startup dan reset:

- **2D Mode (GridBezier)**: Grid bezier pada bidang 2D dengan 7 mode rendering
- **3D Mode (GridBezier3D)**: Grid bezier dalam ruang 3D dengan:
  - **Z-Axis Curve**: 5 variasi trigonometric functions (sin, cos, tan) untuk posisi Z
  - **3D Bezier Curves**: Kurva bezier dengan control points dalam ruang 3D
  - **Camera Animation**: Auto movement kamera dengan smooth easing
  - **3D Wave Effects**: Gelombang 3D yang mempengaruhi posisi Z dan control points
  - **3D Wobble Effects**: Perlin noise dalam 3 axis (X, Y, Z) untuk gerakan organik

---

## ✨ Fitur & Teknik

- **Grid Layout System** — 2D grid dengan node yang terkonfigurasi (cols & rows)
- **Phyllotaxis Pattern** — Pola spiral dengan golden angle 137.5° yang ditemukan di alam (NEW!)
- **Fully Automated Sequence** — Sistem otomatis penuh: Run → Delay → Grid → Phyllotaxis → Grid → Reset → Loop (NEW!)
- **Random Initialization Direction** — 6 arah pertumbuhan grid: TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, RADIAL_OUT, RADIAL_IN
- **Multiple Animation Strategies** — 5 jenis easing: Linear, Quadratic, Cubic, Wobble, dan Wave
- **Multiple Color Strategies** — 6 jenis pewarnaan: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
- **Bright Colors Only** — HSB color system dengan high saturation (200-255) dan brightness (200-255) untuk vivid colors (NEW!)
- **Strategy Pattern** — Arsitektur yang fleksibel untuk animasi dan pewarnaan
- **Modular Design** — Terpisah dalam kategori: `anim/`, `clr/`, `shp/`, `strategy/`
- **Smooth Easing Functions** — Power-based easing (1, 2, 3) untuk tingkat smoothness berbeda
- **Cubic Ease-In-Out Phyllotaxis** — Animasi phyllotaxis dengan transisi smooth (~1 detik)
- **Special Effects** — Wobble (spring) dan Wave (gelombang) untuk creative animations
- **Dynamic Line Width** — Ketebalan garis berubah mengikuti gelombang (WAVE, RADIALWAVE, HORIZONTALWAVE, VERTICALWAVE & WOBBLE mode)
- **HSB Color System** — Hue-Saturation-Brightness untuk vivid colors dan smooth gradients
- **Animated Colors** — Time-based color transitions untuk dynamic visual effects
- **Trails Effect** — Semi-transparent overlay untuk efek jejak visual yang menarik
- **Interactive Controls** — Keyboard shortcuts untuk kontrol realtime
- **Anti-Aliasing & Smoothing** — Garis dan kurva yang smooth untuk visual yang lebih baik
- **Cursor Hidden by Default** — Kursor otomatis tersembunyi saat aplikasi berjalan (NEW!)

---

## 🎮 Controls

| Input | Action |
| --- | --- |
| **Key 'S'** | Toggle visibility shape grid (Show/Hide) |
| **Key 'X'** | Toggle Phyllotaxis pattern on/off (2D & 3D mode) |
| **Key 'R'** | Reset dengan mode, animasi, warna, dan arah baru (random 2D/3D) |
| **Key 'Q'** | Keluar dari aplikasi |
| **Key 'P'** | Print camera position dan orientation (3D mode only) |
| **Right Click** | Toggle visibilitas kursor |

---

## 🎨 GridBezier Rendering Modes

GridBezier mendukung **7 mode rendering** berbeda untuk efek visual yang bervariasi:

| Mode | Deskripsi | Karakteristik |
|------|-----------|---------------|
| **VARYING** | Varying bezier curves | Grid statis dengan semua nodes visible dari awal. Curve intensity bervariasi secara random (0-5) setiap reset, menciptakan pola kurva yang unik. |
| **MULURLR** | Growing grid animation | Grid tumbuh dari (0,0) dengan animasi easing. Nodes bertambah secara gradual hingga penuh. |
| **WOBBLE** | Perlin noise wobble | Setiap node bergoyang dengan Perlin noise untuk efek organik "bernapas". Gerakan acak halus seperti cairan. **Termasuk hybrid dynamic line width (noise + pulse)!** |
| **WAVE** | Diagonal wave effect | Kurva bernapas dengan pola gelombang diagonal yang merambat. Menggunakan fungsi sinus untuk pattern teratur. **Termasuk dynamic line width!** |
| **RADIALWAVE** | Radial wave effect | Gelombang melinglar merambat dari tengah grid ke luar seperti efek ripple di air. Menggunakan distance-based sinus wave. **Termasuk dynamic line width!** |
| **HORIZONTALWAVE** | Horizontal wave effect | Gelombang horizontal merambat dari kiri ke kanan. Menggunakan fungsi sinus berdasarkan posisi kolom (x-axis). **Termasuk dynamic line width!** |
| **VERTICALWAVE** | Vertical wave effect | Gelombang vertikal merambat dari atas ke bawah. Menggunakan fungsi sinus berdasarkan posisi baris (y-axis). **Termasuk dynamic line width!** |

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
// 6 Arah pertumbuhan grid yang di-random saat constructor:
enum initDirection { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, RADIAL_OUT, RADIAL_IN };

// TOP_LEFT:    Atas → Bawah, Kiri → Kanan
// TOP_RIGHT:   Atas → Bawah, Kanan → Kiri
// BOTTOM_LEFT: Bawah → Atas, Kiri → Kanan
// BOTTOM_RIGHT:Bawah → Atas, Kanan → Kiri
// RADIAL_OUT:  Tengah → Luar (distance-based, ascending)
// RADIAL_IN:   Luar → Tengah (distance-based, descending)

// Arah ditentukan sekali di constructor dan berlaku untuk SEMUA mode
int randomDir = (int)ofRandom(0, 6);
this->currentInitDir = static_cast<initDirection>(randomDir);
```

**Fitur Spesial Random Initialization:**
- 🎲 **6 Arah Berbeda**: Setiap reset memberikan arah pertumbuhan yang random
- 🌀 **RADIAL_OUT Mode**: Grid tumbuh dari tengah ke luar dengan distance-based sorting (ascending)
- 🌀 **RADIAL_IN Mode**: Grid tumbuh dari luar ke tengah dengan distance-based sorting (descending)
- 🌱 **Growing Animation**: MULURLR mode akan tumbuh dari arah yang berbeda-beda
- 🎯 **All Modes**: Berlaku untuk SEMUA GridBezier modes (VARYING, MULURLR, WOBBLE, WAVE, RADIALWAVE, HORIZONTALWAVE, VERTICALWAVE)
- 🔄 **Consistent Direction**: Arah tetap sama selama lifecycle object, berubah saat reset ('R')
- ✨ **Auto Re-initialize**: RADIAL_OUT & RADIAL_IN otomatis re-initialize ke arah random setelah animasi selesai untuk hasil akhir yang rapi

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

**HORIZONTALWAVE Mode:**
```cpp
// Horizontal wave untuk curve dan line width (dynamic!)
float wave = sin(i * frequency + time * speed);

// Dynamic line width: wave mempengaruhi ketebalan garis
float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Wave tinggi → Line tebal
ofSetLineWidth(lineWidth);

// Curve amount dengan horizontal wave
float curveAmount = baseCurve + (wave * amplitude);
```

**Fitur Spesial HORIZONTALWAVE:**
- ✨ **Dynamic Line Width** - Ketebalan garis berubah mengikuti gelombang horizontal
  - Wave tinggi (1) → Line tebal (6px)
  - Wave rendah (-1) → Line tipis (3px)
  - Menciptakan efek "berdenyut" horizontal yang dramatis
- 🌊 **Horizontal Propagation** - Gelombang merambat dari kiri ke kanan (hanya bergantung pada posisi kolom/i)

**VERTICALWAVE Mode:**
```cpp
// Vertical wave untuk curve dan line width (dynamic!)
float wave = sin(j * frequency + time * speed);

// Dynamic line width: wave mempengaruhi ketebalan garis
float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Wave tinggi → Line tebal
ofSetLineWidth(lineWidth);

// Curve amount dengan vertical wave
float curveAmount = baseCurve + (wave * amplitude);
```

**Fitur Spesial VERTICALWAVE:**
- ✨ **Dynamic Line Width** - Ketebalan garis berubah mengikuti gelombang vertikal
  - Wave tinggi (1) → Line tebal (6px)
  - Wave rendah (-1) → Line tipis (3px)
  - Menciptakan efek "berdenyut" vertikal yang dramatis
- 🌊 **Vertical Propagation** - Gelombang merambat dari atas ke bawah (hanya bergantung pada posisi baris/j)

Mode dipilih secara **random** saat aplikasi start atau saat tekan tombol 'R'.

---

## ✨ Dynamic Line Width Feature

**WAVE**, **RADIALWAVE**, **HORIZONTALWAVE**, **VERTICALWAVE**, dan **WOBBLE** mode memiliki fitur spesial **Dynamic Line Width** yang membuat ketebalan garis berubah mengikuti gelombang atau noise.

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

**Horizontal Wave (HORIZONTALWAVE Mode):**
```cpp
// Hitung horizontal wave value (-1 sampai 1)
float wave = sin(i * frequency + time * speed);

// Mapping wave ke line width (3px sampai 6px)
float lineWidth = ofMap(wave, -1, 1, 3, 6);
ofSetLineWidth(lineWidth);
```

**Vertical Wave (VERTICALWAVE Mode):**
```cpp
// Hitung vertical wave value (-1 sampai 1)
float wave = sin(j * frequency + time * speed);

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
- **HORIZONTALWAVE**: Pola horizontal dari kiri ke kanan
- **VERTICALWAVE**: Pola vertikal dari atas ke bawah
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

## 🤖 Fully Automated Sequence (NEW!)

JaringSketch sekarang memiliki **sistem otomatis penuh** tanpa perlu menekan tombol keyboard. Aplikasi akan menjalankan sequence secara otomatis:

### Alur Otomatis

```
Run → Delay → Grid Formation → Phyllotaxis → Return to Grid → Reset → Loop
```

**Detail Step-by-Step:**

1. **AUTO_DELAY_START** (3 detik)
   - Delay sebelum grid mulai terbentuk
   - Background dark dengan trails effect

2. **AUTO_GRID_GROWING** (±2-3 detik)
   - Grid mulai tumbuh dengan animasi easing
   - Menunggu hingga semua nodes selesai animasi

3. **AUTO_DELAY_PHYLLLO** (2 detik)
   - Delay setelah grid selesai terbentuk
   - Menikmati grid normal sebentar

4. **AUTO_PHYLLAXIS_ACTIVE** (±2-3 detik)
   - Phyllotaxis pattern diaktifkan otomatis
   - Nodes bergerak membentuk spiral dengan golden angle
   - **2D Mode**: Spiral dengan 360° rotation
   - **3D Mode**: Random FLAT/SPHERE/CONE dengan rotation

5. **AUTO_DELAY_BACK** (3 detik)
   - Delay setelah phyllotaxis selesai
   - Menikmati pola spiral sebentar

6. **AUTO_RETURNING** (±2-3 detik)
   - Kembali ke grid normal
   - Nodes bergerak kembali ke posisi grid asli

7. **AUTO_DELAY_RESET** (3 detik)
   - Delay sebelum reset
   - Persiapan untuk cycle baru

8. **AUTO_RESETTING**
   - Reset dengan mode baru (random 2D/3D)
   - Warna baru (random color strategy)
   - Animasi baru (random animation strategy)
   - Arah init baru (random initialization direction)
   - Kembali ke step 1 (loop terus menerus)

### State Machine Implementation

```cpp
enum AutoPlayState {
    AUTO_DELAY_START,      // Delay 3 detik sebelum mulai
    AUTO_GRID_GROWING,     // Grid sedang tumbuh
    AUTO_DELAY_PHYLLLO,    // Delay 2 detik sebelum phyllotaxis
    AUTO_PHYLLAXIS_ACTIVE, // Phyllotaxis aktif dengan animasi
    AUTO_DELAY_BACK,       // Delay 3 detik sebelum kembali
    AUTO_RETURNING,        // Kembali ke grid normal
    AUTO_DELAY_RESET,      // Delay 3 detik sebelum reset
    AUTO_RESETTING         // Reset ke mode baru
};
```

### Timing Configuration

```cpp
float delayBeforeStart = 3.0f;    // Delay awal
float delayBeforePhyllo = 2.0f;   // Delay sebelum phyllotaxis
float delayBeforeBack = 3.0f;     // Delay sebelum kembali ke grid
float delayBeforeReset = 3.0f;    // Delay sebelum reset
```

### Catatan Penting

- ✅ **Fully Automated** - Tidak perlu tekan tombol sama sekali
- 🔄 **Infinite Loop** - Akan terus berulang sampai aplikasi ditutup (Q)
- 🎲 **Random Setiap Reset** - Mode 2D/3D, warna, animasi, arah selalu baru
- ⏱️ **Total Cycle Time** - Sekitar 20-25 detik per cycle
- 🎨 **Fresh Experience** - Setiap cycle memberikan visual yang berbeda
- 💡 **Still Interactive** - Tombol S, X, R, P tetap berfungsi untuk override

### Interactive Override

Walaupun otomatis, Anda tetap bisa mengambil alih kontrol:

| Key | Action |
|-----|--------|
| **S** | Toggle show/hide shape (override auto) |
| **X** | Toggle phyllotaxis manual (override auto sequence) |
| **R** | Force reset ke mode baru (restart cycle) |
| **Q** | Keluar dari aplikasi |
| **P** | Print camera position (3D mode only) |

---

## 🎨 Bright Colors System (NEW!)

JaringSketch menggunakan **HSB color system** dengan **high saturation & brightness** untuk menghasilkan warna-warna cerah dan vivid.

### HSB Color Configuration

```cpp
ofColor randomC;
randomC.setHsb(
    ofRandom(255),          // Hue: 0-255 (semua warna)
    ofRandom(200, 255),     // Saturation: 200-255 (vivid cerah)
    ofRandom(200, 255)      // Brightness: 200-255 (terang cerah)
);
```

### Why High Saturation & Brightness?

**HSB Range Explanation:**

| Component | Range | Effect |
|-----------|-------|--------|
| **Hue** | 0-255 | Menentukan warna (merah, hijau, biru, dll) |
| **Saturation** | 0-255 | 0 = grayscale, 255 = warna murni |
| **Brightness** | 0-255 | 0 = hitam, 255 = putih terang |

**High S/B (200-255) = Vivid & Bright:**
- ✨ **Colors pop out** - Warna terlihat cerah dan eye-catching
- 🌈 **Maximum vibrancy** - Tidak ada warna yang kusam
- 💡 **Glowing effect** - Seperti neon lights di dark background
- 🎨 **Professional look** - Hasil seperti creative coding profesional

**Comparison:**

```
Low S/B (0-100):    ░░░░░░░░░  (Kusam, gelap, boring)
Medium S/B (100-200): ▒▒▒▒▒▒▒▒  (Cukup tapi kurang pop)
High S/B (200-255):  ██████████  (Cerah, vivid, stunning!) ← Current
```

### Color Strategies dengan High S/B

**1. Solid Color:**
```cpp
randomC.setHsb(ofRandom(255), ofRandom(200, 255), ofRandom(200, 255));
```

**2. Horizontal/Vertical Gradient:**
```cpp
HorizontalGradient(startHue, endHue, 200, 230);
//                                        ^     ^
//                                      Sat    Bright (high values)
```

**3. Radial Gradient:**
```cpp
RadialGradient(startHue, endHue, 200, 230);
//                                  ^     ^
//                                Sat    Bright
```

**4. Rainbow Spiral:**
```cpp
RainbowSpiral(speed, 200, 230);
//                   ^     ^
//                 Sat    Bright
```

**5. Time-Based Color:**
```cpp
TimeBasedColor(startHue, endHue, speed, mode);
// Colors selalu menggunakan high S/B
```

### Visual Result

Dengan high S/B (200-255), hasilnya:
- 🌈 **Rainbow gradients** yang cerah dan memukau
- 💎 **Vivid solid colors** yang tidak pernah kusam
- ✨ **Smooth transitions** antar warna yang tetap bright
- 🎆 **Festive atmosphere** - Seperti celebration lights
- 🖼️ **Gallery quality** - Siap untuk showcase/portfolio

### Customization

Jika ingin mengubah brightness/saturation:

```cpp
// Ultra bright (lebih terang)
ofRandom(220, 255), ofRandom(220, 255)

// Medium bright (sedikit lebih gelap)
ofRandom(180, 230), ofRandom(180, 230)

// Pastel colors (lebih soft)
ofRandom(150, 200), ofRandom(200, 255)
```

---

## 🌻 Phyllotaxis Pattern (NEW!)

GridBezier dan GridBezier3D mendukung **Phyllotaxis pattern** - pola spiral yang ditemukan di alam (bunga matahari, pinecone, bunga matahari). Fitur ini mengubah grid menjadi pola spiral dengan golden angle.

### Cara Menggunakan

**Untuk 2D Grid Mode:**
1. Pastikan aplikasi berjalan di mode 2D
2. Tekan **'S'** untuk menampilkan grid
3. Tekan **'X'** untuk mengaktifkan Phyllotaxis pattern
4. Tekan **'X'** lagi untuk menonaktifkan kembali ke grid normal

**Untuk 3D Grid Mode:**
1. Pastikan aplikasi berjalan di mode 3D
2. Tekan **'S'** untuk menampilkan grid
3. Tekan **'X'** untuk mengaktifkan Phyllotaxis pattern 3D (random: FLAT, SPHERE, atau CONE)
4. Tekan **'X'** lagi untuk menonaktifkan kembali ke grid normal
5. Setiap tekan 'X' akan memilih mode phyllotaxis secara random (3 mode tersedia!)

### Visual Effect

**2D Mode (GridBezier):**
- ✨ **Smooth Animation** - Transisi grid ↔ phyllotaxis dengan cubic ease-in-out (~1 detik)
- 🌀 **Golden Angle Spiral** - Menggunakan angle 137.5° (sudut emas)
- 🌊 **Bidirectional Animation** - Toggle on/off dengan animasi smooth
- 🔄 **360° Rotation** - Pola phyllotaxis berputar penuh saat aktif (NEW!)
- 🎨 **Preserve Grid Structure** - Bezier curves tetap terbentuk antar nodes

**3D Mode (GridBezier3D):**
- ✨ **Smooth Animation** - Transisi grid ↔ phyllotaxis dengan cubic ease-in-out (~2 detik)
- 🎲 **3 Mode Phyllotaxis 3D** - Random choice antara FLAT, SPHERE, dan CONE
- 🌀 **Mode PHYLLO_FLAT** - Spiral phyllotaxis 2D dalam ruang 3D dengan Z-axis curves (berotasi)
- 🌍 **Mode PHYLLO_SPHERE** - Phyllotaxis di permukaan bola menggunakan Fibonacci Sphere algorithm (berotasi)
- 🌪️ **Mode PHYLLO_CONE** - Spiral phyllotaxis dengan Z menurun seiring radius seperti tornado/cone terbalik (swing kiri-kanan)
- 🎥 **Camera Auto-Movement** - Kamera otomatis menyesuaikan posisi terbaik untuk setiap mode
- 🔄 **Rotation System** - FLAT & SPHERE berputar penuh (360°), CONE swing kiri-kanan (oscillating)
- 🎨 **Preserve 3D Curves** - Bezier curves 3D tetap terbentuk dengan wave/dome/bowl effect
- 🌊 **Depth Effect** - Spiral phyllotaxis dengan variasi Z (5 variasi trigonometric functions)

### Teknik Phyllotaxis

**Golden Angle:**
```cpp
float goldenAngle = 137.5 * (PI / 180.0f);  // ~2.39996 radian
```

**Position Calculation:**
```cpp
float angle = index * goldenAngle;
float radius = cellSize * 0.3f * sqrt(index);
float x = centerX + radius * cos(angle);
float y = centerY + radius * sin(angle);
```

**Bounds Checking:**
```cpp
bool isValid = (x >= 0 && x <= screenWidth &&
               y >= 0 && y <= screenHeight);
```

### Technical Implementation

**Node Properties (2D):**
```cpp
class Node {
    float x, y;                    // Posisi saat ini
    float startX, startY;          // Posisi awal (di-update tiap animasi)
    float originalGridX, originalGridY;  // Posisi grid asli (tidak berubah)
    float targetX, targetY;        // Posisi target

    bool isAnimating;              // Flag animasi
    float animProgress;            // 0.0 - 1.0
    float animSpeed;               // 0.008f (~1 detik di 120FPS)
};

// Phyllotaxis Rotation Properties (GridBezier class)
float phyllotaxisRotationAngle;      // Sudut rotasi saat ini (0-360°)
bool isPhyllotaxisRotating;          // Flag rotasi aktif/non-aktif
```

**Node3D Properties (3D):**
```cpp
class Node3D {
    float x, y, z;                 // Posisi saat ini
    float startX, startY, startZ; // Posisi awal (di-update tiap animasi)
    float originalGridX, originalGridY, originalGridZ;  // Posisi grid asli
    float targetX, targetY, targetZ;  // Posisi target

    bool isAnimating;              // Flag animasi
    float animProgress;            // 0.0 - 1.0
    float animSpeed;               // 0.004f (~2 detik di 120FPS)
};
```

**Phyllotaxis 2D Calculation:**
```cpp
float angle = index * goldenAngle;
float radius = cellSize * 0.35f * sqrt(index);
float phylloX = centerX + radius * cos(angle);
float phylloY = centerY + radius * sin(angle);
```

**Phyllotaxis 3D Calculation (3 Mode Tersedia):**

**Mode 1 - PHYLLO_FLAT (2D Spiral dalam 3D Space):**
```cpp
float angle = index * goldenAngle;
float radius = cellSize * 0.35f * sqrt(index);
float phylloX = centerX + radius * cos(angle);
float phylloY = centerY + radius * sin(angle);
float phylloZ = nodes[i]->z;  // Z dari existing grid 3D (dipertahankan)
```

**Mode 2 - PHYLLO_SPHERE (Fibonacci Sphere):**
```cpp
// Fibonacci Sphere Algorithm untuk distribusi uniform di permukaan bola
float goldenAngle = PI * (3.0f - sqrt(5.0f));  // ~2.399 rad
float offset = 2.0f / nodes.size();
float sphereRadius = cellSize * 4.0f;

float y = ((i * offset) - 1) + (offset / 2);
float radius = sqrt(1.0f - pow(y, 2));
float phi = ((i + 1) % (int)nodes.size()) * goldenAngle;

float x = radius * cos(phi);
float z = radius * sin(phi);

float phylloX = centerX + x * sphereRadius;
float phylloY = centerY + y * sphereRadius;
float phylloZ = centerZ + z * sphereRadius;
```

**Mode 3 - PHYLLO_CONE (Cone/Tornado Spiral):**
```cpp
float angle = index * goldenAngle;
float radius = cellSize * 0.35f * sqrt(index);
float phylloX = centerX + radius * cos(angle);
float phylloY = centerY + radius * sin(angle);

// Z menurun seiring radius (cone terbalik seperti funnel)
float centerZ = 400.0f;  // Mulai dari atas
float maxRadius = cellSize * 0.35f * sqrt(nodes.size());
float normalizedRadius = radius / maxRadius;  // 0.0 di center, 1.0 di edge
float phylloZ = centerZ - (normalizedRadius * 400.0f);  // Z menurun
```

**Cubic Ease-In-Out Easing:**
```cpp
float t = animProgress;
float easedT = t < 0.5 ? 4 * t * t * t : 1 - pow(-2 * t + 2, 3) / 2;
x = ofLerp(startX, targetX, easedT);
y = ofLerp(startY, targetY, easedT);
```

**Key Methods:**
- `enablePhyllotaxis()` - Hitung posisi phyllotaxis untuk setiap node
- `disablePhyllotaxis()` - Kembalikan ke posisi grid asli (originalGridX/Y)
- `togglePhyllotaxis()` - Switch on/off
- `updatePhyllotaxisAnimation()` - Update posisi setiap frame dengan easing

### Alur Animasi

**Grid → Phyllotaxis:**
```
1. Grid awal: x=100, y=100
2. enablePhyllotaxis(): targetX=500, targetY=500
3. Animasi: x bergerak 100 → 500 (smooth)
4. Selesai: x=500, y=500
   Update: startX=500, startY=500
```

**Phyllotaxis → Grid:**
```
1. Phyllotaxis: x=500, y=500
2. disablePhyllotaxis(): targetX=100, targetY=100 (originalGridX/Y)
3. Animasi: x bergerak 500 → 100 (smooth)
4. Selesai: x=100, y=100
   Update: startX=100, startY=100
```

### Catatan Penting

- ✅ **Support 2D & 3D mode** - Tersedia untuk GridBezier (2D) dan GridBezier3D (3D)
- ⚠️ **Preserve bezier connections** - Curve antar nodes tetap terbentuk
- ✅ **Reusable** - Bisa toggle on/off berkali-kali
- ✅ **Performance optimized** - Menggunakan `std::unique_ptr` dan efficient loops
- 🎨 **Z-Axis Preservation (FLAT)** - Mode FLAT mempertahankan Z-axis curves dari grid asli
- 🎲 **Random Mode Selection (3D)** - Setiap tekan 'X' memilih secara random dari 3 mode phyllotaxis 3D
- 🔄 **2D Rotation System (NEW!)** - GridBezier 2D memiliki rotasi 360° saat phyllotaxis aktif

### 2D Rotation System

**GridBezier 2D** sekarang memiliki sistem rotasi saat dalam mode phyllotaxis:

```cpp
// Update rotation angle di updateAnimation()
if (isPhyllotaxisRotating) {
    phyllotaxisRotationAngle += 0.5f;  // Kecepatan rotasi (derajat per frame)
    if (phyllotaxisRotationAngle >= 360.0f) {
        phyllotaxisRotationAngle -= 360.0f;
    }
}

// Apply rotation di display()
if (isPhyllotaxisRotating) {
    ofPushMatrix();
    float centerX = ofGetWidth() / 2.0f;
    float centerY = ofGetHeight() / 2.0f;
    ofTranslate(centerX, centerY);
    ofRotate(phyllotaxisRotationAngle);
    ofTranslate(-centerX, -centerY);
}

// ... semua rendering grid/bezier ...

if (isPhyllotaxisRotating) {
    ofPopMatrix();
}
```

**Fitur Rotasi 2D:**
- 🔄 **Full 360° Rotation** - Pola phyllotaxis berputar penuh terus-menerus
- ⚡ **Smooth Rotation** - Kecepatan 0.5° per frame pada 120 FPS
- 🎯 **Center-Based** - Rotasi mengelilingi center screen
- ✅ **Toggle On/Off** - Rotasi otomatis aktif saat phyllotaxis di-enable, stop saat disable
- 🎨 **Preserve Grid** - Struktur grid/bezier tetap terbentuk selama rotasi

### 3D Phyllotaxis Modes

GridBezier3D mendukung **3 mode phyllotaxis 3D** yang dipilih secara random:

| Mode | Deskripsi | Algoritma | Rotasi |
|------|-----------|-----------|--------|
| **PHYLLO_FLAT** | 2D spiral dalam 3D space | Golden angle spiral (X, Y) + Z dari grid | ✅ 360° rotation |
| **PHYLLO_SPHERE** | Phyllotaxis di permukaan bola | Fibonacci Sphere algorithm | ✅ 360° rotation |
| **PHYLLO_CONE** | Cone/tornado spiral | Golden angle + Z menurun per radius | 🌪️ Swing kiri-kanan |

**Detail Per Mode:**

**PHYLLO_FLAT:**
- Golden angle spiral (137.5°) untuk X dan Y
- Z-axis diambil dari existing grid 3D (dipertahankan)
- Berputar 360° pada sumbu Y (seperti planet)
- Visual: Pola spiral "datar" dengan efek 3D dari Z-axis curves

**PHYLLO_SPHERE:**
- Fibonacci Sphere algorithm untuk distribusi uniform di permukaan bola
- Golden angle sphere: `π × (3 - √5)` ≈ 2.399 radian
- X, Y, Z dihitung dari spherical coordinates
- Berputar 360° pada sumbu Y + X (sedikit miring untuk dinamis)
- Kamera otomatis menyesuaikan posisi terbaik untuk melihat sphere
- Visual: Planet dengan garis spiral di permukaan

**PHYLLO_CONE:**
- Golden angle spiral (137.5°) untuk X dan Y
- Z menurun seiring radius (400 → 0) seperti cone terbalik/funnel
- Swing kiri-kanan menggunakan `sin()` function (oscillating, bukan full rotation)
- Formula: `swingAngle = sin(angle * DEG_TO_RAD) * 60°`
- Visual: Tornado spiral dengan ayunan kiri-kanan

**Rotation System:**
```cpp
// Untuk 2D (GridBezier): Full rotation 360°
phyllotaxisRotationAngle += 0.5f;  // Derajat per frame
ofPushMatrix();
ofTranslate(centerX, centerY);
ofRotate(phyllotaxisRotationAngle);
ofTranslate(-centerX, -centerY);
// ... rendering ...
ofPopMatrix();

// Untuk FLAT dan SPHERE (3D): Full rotation 360°
phyllotaxisRotationAngle += 0.5f;  // Derajat per frame
ofRotateY(phyllotaxisRotationAngle);
ofRotateX(phyllotaxisRotationAngle * 0.3f);  // Sedikit miring

// Untuk CONE (3D): Oscillating swing
float swingAngle = sin(phyllotaxisRotationAngle * DEG_TO_RAD) * 60.0f;
ofRotateY(swingAngle);  // Swing 60° kiri-kanan
```

**Camera Auto-Position:**
```cpp
// Kamera otomatis menyesuaikan posisi terbaik berdasarkan mode phyllotaxis
if (isSphereMode) {
    cameraTargetPos = sphereCameraPos;  // Posisi optimal untuk sphere
} else {
    cameraTargetPos = normalCameraPos;  // Posisi normal
}
```

---

## 🎨 GridBezier3D: 3D Rendering System

GridBezier3D adalah ekstensi 3D dari GridBezier yang menampilkan grid bezier dalam ruang 3D dengan efek visual yang lebih dramatis.

### 3D Mode Rendering

GridBezier3D mendukung **7 mode rendering 3D** yang setara dengan versi 2D:

| Mode | Deskripsi | Fitur 3D |
|------|-----------|----------|
| **VARYING3D** | Static 3D grid | Bezier curves di ruang 3D dengan Z-axis curve |
| **MULURLR3D** | Growing 3D grid | Animasi easing di 3D space |
| **WOBBLE3D** | 3D Perlin noise | **Wobble di 3 axis (X, Y, Z)** untuk gerakan organik |
| **WAVE3D** | 3D Diagonal wave | **Wave pada posisi Z** dan control points |
| **RADIALWAVE3D** | 3D Radial ripple | **Radial wave pada Z-axis** dari center ke luar |
| **HORIZONTALWAVE3D** | 3D Horizontal wave | **Horizontal wave pada Z-axis** dari kiri ke kanan |
| **VERTICALWAVE3D** | 3D Vertical wave | **Vertical wave pada Z-axis** dari atas ke bawah |

### Z-Axis Calculation

GridBezier3D menggunakan **5 variasi trigonometric functions** untuk menghitung posisi Z setiap node:

```cpp
// Normalized distance dari center (0.0 - 1.0)
float normalizedDist = distFromCenter / maxDist;

switch (zCoordinate) {
    case 0: return sin(normalizedDist * PI / 2) * 200 - 100;     // Smooth rise
    case 1: return cos(normalizedDist * PI / 2) * 200 - 100;     // Smooth fall
    case 2: return sin(normalizedDist * TWO_PI) * 200 - 100;     // Full sine wave
    case 3: return cos(normalizedDist * TWO_PI) * 200 - 100;     // Full cosine wave
    case 4:                                                      // Tangent wave (clamped)
        float tanVal = tan(normalizedDist * TWO_PI);
        if (tanVal > 2.0f) tanVal = 2.0f;
        if (tanVal < -2.0f) tanVal = -2.0f;
        return tanVal * 170 - 100;
}
```

**Z-coordinate dipilih secara random** (0-4) saat setiap initialize/reset, menciptakan variasi bentuk 3D yang berbeda-beda.

### 3D Bezier Curves

Berbeda dengan versi 2D yang menggunakan `ofDrawBezier(x1, y1, x2, y2, ...)`, GridBezier3D menggunakan 3D bezier curves:

```cpp
// 2D Bezier (GridBezier)
ofDrawBezier(n1.x, n1.y, cp1_x, cp1_y, cp2_x, cp2_y, n2.x, n2.y);

// 3D Bezier (GridBezier3D)
ofDrawBezier(n1.x, n1.y, n1.z,           // Start point (X, Y, Z)
             cp1_x, cp1_y, cp1_z,        // Control point 1 (X, Y, Z)
             cp2_x, cp2_y, cp2_z,        // Control point 2 (X, Y, Z)
             n2.x, n2.y, n2.z);          // End point (X, Y, Z)
```

Control points juga memiliki offset Z untuk menciptakan kurva 3D yang dinamis.

### 3D Wave Effects

Mode WAVE3D, RADIALWAVE3D, HORIZONTALWAVE3D, dan VERTICALWAVE3D memiliki efek wave 3D:

**Wave pada Z-axis:**
```cpp
// Hitung wave value (-1 sampai 1)
float wave = sin(i * frequency + j * frequency + time * speed);

// Wave offset untuk Z-axis (3D effect!)
float waveZ = sin(i * frequency * 0.7 + j * frequency * 0.7 + time * waveSpeed);
float waveZOffset = waveZ * waveAmplitudeZ;  // AmplitudeZ = 30

// Posisi Z dengan wave effect
float z1 = n1.z + waveZOffset;
float z2 = n2.z + waveZOffset;

// Control points juga di-wave di Z
float cp1_z = z1 + 50 + waveZOffset;
float cp2_z = z2 - 50 + waveZOffset;
```

**Vertical & Horizontal Bezier dengan 3D Wave:**
```cpp
ofDrawBezier(n1.x, n1.y, z1,              // Start dengan wave Z
             n1.x + curveAmount, (n1.y + n2.y) / 2, cp1_z,  // CP1 dengan wave Z
             n2.x - curveAmount, (n1.y + n2.y) / 2, cp2_z,  // CP2 dengan wave Z
             n2.x, n2.y, z2);              // End dengan wave Z
```

### 3D Wobble Effects

WOBBLE3D mode menggunakan **Perlin noise dalam 3 axis** (X, Y, Z) untuk gerakan organik:

```cpp
// WOBBLE 3D dengan PERLIN NOISE untuk setiap node
float time = ofGetFrameNum() * 0.02f;

// Hitung wobble untuk node1 (X, Y, Z)
float noise1_x = ofNoise(time + n1.noiseOffset);
float noise1_y = ofNoise(time + n1.noiseOffset + 100);  // Offset berbeda
float noise1_z = ofNoise(time + n1.noiseOffset + 200);  // Offset berbeda
float wobble1_x = ofMap(noise1_x, 0, 1, -15, 15);
float wobble1_y = ofMap(noise1_y, 0, 1, -15, 15);
float wobble1_z = ofMap(noise1_z, 0, 1, -20, 20);

// Hitung wobble untuk node2 (X, Y, Z)
float noise2_x = ofNoise(time + n2.noiseOffset);
float noise2_y = ofNoise(time + n2.noiseOffset + 100);
float noise2_z = ofNoise(time + n2.noiseOffset + 200);
float wobble2_x = ofMap(noise2_x, 0, 1, -15, 15);
float wobble2_y = ofMap(noise2_y, 0, 1, -15, 15);
float wobble2_z = ofMap(noise2_z, 0, 1, -20, 20);

// Pulse untuk line width (hybrid approach)
float pulse = cos(ofGetFrameNum() * 0.05f);
float combined = ((noise1_x + noise2_x) / 2.0f + pulse) / 2.0f;
float lineWidth = ofMap(combined, 0, 1, 3, 7);
ofSetLineWidth(lineWidth);

// Posisi node dengan wobble 3D
float x1 = n1.x + wobble1_x;
float y1 = n1.y + wobble1_y;
float z1 = n1.z + wobble1_z;

// Control points juga di-wobble
float cp1_z = z1 + 50 + wobble1_z;
float cp2_z = z2 - 50 + wobble2_z;

// Draw bezier di 3D space dengan wobble
ofDrawBezier(x1, y1, z1,
             cp1_x, cp1_y, cp1_z,
             cp2_x, cp2_y, cp2_z,
             x2, y2, z2);
```

### Camera Animation System

GridBezier3D menggunakan **ofEasyCam** dengan sistem animasi otomatis:

**State Machine dengan 5 States:**
```cpp
enum CameraAnimState {
    CAM_IDLE,           // Tidak ada animasi
    CAM_TO_TARGET,      // Animasi dari awal ke target
    CAM_TO_START,       // Animasi dari target ke awal (reverse)
    CAM_DELAY_TO_TARGET // Delay sebelum animasi ke target
};
```

**Parameter Animation:**
- **Animation Duration**: 8.0 detik (dengan smooth easing)
- **Initial Delay**: 5.5 detik sebelum animasi pertama
- **Reverse Delay**: 1.0 detik delay saat reverse complete

**Camera Positions:**
```cpp
// Start position (awal)
cameraStartPos = ofVec3f(ofGetWidth() / 2, (ofGetHeight() / 2) + 100, 811);

// Target position (setelah animasi)
cameraTargetPos = ofVec3f(ofGetWidth() / 2, -181, 996);

// Look at center (selalu)
cam.lookAt(ofVec3f(ofGetWidth() / 2, ofGetHeight() / 2, 0));
```

**Easing Function (Smooth Step):**
```cpp
float t = cameraAnimationProgress;
float easedT = t * t * (3.0f - 2.0f * t);  // Smooth step (3t² - 2t³)

// Interpolate posisi kamera
ofVec3f currentPos = cameraStartPos.getInterpolated(cameraTargetPos, easedT);
cam.setPosition(currentPos);
```

### Node3D Class

GridBezier3D menggunakan `Node3D` class yang memiliki tambahan noise offsets untuk 3D wobble:

```cpp
class Node3D {
public:
    float x, y, z;           // 3D position
    float noiseOffset;       // Untuk Perlin noise wobble

    Node3D(float x, float y, float z) {
        this->x = x;
        this->y = y;
        this->z = z;
        this->noiseOffset = ofRandom(1000);  // Random offset untuk noise
    }
};
```

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
  - **ofEasyCam** untuk 3D camera system
  - **3D Rendering** dengan OpenGL-based functions
- **C++17**
- **Visual Studio 2022 Community** (v143 toolset)
- **Strategy Pattern** untuk arsitektur yang fleksibel
- **Bezier Curve Algorithms** untuk smooth animations
- **3D Mathematics** (trigonometric functions untuk Z-axis calculation)

---

## 📦 Installation

### Prerequisites

1. Install **[OpenFrameworks](https://openframeworks.cc/)** untuk Windows
2. Install **Visual Studio 2022 Community** dengan workload "Desktop development with C++"

### Setup

```bash
# Clone repository ini
git clone https://github.com/username/JaringSketch.git

# Checkout branch sketch-grid-bezier-3d
git checkout sketch-grid-bezier-3d

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
- Mode **MULURLR/WOBBLE/WAVE/RADIALWAVE/HORIZONTALWAVE/VERTICALWAVE**: Linear, Quadratic, Cubic, atau Wobble saja (NO WaveAnimation!) ⚠️

**Untuk GridBezier Visual Effect:**
Gunakan mode: VARYING, MULURLR, WOBBLE, WAVE, RADIALWAVE, HORIZONTALWAVE, atau VERTICALWAVE (rendering mode).

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
│   ├── Node.h                # 2D Node class untuk grid positions
│   ├── Node3D.h              # 3D Node class untuk grid positions dengan noise offsets
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
│   │   ├── GridBezier.cpp/h              # 2D Grid shape dengan bezier curves
│   │   └── GridBezier3D.cpp/h            # 3D Grid shape dengan bezier curves di ruang 3D
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

## 📝 Current Status: **master**

Branch ini adalah **versi stabil** dari JaringSketch dengan semua fitur terbaru yang telah diimplementasikan. Fitur yang tersedia:

✅ **Auto 2D/3D Selection**: Random choice antara GridBezier (2D) dan GridBezier3D (3D) saat startup/reset
✅ Grid layout system dengan konfigurasi cols/rows
✅ **7 Rendering Modes (2D & 3D)**: VARYING, MULURLR, WOBBLE, WAVE, RADIALWAVE, HORIZONTALWAVE, VERTICALWAVE
✅ **5 Animation Strategies**: Linear, Quadratic, Cubic, Wobble, Wave
✅ **6 Color Strategies**: Solid, Horizontal/Vertical/Radial Gradient, Rainbow Spiral, Time-Based
✅ **6 Initialization Directions**: TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, RADIAL_OUT, RADIAL_IN (random!)
✅ **Multi-mode rendering** dengan efek visual bervariasi
✅ **Dynamic mode selection** (random pada startup/reset)
✅ Trails effect untuk visual impact
✅ Strategy pattern untuk animasi & warna
✅ Bezier curve rendering dengan curve intensity dinamis
✅ Perlin noise untuk organik wobble effects
✅ Sinusoidal wave untuk diagonal, horizontal, vertikal & radial wave patterns
✅ Distance-based radial ripple effects
✅ **Dynamic line width** yang mengikuti gelombang (WAVE, RADIALWAVE, HORIZONTALWAVE, VERTICALWAVE & WOBBLE mode)
✅ **Hybrid dynamic line width** dengan noise + pulse combination (WOBBLE mode)
✅ **🌻 PHYLLO TAXIS PATTERN**: Pola spiral dengan golden angle 137.5° untuk 2D & 3D Grid
  - **2D Mode**: Golden angle spiral dengan smooth toggle animation (~1 detik)
  - **3 Mode Phyllotaxis 3D**: Random choice antara FLAT, SPHERE, dan CONE
    - **PHYLLO_FLAT**: 2D spiral dalam 3D space, Z-axis dipertahankan (berotasi 360°)
    - **PHYLLO_SPHERE**: Fibonacci Sphere algorithm, distribusi uniform di permukaan bola (berotasi 360°)
    - **PHYLLO_CONE**: Cone/tornado spiral, Z menurun seiring radius (swing kiri-kanan oscillating)
  - **Rotation System**: FLAT & SPHERE berputar penuh (360°), CONE swing oscillating (±60°)
  - **Camera Auto-Position**: Kamera otomatis menyesuaikan posisi terbaik untuk setiap mode
  - **Smooth Toggle Animation**: Transisi grid ↔ phyllotaxis dengan cubic ease-in-out (~2 detik untuk 3D)
  - **Bidirectional Animation**: Toggle on/off berkali-kali dengan animasi smooth
  - **Key 'X' Control**: Tekan 'X' untuk memilih mode phyllotaxis secara random
  - **Preserve Grid Structure**: Bezier curves tetap terbentuk antar nodes
✅ **GridBezier3D Features**:
  - **3D Bezier Curves**: Kurva bezier dengan control points dalam ruang 3D (X, Y, Z)
  - **Z-Axis Calculation**: 5 variasi trigonometric functions (sin, cos, tan) untuk posisi Z nodes
  - **3D Wave Effects**: Gelombang 3D yang mempengaruhi posisi Z dan control points (WAVE3D, RADIALWAVE3D, HORIZONTALWAVE3D, VERTICALWAVE3D)
  - **3D Wobble Effects**: Perlin noise dalam 3 axis (X, Y, Z) untuk gerakan organik (WOBBLE3D)
  - **Camera Animation System**: State machine dengan 5 states (IDLE, TO_TARGET, TO_START, DELAY) untuk smooth camera movement
  - **ofEasyCam Integration**: Kamera 3D dengan auto position dan look-at center grid
  - **Camera Print Debug**: Tekan 'P' untuk print camera position dan orientation ke console
✅ HSB color system untuk vivid gradients
✅ **Bright Colors Only**: High saturation (200-255) dan brightness (200-255) untuk vivid colors (NEW!)
✅ Delta time-based animation (FPS independent)
✅ Memory-safe implementation dengan `std::unique_ptr`
✅ **Auto re-initialization** untuk RADIAL_OUT mode (chaotic → rapi setelah animasi)
✅ **🤖 Fully Automated Sequence**: Sistem otomatis penuh tanpa perlu keypress (NEW!)
  - **State Machine**: 8 states untuk complete automation loop
  - **Auto Loop**: Run → Delay → Grid → Phyllotaxis → Grid → Reset → Loop
  - **Random Every Reset**: Mode 2D/3D, warna, animasi, arah selalu baru
  - **Total Cycle**: ~20-25 detik per cycle dengan infinite loop
  - **Still Interactive**: Tombol S, X, R, Q, P tetap berfungsi untuk override
✅ **2D Phyllotaxis Rotation**: GridBezier 2D memiliki 360° rotation saat phyllotaxis aktif (NEW!)
  - **Smooth Rotation**: 0.5° per frame pada 120 FPS
  - **Center-Based**: Rotasi mengelilingi center screen
  - **Toggle On/Off**: Rotasi otomatis aktif saat phyllotaxis di-enable
✅ **Cursor Hidden by Default**: Kursor otomatis tersembunyi saat aplikasi berjalan (NEW!)

### Mode Highlights:

**2D Mode (GridBezier):**
- **🌻 Phyllotaxis Pattern (NEW!)**: Tekan 'X' untuk toggle pola spiral dengan golden angle 137.5°
  - **Smooth Animation**: Transisi grid ↔ spiral dengan cubic ease-in-out
  - **Bidirectional**: Bisa toggle on/off berkali-kali
  - **360° Rotation**: Pola phyllotaxis berputar penuh saat aktif (NEW!)
  - **Preserve Structure**: Bezier curves tetap terbentuk
- **WOBBLE Mode**: Perlin noise-based organic movement dengan **hybrid dynamic line width** (noise + pulse)
- **WAVE Mode**: Diagonal wave pattern dengan **dynamic line width** yang berdenyut
- **RADIALWAVE Mode**: Radial ripple effect dengan **dynamic line width** yang berdenyut
- **HORIZONTALWAVE Mode**: Horizontal wave pattern dengan **dynamic line width** yang berdenyut
- **VERTICALWAVE Mode**: Vertical wave pattern dengan **dynamic line width** yang berdenyut
- **MULURLR Mode**: Growing grid dengan smooth easing
- **VARYING Mode**: Static grid dengan **random curve intensity** yang bervariasi setiap reset
- **RADIAL_OUT Init Direction**: Grid tumbuh dari tengah ke luar (chaotic visual), lalu otomatis re-initialize ke arah random yang rapi setelah animasi selesai

**3D Mode (GridBezier3D):**
- **🌻 Phyllotaxis Pattern 3D (NEW!)**: Tekan 'X' untuk toggle pola spiral 3D dengan golden angle
  - **Smooth Animation**: Transisi grid 3D ↔ spiral dengan cubic ease-in-out (~2 detik)
  - **Bidirectional**: Bisa toggle on/off berkali-kali
  - **Preserve Z-Axis Curves**: Z dari grid asli tetap dipertahankan
  - **Camera Auto-Movement**: Camera berputar mengelilingi spiral
  - **Depth Effect**: Spiral dengan variasi Z (5 trigonometric functions)
- **VARYING3D Mode**: Static 3D grid dengan bezier curves di ruang 3D
- **MULURLR3D Mode**: Growing 3D grid dengan smooth easing
- **WOBBLE3D Mode**: **3D Perlin noise** dalam 3 axis (X, Y, Z) untuk gerakan organik dengan hybrid dynamic line width
- **WAVE3D Mode**: **3D diagonal wave** yang mempengaruhi curve amount dan posisi Z dengan dynamic line width
- **RADIALWAVE3D Mode**: **3D radial ripple** yang merambat dari tengah dengan efek pada Z-axis dan dynamic line width
- **HORIZONTALWAVE3D Mode**: **3D horizontal wave** yang merambat dari kiri ke kanan dengan efek pada Z-axis dan dynamic line width
- **VERTICALWAVE3D Mode**: **3D vertical wave** yang merambat dari atas ke bawah dengan efek pada Z-axis dan dynamic line width
- **Z-Axis Curve**: 5 variasi trigonometric functions (sin, cos, tan) untuk posisi Z nodes:
  - Case 0: `sin(normalizedDist * PI / 2) * 200 - 100` (Smooth rise)
  - Case 1: `cos(normalizedDist * PI / 2) * 200 - 100` (Smooth fall)
  - Case 2: `sin(normalizedDist * TWO_PI) * 200 - 100` (Full sine wave)
  - Case 3: `cos(normalizedDist * TWO_PI) * 200 - 100` (Full cosine wave)
  - Case 4: `tan(normalizedDist * TWO_PI) * 170 - 100` (Tangent wave dengan clamping)
- **Camera Animation**: Auto movement dari position awal ke target dan kembali dengan smooth easing (8 second duration)

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
- **[Watch Demo](https://youtu.be/R_g6W-CVu7A)** - YouTube demonstration
- **[Support Me](https://sociabuzz.com/abdkdhni)** - Fund the experiments ☕

---

**Made with ❤️ for learning and creative exploration**
