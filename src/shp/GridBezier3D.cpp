#include "GridBezier3D.h"
#include "../clr/SolidColor.h"

GridBezier3D::GridBezier3D(float cellSize, float margin) {
	this->cellSize = cellSize;
	this->margin = margin;
	colorStrategy = std::make_unique<SolidColor>(ofColor(255));
	this->curveIntensity = ofRandom(0, 6);

	// 7 modes: VARYING3D, MULURLR3D, WOBBLE3D, WAVE3D, RADIALWAVE3D, HORIZONTALWAVE3D, VERTICALWAVE3D
	this->randomModeBezier = (int)ofRandom(0, 7);
	this->currentBzMode = static_cast<GridBezier3D::bezierMode3D>(randomModeBezier);

	//teset manual
	//this->currentBzMode = VERTICALWAVE3D;

	// 6 init directions: random pilih salah satu
	this->randomDir = (int)ofRandom(0, 6);
	this->currentInitDir = static_cast<GridBezier3D::initDirection>(randomDir);

	// Test manual
	//this->currentInitDir = RADIAL_OUT;

	this->zCoordinate = (int)ofRandom(0, 5);
	//int zCoordinate = 2;
	isPhyllotaxisActive = false;

	this->currentPhyllotaxisMode = PHYLLO_FLAT;
}

void GridBezier3D::setAnimationStr(std::unique_ptr<AnimationStrategy> animStrategy) {
	this->animStrategy = std::move(animStrategy);
}

void GridBezier3D::setColorStr(std::unique_ptr<ColorStrategy> colorStrategy) {
	this->colorStrategy = std::move(colorStrategy);
}

void GridBezier3D::initialize(int w, int h) {
	// Simpan width/height untuk re-initialize
	lastWidth = w;
	lastHeight = h;

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

	// Clear existing nodes
	nodes.clear();

	// Struct untuk node info (buat RADIAL_OUT dan RADIAL_IN)
	struct NodeInfo {
		int i, j;
		float x, y, z;
		float distance;
	};

	// Hitung semua nodes berdasarkan init direction
	switch (currentInitDir) {
		case TOP_LEFT:
			// Atas ke bawah, kiri ke kanan
			for (int j = 0; j <= maxRows; j++) {
				for (int i = 0; i <= maxCols; i++) {
					float x = offsetX + i * cellSize;
					float y = offsetY + j * cellSize;
					float z = calculateZ(i, j);
					nodes.push_back(std::make_unique<Node3D>(x, y, z));
				}
			}
			break;

		case TOP_RIGHT:
			// Atas ke bawah, kanan ke kiri
			for (int j = 0; j <= maxRows; j++) {
				for (int i = maxCols; i >= 0; i--) {
					float x = offsetX + i * cellSize;
					float y = offsetY + j * cellSize;
					float z = calculateZ(i, j);
					nodes.push_back(std::make_unique<Node3D>(x, y, z));
				}
			}
			break;

		case BOTTOM_LEFT:
			// Bawah ke atas, kiri ke kanan
			for (int j = maxRows; j >= 0; j--) {
				for (int i = 0; i <= maxCols; i++) {
					float x = offsetX + i * cellSize;
					float y = offsetY + j * cellSize;
					float z = calculateZ(i, j);
					nodes.push_back(std::make_unique<Node3D>(x, y, z));
				}
			}
			break;

		case BOTTOM_RIGHT:
			// Bawah ke atas, kanan ke kiri
			for (int j = maxRows; j >= 0; j--) {
				for (int i = maxCols; i >= 0; i--) {
					float x = offsetX + i * cellSize;
					float y = offsetY + j * cellSize;
					float z = calculateZ(i, j);
					nodes.push_back(std::make_unique<Node3D>(x, y, z));
				}
			}
			break;

		case RADIAL_OUT:
			{
				// Tengah ke luar (distance-based sorting)
				std::vector<NodeInfo> nodeInfos;
				float centerX = maxCols / 2.0f;
				float centerY = maxRows / 2.0f;

				// Hitung semua node positions dan distances
				for (int j = 0; j <= maxRows; j++) {
					for (int i = 0; i <= maxCols; i++) {
						float x = offsetX + i * cellSize;
						float y = offsetY + j * cellSize;
						float z = calculateZ(i, j);
						float dist = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
						nodeInfos.push_back({i, j, x, y, z, dist});
					}
				}

				// Sort by distance ascending (terdekat dulu)
				std::sort(nodeInfos.begin(), nodeInfos.end(),
					[](const NodeInfo& a, const NodeInfo& b) {
						return a.distance < b.distance;
					});

				// Push nodes in sorted order
				for (const auto& info : nodeInfos) {
					nodes.push_back(std::make_unique<Node3D>(info.x, info.y, info.z));
				}
			}
			break;

		case RADIAL_IN:
			{
				// Luar ke tengah (distance-based sorting, descending)
				std::vector<NodeInfo> nodeInfos;
				float centerX = maxCols / 2.0f;
				float centerY = maxRows / 2.0f;

				// Hitung semua node positions dan distances
				for (int j = 0; j <= maxRows; j++) {
					for (int i = 0; i <= maxCols; i++) {
						float x = offsetX + i * cellSize;
						float y = offsetY + j * cellSize;
						float z = calculateZ(i, j);
						float dist = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));
						nodeInfos.push_back({i, j, x, y, z, dist});
					}
				}

				// Sort by distance descending (terjauh dulu)
				std::sort(nodeInfos.begin(), nodeInfos.end(),
					[](const NodeInfo& a, const NodeInfo& b) {
						return a.distance > b.distance;
					});

				// Push nodes in sorted order
				for (const auto& info : nodeInfos) {
					nodes.push_back(std::make_unique<Node3D>(info.x, info.y, info.z));
				}
			}
			break;
	}

	totalNodes = nodes.size();
}

