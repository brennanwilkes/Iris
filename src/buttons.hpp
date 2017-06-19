/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#ifndef BUTTONS_H
#define BUTTONS_H

#include "nodePath.h"
#include "pgButton.h"
#include "pgSliderBar.h"
#include <animControlCollection.h>


class Buttons{
public:
	Buttons();
	float xs;
	NodePath defbutNP;
	//Menu
	PT(PGButton) QuitButton;
	PGButton* HitTogButton;
	PGButton* DoubleTogButton;
	PGButton* OptionTogButton;
	PGButton* SaveButton;
	//Start
	PGButton* StartGameButton;
	PGButton* loadGameButton;
	PGButton* realQuitButton;
	PGButton* OptionTogButton3;
	NodePath nd_hellothere, loadnode2;
	AnimControlCollection start_anim_collection;
	PT(AnimControl) animPtrLoad2;
	//Option
	PGButton* OptionTogButton2;
	PGButton* mouseSensBut;
	PT(PGSliderBar) mouseSlider;
	//Death
	PGButton* respawnButton;
	PGButton* restartButton;
	PT(TextNode) deathNode;
	NodePath deathMessage;
	//Load
	PGButton* MainMenuReturnButton;
};

#endif
