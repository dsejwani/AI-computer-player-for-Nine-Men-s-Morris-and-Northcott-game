//
// MainPage1.xaml.cpp
// Implementation of the MainPage1 class.
//

#include "pch.h"
#include "MainPage1.xaml.h"
//#include "afxwin.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include "board.h"
#include "move.h"
#include "Gamecontroller.h"
using namespace App2;

using namespace Platform;
using namespace Windows::Foundation;
using namespace Windows::Foundation::Collections;
using namespace Windows::UI::Xaml;
using namespace Windows::UI::Xaml::Controls;
using namespace Windows::UI::Xaml::Controls::Primitives;
using namespace Windows::UI::Xaml::Data;
using namespace Windows::UI::Xaml::Input;
using namespace Windows::UI::Xaml::Media;
using namespace Windows::UI::Xaml::Navigation;
using namespace std;

//using namespace Windows::UI::Xaml::Controls::Image;

// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=402352&clcid=0x409
int tokenvalx[24], placed1x = 0, placed2x = 0, captured1x = 0, captured2x = 0;
bool turnx = true;
bool situation3_turnx, situation34x = false;
int situationx = 1;
//Image* token1x[9], token2x[9];
double positionx[24][2];
Image ^token1x[9], ^token2x[9], ^quote1x[4], ^quote2x[4];
Button ^buttonx[24];
void move_situation11x(int index);
void move_situation1x(int index);

void move_situation22x(int index);
void move_situation2x(int index);

string map1x[24] = {
	"A1","D1","G1","B2","D2","F2","C3","D3","E3","A4","B4","C4",
	"E4","F4","G4","C5","D5","E5","B6","D6","F6","A7","D7","G7"
};

string starkx[4] = {
	"Winter is indeed coming!", "By the old Gods and new, kill him!",
	"Long live King of the North!", "Slay that bastard!"
};

string lannisterx[4] = {
	"The debt is paid.", "Let's show 'em how it's done in King's Landing!",
	"Hear us roar!", "Time for a long summer!"
};

int player_movex, player_movex_fromx, player_cutx, com_movex, com_cutx;

int what_move_num1(string to_find)
{
	for (int i = 0; i < 24; i++)
	{
		if (map1x[i] == to_find)
			return i;
	}
	return -1;
}

int movementx[24][4] = {
	{ 1,9,-1,-1 },
	{ 0,2,4,-1 },
	{ 1,14,-1,-1 },
	{ 4,10,-1,-1 },
	{ 1,3,5,7 },
	{ 4,13,-1,-1 },
	{ 7,11,-1,-1 },
	{ 4,6,8,-1 },
	{ 7,12,-1,-1 },
	{ 0,10,21,-1 },
	{ 3,9,11,18 },
	{ 6,10,15,-1 },
	{ 8,13,17,-1 },
	{ 5,12,14,20 },
	{ 2,13,23,-1 },
	{ 11,16,-1,-1 },
	{ 15,17,19,-1 },
	{ 12,16,-1,-1 },
	{ 10,19,-1,-1 },
	{ 16,18,20,22 },
	{ 13,19,-1,-1 },
	{ 9,22,-1,-1 },
	{ 19,21,23,-1 },
	{ 14,22,-1,-1 }
};
//TextBlock ^textblock12x;
int millx[24][2][2] = {
	{ { 1,2 },{ 9,21 } },
	{ { 0,2 },{ 4,7 } },
	{ { 0,1 },{ 14,23 } },
	{ { 4,5 },{ 10,18 } },
	{ { 1,7 },{ 3,5 } },
	{ { 3,4 },{ 13,20 } },
	{ { 7,8 },{ 11,15 } },
	{ { 1,4 },{ 6,8 } },
	{ { 6,7 },{ 12,17 } },
	{ { 0,21 },{ 10,11 } },
	{ { 3,18 },{ 9,11 } },
	{ { 6,15 },{ 9,10 } },
	{ { 8,17 },{ 13,14 } },
	{ { 5,20 },{ 12,14 } },
	{ { 2,23 },{ 12,13 } },
	{ { 6,11 },{ 16,17 } },
	{ { 15,17 },{ 19,22 } },
	{ { 15,16 },{ 12,8 } },
	{ { 19,20 },{ 3,10 } },
	{ { 18,20 },{ 16,22 } },
	{ { 18,19 },{ 5,13 } },
	{ { 0,9 },{ 22,23 } },
	{ { 21,23 },{ 16,19 } },
	{ { 21,22 },{ 2,14 } }
};
int select_posx = -1, select_img_nox = -1;
int image_corr_buttonx[24];
int cutchancesx = 0, no_in_mill2x = 0, no_in_mill1x = 0;
//TextBox ^textbox1;
Shapes::Rectangle ^R12x;
GameController *gamex;
Image ^p1x, ^p2x;

