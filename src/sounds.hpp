/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
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
