#include "GridBezier.h"
#include "../clr/SolidColor.h"

GridBezier::GridBezier(float cellSize, float margin) {
  this->cellSize = cellSize;
  this->margin = margin;
  currentCols = 0;
  currentRows = 0;
  colorStrategy = std::make_unique<SolidColor>(ofColor(255));
  this->curveIntensity = ofRandom(0, 6);

  this->randomModeBezier = (int)ofRandom(0, 5);
  this->currentBzMode = static_cast<GridBezier::bezierMode>(randomModeBezier);

  //test currentBzMode
//this->currentBzMode = VARYING;

  // Random arah inisialisasi (5 arah)
  int randomDir = (int)ofRandom(0, 5);
  this->currentInitDir = static_cast<GridBezier::initDirection>(randomDir);
  
  //test arah inisialisasi
  //this->currentInitDir = RADIAL_OUT;
}

void GridBezier::setAnimationStr(
    std::unique_ptr<AnimationStrategy> animStrategy) {
  this->animStrategy = std::move(animStrategy);
}

void GridBezier::setColorStr(std::unique_ptr<ColorStrategy> colorStrategy) {
  this->colorStrategy = std::move(colorStrategy);
}

void GridBezier::initialize(int w, int h) {
  // Simpan width/height untuk re-initialize
  lastWidth = w;
  lastHeight = h;

  // Hitung area yang bisa digunakan
  float usableWidth = w - margin * 2;
  targetCols = (int)(usableWidth / cellSize);
  float usableHeight = h - margin * 2;
  targetRows = (int)(usableHeight / cellSize);

  maxCols = targetCols;
  maxRows = targetRows;

  offsetX = margin + (usableWidth - targetCols * cellSize) / 2.0;
  offsetY = margin + (usableHeight - targetRows * cellSize) / 2.0;

  // Allocate node array
  totalNodes = (maxCols + 1) * (maxRows + 1);

  // Inisialisasi semua node berdasarkan arah random
  switch (currentInitDir) {
    case TOP_LEFT:
      // Atas ke bawah, kiri ke kanan
      for (int j = 0; j <= maxRows; j++) {
        for (int i = 0; i <= maxCols; i++) {
          float startX = offsetX + i * cellSize;
          float startY = offsetY + j * cellSize;
          nodes.push_back(std::make_unique<Node>(startX, startY));
        }
      }
      break;

    case TOP_RIGHT:
      // Atas ke bawah, kanan ke kiri
      for (int j = 0; j <= maxRows; j++) {
        for (int i = maxCols; i >= 0; i--) {
          float startX = offsetX + i * cellSize;
          float startY = offsetY + j * cellSize;
          nodes.push_back(std::make_unique<Node>(startX, startY));
        }
      }
      break;

    case BOTTOM_LEFT:
      // Bawah ke atas, kiri ke kanan
      for (int j = maxRows; j >= 0; j--) {
        for (int i = 0; i <= maxCols; i++) {
          float startX = offsetX + i * cellSize;
          float startY = offsetY + j * cellSize;
          nodes.push_back(std::make_unique<Node>(startX, startY));
        }
      }
      break;

    case BOTTOM_RIGHT:
      // Bawah ke atas, kanan ke kiri
      for (int j = maxRows; j >= 0; j--) {
        for (int i = maxCols; i >= 0; i--) {
          float startX = offsetX + i * cellSize;
          float startY = offsetY + j * cellSize;
          nodes.push_back(std::make_unique<Node>(startX, startY));
        }
      }
      break;

    case RADIAL_OUT:
      // Tengah ke luar (distance-based sorting)
      {
        // Struct untuk menyimpan info node
        struct NodeInfo {
          int i, j;
          float distance;
        };

        std::vector<NodeInfo> nodeInfos;
        float centerX = maxCols / 2.0f;
        float centerY = maxRows / 2.0f;

        // Hitung jarak semua node dari center
        for (int j = 0; j <= maxRows; j++) {
          for (int i = 0; i <= maxCols; i++) {
            float dist = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
            nodeInfos.push_back({i, j, dist});
          }
        }

        // Sort berdasarkan distance (terdekat dulu)
        std::sort(nodeInfos.begin(), nodeInfos.end(),
          [](const NodeInfo& a, const NodeInfo& b) {
            return a.distance < b.distance;
          });

        // Push nodes ke vector BERDASARKAN URUTAN SORTED
        for (const auto& info : nodeInfos) {
          float startX = offsetX + info.i * cellSize;
          float startY = offsetY + info.j * cellSize;
          nodes.push_back(std::make_unique<Node>(startX, startY));
        }
      }
      break;
  }
}

