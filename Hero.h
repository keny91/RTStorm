#pragma once

#ifndef _HERO_H_
#define _HERO_H_ 

// list in alphabetic order
// last added Cain
enum heroName {Abathur, Alarak,Alextraza, Ana, Anubarak, Artanis, Arthas, 
	Auriel,Azmodan, Butcher, Blaze, Brightwing, Cassia, Chen, Cho, Gall,
	Chromie, Cain, Dehaka, Diablo, DVa, ETC, Falstad, Fenix, Garrosh, Gazlowe,
	Genji, Greymane, Guldan, Hanzo, Ilidan, Jaina, Johana, Junkrat, Kaelthas,
	Keltuzad,Kerrigan, Kharazim, Leoric, Lili, Ñiming, LostVikings, Morales,
	Lucio, Lunara, Maiev, Malfurion, Malthael,Medivh, Muradin, Murky, Nazeboo,
	Nova, Probious, Ragnaros, Raynor, Reghar, Rexxar, Samuro, Hammer, Sonya,
	Stitches ,Stukov, Sylvanas,Tassadar, Thrall, Tracer , Tychus, Tyrael,
	Tyrande, Uther, Valyra, Valla, Varian, Xul, Zagara, Zarya, Zeratul, Zuljin};


/* This function will load data from an XML and initialize classes like health*/
void LoadHeroFromTemplate(heroName name);


// hero creation will be a 
typedef class HeroClass
{
protected:


public:

	/* This is a very complex constructor; it will initialize different 
	classes and structures giving them their values based on a template 
	loaded from a .xml with the name of the hero*/
	HeroClass(heroName name);

} *Hero;

#endif // _HERO_H_