void GridBezier3D::updateAnimation() {
	if (animStrategy) {
		animStrategy->update();
		currentCols = animStrategy->getValue(targetCols);
		currentRows = animStrategy->getValue(targetRows);

		if (currentCols > maxCols) currentCols = maxCols;
		if (currentRows > maxRows) currentRows = maxRows;
	}

	// Re-initialize dengan random arah setelah RADIAL_OUT/RADIAL_IN selesai
	if ((currentInitDir == RADIAL_OUT || currentInitDir == RADIAL_IN) && isAnimationFinished() && !hasReinitialized) {
		// Clear nodes
		nodes.clear();

		// Random hanya 4 directional (TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT)
		randomDir = (int)ofRandom(0, 4);
		currentInitDir = static_cast<GridBezier3D::initDirection>(randomDir);

		// Re-initialize
		initialize(lastWidth, lastHeight);

		// Reset flag
		hasReinitialized = true;

		currentCols = maxCols;
		currentRows = maxRows;
	}
}

void GridBezier3D::display() {
	// Update animasi phyllotaxis untuk semua node
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->updatePhyllotaxisAnimation();
	}
	switch (currentBzMode) {
	case VARYING3D:
		setBezierVarying3D();
		break;
	case MULURLR3D:
		setBezierMulurLR3D();
		break;
	case WOBBLE3D:
		setBezierWobble3D();
		break;
	case WAVE3D:
		setBezierWave3D();
		break;
	case RADIALWAVE3D:
		setBezierRadialWave3D();
		break;
	case HORIZONTALWAVE3D:
		setBezierHorizontalWave3D();
		break;
	case VERTICALWAVE3D:
		setBezierVerticalWave3D();
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
	currentCols = 0;
	currentRows = 0;
	hasReinitialized = false;  // Reset flag untuk RADIAL_OUT
	if (animStrategy) {
		animStrategy->reset();
	}
}

