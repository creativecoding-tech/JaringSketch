#pragma once
#include "../strategy/Shape.h"
#include "../Node3D.h"
#include "../strategy/AnimationStrategy.h"
#include "../strategy/ColorStrategy.h"

class GridBezier3D : public Shape
{
public:
	std::vector<std::unique_ptr<Node3D>> nodes;
	int cols, rows, maxCols, maxRows;
	int currentCols, currentRows;  // Untuk animasi growing
	int targetCols, targetRows;     // Target akhir animasi
	float cellSize, margin;
	float offsetX, offsetY, offsetZ;  // offsetZ untuk centering di z-axis
	int totalNodes;
	std::unique_ptr<AnimationStrategy> animStrategy;
	std::unique_ptr<ColorStrategy> colorStrategy;

	enum bezierMode3D { VARYING3D, MULURLR3D, WOBBLE3D, WAVE3D, RADIALWAVE3D, HORIZONTALWAVE3D, VERTICALWAVE3D };
	bezierMode3D currentBzMode = VARYING3D;

	// Init direction untuk growing animation
	enum initDirection { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, RADIAL_OUT, RADIAL_IN };
	initDirection currentInitDir;
	int randomDir;
	bool hasReinitialized = false;
	int lastWidth, lastHeight;  // Simpan width/height untuk re-initialize

	// Phyllotaxis mode enum
	enum PhyllotaxisMode {
		PHYLLO_FLAT,   // Opsi 1: Flat phyllotaxis (X, Y dari phyllotaxis, Z dari existing)
		PHYLLO_SPHERE  // Opsi 3: Sphere phyllotaxis (X, Y, Z dari spherical mapping)
	};
	PhyllotaxisMode currentPhyllotaxisMode;  // Track mode saat ini

	GridBezier3D(float cellSize, float margin);
	void setAnimationStr(std::unique_ptr<AnimationStrategy> strategy) override;
	void setColorStr(std::unique_ptr<ColorStrategy> strategy) override;
	void initialize(int w, int h);
	void updateAnimation() override;
	void display() override;
	bool isAnimationFinished() override;
	void resetAnimation() override;
	// Phyllotaxis methods
	void enablePhyllotaxis();
	void disablePhyllotaxis();
	void togglePhyllotaxis();

	bool getIsPhyllotaxisActive();
	PhyllotaxisMode getCurrentPhyllotaxisMode();

private:
	float curveIntensity = 0;
	int randomModeBezier;
	int zCoordinate;
	bool isPhyllotaxisActive;
	void enablePhyllotaxisFlat();
	void  enablePhyllotaxisSphere();
	float calculateZ(int i, int j);  // Helper untuk menghitung Z position
	void setBezierVarying3D();
	void setBezierMulurLR3D();
	void setBezierWobble3D();
	void setBezierWave3D();
	void setBezierRadialWave3D();
	void setBezierHorizontalWave3D();
	void setBezierVerticalWave3D();
};
