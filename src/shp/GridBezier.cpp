#include "GridBezier.h"
#include "../clr/SolidColor.h"

GridBezier::GridBezier(float cellSize, float margin,bezierMode currentBzMode) {
  this->cellSize = cellSize;
  this->margin = margin;
  currentCols = 0;
  currentRows = 0;
  colorStrategy = std::make_unique<SolidColor>(ofColor(255));
  this->currentBzMode = currentBzMode;
  this->curveIntensity = ofRandom(0, 5);
}

void GridBezier::setAnimationStr(
    std::unique_ptr<AnimationStrategy> animStrategy) {
  this->animStrategy = std::move(animStrategy);
}

void GridBezier::setColorStr(std::unique_ptr<ColorStrategy> colorStrategy) {
  this->colorStrategy = std::move(colorStrategy);
}

void GridBezier::initialize(int w, int h) {
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

  // Inisialisasi semua node
  for (int j = 0; j <= maxRows; j++) {
    for (int i = 0; i <= maxCols; i++) {
      float startX = offsetX + i * cellSize;
      float startY = offsetY + j * cellSize;
      nodes.push_back(std::make_unique<Node>(startX, startY));
    }
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
}

void GridBezier::display() {
    switch (currentBzMode) {
    case MULURLR:
        setBezierMulurLR();
        break;
    case WOBBLE:
        setBezierWobble();
        break;
    case NORMAL:
        setBezierNormal();
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

void GridBezier::setBezierNormal() {
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

            // WOBBLE EFFECT: Random curve intensity untuk setiap garis!
            float curveFactor = ofRandom(0, 1.5);  // Random 0-1.5
            float curveAmount = cellSize * curveFactor;

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

            // WOBBLE EFFECT: Random curve intensity untuk setiap garis!
            float curveFactor = ofRandom(0, 1.5);  // Random 0-1.5
            float curveAmount = cellSize * curveFactor;

            ofDrawBezier(n1.x, n1.y, (n1.x + n2.x) / 2, n1.y + curveAmount,
                (n1.x + n2.x) / 2, n2.y - curveAmount, n2.x, n2.y);
        }
    }
}