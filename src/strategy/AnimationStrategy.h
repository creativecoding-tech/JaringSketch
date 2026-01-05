#pragma once
class AnimationStrategy {
public:
	//wajib override semua method
	//jika sebuah kelas mewarisi class ini
	virtual void update() = 0;
	virtual int getValue(int target) = 0;
	virtual bool isFinished() = 0;
	virtual void reset() = 0;
	virtual ~AnimationStrategy() = default; //destructor
};