void GridBezier::updateAnimation() {
  if (animStrategy) {
    animStrategy->update();
    currentCols = animStrategy->getValue(targetCols);
    currentRows = animStrategy->getValue(targetRows);

    if (currentCols > maxCols) currentCols = maxCols;
    if (currentRows > maxRows) currentRows = maxRows;
  }

  // Re-initialize dengan TOP_LEFT setelah RADIAL_OUT selesai
  if (currentInitDir == RADIAL_OUT && isAnimationFinished() && !hasReinitialized) {
    // Clear nodes
    nodes.clear();
    int randomDir = (int)ofRandom(0, 4);
    this->currentInitDir = static_cast<GridBezier::initDirection>(randomDir);

    // Re-initialize
    initialize(lastWidth, lastHeight);

    // Reset flag
    hasReinitialized = true;

    // Set ke full grid (karena setelah re-init, langsung tampilkan full)
    currentCols = maxCols;
    currentRows = maxRows;
  }
}

void GridBezier::display() {
    switch (currentBzMode) {
    case MULURLR:
        setBezierMulurLR();
        break;
    case WOBBLE:
        setBezierWobble();
        break;
    case WAVE:
        setBezierWave();
        break;
    case RADIALWAVE:
        setBezierRadialWave();
        break;
    case VARYING:
        setBezierVarying();
        break;
   }
}

bool GridBezier::isAnimationFinished() {
  if (animStrategy) {
    return animStrategy->isFinished();
  }
  return true;
}

void GridBezier::resetAnimation() {
  currentCols = 0;
  currentRows = 0;
  hasReinitialized = false;  // Reset flag untuk RADIAL_OUT
  if (animStrategy) {
    animStrategy->reset();
  }
}

int GridBezier::getTargetCols() { return targetCols; }

int GridBezier::getTargetRows() { return targetRows; }

int GridBezier::getCurrentCols() { return currentCols; }

int GridBezier::getCurrentRows() { return currentRows; }

int GridBezier::getTotalNodes() { return totalNodes; }

void GridBezier::setBezierMulurLR() {
    // Gambar bezier vertikal (setiap kolom)
    for (int i = 0; i <= currentCols; i++) {
        for (int j = 0; j < currentRows; j++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = (j + 1) * (currentCols + 1) + i;

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna dari color strategy
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            float curveAmount = cellSize * curveIntensity;

            ofDrawBezier(n1.x, n1.y, n1.x + curveAmount, (n1.y + n2.y) / 2,
                n2.x - curveAmount, (n1.y + n2.y) / 2, n2.x, n2.y);
        }
    }

    // Gambar bezier horizontal (setiap baris)
    for (int j = 0; j <= currentRows; j++) {
        for (int i = 0; i < currentCols; i++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = j * (currentCols + 1) + (i + 1);

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna dari color strategy
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();
            float curveAmount = cellSize * curveIntensity;

            ofDrawBezier(n1.x, n1.y, (n1.x + n2.x) / 2, n1.y + curveAmount,
                (n1.x + n2.x) / 2, n2.y - curveAmount, n2.x, n2.y);
        }
    }
}

void GridBezier::setBezierVarying() {
    // Gambar bezier vertikal (setiap kolom)

    for (int i = 0; i <= currentCols; i++) {
        for (int j = 0; j < currentRows; j++) {
            int node1 = j * (maxCols + 1) + i;
            int node2 = (j + 1) * (maxCols + 1) + i;

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna dari color strategy
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            float curveAmount = cellSize * curveIntensity;

            ofDrawBezier(n1.x, n1.y, n1.x + curveAmount, (n1.y + n2.y) / 2,
                n2.x - curveAmount, (n1.y + n2.y) / 2, n2.x, n2.y);
        }
    }

    // Gambar bezier horizontal (setiap baris)
    for (int j = 0; j <= currentRows; j++) {
        for (int i = 0; i < currentCols; i++) {
            int node1 = j * (maxCols + 1) + i;
            int node2 = j * (maxCols + 1) + (i + 1);

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna dari color strategy
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();
            float curveAmount = cellSize * curveIntensity;

            ofDrawBezier(n1.x, n1.y, (n1.x + n2.x) / 2, n1.y + curveAmount,
                (n1.x + n2.x) / 2, n2.y - curveAmount, n2.x, n2.y);
        }
    }
}

