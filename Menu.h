#pragma once

#include <string>
#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_image.h>

#include "main.h"

class Button
{
	enum myState { Pressed, Hover, Nothing }; //Enum used to assign a set of constants to a list, button states
	myState myButton_State; 
	ALLEGRO_BITMAP *button_tex_n; //Button texture
	ALLEGRO_BITMAP *button_tex_h; //Button texture

	//rectangle positions
	int x_position, y_position, button_w, button_h;
	std::string Button_Name; //Name of the button, will be used when refering to what action to take after the button has been clicked
	std::string Button_Text; //The text that may or may not be on the button

	bool isPressed(); //Check for pressed, easier to manage by have it in it's own function

	bool Collision(int input_x, int input_y); //The collision checking algorithm

public:
	void Create(int Input_X, int Input_Y, std::string Input_Name, ALLEGRO_BITMAP *Input_Texture1 , ALLEGRO_BITMAP *Input_Texture2, std::string Input_Text);


	void Update_State(int input_mouse_x, int input_mouse_y, int input_mouse_button); //Check the state of the button by compareng mouse position and button area, updates state

	void Draw_Button(); 
};

class Screen
{
private :
	Button *Button_List;
	int limit;
	bool finished;


	ALLEGRO_BITMAP *button_n; //Normal button
	ALLEGRO_BITMAP *button_h; //Hover button

	ALLEGRO_BITMAP *screen_background;
	ALLEGRO_DISPLAY *display;
	ALLEGRO_MOUSE_STATE *Current_Mouse_State;


public:

	void Load_Title();

	void run();
	

	void Update(int input_mouse_x, int input_mouse_y, int input_mouse_button);

	void Draw();


};