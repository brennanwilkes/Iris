/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "sounds.hpp"

void Sounds::setup(string mydir){
	
	AM = AudioManager::create_AudioManager();
	akFireSound = AM->get_sound(mydir+"Assets/Sounds/akFire.wav");
	akFireSound->set_volume(0.25);
	akEmptySound = AM->get_sound(mydir+"Assets/Sounds/akEmpty.wav");
	akEmptySound->set_volume(0.75);
	akReloadSound = AM->get_sound(mydir+"Assets/Sounds/akReload.wav");
	akReloadSound->set_volume(0.75);
	
	
	
	pistolFireSound = AM->get_sound(mydir+"Assets/Sounds/pistolFire.wav");
	pistolFireSound->set_volume(0.25);
	pistolEmptySound = akEmptySound;
	pistolEmptySound->set_volume(0.75);
	pistolReloadSound = akReloadSound;
	pistolReloadSound->set_volume(0.75);
	
	batFireSound = AM->get_sound(mydir+"Assets/Sounds/batFire.wav");
	batFireSound->set_volume(0.5);
	
	
	ricochetSound1 = AM->get_sound(mydir+"Assets/Sounds/ricochet-1.wav");
	ricochetSound1->set_volume(0.25);
	ricochetSound2 = AM->get_sound(mydir+"Assets/Sounds/ricochet-2.wav");
	ricochetSound2->set_volume(0.25);
	ricochetSound3 = AM->get_sound(mydir+"Assets/Sounds/ricochet-3.wav");
	ricochetSound3->set_volume(0.25);
	ricochetSound4 = AM->get_sound(mydir+"Assets/Sounds/ricochet-4.wav");
	ricochetSound4->set_volume(0.25);
	ricochetSound5 = AM->get_sound(mydir+"Assets/Sounds/ricochet-5.wav");
	ricochetSound5->set_volume(0.25);
	ricochetSound6 = AM->get_sound(mydir+"Assets/Sounds/ricochet-6.wav");
	ricochetSound6->set_volume(0.25);
	
	walkSound1 = AM->get_sound(mydir+"Assets/Sounds/walk1.wav");
	walkSound1->set_volume(1.0);
	walkSound2 = AM->get_sound(mydir+"Assets/Sounds/walk2.wav");
	walkSound2->set_volume(1.0);
	walkSound3 = AM->get_sound(mydir+"Assets/Sounds/walk3.wav");
	walkSound3->set_volume(1.0);
	walkSound4 = AM->get_sound(mydir+"Assets/Sounds/walk4.wav");
	walkSound4->set_volume(1.0);
	walkSound5 = AM->get_sound(mydir+"Assets/Sounds/walk5.wav");
	walkSound5->set_volume(1.0);
	walkSound6 = AM->get_sound(mydir+"Assets/Sounds/walk6.wav");
	walkSound6->set_volume(1.0);
	
	bulletHitSound1 = AM->get_sound(mydir+"Assets/Sounds/bulletHit.wav");
	bulletHitSound1->set_volume(1.0);
	bulletHitSound2 = AM->get_sound(mydir+"Assets/Sounds/bulletHit2.wav");
	bulletHitSound2->set_volume(1.0);
	
	bulletCasingFallSound = AM->get_sound(mydir+"Assets/Sounds/BulletCasingFall.wav");
	bulletCasingFallSound->set_volume(1.0);
	
	femaleGrunt1 = AM->get_sound(mydir+"Assets/Sounds/female-grunt1.wav");
	femaleGrunt1->set_volume(1.0);
	femaleGrunt2 = AM->get_sound(mydir+"Assets/Sounds/female-grunt2.wav");
	femaleGrunt2->set_volume(1.0);
	femaleGrunt3 = AM->get_sound(mydir+"Assets/Sounds/female-grunt3.wav");
	femaleGrunt3->set_volume(1.0);
	femaleGrunt4 = AM->get_sound(mydir+"Assets/Sounds/female-grunt4.wav");
	femaleGrunt4->set_volume(1.0);
	femaleGrunt5 = AM->get_sound(mydir+"Assets/Sounds/female-grunt5.wav");
	femaleGrunt5->set_volume(1.0);
	femaleGrunt6 = AM->get_sound(mydir+"Assets/Sounds/female-grunt6.wav");
	femaleGrunt6->set_volume(1.0);
	femaleGrunt7 = AM->get_sound(mydir+"Assets/Sounds/female-grunt7.wav");
	femaleGrunt7->set_volume(1.0);
	
	
	scream1 = AM->get_sound(mydir+"Assets/Sounds/scream1.wav");
	scream1->set_volume(1.0);
	scream2 = AM->get_sound(mydir+"Assets/Sounds/scream2.wav");
	scream2->set_volume(1.0);
	scream3 = AM->get_sound(mydir+"Assets/Sounds/scream3.wav");
	scream3->set_volume(1.0);
	scream4 = AM->get_sound(mydir+"Assets/Sounds/scream4.wav");
	scream4->set_volume(1.0);
	
	
	glass = AM->get_sound(mydir+"Assets/Sounds/glass.wav");
	glass->set_volume(1.0);
	
	heyShout = AM->get_sound(mydir+"Assets/Sounds/heyShout.wav");
	heyShout->set_volume(1.0);
	
	hiss = AM->get_sound(mydir+"Assets/Sounds/hiss.wav");
	hiss->set_volume(1.0);
	
	impact = AM->get_sound(mydir+"Assets/Sounds/impact.wav");
	impact->set_volume(1.0);
	
	Snarl = AM->get_sound(mydir+"Assets/Sounds/Snarl.wav");
	Snarl->set_volume(1.0);
	Snarl2 = AM->get_sound(mydir+"Assets/Sounds/Snarl2.wav");
	Snarl2->set_volume(1.0);
	
	walkSand = AM->get_sound(mydir+"Assets/Sounds/walk-sand.wav");
	walkSand->set_volume(1.0);
	
	wood1 = AM->get_sound(mydir+"Assets/Sounds/wood1.wav");
	wood1->set_volume(1.0);
	wood2 = AM->get_sound(mydir+"Assets/Sounds/wood2.wav");
	wood2->set_volume(1.0);
	
	background1 = AM->get_sound(mydir+"Assets/Sounds/background1.wav");
	background1->set_volume(0.25);
	
	
	
}
