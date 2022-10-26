#pragma once
#include "object.h"
#include "renderer.h"

class Roller :public Object
{

private:

public:
	Roller() {}
	~Roller( ) {}

	void Update(void) override;

	//void Draw(void) override {
	//	//SetBlendState(BLEND_MODE_NONE);
	//};


};
