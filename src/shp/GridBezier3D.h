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

	enum bezierMode3D { VARYING3D, MULURLR3D };
	bezierMode3D currentBzMode = VARYING3D;

	GridBezier3D(float cellSize, float margin);
	void setAnimationStr(std::unique_ptr<AnimationStrategy> strategy) override;
	void setColorStr(std::unique_ptr<ColorStrategy> strategy) override;
	void initialize(int w, int h);
	void updateAnimation() override;
	void display() override;
	bool isAnimationFinished() override;
	void resetAnimation() override;

private:
	float curveIntensity = 0;
	int randomModeBezier;
	void setBezierVarying3D();
	void setBezierMulurLR3D();
};