MainPage1::MainPage1()
{
	InitializeComponent();
	for (int i = 0; i < 24; i++)
	{
		tokenvalx[i] = 0;
		image_corr_buttonx[i] = -1;
	};

	R12x = R1x;
	p1x = imagep1x;
	p2x = imagep2x;
	//textblock12x = textBlock121;
	positionx[0][0] = 452 - 15;
	positionx[0][1] = 72.5 - 15;
	positionx[1][0] = 732 - 15;
	positionx[1][1] = 72.5 - 15;
	positionx[2][0] = 1012 - 15;
	positionx[2][1] = 72.5 - 15;
	positionx[3][0] = 532 - 15;
	positionx[3][1] = 152 - 15;
	positionx[4][0] = 732 - 15;
	positionx[4][1] = 152 - 15;
	positionx[5][0] = 932 - 15;
	positionx[5][1] = 152 - 15;
	positionx[6][0] = 612 - 15;
	positionx[6][1] = 232.5 - 15;
	positionx[7][0] = 732 - 15;
	positionx[7][1] = 232.5 - 15;
	positionx[8][0] = 852 - 15;
	positionx[8][1] = 232.5 - 15;
	positionx[9][0] = 452 - 15;
	positionx[9][1] = 352.5 - 15;
	positionx[10][0] = 532 - 15;
	positionx[10][1] = 352.5 - 15;
	positionx[11][0] = 612 - 15;
	positionx[11][1] = 352.5 - 15;
	positionx[12][0] = 852 - 15;
	positionx[12][1] = 352.5 - 15;
	positionx[13][0] = 932 - 15;
	positionx[13][1] = 352.5 - 15;
	positionx[14][0] = 1012 - 15;
	positionx[14][1] = 352.5 - 15;
	positionx[15][0] = 612 - 15;
	positionx[15][1] = 472.5 - 15;
	positionx[16][0] = 732 - 15;
	positionx[16][1] = 472.5 - 15;
	positionx[17][0] = 852 - 15;
	positionx[17][1] = 472.5 - 15;
	positionx[18][0] = 532 - 15;
	positionx[18][1] = 552.5 - 15;
	positionx[19][0] = 732 - 15;
	positionx[19][1] = 552.5 - 15;
	positionx[20][0] = 932 - 15;
	positionx[20][1] = 552.5 - 15;
	positionx[21][0] = 452 - 15;
	positionx[21][1] = 632.5 - 15;
	positionx[22][0] = 732 - 15;
	positionx[22][1] = 632.5 - 15;
	positionx[23][0] = 1012 - 15;
	positionx[23][1] = 632.5 - 15;
	//token1x[0]=
	//array< Image^ >^ local = gcnew array< MyClass^ >(ARRAY_SIZE);
	//Array<Image, 9> token1;
	//token1x[0]= &image11;

	//textblock12x->Text = "vadh(char)cutchancesx";

	quote1x[0] = image1_11;
	quote1x[1] = image1_21;
	quote1x[2] = image1_31;
	quote1x[3] = image1_41;

	quote2x[0] = image2_11;
	quote2x[1] = image2_21;
	quote2x[2] = image2_31;
	quote2x[3] = image2_41;


	token1x[0] = image111;
	token1x[1] = image121;
	token1x[2] = image131;
	token1x[3] = image141;
	token1x[4] = image151;
	token1x[5] = image161;
	token1x[6] = image171;
	token1x[7] = image181;
	token1x[8] = image191;

	token2x[0] = image211;
	token2x[1] = image221;
	token2x[2] = image231;
	token2x[3] = image241;
	token2x[4] = image251;
	token2x[5] = image261;
	token2x[6] = image271;
	token2x[7] = image281;
	token2x[8] = image291;

	buttonx[0] = button01;
	buttonx[1] = button11;
	buttonx[2] = button21;
	buttonx[3] = button31;
	buttonx[4] = button41;
	buttonx[5] = button51;
	buttonx[6] = button61;
	buttonx[7] = button71;
	buttonx[8] = button81;
	buttonx[9] = button91;
	buttonx[10] = button101;
	buttonx[11] = button111;
	buttonx[12] = button121;
	buttonx[13] = button131;
	buttonx[14] = button141;
	buttonx[15] = button151;
	buttonx[16] = button161;
	buttonx[17] = button171;
	buttonx[18] = button181;
	buttonx[19] = button191;
	buttonx[20] = button201;
	buttonx[21] = button211;
	buttonx[22] = button221;
	buttonx[23] = button231;

	int timel = 1;
	gamex = new GameController(timel, 'H', 'W');
	//textblock12x->Text = "started";
}

void disable_all_buttons1()
{
	for (int i = 0; i < 24; i++)
	{
		buttonx[i]->IsEnabled = false;
	}
}

