/*
Copyright <2017> <Romar Lamanilao, Ryan Carrusca, Brennan Wilkes, and Michael Liu>

Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:

1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.

2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.

THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/
#include "weapon.hpp"

WeaponObject::WeaponObject(char t,int xx,int yy,int zz,float wei,float vol, std::string fn,NodePath* parent,WindowFramework* w,PandaFramework* pf,float scale,int zzz,int xxx,int yyy,float rad,int zzzz,std::string fn2,float am,int idd):Item(t,xx,yy,zz,wei,vol, fn,parent,w,pf,scale,zzz,xxx,yyy,rad,zzzz,fn2,am,idd){}

void WeaponObject::action1(){
	cout<<"shooty shooty"<<endl;
}

void WeaponObject::weapon_init(int max,float f,float a,int bt,int mc,int c){
	//id=idd;
	//int max_ammo;
	max_amount=max;
	
	
	//DO random colours like this
	//model.set_color_scale(222/255.0,184/225.0,135/225.0,1.0);
	
	
	
	if(id==10){	//ak
		
	}
	else if(id==0){	//pistol
		
	}
	else if(id==2){	//bat
		
	}
	if(id==11){	//nedgev
		
	}
	
	
	
	
	firerate=f;
	accuracy=a;
	bullet_type=bt;
	tot_ammo=mc;
	clip=c;
	
}
