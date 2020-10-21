
//
// Bachelor of Software Engineering
// Media Design School
// Auckland
// New Zealand
//
// (c) 2019 Media Design School
//
// File Name 	: audio.h
// Description	: audio using FMOD
// Author 		: Himanshu Chawla
// Mail 		: Himanshu.Cha8420
//
//Local Includes


#pragma once

#include<fmod.hpp>
#include<vector>
#include<string>
#include<map>
class audio
{
private:
	FMOD::System* AudioSystem;
	std::map<std::string, FMOD::Sound*> sounds;

public:
	FMOD::Channel* bgChannel;

	bool audioInit();
	void create(std::string audio);
	void play(std::string audio);
	void bgPlay();
	void update()
	{
		AudioSystem->update();
	}
	

};