void GridBezier::setBezierWobble() {
    // Clamp untuk safety

    // Gambar bezier vertikal
    for (int i = 0; i <= currentCols; i++) {
        for (int j = 0; j < currentRows; j++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = (j + 1) * (currentCols + 1) + i;

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            // WOBBLE dengan PERLIN NOISE
            float time = ofGetFrameNum() * 0.02f;  // Kecepatan animasi noise (lebih cepat)

            // Hitung wobble untuk node1
            float noise1 = ofNoise(time + n1.noiseOffset); 
            float wobble1 = ofMap(noise1, 0, 1, -10, 10);    

            // Hitung wobble untuk node2
            float noise2 = ofNoise(time + n2.noiseOffset);
            float wobble2 = ofMap(noise2, 0, 1, -10, 10);

            // Pulse untuk animasi global
            float pulse = cos(ofGetFrameNum() * 0.05f);
            float combined = ((noise1 + noise2) / 2.0f + pulse) / 2.0f;
            float lineWidth = ofMap(combined, 0, 1, 3, 6);
            ofSetLineWidth(lineWidth);


            // Curve amount bisa tetap atau juga di-wobble
            float curveAmount = cellSize * curveIntensity;

            // Posisi node dengan wobble
            float x1 = n1.x + wobble1;
            float y1 = n1.y + wobble1;
            float x2 = n2.x + wobble2;
            float y2 = n2.y + wobble2;


            ofDrawBezier(x1, y1, x1 + curveAmount, (y1 + y2) / 2,
                x2 - curveAmount, (y1 + y2) / 2, x2, y2);
        }
    }

    // Gambar bezier horizontal
    for (int j = 0; j <= currentRows; j++) {
        for (int i = 0; i < currentCols; i++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = j * (currentCols + 1) + (i + 1);

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            // WOBBLE dengan PERLIN NOISE
            float time = ofGetFrameNum() * 0.02f;  // speed
            float noise1 = ofNoise(time + n1.noiseOffset);
            float wobble1 = ofMap(noise1, 0, 1, -10, 10);  
            float noise2 = ofNoise(time + n2.noiseOffset);
            float wobble2 = ofMap(noise2, 0, 1, -10, 10);


            // Pulse untuk animasi global
            float pulse = sin(ofGetFrameNum() * 0.05f);
            float combined = ((noise1 + noise2)/2.0f + pulse) / 2.0f;
            float lineWidth = ofMap(combined, 0, 1, 3, 6);
            ofSetLineWidth(lineWidth);

            float curveAmount = cellSize * curveIntensity;


            float x1 = n1.x + wobble1;
            float y1 = n1.y + wobble1;
            float x2 = n2.x + wobble2;
            float y2 = n2.y + wobble2;


            ofDrawBezier(x1, y1, (x1 + x2) / 2, y1 + curveAmount,
                (x1 + x2) / 2, y2 - curveAmount, x2, y2);
        }
    }
}