// Helper function untuk menghitung Z position berdasarkan grid position
float GridBezier3D::calculateZ(int i, int j) {
	float centerX = maxCols / 2.0f;
	float centerY = maxRows / 2.0f;
	float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

	// Normalized distance
	float maxDist = sqrt(pow(centerX, 2) + pow(centerY, 2));
	float normalizedDist = distFromCenter / maxDist;

	// Z curve untuk efek 3D
	//test 
	switch (zCoordinate) {
	case 0:
		return sin(normalizedDist * PI / 2) * 200 - 100;
	case 1:
		return cos(normalizedDist * PI / 2) * 200 - 100;
	case 2:
		return sin(normalizedDist * TWO_PI) * 200 - 100;
	case 3 : 
		return cos(normalizedDist * TWO_PI) * 200 - 100;
	case 4:
		float tanVal = tan(normalizedDist * TWO_PI);
		if (tanVal > 2.0f) tanVal = 2.0f;  // Clamp max
		if (tanVal < -2.0f) tanVal = -2.0f;  // Clamp min
		return tanVal * 170 - 100;
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

void GridBezier3D::setBezierWobble3D() {
	// Gambar bezier vertikal dengan PERLIN NOISE di 3D space
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// WOBBLE 3D dengan PERLIN NOISE
			float time = ofGetFrameNum() * 0.02f;  // Kecepatan animasi noise

			// Hitung wobble untuk node1 (X, Y, Z)
			float noise1_x = ofNoise(time + n1.noiseOffset);
			float noise1_y = ofNoise(time + n1.noiseOffset + 100);
			float noise1_z = ofNoise(time + n1.noiseOffset + 200);
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

			// Pulse untuk animasi global
			float pulse = cos(ofGetFrameNum() * 0.05f);
			float combined = ((noise1_x + noise2_x) / 2.0f + pulse) / 2.0f;
			float lineWidth = ofMap(combined, 0, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Curve amount
			float curveAmount = cellSize * curveIntensity;

			// Posisi node dengan wobble 3D
			float x1 = n1.x + wobble1_x;
			float y1 = n1.y + wobble1_y;
			float z1 = n1.z + wobble1_z;

			float x2 = n2.x + wobble2_x;
			float y2 = n2.y + wobble2_y;
			float z2 = n2.z + wobble2_z;

			// Control points juga di-wobble
			float cp1_x = x1 + curveAmount + wobble1_x;
			float cp1_y = (y1 + y2) / 2;
			float cp1_z = z1 + 50 + wobble1_z;

			float cp2_x = x2 - curveAmount + wobble2_x;
			float cp2_y = (y1 + y2) / 2;
			float cp2_z = z2 - 50 + wobble2_z;

			// Draw bezier curve di 3D space dengan wobble
			ofDrawBezier(x1, y1, z1,
					   cp1_x, cp1_y, cp1_z,
					   cp2_x, cp2_y, cp2_z,
					   x2, y2, z2);
		}
	}

	// Gambar bezier horizontal dengan PERLIN NOISE
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// WOBBLE 3D dengan PERLIN NOISE
			float time = ofGetFrameNum() * 0.02f;

			// Hitung wobble untuk node1 (X, Y, Z)
			float noise1_x = ofNoise(time + n1.noiseOffset + 300);
			float noise1_y = ofNoise(time + n1.noiseOffset + 400);
			float noise1_z = ofNoise(time + n1.noiseOffset + 500);
			float wobble1_x = ofMap(noise1_x, 0, 1, -15, 15);
			float wobble1_y = ofMap(noise1_y, 0, 1, -15, 15);
			float wobble1_z = ofMap(noise1_z, 0, 1, -20, 20);

			// Hitung wobble untuk node2 (X, Y, Z)
			float noise2_x = ofNoise(time + n2.noiseOffset + 300);
			float noise2_y = ofNoise(time + n2.noiseOffset + 400);
			float noise2_z = ofNoise(time + n2.noiseOffset + 500);
			float wobble2_x = ofMap(noise2_x, 0, 1, -15, 15);
			float wobble2_y = ofMap(noise2_y, 0, 1, -15, 15);
			float wobble2_z = ofMap(noise2_z, 0, 1, -20, 20);

			// Pulse untuk line width
			float pulse = cos(ofGetFrameNum() * 0.05f);
			float combined = ((noise1_x + noise2_x) / 2.0f + pulse) / 2.0f;
			float lineWidth = ofMap(combined, 0, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			float curveAmount = cellSize * curveIntensity;

			// Posisi node dengan wobble 3D
			float x1 = n1.x + wobble1_x;
			float y1 = n1.y + wobble1_y;
			float z1 = n1.z + wobble1_z;

			float x2 = n2.x + wobble2_x;
			float y2 = n2.y + wobble2_y;
			float z2 = n2.z + wobble2_z;

			// Control points untuk horizontal
			float cp1_x = (x1 + x2) / 2;
			float cp1_y = y1 + curveAmount + wobble1_y;
			float cp1_z = z1 + 50 + wobble1_z;

			float cp2_x = (x1 + x2) / 2;
			float cp2_y = y2 - curveAmount + wobble2_y;
			float cp2_z = z2 - 50 + wobble2_z;

			// Draw bezier curve di 3D space dengan wobble
			ofDrawBezier(x1, y1, z1,
					   cp1_x, cp1_y, cp1_z,
					   cp2_x, cp2_y, cp2_z,
					   x2, y2, z2);
		}
	}
}

