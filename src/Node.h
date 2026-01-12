#pragma once
class Node
{
public:
	float x, y;
	float startX, startY;
	float originalGridX, originalGridY;
	float targetX, targetY;
	float noiseOffset;
	//Animation
	bool isAnimating;
	float animProgress;
	float animSpeed;
	Node(float startX, float startY);
	void startPhyllotaxisAnimation(float targetX, float targetY);
	void updatePhyllotaxisAnimation();
};