void hide_empty1()
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] != 0 || buttonx[i]->IsEnabled == false)
		{
			buttonx[i]->Opacity = 0;
		}
		else
		{
			buttonx[i]->Opacity = 1;
		}
	}
}

bool is_valid_p1_moves1()
{

	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] > 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (movementx[i][j] >= 0)
				{
					if (tokenvalx[movementx[i][j]] == 0)
						return true;
				}
			}
		}
	}
	return false;

}
bool is_valid_p2_moves1()
{

	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] < 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (movementx[i][j] >= 0)
				{
					if (tokenvalx[movementx[i][j]] == 0)
						return true;
				}
			}
		}
	}
	return false;

}
int checkmill1(int index, bool value)
{
	int result = 0;
	if (!value)
	{
		tokenvalx[index] = 0;// (value) ? ((turn) ? 2 : -2) : 0;
		turnx = !turnx;

		//textblock12x->Text += " t " + turnx.ToString() + " ";
	}
	if (turnx)
	{
		if (tokenvalx[millx[index][0][0]] > 0 && tokenvalx[millx[index][0][1]]>0)
		{
			tokenvalx[millx[index][0][0]] = (value) ? 2 : ((checkmill1(millx[index][0][0], true)>0) ? 2 : 1);

			tokenvalx[millx[index][0][1]] = (value) ? 2 : ((checkmill1(millx[index][0][1], true)>0) ? 2 : 1);
			if (value)
				tokenvalx[index] = 2;
			result++;
		}
		if (tokenvalx[millx[index][1][0]] > 0 && tokenvalx[millx[index][1][1]]>0)
		{

			tokenvalx[millx[index][1][0]] = (value) ? 2 : ((checkmill1(millx[index][1][0], true)>0) ? 2 : 1);

			tokenvalx[millx[index][1][1]] = (value) ? 2 : ((checkmill1(millx[index][1][1], true)>0) ? 2 : 1);
			if (value)
				tokenvalx[index] = 2;
			result++;
		}
	}
	else
	{
		if (tokenvalx[millx[index][0][0]] <0 && tokenvalx[millx[index][0][1]]<0)
		{
			tokenvalx[millx[index][0][0]] = (value) ? -2 : ((checkmill1(millx[index][0][0], true)>0) ? -2 : -1);

			tokenvalx[millx[index][0][1]] = (value) ? -2 : ((checkmill1(millx[index][0][1], true)>0) ? -2 : -1);
			result++;
			if (value)
				tokenvalx[index] = -2;
		}
		if (tokenvalx[millx[index][1][0]] < 0 && tokenvalx[millx[index][1][1]]<0)
		{
			tokenvalx[millx[index][1][0]] = (value) ? -2 : ((checkmill1(millx[index][1][0], true)>0) ? -2 : -1);

			tokenvalx[millx[index][1][1]] = (value) ? -2 : ((checkmill1(millx[index][1][1], true)>0) ? -2 : -1);
			result++;
			if (value)
				tokenvalx[index] = -2;
		}

	}
	if (!value)
	{
		turnx = !turnx;
		//textblock12x->Text += " t " + turnx.ToString() + " ";
	}
	return result;
}
void p1clickable1(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] > 0)
		{
			buttonx[i]->IsEnabled = clickmode;

		}
	}
}
void p2clickable1(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] < 0)
		{
			buttonx[i]->IsEnabled = clickmode;
		}

	}
}
int calc_num_mill1()
{
	int result = 0;
	for (int i = 0; i < 24; i++)
	{
		if (turnx && tokenvalx[i] == -2)
			result++;
		if (!turnx && tokenvalx[i] == 2)
			result++;

	}
	return result;
}
void p2notmillclickable1(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] == -1)
		{
			buttonx[i]->IsEnabled = clickmode;

		}
	}
}

