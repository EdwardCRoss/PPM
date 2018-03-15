#pragma once
#include "Menu.h"



//Game doesn't need to be updated in real time, only call the draw at the end of the update and if something changed
void Button :: Create(int Input_X, int Input_Y, std::string Input_Name, ALLEGRO_BITMAP *Input_TextureN , ALLEGRO_BITMAP *Input_TextureH, std::string Input_Text) //Texture2D Hover_Texture , Texture2D Pressed_Texture)
{

	//BUtton action, how to refer to it as
	Button_Name = Input_Name;
	//Writing stuff on button data
	Button_Text = Input_Text;

	//Button image and values
	button_tex_n = Input_TextureN; //Basic texture, when nothing is happening
	button_tex_h = Input_TextureH; //Hover / click texture

	//gets the position of the button
	x_position = Input_X;
	y_position = Input_Y;

	//Gets the dimensions of the button bitmap
	button_h = al_get_bitmap_height(button_tex_n);
	button_w = al_get_bitmap_width(button_tex_n);

}

bool Button :: isPressed()
{
	if (myButton_State == Pressed) //If it's pressed, return true
		return true;
	return false;
}

void Button :: Update_State(int input_mouse_x , int input_mouse_y , int input_mouse_button)
{


	if (Collision(input_mouse_x, input_mouse_y)) // if cursor is over button
	{
		if (input_mouse_button == 1) //If the left (==1) or the right (==2) button is held
		{
			myButton_State = Pressed;
		}

		else //Curser is over button, but not clicked
		{
			myButton_State = Hover;

		}

	}
	else
	{
		myButton_State = Nothing;
	}
}

bool Button :: Collision(int input_x, int input_y)
{
	//For simplicity work out each plane seperately, and both booleans have to be true to work
	bool isX = false;
	bool isY = false;

	if (input_x > x_position && input_x < x_position + button_w) //If the position is on the same x area as the button
		isX = true;

	if (input_y >= x_position && input_y <= x_position + button_h)
		isY = true;

	if (isX && isY) //final check
		return true;
	else
		return false;
}

void Button :: Draw_Button()
{
	ALLEGRO_BITMAP *temp;

	if (myButton_State == Nothing)
		al_draw_bitmap(button_tex_n, x_position, y_position, 1); //Draw the button at the positions stored in the class
	else if (myButton_State == Hover)
		al_draw_bitmap(button_tex_h, x_position, y_position, 1); //Draw the button at the positions stored in the class


}

//Screen functions

void Screen :: Load_Title()
{
	limit = 3;
	Button_List = new Button[limit]; //3 buttons on screen

									 //Input values into the buttons
	Button_List[0].Create(200, 200, "PLAY", button_n , button_h, "Play");
	Button_List[1].Create(200, 400, "HELP", button_n, button_h, "Help");
	Button_List[2].Create(200, 600, "EXIT", button_n, button_h, "Exit");

}

void Screen::run()
{
	//Initialisations, needed or the program crashes :(
	al_init();
	al_init_font_addon();
	al_init_image_addon();
	al_install_keyboard();
	al_install_mouse();


	finished = false;

	//Bring in the bitmaps
	button_n = al_load_bitmap("Button1.png");
	button_h = al_load_bitmap("Button2.png");
	screen_background = al_load_bitmap("Title_Background.png");


	display = al_create_display(windowWidth, windowHeight);

	al_clear_to_color(al_map_rgb(0, 0, 0));

	//Get the queue going
	ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();

	al_register_event_source(event_queue, al_get_display_event_source(display));
	al_register_event_source(event_queue, al_get_mouse_event_source());

	Load_Title(); //Load the title elements

	while (!finished)
	{
		ALLEGRO_EVENT events;
		al_wait_for_event_timed(event_queue, &events, 1 / 60);

		if (events.type == ALLEGRO_EVENT_MOUSE_AXES)
			Update(events.mouse.x , events.mouse.y , events.mouse.button);



		Draw(); //Draw the buttons
		al_flip_display(); //Load the new screen
	}
}

void Screen :: Update(int input_mouse_x, int input_mouse_y, int input_mouse_button)
{
	//Loop through all of the buttons and update them


	for (int i = 0; i < limit; i++)
	{
		Button_List[i].Update_State(input_mouse_x,input_mouse_y,input_mouse_button);
	}

}

void Screen :: Draw()
{
	//Draw background first
	al_draw_bitmap(screen_background , 0 , 0 , 0);
	//Loop through and Draw buttons
	for (int i = 0; i < limit; i++)
	{
		Button_List[i].Draw_Button();
	}


}

