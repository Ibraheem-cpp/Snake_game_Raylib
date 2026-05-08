#pragma once

#include <iostream>
#include <string>
#include "raylib.h"

using namespace std;

class Button {
private:
	float Px = 0;
	float Py = 0;
	float length = 0;
	float width = 0;
	string label = "Button";

	bool isMouseOver() const {
		int Mx = GetMouseX();
		int My = GetMouseY();
		if ((Mx >= this->Px && Mx <= this->Px + this->length) && (My >= this->Py && My <= this->Py + this->width)) {
			return true;
		}
		return false;
	}

public:
	Button() {}
	Button(float Px, float Py, string label, float heightOffset, float widthOffset) {
		this->label = label;
		this->length = 200;
		this->width = 100;
		this->Px = Px - (this->length / 2) + widthOffset;
		this->Py = Py - (this->width/ 2) + heightOffset;
	}

	void Draw() const {
		DrawRectangleRounded({ this->Px, this->Py, this->length, this->width }, 0.5, 5, BLACK);
		int textSize = 50;
		int textWidth = MeasureText(this->label.c_str(), textSize);
		int posX = this->Px + this->length / 2 - textWidth / 2.0;
		int posY = this->Py + this->width / 2 - textSize / 2.0;
		DrawText(this->label.c_str(), posX, posY, textSize, WHITE);
	}

	void isHovering() const {
		if (isMouseOver()) {
			DrawRectangleRounded({ this->Px, this->Py, this->length, this->width }, 0.5, 5, RED);
			int textSize = 50;
			int textWidth = MeasureText(this->label.c_str(), textSize);
			int posX = this->Px + this->length / 2 - textWidth / 2.0;
			int posY = this->Py + this->width / 2 - textSize / 2.0;
			DrawText(this->label.c_str(), posX, posY, textSize, WHITE);
		}
	}

	bool isClicked() const {
		if (isMouseOver() && (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))) {
			return true;
		}
		return false;
	}

};