void p1notmillclickable1(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] == 1)
		{
			buttonx[i]->IsEnabled = clickmode;

		}
	}
}
void dotsclickable1(bool emptydotsclick)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenvalx[i] == 0)
		{
			buttonx[i]->IsEnabled = emptydotsclick;
		}
	}
}
void gameOverx(bool player)
{
	R12x->Margin = Thickness(48, 406, 0, 0);
	if (player)
		p1x->Margin = Thickness(102, 500, 0, 0);
	else
		p2x->Margin = Thickness(102, 500, 0, 0);
}
void move_situation1x(int index)
{
	//textblock12x->Text = "abcxyz" + situationx.ToString();

	if (turnx)
	{
		tokenvalx[index] = 1;//player 1 placed
		hide_empty1();

		//textblock12x->Text = "abcxyz" + situationx.ToString();
		token1x[placed1x]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
		image_corr_buttonx[index] = placed1x;
		placed1x++;

	}
	else
	{
		tokenvalx[index] = -1;//player 2 placed
		hide_empty1();

		token2x[placed2x]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
		image_corr_buttonx[index] = placed2x;
		placed2x++;
	}
	buttonx[index]->IsEnabled = false;
	cutchancesx = checkmill1(index, true);

	if (cutchancesx > 0)
	{

		situationx = 11;
		player_movex = index;
		if (turnx)
		{
			p1clickable1(false);
			dotsclickable1(false);
			no_in_mill2x = calc_num_mill1();
			//		textblock12x->Text= ("\nplaced2x:" + placed2x + "\ncaptured2x:" + captured2x + " nummill2" + no_in_mill2x);
			if (placed2x - captured2x == no_in_mill2x)
			{
				p2clickable1(true);
			}
			else
			{
				p2notmillclickable1(true);
			}
		}
		else
		{

			p2clickable1(false);
			dotsclickable1(false);
			no_in_mill1x = calc_num_mill1();
			//	textblock12x->Text += ("\nplaced1x:" + placed1x + "\ncaptured1x:" + captured1x + " nummill1" + no_in_mill1x);

			if (placed1x - captured1x == no_in_mill1x)
			{
				p1clickable1(true);
			}
			else
			{
				p1notmillclickable1(true);
			}

			//move_situation11x(com_cutx);
			//Sleep(2000);
		}
		hide_empty1();
		return;
	}
	else
	{
		turnx = !turnx;
		/*if (!turnx)
		{
		string x = gamex->move(map1x[index]);
		if (x.length() > 2)
		{
		com_movex = what_move_num1(x.substr(0, 2));
		com_cutx = what_move_num1(x.substr(3, 2));
		}
		else
		com_movex = what_move_num1(x);
		wstring ws;
		ws.assign(x.begin(), x.end());
		textblock12x->Text = "h" + ref new Platform::String(ws.c_str()) +"h";
		move_situation1x(com_movex);
		}*/
	}
	if (placed2x == 9)
	{
		situationx = 2;
		p1clickable1(true);
		dotsclickable1(false);
		hide_empty1();
	}
}

void move_situation11x(int index)
{
	//textblock12x->Text += "abcxyz" + situationx.ToString();

	cutchancesx = 0;

	checkmill1(index, false);

	if (turnx)
	{
		int x = captured2x % 4;
		for (int i = 0; i < 4; i++)
			quote1x[i]->Visibility = Visibility(true);
		quote1x[x]->Visibility = Visibility(false);
		captured2x++;
		//textblock12x->Text += "xyz";
		token2x[image_corr_buttonx[index]]->Visibility = Visibility(true);

		//token2x[image_corr_buttonx[index]]->Margin = Thickness(50000, 50000,0,0);
	}
	else
	{
		int x = captured1x % 4;
		for (int i = 0; i < 4; i++)
			quote2x[i]->Visibility = Visibility(true);
		quote2x[x]->Visibility = Visibility(false);
		captured1x++;
		//textblock12x->Text += "xyz";

		token1x[image_corr_buttonx[index]]->Visibility = Visibility(true);
	}
	if (cutchancesx == 0)
	{
		if (placed2x == 9)
		{
			situationx = 2;
			p1clickable1(true);
			dotsclickable1(false);

		}
		else
		{
			situationx = 1;
			p1clickable1(false);
			p2clickable1(false);
			dotsclickable1(true);

		}
		hide_empty1();
		turnx = !turnx;
		/*	if (!turnx)
		{
		string x = gamex->move(map1x[player_movex] + "," + map1x[index]);
		if (x.length() > 2)
		{
		com_movex = what_move_num1(x.substr(0, 2));
		com_cutx = what_move_num1(x.substr(3, 2));
		}
		else
		com_movex = what_move_num1(x);
		move_situation1x(com_movex);
		textblock12x->Text += " t " + turnx.ToString() + " ";

		}*/
	}

}


void enable_adjacent1(int index)
{
	for (int i = 0; i < 4; i++)
	{
		if (movementx[index][i] != -1)
		{
			buttonx[movementx[index][i]]->IsEnabled = true;
		}
	}
}

