#include "GridBezier3D.h"
#include "../clr/SolidColor.h"

GridBezier3D::GridBezier3D(float cellSize, float margin) {
	this->cellSize = cellSize;
	this->margin = margin;
	colorStrategy = std::make_unique<SolidColor>(ofColor(255));
	this->curveIntensity = ofRandom(0, 6);

	// 2 modes: VARYING3D, MULURLR3D
	/*this->randomModeBezier = (int)ofRandom(0, 2);
	this->currentBzMode = static_cast<GridBezier3D::bezierMode3D>(randomModeBezier);*/

	this->currentBzMode = MULURLR3D;
}

void GridBezier3D::setAnimationStr(std::unique_ptr<AnimationStrategy> animStrategy) {
	this->animStrategy = std::move(animStrategy);
}

void GridBezier3D::setColorStr(std::unique_ptr<ColorStrategy> colorStrategy) {
	this->colorStrategy = std::move(colorStrategy);
}

void GridBezier3D::initialize(int w, int h) {
	// Hitung area yang bisa digunakan
	float usableWidth = w - margin * 2;
	maxCols = (int)(usableWidth / cellSize);
	float usableHeight = h - margin * 2;
	maxRows = (int)(usableHeight / cellSize);

	offsetX = margin + (usableWidth - maxCols * cellSize) / 2.0;
	offsetY = margin + (usableHeight - maxRows * cellSize) / 2.0;
	offsetZ = 0;  // Center di z-axis

	// Set target untuk animasi
	targetCols = maxCols;
	targetRows = maxRows;
	currentCols = 0;
	currentRows = 0;

	// Allocate node array
	totalNodes = (maxCols + 1) * (maxRows + 1);

	// Inisialisasi semua node dengan 3D position
	for (int j = 0; j <= maxRows; j++) {
		for (int i = 0; i <= maxCols; i++) {
			float startX = offsetX + i * cellSize;
			float startY = offsetY + j * cellSize;

			// Hitung z position berdasarkan distance dari center untuk efek 3D
			float centerX = maxCols / 2.0f;
			float centerY = maxRows / 2.0f;
			float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

			// Z variation: gelombang 3D dari center
			float maxDist = sqrt(pow(centerX, 2) + pow(centerY, 2));
			float normalizedDist = distFromCenter / maxDist;  // 0.0 - 1.0

			// Z position: SINUSOIDAL CURVE - melengkung halus dari center ke edge
			float startZ = sin(normalizedDist * PI / 2) * 200 - 100;

			nodes.push_back(std::make_unique<Node3D>(startX, startY, startZ));
		}
	}
}

void GridBezier3D::updateAnimation() {
	if (animStrategy) {
		animStrategy->update();
		currentCols = animStrategy->getValue(targetCols);
		currentRows = animStrategy->getValue(targetRows);

		if (currentCols > maxCols) currentCols = maxCols;
		if (currentRows > maxRows) currentRows = maxRows;
	}
}

void GridBezier3D::display() {
	switch (currentBzMode) {
	case VARYING3D:
		setBezierVarying3D();
		break;
	case MULURLR3D:
		setBezierMulurLR3D();
		break;
	}
}

bool GridBezier3D::isAnimationFinished() {
	if (animStrategy) {
		return animStrategy->isFinished();
	}
	return true;
}

void GridBezier3D::resetAnimation() {
	if (animStrategy) {
		animStrategy->reset();
		currentCols = 0;
		currentRows = 0;
	}
}

void GridBezier3D::setBezierMulurLR3D() {
	// Gambar bezier vertikal (setiap kolom) di 3D space
	// INDEXING DENGAN currentCols/currentRows (dinamis sesuai animasi growing)
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna dari color strategy dengan ukuran DINAMIS
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			float curveAmount = cellSize * curveIntensity;

			// Draw bezier curve di 3D space
			ofDrawBezier(n1.x, n1.y, n1.z,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, n1.z + 50,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, n2.z - 50,
					   n2.x, n2.y, n2.z);
		}
	}

	// Gambar bezier horizontal (setiap baris) di 3D space
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Color dengan ukuran DINAMIS
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			float curveAmount = cellSize * curveIntensity;

			// Draw bezier curve di 3D space
			ofDrawBezier(n1.x, n1.y, n1.z,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, n1.z + 50,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, n2.z - 50,
					   n2.x, n2.y, n2.z);
		}
	}
}

void GridBezier3D::setBezierVarying3D() {
	// Gambar bezier vertikal (setiap kolom) di 3D space
	// Hanya render sampai currentCols dan currentRows untuk animasi growing
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (maxCols + 1) + i;
			int node2 = (j + 1) * (maxCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna dari color strategy
			ofColor c = colorStrategy->getColor(i, j, maxCols, maxRows);
			ofSetColor(c);
			ofNoFill();

			float curveAmount = cellSize * curveIntensity;

			// Draw bezier curve di 3D space
			ofDrawBezier(n1.x, n1.y, n1.z,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, n1.z + 50,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, n2.z - 50,
					   n2.x, n2.y, n2.z);
		}
	}

	// Gambar bezier horizontal (setiap baris) di 3D space
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (maxCols + 1) + i;
			int node2 = j * (maxCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, maxCols, maxRows);
			ofSetColor(c);
			ofNoFill();

			float curveAmount = cellSize * curveIntensity;

			// Draw bezier curve di 3D space
			ofDrawBezier(n1.x, n1.y, n1.z,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, n1.z + 50,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, n2.z - 50,
					   n2.x, n2.y, n2.z);
		}
	}
}
