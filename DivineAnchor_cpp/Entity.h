#pragma once
#include "Globals.h"

class Entity {
protected:
	Sprite sprite;
	Texture texture;

public:
	void Render(RenderTarget& target) {
		target.draw(this->sprite);
	}
};