void move_situation22x(int index)
{
	//textblock12x->Text += "abcxyz" + situationx.ToString();

	cutchancesx = 0;

	checkmill1(index, false);
	situationx = 2;
	if (turnx)
	{
		int x = captured2x % 4;
		for (int i = 0; i < 4; i++)
			quote1x[i]->Visibility = Visibility(true);
		quote1x[x]->Visibility = Visibility(false);
		captured2x++;
		//textblock12x->Text += "xyz";
		token2x[image_corr_buttonx[index]]->Visibility = Visibility(true);
		player_cutx = index;
		if (captured2x > 6)
		{
			//textblock12x->Text = "Playe 1 Won";
			disable_all_buttons1();
			gameOverx(true);
		}
	}
	else
	{
		int x = captured1x % 4;
		for (int i = 0; i < 4; i++)
			quote2x[i]->Visibility = Visibility(true);
		quote2x[x]->Visibility = Visibility(false);
		captured1x++;
		//textblock12x->Text += "xyz";
		token1x[image_corr_buttonx[index]]->Visibility = Visibility(true);

		if (captured1x > 6)
		{
			//textblock12x->Text = "Player 2 Won";
			disable_all_buttons1();
			gameOverx(false);
		}
	}
	if (cutchancesx == 0)
	{

		situationx = 2;
		//if(turnx)
		p1clickable1(!turnx);
		p2clickable1(turnx);
		dotsclickable1(false);
		//turnx = !turnx;
		//textblock12x->Text += " t " + turnx.ToString() + " ";
		select_posx = -1;

		if (captured1x >= 6 || captured2x >= 6)
		{
			situationx = 3;

			if (captured1x >= 6 && captured2x >= 6)
				situation34x = true;
			if (captured1x >= 6)
				situation3_turnx = true;
			else
				situation3_turnx = false;

		}

		turnx = !turnx;
		if (turnx)
		{
			if (!is_valid_p1_moves1())
			{
				//textblock12x->Text = "Player 2 Won";
				disable_all_buttons1();
				gameOverx(false);
			}
		}
		else
		{
			if (!is_valid_p2_moves1())
			{
				//textblock12x->Text = "Player 1 Won";
				disable_all_buttons1();
				gameOverx(true);
			}
		}
		hide_empty1();
		/*if (!turnx)
		{
		string x = gamex->move(map1x[player_movex_fromx]+"-"+ map1x[player_movex] + "," + map1x[index]);
		if (x.length() > 5)
		{
		com_movex = what_move_num1(x.substr(3, 2));
		com_cutx = what_move_num1(x.substr(6, 2));
		}
		else
		com_movex = what_move_num1(x.substr(3,2));
		move_situation2x(what_move_num1(x.substr(0, 2)));
		wstring ws;
		ws.assign(x.begin(), x.end());
		textblock12x->Text = "hcom_movex" + ref new Platform::String(ws.c_str()) + "h";
		*/
		//textblock12x->Text += " com_mnove " + x+ " ";

		//}

	}
}

