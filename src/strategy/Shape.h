#pragma once
#include "AnimationStrategy.h"
#include "ColorStrategy.h"
class Shape {
public:
	//wajib override semua method
//jika sebuah kelas mewarisi class ini
	virtual ~Shape() = default; //destructor
	virtual void setAnimationStr(std::unique_ptr<AnimationStrategy> strategy) = 0;
	virtual void setColorStr(std::unique_ptr<ColorStrategy> strategy) = 0;
	virtual void updateAnimation() = 0;
	virtual void display() = 0;
	virtual bool isAnimationFinished() = 0;
	virtual void resetAnimation() = 0;
};