void GridBezier3D::setBezierWave3D() {
	// Parameter Wave 3D
	float waveAmplitude = 40;    // Tinggi gelombang (pixel)
	float waveFrequency = 0.4;   // Kerapatan gelombang
	float waveSpeed = 4;         // Kecepatan merambat
	float waveAmplitudeZ = 30;   // Amplitude khusus untuk Z-axis
	float time = ofGetFrameNum() * 0.03f;  // Time-based animation

	// Gambar bezier vertikal dengan WAVE 3D
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung WAVE DIAGONAL (sama untuk X, Y, Z)
			float wave = sin(i * waveFrequency + j * waveFrequency + time * waveSpeed);

			// Line width dynamic berdasarkan wave
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Wave offset untuk Z-axis (3D effect!)
			float waveZ = sin(i * waveFrequency * 0.7 + j * waveFrequency * 0.7 + time * waveSpeed);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan wave
			ofDrawBezier(n1.x, n1.y, z1,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, cp1_z,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, cp2_z,
					   n2.x, n2.y, z2);
		}
	}

	// Gambar bezier horizontal dengan WAVE 3D
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung WAVE DIAGONAL
			float wave = sin(i * waveFrequency + j * waveFrequency + time * waveSpeed);

			// Line width dynamic
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Wave offset untuk Z-axis (dengan phase shift)
			float waveZ = sin(i * waveFrequency * 0.7 + j * waveFrequency * 0.7 + time * waveSpeed + PI);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan wave
			ofDrawBezier(n1.x, n1.y, z1,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, cp1_z,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, cp2_z,
					   n2.x, n2.y, z2);
		}
	}
}

void GridBezier3D::setBezierRadialWave3D() {
	// Parameter Radial Wave 3D
	float waveAmplitude = 40;    // Tinggi gelombang (pixel)
	float waveFrequency = 0.4;   // Kerapatan gelombang
	float waveSpeed = 4;         // Kecepatan merambat
	float waveAmplitudeZ = 30;   // Amplitude khusus untuk Z-axis
	float time = ofGetFrameNum() * 0.03f;  // Time-based animation

	// Center grid untuk radial calculation
	float centerX = currentCols / 2.0f;
	float centerY = currentRows / 2.0f;

	// Gambar bezier vertikal dengan RADIAL WAVE 3D
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung jarak dari center untuk RADIAL WAVE
			float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

			// Radial wave: gelombang merambat dari tengah ke luar
			float wave = sin(distFromCenter * waveFrequency - time * waveSpeed);

			// Line width dynamic berdasarkan wave
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Radial wave untuk Z-axis (3D effect!)
			float waveZ = sin(distFromCenter * waveFrequency * 0.8 - time * waveSpeed);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan radial wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan radial wave
			ofDrawBezier(n1.x, n1.y, z1,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, cp1_z,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, cp2_z,
					   n2.x, n2.y, z2);
		}
	}

	// Gambar bezier horizontal dengan RADIAL WAVE 3D
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung jarak dari center untuk RADIAL WAVE
			float distFromCenter = sqrt(pow(i - centerX, 2) + pow(j - centerY, 2));

			// Radial wave: gelombang merambat dari tengah ke luar
			float wave = sin(distFromCenter * waveFrequency - time * waveSpeed);

			// Line width dynamic
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Radial wave untuk Z-axis (dengan phase shift)
			float waveZ = sin(distFromCenter * waveFrequency * 0.8 - time * waveSpeed + PI);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan radial wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan radial wave
			ofDrawBezier(n1.x, n1.y, z1,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, cp1_z,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, cp2_z,
					   n2.x, n2.y, z2);
		}
	}
}