void move_situation2x(int index)
{
	if (select_posx >= 0 && tokenvalx[index] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			token1x[i]->Height = 60;
			token1x[i]->Width = 60;
			token2x[i]->Height = 60;
			token2x[i]->Width = 60;
		}
		//textblock12x->Text += "s11";
		if (turnx)
		{
			token1x[select_img_nox]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
			tokenvalx[index] = 1;
			player_movex = index;
		}
		else
		{
			token2x[select_img_nox]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
			tokenvalx[index] = -1;
		}
		hide_empty1();
		tokenvalx[select_posx] = 0;

		image_corr_buttonx[index] = select_img_nox;
		image_corr_buttonx[select_posx] = -1;
		cutchancesx = checkmill1(index, true);

		if (cutchancesx > 0)
		{
			situationx = 22;
			if (turnx)
			{
				p1clickable1(false);
				dotsclickable1(false);
				no_in_mill2x = calc_num_mill1();
				//textblock12x->Text += (" placed2x:" + placed2x + " captured2x:" + captured2x + " nummill2" + no_in_mill2x);
				if (9 - captured2x == no_in_mill2x)
				{
					p2clickable1(true);
				}
				else
				{
					p2notmillclickable1(true);
				}
			}
			else
			{
				p2clickable1(false);
				dotsclickable1(false);
				no_in_mill1x = calc_num_mill1();
				//textblock12x->Text += ("\nplaced1x:" + placed1x + "\ncaptured1x:" + captured1x + " nummill1" + no_in_mill1x);

				if (9 - captured1x == no_in_mill1x)
				{
					p1clickable1(true);
				}
				else
				{
					p1notmillclickable1(true);
				}
				//move_situation22x(com_cutx);
			}
			select_posx = -1;

			return;
		}
		else
		{
			//textblock12x->Text += "s12";
			turnx = !turnx;
			//textblock12x->Text += " t " + turnx.ToString() + " ";
			dotsclickable1(false);
			p1clickable1(turnx);
			p2clickable1(!turnx);
			if (turnx)
			{
				if (!is_valid_p1_moves1())
				{
					//textblock12x->Text = "Player 2 Won";
					disable_all_buttons1();
					hide_empty1();
					gameOverx(false);
				}
			}
			else
			{
				if (!is_valid_p2_moves1())
				{
					//textblock12x->Text = "Player 1 Won";
					disable_all_buttons1();
					hide_empty1();
					gameOverx(true);
				}
				/*string x = gamex->move(map1x[player_movex_fromx]+"-"+map1x[player_movex]);
				if (x.length() > 5)
				{
				com_movex = what_move_num1(x.substr(3, 2));
				com_cutx = what_move_num1(x.substr(6, 2));
				}
				else
				com_movex = what_move_num1(x.substr(3,2));
				wstring ws;
				ws.assign(x.begin(), x.end());
				textblock12x->Text = "ah" + ref new Platform::String(ws.c_str()) + "h";
				move_situation2x(what_move_num1(x.substr(0, 2)));
				*/
			}
		}
		select_posx = -1;

	}
	else
	{
		if (turnx)
		{
			for (int i = 0; i < 9; i++)
			{
				token1x[i]->Height = 60;
				token1x[i]->Width = 60;
			}
			token1x[image_corr_buttonx[index]]->Height = 75;
			token1x[image_corr_buttonx[index]]->Width = 75;
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				token2x[i]->Height = 60;
				token2x[i]->Width = 60;
			}
			token2x[image_corr_buttonx[index]]->Height = 75;
			token2x[image_corr_buttonx[index]]->Width = 75;
		}

		//textblock12x->Text += "s2";
		select_posx = index;
		select_img_nox = image_corr_buttonx[index];
		//hide_empty1();
		disable_all_buttons1();
		enable_adjacent1(select_posx);
		p1clickable1(turnx);
		p2clickable1(!turnx);
		hide_empty1();
		//	if(turnx)
		//	player_movex_fromx = index;
		//else
		//move_situation2x(com_movex);

	}
}
void move_situation31(int index)
{
	/*if (situation3_turnx == true && turn)
	{

	}*/
	if (select_posx >= 0 && tokenvalx[index] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			token1x[i]->Height = 60;
			token1x[i]->Width = 60;
			token2x[i]->Height = 60;
			token2x[i]->Width = 60;
		}
		//textblock12x->Text += "s11";
		if (turnx)
		{
			token1x[select_img_nox]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
			tokenvalx[index] = 1;
			player_movex = index;
		}
		else
		{
			token2x[select_img_nox]->Margin = Thickness(positionx[index][0], positionx[index][1], 0, 0);
			tokenvalx[index] = -1;
		}
		tokenvalx[select_posx] = 0;

		image_corr_buttonx[index] = select_img_nox;
		image_corr_buttonx[select_posx] = -1;
		cutchancesx = checkmill1(index, true);

		if (cutchancesx > 0)
		{
			situationx = 22;
			if (turnx)
			{
				p1clickable1(false);
				dotsclickable1(false);
				no_in_mill2x = calc_num_mill1();
				//textblock12x->Text += (" placed2x:" + placed2x + " captured2x:" + captured2x + " nummill2" + no_in_mill2x);
				if (9 - captured2x == no_in_mill2x)
				{
					p2clickable1(true);
				}
				else
				{
					p2notmillclickable1(true);
				}
			}
			else
			{
				p2clickable1(false);
				dotsclickable1(false);
				no_in_mill1x = calc_num_mill1();
				//textblock12x->Text += ("\nplaced1x:" + placed1x + "\ncaptured1x:" + captured1x + " nummill1" + no_in_mill1x);

				if (9 - captured1x == no_in_mill1x)
				{
					p1clickable1(true);
				}
				else
				{
					p1notmillclickable1(true);
				}
				//	move_situation22x(com_cutx);
			}
			hide_empty1();
			select_posx = -1;
			return;
		}
		else
		{
			//textblock12x->Text += "s12";
			turnx = !turnx;
			//textblock12x->Text += " t " + turnx.ToString() + " ";
			dotsclickable1(false);
			p1clickable1(turnx);
			p2clickable1(!turnx);
			hide_empty1();
			if (turnx)
			{
				if (!is_valid_p1_moves1())
				{
					//textblock12x->Text = "Player 2 Won";
					disable_all_buttons1();
					hide_empty1();
					gameOverx(false);
				}
			}
			else
			{
				if (!is_valid_p2_moves1())
				{
					//textblock12x->Text = "Player 1 Won";
					disable_all_buttons1();
					hide_empty1();
					gameOverx(true);
				}
				/*string x = gamex->move(map1x[player_movex_fromx] + "-" + map1x[player_movex]);
				if (x.length() > 5)
				{
				com_movex = what_move_num1(x.substr(3, 2));
				com_cutx = what_move_num1(x.substr(6, 2));
				}
				else
				com_movex = what_move_num1(x.substr(3, 2));
				wstring ws;
				ws.assign(x.begin(), x.end());
				textblock12x->Text = "ah" + ref new Platform::String(ws.c_str()) + "h";
				move_situation2x(what_move_num1(x.substr(0, 2)));
				*/
			}
		}
		select_posx = -1;

	}
	else
	{
		if (turnx)
		{
			for (int i = 0; i < 9; i++)
			{
				token1x[i]->Height = 60;
				token1x[i]->Width = 60;
			}
			token1x[image_corr_buttonx[index]]->Height = 75;
			token1x[image_corr_buttonx[index]]->Width = 75;
		}
		else
		{
			for (int i = 0; i < 9; i++)
			{
				token2x[i]->Height = 60;
				token2x[i]->Width = 60;
			}
			token2x[image_corr_buttonx[index]]->Height = 75;
			token2x[image_corr_buttonx[index]]->Width = 75;
		}

		//textblock12x->Text += "s2";
		select_posx = index;
		select_img_nox = image_corr_buttonx[index];
		if (turnx == situation3_turnx || situation34x)
			dotsclickable1(true);
		else
			enable_adjacent1(select_posx);
		p1clickable1(turnx);
		p2clickable1(!turnx);
		/*if (turnx)
		player_movex_fromx = index;
		else
		move_situation2x(com_movex);
		*/
	}

}


