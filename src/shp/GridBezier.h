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
	enum bezierMode { VARYING,MULURLR, WOBBLE,WAVE, RADIALWAVE};
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
private:
	int randomModeBezier;
	float curveIntensity = 0;
	void setBezierMulurLR();
	void setBezierVarying();
	void setBezierWobble();
	void setBezierWave();
	void setBezierRadialWave();
};