void GridBezier3D::setBezierHorizontalWave3D() {
	// Parameter Horizontal Wave 3D
	float waveAmplitude = 40;    // Tinggi gelombang (pixel)
	float waveFrequency = 0.4;   // Kerapatan gelombang
	float waveSpeed = 3;         // Kecepatan merambat
	float waveAmplitudeZ = 30;   // Amplitude khusus untuk Z-axis
	float time = ofGetFrameNum() * 0.03f;  // Time-based animation

	// Gambar bezier vertikal dengan HORIZONTAL WAVE 3D
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung wave offset (HORIZONTAL WAVE - hanya berdasarkan kolom/i)
			float wave = sin(i * waveFrequency + time * waveSpeed);

			// Line width dynamic berdasarkan wave
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Horizontal wave untuk Z-axis (3D effect!)
			float waveZ = sin(i * waveFrequency * 0.7 + time * waveSpeed);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan horizontal wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan horizontal wave
			ofDrawBezier(n1.x, n1.y, z1,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, cp1_z,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, cp2_z,
					   n2.x, n2.y, z2);
		}
	}

	// Gambar bezier horizontal dengan HORIZONTAL WAVE 3D
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung wave offset (HORIZONTAL WAVE - hanya berdasarkan kolom/i)
			float wave = sin(i * waveFrequency + time * waveSpeed);

			// Line width dynamic
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Horizontal wave untuk Z-axis (dengan phase shift)
			float waveZ = sin(i * waveFrequency * 0.7 + time * waveSpeed + PI);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan horizontal wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan horizontal wave
			ofDrawBezier(n1.x, n1.y, z1,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, cp1_z,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, cp2_z,
					   n2.x, n2.y, z2);
		}
	}
}