void App2::MainPage1::button_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(0);
	}
	else if (situationx == 11)
	{
		move_situation11x(0);
	}
	else if (situationx == 2)
	{
		move_situation2x(0);
	}
	else if (situationx == 22)
	{
		move_situation22x(0);
	}

	else if (situationx == 3)
	{
		move_situation31(0);
	}
}




void App2::MainPage1::button1_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(1);
	}
	else if (situationx == 11)
	{
		move_situation11x(1);
	}
	else if (situationx == 2)
	{
		move_situation2x(1);

	}

	else if (situationx == 22)
	{
		move_situation22x(1);
	}
	else if (situationx == 3)
	{
		move_situation31(1);
	}
}


void App2::MainPage1::button2_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(2);
	}
	else if (situationx == 11)
	{
		move_situation11x(2);
	}
	else if (situationx == 2)
	{
		move_situation2x(2);
	}
	else if (situationx == 22)
	{
		move_situation22x(2);
	}
	else if (situationx == 3)
	{
		move_situation31(2);
	}
}


void App2::MainPage1::button3_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(3);
	}
	else if (situationx == 11)
	{
		move_situation11x(3);
	}
	else if (situationx == 2)
	{
		move_situation2x(3);

	}

	else if (situationx == 22)
	{
		move_situation22x(3);
	}
	else if (situationx == 3)
	{
		move_situation31(3);
	}
}


void App2::MainPage1::button4_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(4);
	}

	else if (situationx == 11)
	{
		move_situation11x(4);
	}
	else if (situationx == 2)
	{
		move_situation2x(4);

	}

	else if (situationx == 22)
	{
		move_situation22x(4);
	}

	else if (situationx == 3)
	{
		move_situation31(4);
	}
}


void App2::MainPage1::button5_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(5);
	}

	else if (situationx == 11)
	{
		move_situation11x(5);
	}
	else if (situationx == 2)
	{
		move_situation2x(5);

	}

	else if (situationx == 22)
	{
		move_situation22x(5);
	}
	else if (situationx == 3)
	{
		move_situation31(5);
	}
}


void App2::MainPage1::button6_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(6);
	}

	else if (situationx == 11)
	{
		move_situation11x(6);
	}
	else if (situationx == 2)
	{
		move_situation2x(6);

	}

	else if (situationx == 22)
	{
		move_situation22x(6);
	}
	else if (situationx == 3)
	{
		move_situation31(6);
	}
}


void App2::MainPage1::button7_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(7);
	}
	else if (situationx == 11)
	{
		move_situation11x(7);
	}
	else if (situationx == 2)
	{
		move_situation2x(7);

	}

	else if (situationx == 22)
	{
		move_situation22x(7);
	}

	else if (situationx == 3)
	{
		move_situation31(7);
	}
}


void App2::MainPage1::button8_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(8);
	}
	else if (situationx == 11)
	{
		move_situation11x(8);
	}
	else if (situationx == 2)
	{
		move_situation2x(8);

	}
	else if (situationx == 22)
	{
		move_situation22x(8);
	}
	else if (situationx == 3)
	{
		move_situation31(8);
	}
}


void App2::MainPage1::button9_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(9);
	}
	else if (situationx == 11)
	{
		move_situation11x(9);
	}
	else if (situationx == 2)
	{
		move_situation2x(9);

	}
	else if (situationx == 22)
	{
		move_situation22x(9);
	}
	else if (situationx == 3)
	{
		move_situation31(9);
	}
}


