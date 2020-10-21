
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
//Implementation


#include "audio.h"


//Audio Initialising
bool audio::audioInit()
{
	if (FMOD::System_Create(&AudioSystem) != FMOD_OK)
	{
		return false;
	}

	if (AudioSystem->init(100, FMOD_INIT_NORMAL | FMOD_INIT_3D_RIGHTHANDED, 0) !=FMOD_OK)
	{
		return false;
	}

	return true;
}


//Adding new music to the array
void audio::create(std::string audio)
{
	FMOD::Sound* temp;
	std::string path = "Resources/Audio/";
	path.append(audio);
	AudioSystem->createSound(path.c_str(), FMOD_DEFAULT, 0, &temp);
	temp->setLoopCount(-1);
	sounds.insert(std::pair<std::string, FMOD::Sound*>(audio, temp));
}

//Play given music from the array
void audio::play(std::string audio)
{
	for (auto& itr : sounds)
	{
		if (itr.first == audio)
		{
			itr.second->setLoopCount(1);
			AudioSystem->playSound(itr.second, 0, false, 0);
		}
		
	}
}

//play background music
void audio::bgPlay()
{
	if (sounds.size() >= 1)
	{
	
		AudioSystem->playSound(sounds.begin()->second, 0, false, &bgChannel);

	}
}
