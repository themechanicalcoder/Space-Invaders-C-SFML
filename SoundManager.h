#pragma once

#include <iostream>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
using namespace std;

class SoundManager
{
public:
	SoundManager();
	void playBackgroundMusic();
	void pauseBackgroundMusic();
	void playLazer();
	void playExplosion();
	void playReward();
private:
	sf::SoundBuffer lazerBuffer;
	sf::SoundBuffer explosionBuffer;
	sf::SoundBuffer rewardBuffer;
	sf::Music music;
	sf::Sound lazerSound;
	sf::Sound explosionSound;
	sf::Sound rewardSound;
};


