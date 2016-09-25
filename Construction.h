#pragma once



class Construction {


public:



private:


	void JumpCommand();
	void ClimbCommand();


	bool isAlive;
	bool onGround;



	bool isSingleJumping;
	bool isDoubleJumping;
	bool falling;
	bool takingDamage;
	bool firing;
	bool swinging;


};