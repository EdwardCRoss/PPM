#pragma once
#include "Gameplay.h"


ALLEGRO_BITMAP *testImage, *background, *enemyShip, *projectileMain, *projectileSide, *tempProjectile;
int playerX, playerY, frameCount;
ALLEGRO_KEYBOARD_STATE *keyboardState;
bool firing = false;
bool focus = false;

int playerSpeed = 10;
int windowWidth = 800;
int windowHeight = 600;

std::vector<standardEnemy> enemyList; //lists for sprites
std::vector<std::vector<int>> projectileList;
std::vector<std::vector<int>> otherElementsList;
std::vector<projectile> enemyProjectiles;
std::vector<projectile> playerProjectiles;



//Background functions
void backgroundC :: draw() 
{
	al_draw_bitmap(background, x, y, 0);
	if (y>windowHeight) {
		y = -(2000 - windowHeight); // if off screen move back up to teselate


	}
	else if (y > 0) {
		al_draw_bitmap(background, 0, y - 2000, 0);//draws teserlated background when main partially off screen
	}
}

void backgroundC :: update()
{
	y += speed;//moves background down screen

}

void backgroundC :: init() 
{
	x = 0;
	y = 0;
	speed = 1;

	background = al_load_bitmap("background1.png");
}


//enemy functions
void standardEnemy :: draw() 
{
	al_draw_bitmap(enemySprite, x + xOffSet, y + yOffSet, 0);
}

void standardEnemy :: update() 
{
	x += 1;
	y = gradient*(pow(x, power));

}

void standardEnemy::fireProjetile(float direction) {
	projectile temp;
	temp.init(x+xOffSet+40,y+yOffSet+50,5,direction, tempProjectile);
	enemyProjectiles.push_back(temp);
}

void standardEnemy::fireCircle(int numberOf) {
	float interval = 6.28 / numberOf;
	for (float i = -3.14; i < 3.14;i+=interval) {
		fireProjetile(i);
	}
}


//projectile fucntions
void projectile::update() {
	x += velocity*cos(direction);
	y += velocity*sin(direction);
}

void projectile::draw() {
	al_draw_bitmap(projectileSprite, x, y, 0);
}


//non class functions

void drawPlayerProjectiles() {
	for (int i = 0; i < playerProjectiles.size(); i++) { //Go through each projecile in the list and draw them
		playerProjectiles[i].update();
		if (playerProjectiles[i].y < -100) {
			playerProjectiles.erase(playerProjectiles.begin()+i);
		}
		else {
			al_draw_bitmap(playerProjectiles[i].projectileSprite,playerProjectiles[i].x ,playerProjectiles[i].y , 0);
		}
	}
}

void drawEnemyProjectiles() {
	for (int i = 0; i < enemyProjectiles.size(); i++) {
		enemyProjectiles[i].draw();
		enemyProjectiles[i].update();
	}

}

void drawEnemies() {
	for (int i = 0; i < enemyList.size(); i++) {
		enemyList[i].draw();
		
	}

}
void updateEnemies() {
	for (int i = 0; i < enemyList.size(); i++) {

		enemyList[i].update();

		for (int j = 0; j < playerProjectiles.size(); j++) {
			if (distanceBetween((enemyList[i].x + enemyList[i].xOffSet), (enemyList[i].y + enemyList[i].yOffSet), playerProjectiles[j].x, playerProjectiles[j].y)<20) {
				playerProjectiles.erase(playerProjectiles.begin() + j);
				enemyList.erase(enemyList.begin() + i);
				j = playerProjectiles.size();
			}

			
		}
	}
}

void drawScreen() {

	drawEnemies();
	drawPlayerProjectiles();
	drawEnemyProjectiles();
	al_draw_bitmap(testImage, playerX, playerY, 0);
	al_flip_display();
	al_clear_depth_buffer(0);
	frameCount++;
}


