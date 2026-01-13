#pragma once
#include "../strategy/Shape.h"
#include "../Node.h"
class GridBezier : public Shape
{
public:
	std::vector<std::unique_ptr<Node>> nodes;
	int cols, rows, maxCols, maxRows, targetCols, targetRows;
	float cellSize, margin;
	float offsetX, offsetY;
	int totalNodes;
	std::unique_ptr<AnimationStrategy> animStrategy;
	std::unique_ptr<ColorStrategy> colorStrategy;
	int currentCols, currentRows;
	enum bezierMode { VARYING,MULURLR, WOBBLE,WAVE, RADIALWAVE,HORIZONTALWAVE,VERTICALWAVE};
	bezierMode currentBzMode = MULURLR;
	GridBezier(float cellSize, float margin); //constructor
	void setAnimationStr(std::unique_ptr<AnimationStrategy> strategy) override;
	void setColorStr(std::unique_ptr<ColorStrategy> strategy) override;
	void initialize(int w, int h);
	void updateAnimation() override;
	void display() override;
	bool isAnimationFinished() override;
	void resetAnimation() override;
	int getTargetCols();
	int getTargetRows();
	int getCurrentCols();
	int getCurrentRows();
	int getTotalNodes();
	void enablePhyllotaxis();
	void disablePhyllotaxis();
	void togglePhyllotaxis();
	
private:
	int randomModeBezier;
	float curveIntensity = 0;
	enum initDirection { TOP_LEFT, TOP_RIGHT, BOTTOM_LEFT, BOTTOM_RIGHT, RADIAL_OUT, RADIAL_IN};
	initDirection currentInitDir;
	int randomDir;
	bool hasReinitialized = false;
	int lastWidth, lastHeight;  // Simpan width/height untuk re-initialize
	bool isPhyllotaxisActive; //phyllotaxis
	float phyllotaxisRotationAngle;      // Sudut rotasi phyllotaxis 2D
	bool isPhyllotaxisRotating;          // Flag untuk mengaktifkan rotasi
	void setBezierMulurLR();
	void setBezierVarying();
	void setBezierWobble();
	void setBezierWave();
	void setBezierRadialWave();
	void setBezierHorizontalWave();
	void setBezierVerticalWave();
};