void App2::MainPage1::button10_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(10);
	}
	else if (situationx == 11)
	{
		move_situation11x(10);
	}
	else if (situationx == 2)
	{
		move_situation2x(10);

	}
	else if (situationx == 22)
	{
		move_situation22x(10);
	}
	else if (situationx == 3)
	{
		move_situation31(10);
	}
}


void App2::MainPage1::button11_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(11);
	}
	else if (situationx == 11)
	{
		move_situation11x(11);
	}
	else if (situationx == 2)
	{
		move_situation2x(11);

	}
	else if (situationx == 22)
	{
		move_situation22x(11);
	}
	else if (situationx == 3)
	{
		move_situation31(11);
	}
}


void App2::MainPage1::button12_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(12);
	}
	else if (situationx == 11)
	{
		move_situation11x(12);
	}
	else if (situationx == 2)
	{
		move_situation2x(12);

	}
	else if (situationx == 22)
	{
		move_situation22x(12);
	}
	else if (situationx == 3)
	{
		move_situation31(12);
	}
}


void App2::MainPage1::button13_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(13);
	}
	else if (situationx == 11)
	{
		move_situation11x(13);
	}
	else if (situationx == 2)
	{
		move_situation2x(13);

	}
	else if (situationx == 22)
	{
		move_situation22x(13);
	}
	else if (situationx == 3)
	{
		move_situation31(13);
	}
}


void App2::MainPage1::button14_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(14);
	}
	else if (situationx == 11)
	{
		move_situation11x(14);
	}
	else if (situationx == 2)
	{
		move_situation2x(14);

	}
	else if (situationx == 22)
	{
		move_situation22x(14);
	}
	else if (situationx == 3)
	{
		move_situation31(14);
	}
}


void App2::MainPage1::button15_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(15);
	}
	else if (situationx == 11)
	{
		move_situation11x(15);
	}
	else if (situationx == 2)
	{
		move_situation2x(15);

	}
	else if (situationx == 22)
	{
		move_situation22x(15);
	}
	else if (situationx == 3)
	{
		move_situation31(15);
	}
}


void App2::MainPage1::button16_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(16);
	}
	else if (situationx == 11)
	{
		move_situation11x(16);
	}
	else if (situationx == 2)
	{
		move_situation2x(16);

	}
	else if (situationx == 22)
	{
		move_situation22x(16);
	}
	else if (situationx == 3)
	{
		move_situation31(16);
	}
}


void App2::MainPage1::button17_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(17);
	}
	else if (situationx == 11)
	{
		move_situation11x(17);
	}
	else if (situationx == 2)
	{
		move_situation2x(17);

	}
	else if (situationx == 22)
	{
		move_situation22x(17);
	}
	else if (situationx == 3)
	{
		move_situation31(17);
	}
}


void App2::MainPage1::button18_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(18);
	}
	else if (situationx == 11)
	{
		move_situation11x(18);
	}
	else if (situationx == 2)
	{
		move_situation2x(18);

	}
	else if (situationx == 22)
	{
		move_situation22x(18);
	}
	else if (situationx == 3)
	{
		move_situation31(18);
	}
}


void App2::MainPage1::button19_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(19);
	}
	else if (situationx == 11)
	{
		move_situation11x(19);
	}
	else if (situationx == 2)
	{
		move_situation2x(19);

	}
	else if (situationx == 22)
	{
		move_situation22x(19);
	}
	else if (situationx == 3)
	{
		move_situation31(19);
	}
}


void App2::MainPage1::button20_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(20);
	}
	else if (situationx == 11)
	{
		move_situation11x(20);
	}
	else if (situationx == 2)
	{
		move_situation2x(20);

	}
	else if (situationx == 22)
	{
		move_situation22x(20);
	}
	else if (situationx == 3)
	{
		move_situation31(20);
	}
}


void App2::MainPage1::button21_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(21);
	}
	else if (situationx == 11)
	{
		move_situation11x(21);
	}
	else if (situationx == 2)
	{
		move_situation2x(21);

	}
	else if (situationx == 22)
	{
		move_situation22x(21);
	}
	else if (situationx == 3)
	{
		move_situation31(21);
	}
}


void App2::MainPage1::button22_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(22);
	}
	else if (situationx == 11)
	{
		move_situation11x(22);
	}
	else if (situationx == 2)
	{
		move_situation2x(22);

	}
	else if (situationx == 22)
	{
		move_situation22x(22);
	}
	else if (situationx == 3)
	{
		move_situation31(22);
	}
}


void App2::MainPage1::button23_Click1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situationx == 1)
	{
		move_situation1x(23);
	}
	else if (situationx == 11)
	{
		move_situation11x(23);
	}
	else if (situationx == 2)
	{
		move_situation2x(23);

	}
	else if (situationx == 22)
	{
		move_situation22x(23);
	}
	else if (situationx == 3)
	{
		move_situation31(23);
	}
}