int Gameplay()
{
	al_init(); // initilisations
	al_init_font_addon();
	al_init_image_addon();
	al_install_keyboard();

	ALLEGRO_DISPLAY* display = al_create_display(windowWidth, windowHeight);
	ALLEGRO_FONT* font = al_create_builtin_font();

	al_clear_to_color(al_map_rgb(0, 0, 0));

	testImage = al_load_bitmap("ship.png"); // load images to sprites
	background = al_load_bitmap("background1.png");
	enemyShip = al_load_bitmap("enemyShip.png");
	projectileMain = al_load_bitmap("Red_note_.png");
	projectileSide = al_load_bitmap("Green_note.png");
	tempProjectile = al_load_bitmap("tempProjectile.png");
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_keyboard_event_source());

	backgroundC currentBackground;
	currentBackground.init();
	
	bool done = false;
	int xMoveSpeedLeft = 0;
	int xMoveSpeedRight = 0;
	int yMoveSpeedUp = 0;
	int yMoveSpeedDown = 0;

	while (!done) { //user input handling
		ALLEGRO_EVENT events;
		al_wait_for_event_timed(event_queue, &events, 1 / 60);


		if (events.type == ALLEGRO_EVENT_KEY_DOWN) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				yMoveSpeedDown = playerSpeed;
				break;
			case ALLEGRO_KEY_UP:
				yMoveSpeedUp = -playerSpeed;
				break;
			case ALLEGRO_KEY_LEFT:
				xMoveSpeedLeft = -playerSpeed;
				break;
			case ALLEGRO_KEY_RIGHT:
				xMoveSpeedRight = playerSpeed;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_J:
				standardEnemy temp;
				temp.init(1, 1, -50, -30, 0.01, 2, enemyShip);
				enemyList.push_back(temp);
				break;
			case ALLEGRO_KEY_Z:
				firing = true;
				break;
			case ALLEGRO_KEY_X:
				focus = true;
				playerSpeed = 5;
				break;
			case ALLEGRO_KEY_I:
				for (int i = 0; i < enemyList.size(); i++) { 
					enemyList[i].fireProjetile(1.57); 
					enemyList[i].fireProjetile(0);
					enemyList[i].fireProjetile(3.14);
				}
				break;
			case ALLEGRO_KEY_O:
				for (int i = 0; i < enemyList.size(); i++) {
					enemyList[i].fireCircle(16);
				}
				break;
			case ALLEGRO_KEY_P:
				break;
			case ALLEGRO_KEY_COMMA:
				currentBackground.speed++;

				//std::cout << currentBackground.speed << std::endl;
				break;
			case ALLEGRO_KEY_FULLSTOP:
				if (currentBackground.speed > 1) {
					currentBackground.speed--;
				}
				break;
			}
		}
		if (events.type == ALLEGRO_EVENT_KEY_UP) {
			switch (events.keyboard.keycode) {
			case ALLEGRO_KEY_DOWN:
				yMoveSpeedDown = 0;
				break;
			case ALLEGRO_KEY_UP:
				yMoveSpeedUp = 0;
				break;
			case ALLEGRO_KEY_LEFT:
				xMoveSpeedLeft = 0;
				break;
			case ALLEGRO_KEY_RIGHT:
				xMoveSpeedRight = 0;
				break;
			case ALLEGRO_KEY_ESCAPE:
				done = true;
				break;
			case ALLEGRO_KEY_Z:
				firing = false;
				break;
			case ALLEGRO_KEY_X:
				focus = false;
				playerSpeed = 10;
				break;
			}
		}

		if (firing && (frameCount % 5 == 0)) { //fires every 5 frames, checks for multiples of 5
			
			projectile temp;
			if (focus == false) {
				temp.init(playerX, playerY, 10, -1.68, projectileSide);
				playerProjectiles.push_back(temp);
				temp.init(playerX + 80, playerY, 10, -1.44, projectileSide);
				playerProjectiles.push_back(temp);
				temp.init(playerX + 40, playerY - 10, 10, -1.57, projectileMain);
				playerProjectiles.push_back(temp);
			}
			else {
				temp.init(playerX, playerY, 10, -1.57, projectileSide);
				playerProjectiles.push_back(temp);
				temp.init(playerX + 80, playerY, 10, -1.57, projectileSide);
				playerProjectiles.push_back(temp);
				temp.init(playerX + 40, playerY - 10, 10, -1.57, projectileMain);
				playerProjectiles.push_back(temp);
			
			}
		}

		playerX += (xMoveSpeedLeft + xMoveSpeedRight);//updates player position
		playerY += (yMoveSpeedUp + yMoveSpeedDown);
		currentBackground.draw();//other updates
		
		drawScreen();
		updateEnemies();
		currentBackground.update();

		
		

		al_rest(1.0 / 60);//framerate limiter
	}



	return 0;
}


float distanceBetween(int x1, int y1, int x2, int y2) 
{
	return sqrt((pow((x2 - x1), 2)) + (pow((y2 - y1), 2)));
}