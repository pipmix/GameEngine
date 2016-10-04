#pragma once



class Background {


public:
	Background();
	void Create();

private:
	int width;
	int height;
	bool RepeatX;
	bool RepeatY;
	float posX;
	float posY;
	float xSpeed;
	float ySpeed;
	float zDepth;

	int borderX;
	int borderY;
};