void GridBezier3D::setBezierVerticalWave3D() {
	// Parameter Vertical Wave 3D
	float waveAmplitude = 40;    // Tinggi gelombang (pixel)
	float waveFrequency = 0.4;   // Kerapatan gelombang
	float waveSpeed = 3;         // Kecepatan merambat
	float waveAmplitudeZ = 30;   // Amplitude khusus untuk Z-axis
	float time = ofGetFrameNum() * 0.03f;  // Time-based animation

	// Gambar bezier vertikal dengan VERTICAL WAVE 3D
	for (int i = 0; i <= currentCols; i++) {
		for (int j = 0; j < currentRows; j++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = (j + 1) * (currentCols + 1) + i;

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			// Dapatkan warna
			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung wave offset (VERTICAL WAVE - hanya berdasarkan baris/j)
			float wave = sin(j * waveFrequency + time * waveSpeed);

			// Line width dynamic berdasarkan wave
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Vertical wave untuk Z-axis (3D effect!)
			float waveZ = sin(j * waveFrequency * 0.7 + time * waveSpeed);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan vertical wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan vertical wave
			ofDrawBezier(n1.x, n1.y, z1,
					   n1.x + curveAmount, (n1.y + n2.y) / 2, cp1_z,
					   n2.x - curveAmount, (n1.y + n2.y) / 2, cp2_z,
					   n2.x, n2.y, z2);
		}
	}

	// Gambar bezier horizontal dengan VERTICAL WAVE 3D
	for (int j = 0; j <= currentRows; j++) {
		for (int i = 0; i < currentCols; i++) {
			int node1 = j * (currentCols + 1) + i;
			int node2 = j * (currentCols + 1) + (i + 1);

			Node3D& n1 = *nodes[node1];
			Node3D& n2 = *nodes[node2];

			ofColor c = colorStrategy->getColor(i, j, currentCols, currentRows);
			ofSetColor(c);
			ofNoFill();

			// Hitung wave offset (VERTICAL WAVE - hanya berdasarkan baris/j)
			float wave = sin(j * waveFrequency + time * waveSpeed);

			// Line width dynamic
			float lineWidth = ofMap(wave, -1, 1, 3, 7);
			ofSetLineWidth(lineWidth);

			// Wave offset untuk curve amount
			float waveOffset = wave * waveAmplitude;
			float baseCurve = cellSize * curveIntensity;
			float curveAmount = baseCurve + waveOffset;

			// Vertical wave untuk Z-axis (dengan phase shift)
			float waveZ = sin(j * waveFrequency * 0.7 + time * waveSpeed + PI);
			float waveZOffset = waveZ * waveAmplitudeZ;

			// Posisi Z dengan vertical wave effect
			float z1 = n1.z + waveZOffset;
			float z2 = n2.z + waveZOffset;

			// Control points dengan wave di Z
			float cp1_z = z1 + 50 + waveZOffset;
			float cp2_z = z2 - 50 + waveZOffset;

			// Draw bezier curve di 3D space dengan vertical wave
			ofDrawBezier(n1.x, n1.y, z1,
					   (n1.x + n2.x) / 2, n1.y + curveAmount, cp1_z,
					   (n1.x + n2.x) / 2, n2.y - curveAmount, cp2_z,
					   n2.x, n2.y, z2);
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

void GridBezier3D::enablePhyllotaxis() {
	if (isPhyllotaxisActive) return;
	isPhyllotaxisActive = true;

	// RANDOM pilih mode phyllotaxis: 0 = FLAT, 1 = SPHERE
	/*int randomMode = (int)ofRandom(0, 2);
	currentPhyllotaxisMode = static_cast<PhyllotaxisMode>(randomMode);*/

	//test manual
	currentPhyllotaxisMode = PHYLLO_SPHERE;

	// Print ke console untuk debug (opsional, bisa dihapus nanti)
	if (currentPhyllotaxisMode == PHYLLO_FLAT) {
		enablePhyllotaxisFlat();
	}
	else if (currentPhyllotaxisMode == PHYLLO_SPHERE) {
		enablePhyllotaxisSphere();
	}
}

void GridBezier3D::disablePhyllotaxis() {
	if (!isPhyllotaxisActive) return;
	isPhyllotaxisActive = false;

	// Kembalikan semua node ke posisi grid ASLI
	for (int i = 0; i < nodes.size(); i++) {
		nodes[i]->startPhyllotaxisAnimation(
			nodes[i]->originalGridX,  // ← Posisi grid asli
			nodes[i]->originalGridY,
			nodes[i]->originalGridZ   // ← Z juga kembali ke asli
		);
	}
}

void GridBezier3D::togglePhyllotaxis() {
	if (isPhyllotaxisActive) {
		disablePhyllotaxis();
	}
	else {
		enablePhyllotaxis();
	}
}

void GridBezier3D::enablePhyllotaxisFlat() {
	// Golden angle untuk phyllotaxis
	float goldenAngle = ofDegToRad(137.5f);

	// Center screen
	float centerX = ofGetWidth() / 2.0f;
	float centerY = ofGetHeight() / 2.0f;
	float centerZ = 0.0f;  // Center di Z-axis

	// Untuk setiap node, hitung posisi phyllotaxis
	for (int i = 0; i < nodes.size(); i++) {
		// Hitung posisi phyllotaxis untuk X dan Y
		float angle = i * goldenAngle;
		float radius = cellSize * 0.35f * sqrt(i);  // Spacing

		float phylloX = centerX + radius * cos(angle);
		float phylloY = centerY + radius * sin(angle);

		// Z tetap pakai posisi EXISTING dari grid 3D
		float phylloZ = nodes[i]->z;  // ← PENTING! Z dari existing

		// Cek bounds (hanya X dan Y, Z bebas)
		bool isValid = (phylloX >= 0 && phylloX <= ofGetWidth() &&
			phylloY >= 0 && phylloY <= ofGetHeight());

		if (isValid) {
			// Mulai animasi 3D
			nodes[i]->startPhyllotaxisAnimation(phylloX, phylloY, phylloZ);
		}
	}
}

void GridBezier3D::enablePhyllotaxisSphere() {
	// Fibonacci Sphere Algorithm untuk distribute nodes di permukaan bola
	float goldenAngle = TWO_PI * (3.0f - sqrt(5.0f));  // ~2.399 radian
	float offset = 2.0f / nodes.size();

	// Sphere size (bisa adjust)
	float sphereRadius = cellSize * 6.0f;  // Radius bola

	// Center screen
	float centerX = ofGetWidth() / 2.0f;
	float centerY = ofGetHeight() / 2.0f;
	float centerZ = 0.0f;  // Center di Z-axis

	// Untuk setiap node, hitung posisi di sphere
	for (int i = 0; i < nodes.size(); i++) {
		// Fibonacci sphere algorithm
		float y = ((i * offset) - 1) + (offset / 2);  // -1 to 1
		float radius = sqrt(1.0f - pow(y, 2));      // Radius di height y

		float phi = ((i + 1) % (int)nodes.size()) * goldenAngle;  // Golden angle spiral

		// Convert spherical to cartesian
		float x = radius * cos(phi);
		float z = radius * sin(phi);

		// Scale ke ukuran sphere
		float phylloX = centerX + x * sphereRadius;
		float phylloY = centerY + y * sphereRadius;
		float phylloZ = centerZ + z * sphereRadius;

		// Start animasi 3D (tanpa bounds check, karena sphere bebas di 3D)
		nodes[i]->startPhyllotaxisAnimation(phylloX, phylloY, phylloZ);
	}
}

bool GridBezier3D::getIsPhyllotaxisActive() {
	return isPhyllotaxisActive;
}

GridBezier3D::PhyllotaxisMode GridBezier3D::getCurrentPhyllotaxisMode() {
	return currentPhyllotaxisMode;
}
