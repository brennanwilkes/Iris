#ifndef SOUNDS_H
#define SOUNDS_H

#include "nodePath.h"
#include "audioManager.h"
#include <string>

class Sounds{
public:
	
	PT(AudioManager) AM;
	
	
	
	PT(AudioSound) pistolFireSound;
	PT(AudioSound) pistolReloadSound;
	PT(AudioSound) pistolEmptySound;
	
	PT(AudioSound) batFireSound;
	
	PT(AudioSound) akFireSound;
	PT(AudioSound) akReloadSound;
	PT(AudioSound) akEmptySound;
	
	PT(AudioSound) ricochetSound1;
	PT(AudioSound) ricochetSound2;
	PT(AudioSound) ricochetSound3;
	PT(AudioSound) ricochetSound4;
	PT(AudioSound) ricochetSound5;
	PT(AudioSound) ricochetSound6;
	
	PT(AudioSound) bulletHitSound1;
	PT(AudioSound) bulletHitSound2;
	
	PT(AudioSound) bulletCasingFallSound;
	
	PT(AudioSound) femaleGrunt1;
	PT(AudioSound) femaleGrunt2;
	PT(AudioSound) femaleGrunt3;
	PT(AudioSound) femaleGrunt4;
	PT(AudioSound) femaleGrunt5;
	PT(AudioSound) femaleGrunt6;
	PT(AudioSound) femaleGrunt7;
	
	PT(AudioSound) scream1;
	PT(AudioSound) scream2;
	PT(AudioSound) scream3;
	PT(AudioSound) scream4;
	
	PT(AudioSound) glass;
	
	PT(AudioSound) heyShout;
	
	PT(AudioSound) hiss;
	
	PT(AudioSound) impact;
	
	PT(AudioSound) Snarl;
	PT(AudioSound) Snarl2;
	
	PT(AudioSound) walkSand;
	
	PT(AudioSound) wood1;
	PT(AudioSound) wood2;
	
	
	
	PT(AudioSound) walkSound1;
	PT(AudioSound) walkSound2;
	PT(AudioSound) walkSound3;
	PT(AudioSound) walkSound4;
	PT(AudioSound) walkSound5;
	PT(AudioSound) walkSound6;
	
	
	PT(AudioSound) background1;
	
	
	void setup(string mydir);
	
private:

};

#endif
