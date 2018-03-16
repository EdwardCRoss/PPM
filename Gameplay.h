#pragma once
#define HEADER

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>
#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <math.h>
#include <string>
#include <iostream>
#include <cmath>
#include <math.h>


class backgroundC {
//Variables
protected:
	int x, y;
	ALLEGRO_BITMAP *background;
public:
	float speed;

//Functions
void draw();
void update();
void init();
};

class projectile {
public:
	int x, y;
	float velocity, direction;
	ALLEGRO_BITMAP *projectileSprite;

	void update();
	void draw();
	void init(int tempx, int tempy, float tempvelocity, float tempdirection, ALLEGRO_BITMAP *tempProjectileSPrite) {
		x = tempx;
		y = tempy;
		velocity = tempvelocity;
		direction = tempdirection;
		projectileSprite = tempProjectileSPrite;
	}
};

class standardEnemy {

protected:
	
	float gradient;
	ALLEGRO_BITMAP *enemySprite;




public:
	int x, y, power, xOffSet, yOffSet;
	void draw();
	
	void update();

	void fireProjetile(float direction);
	void fireLine(float direction, int numberOf);
	void fireCircle( int numberOf);


	void init(int tempx, int tempy, int tempOffx, int tempOffy, float tempgradient, int temppower, ALLEGRO_BITMAP *tempimage) {
		x = tempx;
		y = tempy;
		xOffSet = tempOffx;
		yOffSet = tempOffy;
		gradient = tempgradient;
		power = temppower;
		enemySprite = tempimage;
	}

};


int Gameplay();

float distanceBetween(int x1, int y1, int x2, int y2);


void updateEnemies();



void drawScreen();