void GridBezier::setBezierWave() {
    // Parameter Wave
    float waveAmplitude = 35;   // Tinggi gelombang (pixel)
    float waveFrequency = 0.4;  // Kerapatan gelombang
    float waveSpeed = 4;       // Kecepatan merambat
    float time = ofGetFrameNum() * 0.03f;  // Time-based animation

    // Gambar bezier vertikal (setiap kolom)
    for (int i = 0; i <= currentCols; i++) {
        for (int j = 0; j < currentRows; j++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = (j + 1) * (currentCols + 1) + i;

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            // Hitung wave offset (DIAGONAL WAVE)
            float wave = sin(i * waveFrequency + j * waveFrequency + time * waveSpeed);
            float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Mapping wave ke line width
            ofSetLineWidth(lineWidth);
            float waveOffset = wave * waveAmplitude;

            // Curve amount dasar + wave effect
            float baseCurve = cellSize * curveIntensity;
            float curveAmount = baseCurve + waveOffset;

            ofDrawBezier(n1.x, n1.y, n1.x + curveAmount, (n1.y + n2.y) / 2,
                n2.x - curveAmount, (n1.y + n2.y) / 2, n2.x, n2.y);
        }
    }

    // Gambar bezier horizontal (setiap baris)
    for (int j = 0; j <= currentRows; j++) {
        for (int i = 0; i < currentCols; i++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = j * (currentCols + 1) + (i + 1);

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();

            // Hitung wave offset (DIAGONAL WAVE)
            float wave = sin(i * waveFrequency + j * waveFrequency + time * waveSpeed);
            float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Mapping wave ke line width
            ofSetLineWidth(lineWidth);
            float waveOffset = wave * waveAmplitude;

            // Curve amount dasar + wave effect
            float baseCurve = cellSize * curveIntensity;
            float curveAmount = baseCurve + waveOffset;

            ofDrawBezier(n1.x, n1.y, (n1.x + n2.x) / 2, n1.y + curveAmount,
                (n1.x + n2.x) / 2, n2.y - curveAmount, n2.x, n2.y);
        }
    }
}

void GridBezier::setBezierRadialWave() {
    // Parameter Radial Wave
    float waveAmplitude = 35;    // Tinggi gelombang (pixel)
    float waveFrequency = 0.4;   // Kerapatan gelombang
    float waveSpeed = 4;         // Kecepatan merambat
    float time = ofGetFrameNum() * 0.03f;  // Time-based animation

    // Gambar bezier vertikal (setiap kolom)
    for (int i = 0; i <= currentCols; i++) {
        for (int j = 0; j < currentRows; j++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = (j + 1) * (currentCols + 1) + i;

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            // Dapatkan warna
            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();
            
            // Hitung jarak dari center untuk RADIAL WAVE
            float centerX = currentCols / 2.0f;
            float centerY = currentRows / 2.0f;
            float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

            // Radial wave: gelombang merambat dari tengah ke luar
            float wave = sin(distFromCenter * waveFrequency - time * waveSpeed);
            float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Mapping wave ke line width
            ofSetLineWidth(lineWidth);
            float waveOffset = wave * waveAmplitude;

            // Curve amount dasar + wave effect
            float baseCurve = cellSize * curveIntensity;
            float curveAmount = baseCurve + waveOffset;

            ofDrawBezier(n1.x, n1.y, n1.x + curveAmount, (n1.y + n2.y) / 2,
                n2.x - curveAmount, (n1.y + n2.y) / 2, n2.x, n2.y);
        }
    }

    // Gambar bezier horizontal (setiap baris)
    for (int j = 0; j <= currentRows; j++) {
        for (int i = 0; i < currentCols; i++) {
            int node1 = j * (currentCols + 1) + i;
            int node2 = j * (currentCols + 1) + (i + 1);

            Node& n1 = *nodes[node1];
            Node& n2 = *nodes[node2];

            ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
            ofSetColor(c);
            ofNoFill();
            ofSetLineWidth(ofRandom(3, 6));
            // Hitung jarak dari center untuk RADIAL WAVE
            float centerX = currentCols / 2.0f;
            float centerY = currentRows / 2.0f;
            float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

            // Radial wave: gelombang merambat dari tengah ke luar
            float wave = sin(distFromCenter * waveFrequency - time * waveSpeed);
            float lineWidth = ofMap(wave, -1, 1, 3, 6);  // Mapping wave ke line width
            ofSetLineWidth(lineWidth);
            float waveOffset = wave * waveAmplitude;

            // Curve amount dasar + wave effect
            float baseCurve = cellSize * curveIntensity;
            float curveAmount = baseCurve + waveOffset;

            ofDrawBezier(n1.x, n1.y, (n1.x + n2.x) / 2, n1.y + curveAmount,
                (n1.x + n2.x) / 2, n2.y - curveAmount, n2.x, n2.y);
        }
    }
}