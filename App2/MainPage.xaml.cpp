//
// MainPage.xaml.cpp
// Implementation of the MainPage class.
//

#include "pch.h"
#include "MainPage.xaml.h"
#include "P1.xaml.h"
#include "P2.xaml.h"
//#include "afxwin.h"
#include <string.h>
#include <stdlib.h>
#include <string>
#include "board.h"
#include "move.h"
#include "gamecontroller.h"
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
int tokenval[24], placed1 = 0, placed2 = 0, captured1 = 0, captured2 = 0;
bool turn = true;
bool situation3_turn, situation34 = false;
int situation = 1;
//Image* token1[9], token2[9];
double position[24][2];
Image ^token1[9], ^token2[9], ^quote1[4], ^quote2[4];
Button ^button[24];
MediaElement ^mek, ^mem;

void move_situation11(int index);
void move_situation1(int index);

void move_situation22(int index);
void move_situation2(int index);

string map1[24] = {
	"A1","D1","G1","B2","D2","F2","C3","D3","E3","A4","B4","C4",
	"E4","F4","G4","C5","D5","E5","B6","D6","F6","A7","D7","G7"
};

string stark[4] = {
	"Winter is indeed coming!", "By the old Gods and new, kill him!",
	"Long live King of the North!", "Slay that bastard!"
};

string lannister[4] = {
	"The debt is paid.", "Let's show 'em how it's done in King's Landing!",
	"Hear us roar!", "Time for a long summer!"
};

int player_move, player_move_from, player_cut, com_move, com_cut;

int what_move_num(string to_find)
{
	for (int i = 0; i < 24; i++)
	{
		if (map1[i] == to_find)
			return i;
	}
	return -1;
}

int pos1[9][2] = {
	{1250,429},
	{1330,429},
	{1410,429},
	{1250,509},
	{1330,509},
	{1410,509},
	{1250,589},
	{1330,589},
	{1410,589}
}
, pos2[9][2] = {
	{216,244},
	{136,244},
	{56,244},
	{216,164},
	{136,164},
	{56,164},
	{216,84},
	{136,84},
	{56,84}
};

int movement[24][4] = {
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
//TextBlock ^textblock12;
int mill[24][2][2] = {
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
int select_pos = -1, select_img_no = -1;
int image_corr_button[24];
int cutchances = 0, no_in_mill2 = 0, no_in_mill1 = 0;
//TextBox ^textbox1;
Shapes::Rectangle ^R12;
GameController *game;
Image ^p1, ^p2;

MainPage::MainPage()
{
	InitializeComponent();
	R12 = R1;
	p1 = imagep1;
	p2 = imagep2;
	mek = mediaElementk;
	mem = mediaElementm;
	for (int i = 0; i < 24; i++)
	{
		tokenval[i] = 0;
		image_corr_button[i] = -1;
	};

	//textblock12 = textBlock12;
	position[0][0] = 452 - 15;
	position[0][1] = 72.5 - 15;
	position[1][0] = 732 - 15;
	position[1][1] = 72.5 - 15;
	position[2][0] = 1012 - 15;
	position[2][1] = 72.5 - 15;
	position[3][0] = 532 - 15;
	position[3][1] = 152 - 15;
	position[4][0] = 732 - 15;
	position[4][1] = 152 - 15;
	position[5][0] = 932 - 15;
	position[5][1] = 152 - 15;
	position[6][0] = 612 - 15;
	position[6][1] = 232.5 - 15;
	position[7][0] = 732 - 15;
	position[7][1] = 232.5 - 15;
	position[8][0] = 852 - 15;
	position[8][1] = 232.5 - 15;
	position[9][0] = 452 - 15;
	position[9][1] = 352.5 - 15;
	position[10][0] = 532 - 15;
	position[10][1] = 352.5 - 15;
	position[11][0] = 612 - 15;
	position[11][1] = 352.5 - 15;
	position[12][0] = 852 - 15;
	position[12][1] = 352.5 - 15;
	position[13][0] = 932 - 15;
	position[13][1] = 352.5 - 15;
	position[14][0] = 1012 - 15;
	position[14][1] = 352.5 - 15;
	position[15][0] = 612 - 15;
	position[15][1] = 472.5 - 15;
	position[16][0] = 732 - 15;
	position[16][1] = 472.5 - 15;
	position[17][0] = 852 - 15;
	position[17][1] = 472.5 - 15;
	position[18][0] = 532 - 15;
	position[18][1] = 552.5 - 15;
	position[19][0] = 732 - 15;
	position[19][1] = 552.5 - 15;
	position[20][0] = 932 - 15;
	position[20][1] = 552.5 - 15;
	position[21][0] = 452 - 15;
	position[21][1] = 632.5 - 15;
	position[22][0] = 732 - 15;
	position[22][1] = 632.5 - 15;
	position[23][0] = 1012 - 15;
	position[23][1] = 632.5 - 15;
	//token1[0]=
	//array< Image^ >^ local = gcnew array< MyClass^ >(ARRAY_SIZE);
	//Array<Image, 9> token1;
	//token1[0]= &image11;

	//textBlock12->Text = "vadh(char)cutchances";

	quote1[0] = image1_1;
	quote1[1] = image1_2;
	quote1[2] = image1_3;
	quote1[3] = image1_4;

	quote2[0] = image2_1;
	quote2[1] = image2_2;
	quote2[2] = image2_3;
	quote2[3] = image2_4;


	token1[0] = image11;
	token1[1] = image12;
	token1[2] = image13;
	token1[3] = image14;
	token1[4] = image15;
	token1[5] = image16;
	token1[6] = image17;
	token1[7] = image18;
	token1[8] = image19;

	token2[0] = image21;
	token2[1] = image22;
	token2[2] = image23;
	token2[3] = image24;
	token2[4] = image25;
	token2[5] = image26;
	token2[6] = image27;
	token2[7] = image28;
	token2[8] = image29;

	button[0] = button0;
	button[1] = button1;
	button[2] = button2;
	button[3] = button3;
	button[4] = button4;
	button[5] = button5;
	button[6] = button6;
	button[7] = button7;
	button[8] = button8;
	button[9] = button9;
	button[10] = button10;
	button[11] = button11;
	button[12] = button12;
	button[13] = button13;
	button[14] = button14;
	button[15] = button15;
	button[16] = button16;
	button[17] = button17;
	button[18] = button18;
	button[19] = button19;
	button[20] = button20;
	button[21] = button21;
	button[22] = button22;
	button[23] = button23;

	int timel = 1;
	game = new GameController(timel, 'H', 'W');
	//textBlock12->Text = "started";
}

void disable_all_buttons()
{
	for (int i = 0; i < 24; i++)
	{
		button[i]->IsEnabled = false;
	}
}

void hide_empty()
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] != 0 || button[i]->IsEnabled == false)
		{
			button[i]->Opacity = 0;
		}
		else
		{
			button[i]->Opacity = 1;
		}
	}
}

bool is_valid_p1_moves()
{

	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] > 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (movement[i][j] >= 0)
				{
					if (tokenval[movement[i][j]] == 0)
						return true;
				}
			}
		}
	}
	return false;

}
bool is_valid_p2_moves()
{

	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] < 0)
		{
			for (int j = 0; j < 4; j++)
			{
				if (movement[i][j] >= 0)
				{
					if (tokenval[movement[i][j]] == 0)
						return true;
				}
			}
		}
	}
	return false;

}
int checkmill(int index, bool value)
{
	int result = 0;
	if (!value)
	{
		tokenval[index] = 0;// (value) ? ((turn) ? 2 : -2) : 0;
		turn = !turn;

		//textblock12->Text += " t " + turn.ToString() + " ";
	}
	if (turn)
	{
		if (tokenval[mill[index][0][0]] > 0 && tokenval[mill[index][0][1]]>0)
		{
			tokenval[mill[index][0][0]] = (value) ? 2 : ((checkmill(mill[index][0][0], true)>0) ? 2 : 1);

			tokenval[mill[index][0][1]] = (value) ? 2 : ((checkmill(mill[index][0][1], true)>0) ? 2 : 1);
			if (value)
				tokenval[index] = 2;
			result++;
		}
		if (tokenval[mill[index][1][0]] > 0 && tokenval[mill[index][1][1]]>0)
		{

			tokenval[mill[index][1][0]] = (value) ? 2 : ((checkmill(mill[index][1][0], true)>0) ? 2 : 1);

			tokenval[mill[index][1][1]] = (value) ? 2 : ((checkmill(mill[index][1][1], true)>0) ? 2 : 1);
			if (value)
				tokenval[index] = 2;
			result++;
		}
	}
	else
	{
		if (tokenval[mill[index][0][0]] <0 && tokenval[mill[index][0][1]]<0)
		{
			tokenval[mill[index][0][0]] = (value) ? -2 : ((checkmill(mill[index][0][0], true)>0) ? -2 : -1);

			tokenval[mill[index][0][1]] = (value) ? -2 : ((checkmill(mill[index][0][1], true)>0) ? -2 : -1);
			result++;
			if (value)
				tokenval[index] = -2;
		}
		if (tokenval[mill[index][1][0]] < 0 && tokenval[mill[index][1][1]]<0)
		{
			tokenval[mill[index][1][0]] = (value) ? -2 : ((checkmill(mill[index][1][0], true)>0) ? -2 : -1);

			tokenval[mill[index][1][1]] = (value) ? -2 : ((checkmill(mill[index][1][1], true)>0) ? -2 : -1);
			result++;
			if (value)
				tokenval[index] = -2;
		}

	}
	if (!value)
	{
		turn = !turn;
		//textblock12->Text += " t " + turn.ToString() + " ";
	}
	return result;
}
void p1clickable(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] > 0)
		{
			button[i]->IsEnabled = clickmode;

		}
	}
}
void p2clickable(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] < 0)
		{
			button[i]->IsEnabled = clickmode;
		}

	}
}
int calc_num_mill()
{
	int result = 0;
	for (int i = 0; i < 24; i++)
	{
		if (turn && tokenval[i] == -2)
			result++;
		if (!turn && tokenval[i] == 2)
			result++;

	}
	return result;
}
void p2notmillclickable(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] == -1)
		{
			button[i]->IsEnabled = clickmode;

		}
	}
}

void p1notmillclickable(bool clickmode)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] == 1)
		{
			button[i]->IsEnabled = clickmode;

		}
	}
}
void dotsclickable(bool emptydotsclick)
{
	for (int i = 0; i < 24; i++)
	{
		if (tokenval[i] == 0)
		{
			button[i]->IsEnabled = emptydotsclick;
		}
	}
}
/*
void App2::MainPage::f1()
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(P1::typeid));
}

void App2::MainPage::f2()
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(P2::typeid));
}
*/
void gameOver(bool player)
{
	R12->Margin=Thickness(48, 406, 0, 0);
	if(player)
		p1->Margin= Thickness(102, 500, 0, 0);
	else
		p2->Margin = Thickness(102, 500, 0, 0);
	/*for (int i = 0; i < 9; i++)
	{
		token1[i]->Visibility = Visibility(true);
		token2[i]->Visibility = Visibility(true);
	//	quote1[i]->Visibility = Visibility(true);
		//quote2[i]->Visibility = Visibility(true);
	}
	for (int i = 0; i < 4; i++)
	{
	//	token1[i]->Visibility = Visibility(true);
		//token2[i]->Visibility = Visibility(true);
		quote1[i]->Visibility = Visibility(true);
		quote2[i]->Visibility = Visibility(true);
	}
	for (int i = 0; i < 24; i++)
	{
		button[i]->Visibility = Visibility(true);
	}*/

}
void move_situation1(int index)
{
	//textblock12->Text = "abcxyz" + situation.ToString();
	if (turn)
	{
		tokenval[index] = 1;//player 1 placed
		hide_empty();

		//textblock12->Text = "abcxyz" + situation.ToString();
		token1[placed1]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
		image_corr_button[index] = placed1;
		placed1++;

	}
	else
	{
		tokenval[index] = -1;//player 2 placed
		hide_empty();

		token2[placed2]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
		image_corr_button[index] = placed2;
		placed2++;
	}
	button[index]->IsEnabled = false;
	cutchances = checkmill(index, true);

	if (cutchances > 0)
	{

		situation = 11;
		player_move = index;
		if (turn)
		{
			p1clickable(false);
			dotsclickable(false);
			no_in_mill2 = calc_num_mill();
			//		textblock12->Text= ("\nplaced2:" + placed2 + "\ncaptured2:" + captured2 + " nummill2" + no_in_mill2);
			if (placed2 - captured2 == no_in_mill2)
			{
				p2clickable(true);
			}
			else
			{
				p2notmillclickable(true);
			}
		}
		else
		{

			p2clickable(false);
			dotsclickable(false);
			no_in_mill1 = calc_num_mill();
			//	textblock12->Text += ("\nplaced1:" + placed1 + "\ncaptured1:" + captured1 + " nummill1" + no_in_mill1);

			if (placed1 - captured1 == no_in_mill1)
			{
				p1clickable(true);
			}
			else
			{
				p1notmillclickable(true);
			}

			move_situation11(com_cut);
			//Sleep(2000);
		}
		hide_empty();
		return;
	}
	else
	{
		turn = !turn;
		if (!turn)
		{
			string x = game->move(map1[index]);
			if (x.length() > 2)
			{
				com_move = what_move_num(x.substr(0, 2));
				com_cut = what_move_num(x.substr(3, 2));
			}
			else
				com_move = what_move_num(x);
			wstring ws;
			ws.assign(x.begin(), x.end());
			//textblock12->Text = "h" + ref new Platform::String(ws.c_str()) + "h";
			move_situation1(com_move);
		}
	}
	if (placed2 == 9)
	{
		situation = 2;
		p1clickable(true);
		dotsclickable(false);
		hide_empty();
	}
}

void move_situation11(int index)
{
	//textblock12->Text += "abcxyz" + situation.ToString();

	cutchances = 0;

	checkmill(index, false);

	if (turn)
	{
		int x = captured2 % 4;
		for (int i = 0; i < 4; i++)
			quote1[i]->Visibility = Visibility(true);
		quote1[x]->Visibility = Visibility(false);
		captured2++;
		//textblock12->Text += "xyz";
	//	token2[image_corr_button[index]]->Visibility = Visibility(true);
		token2[image_corr_button[index]]->Margin = Thickness(pos1[captured2-1][0], pos1[captured2-1][1], 0, 0);
		//token2[image_corr_button[index]]->Margin = Thickness(50000, 50000,0,0);
	}
	else
	{
		int x = captured1 % 4;
		for (int i = 0; i < 4; i++)
			quote2[i]->Visibility = Visibility(true);
		quote2[x]->Visibility = Visibility(false);
		captured1++;
		//textblock12->Text += "xyz";

		//token1[image_corr_button[index]]->Visibility = Visibility(true);
		token1[image_corr_button[index]]->Margin = Thickness(pos2[captured1][0], pos2[captured1][1], 0, 0);

	}
	mek->Play();
	mek->Play();
	if (cutchances == 0)
	{
		if (placed2 == 9)
		{
			situation = 2;
			p1clickable(true);
			dotsclickable(false);

		}
		else
		{
			situation = 1;
			p1clickable(false);
			p2clickable(false);
			dotsclickable(true);

		}
		hide_empty();
		turn = !turn;
		if (!turn)
		{
			string x = game->move(map1[player_move] + "," + map1[index]);
			if (x.length() > 2)
			{
				com_move = what_move_num(x.substr(0, 2));
				com_cut = what_move_num(x.substr(3, 2));
			}
			else
				com_move = what_move_num(x);
			move_situation1(com_move);
			//textblock12->Text += " t " + turn.ToString() + " ";

		}
	}

}


void enable_adjacent(int index)
{
	for (int i = 0; i < 4; i++)
	{
		if (movement[index][i] != -1)
		{
			button[movement[index][i]]->IsEnabled = true;
		}
	}
}

void move_situation22(int index)
{
	//textblock12->Text += "abcxyz" + situation.ToString();

	cutchances = 0;

	checkmill(index, false);
	situation = 2;
	if (turn)
	{
		int x = captured2 % 4;
		for (int i = 0; i < 4; i++)
			quote1[i]->Visibility = Visibility(true);
		quote1[x]->Visibility = Visibility(false);
		captured2++;
		//textblock12->Text += "xyz";
//		token2[image_corr_button[index]]->Visibility = Visibility(true);
		token2[image_corr_button[index]]->Margin = Thickness(pos1[captured2-1][0], pos1[captured2-1][1], 0, 0);

//mek->Play(); mek->Play();
		player_cut = index;
		if (captured2 > 6)
		{
			//textblock12->Text = "Playe 1 Won";
			
			disable_all_buttons();
			Sleep(2000);
			gameOver(true);

		}
	}
	else
	{
		int x = captured1 % 4;
		for (int i = 0; i < 4; i++)
			quote2[i]->Visibility = Visibility(true);
		quote2[x]->Visibility = Visibility(false);
		captured1++;
		//textblock12->Text += "xyz";
//		token1[image_corr_button[index]]->Visibility = Visibility(true);
		token1[image_corr_button[index]]->Margin = Thickness(pos2[captured1-1][0], pos2[captured1-1][1], 0, 0);


		if (captured1 > 6)
		{
			//textblock12->Text = "Playe 2 Won";
			disable_all_buttons();
			Sleep(2000);
			gameOver(false);

		}
	}
	mek->Play(); mek->Play();
	if (cutchances == 0)
	{

		situation = 2;
		//if(turn)
		p1clickable(!turn);
		p2clickable(turn);
		dotsclickable(false);
		//turn = !turn;
		//textblock12->Text += " t " + turn.ToString() + " ";
		select_pos = -1;

		if (captured1 >= 6 || captured2 >= 6)
		{
			situation = 3;

			if (captured1 >= 6 && captured2 >= 6)
				situation34 = true;
			if (captured1 >= 6)
				situation3_turn = true;
			else
				situation3_turn = false;

		}

		turn = !turn;
		if (turn)
		{
			if (!is_valid_p1_moves())
			{
				//textblock12->Text = "Player 2 Won";
				//gameOver(false);
				disable_all_buttons();
				Sleep(2000);
				gameOver(false);
			}
		}
		else
		{
			if (!is_valid_p2_moves())
			{
				//textblock12->Text = "Player 1 Won";
				disable_all_buttons();
				Sleep(2000);
				gameOver(true);

			}
		}
		hide_empty();
		if (!turn)
		{
			string x = game->move(map1[player_move_from] + "-" + map1[player_move] + "," + map1[index]);
			if (x.length() > 5)
			{
				com_move = what_move_num(x.substr(3, 2));
				com_cut = what_move_num(x.substr(6, 2));
			}
			else
				com_move = what_move_num(x.substr(3, 2));
			move_situation2(what_move_num(x.substr(0, 2)));
			wstring ws;
			ws.assign(x.begin(), x.end());
			//textblock12->Text = "hcom_move" + ref new Platform::String(ws.c_str()) + "h";

			//textblock12->Text += " com_mnove " + x+ " ";

		}

	}
}

void move_situation2(int index)
{
	if (select_pos >= 0 && tokenval[index] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			token1[i]->Height = 60;
			token1[i]->Width = 60;
		}
		//textblock12->Text += "s11";
		if (turn)
		{
			token1[select_img_no]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
			tokenval[index] = 1;
			player_move = index;
		}
		else
		{
			token2[select_img_no]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
			tokenval[index] = -1;
		}
		hide_empty();
		tokenval[select_pos] = 0;

		image_corr_button[index] = select_img_no;
		image_corr_button[select_pos] = -1;
		cutchances = checkmill(index, true);

		if (cutchances > 0)
		{
			situation = 22;
			if (turn)
			{
				p1clickable(false);
				dotsclickable(false);
				no_in_mill2 = calc_num_mill();
				//textblock12->Text += (" placed2:" + placed2 + " captured2:" + captured2 + " nummill2" + no_in_mill2);
				if (9 - captured2 == no_in_mill2)
				{
					p2clickable(true);
				}
				else
				{
					p2notmillclickable(true);
				}
			}
			else
			{
				p2clickable(false);
				dotsclickable(false);
				no_in_mill1 = calc_num_mill();
				//textblock12->Text += ("\nplaced1:" + placed1 + "\ncaptured1:" + captured1 + " nummill1" + no_in_mill1);

				if (9 - captured1 == no_in_mill1)
				{
					p1clickable(true);
				}
				else
				{
					p1notmillclickable(true);
				}
				move_situation22(com_cut);
			}
			select_pos = -1;

			return;
		}
		else
		{
			//textblock12->Text += "s12";
			turn = !turn;
			//textblock12->Text += " t " + turn.ToString() + " ";
			dotsclickable(false);
			p1clickable(turn);
			p2clickable(!turn);
			if (turn)
			{
				if (!is_valid_p1_moves())
				{
					//textblock12->Text = "Player 2 Won";
					disable_all_buttons();
					Sleep(2000);
					gameOver(false);

					hide_empty();
				}
			}
			else
			{
				if (!is_valid_p2_moves())
				{
					//textblock12->Text = "Player 1 Won";
					disable_all_buttons();
					Sleep(2000);
					gameOver(true);

					hide_empty();
				}
				string x = game->move(map1[player_move_from] + "-" + map1[player_move]);
				if (x.length() > 5)
				{
					com_move = what_move_num(x.substr(3, 2));
					com_cut = what_move_num(x.substr(6, 2));
				}
				else
					com_move = what_move_num(x.substr(3, 2));
				wstring ws;
				ws.assign(x.begin(), x.end());
				//textblock12->Text = "ah" + ref new Platform::String(ws.c_str()) + "h";
				move_situation2(what_move_num(x.substr(0, 2)));

			}
		}
		select_pos = -1;

	}
	else
	{
		if (turn)
		{
			for (int i = 0; i < 9; i++)
			{
				token1[i]->Height = 60;
				token1[i]->Width = 60;
			}
			token1[image_corr_button[index]]->Height = 75;
			token1[image_corr_button[index]]->Width = 75;
		}
		//textblock12->Text += "s2";
		select_pos = index;
		select_img_no = image_corr_button[index];
		//hide_empty();
		disable_all_buttons();
		enable_adjacent(select_pos);
		p1clickable(turn);
		p2clickable(!turn);
		hide_empty();
		if (turn)
			player_move_from = index;
		else
			move_situation2(com_move);

	}
}
void move_situation3(int index)
{
	/*if (situation3_turn == true && turn)
	{

	}*/
	if (select_pos >= 0 && tokenval[index] == 0)
	{
		for (int i = 0; i < 9; i++)
		{
			token1[i]->Height = 60;
			token1[i]->Width = 60;
		}
		//textblock12->Text += "s11";
		if (turn)
		{
			token1[select_img_no]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
			tokenval[index] = 1;
			player_move = index;
		}
		else
		{
			token2[select_img_no]->Margin = Thickness(position[index][0], position[index][1], 0, 0);
			tokenval[index] = -1;
		}
		tokenval[select_pos] = 0;

		image_corr_button[index] = select_img_no;
		image_corr_button[select_pos] = -1;
		cutchances = checkmill(index, true);

		if (cutchances > 0)
		{
			situation = 22;
			if (turn)
			{
				p1clickable(false);
				dotsclickable(false);
				no_in_mill2 = calc_num_mill();
				//textblock12->Text += (" placed2:" + placed2 + " captured2:" + captured2 + " nummill2" + no_in_mill2);
				if (9 - captured2 == no_in_mill2)
				{
					p2clickable(true);
				}
				else
				{
					p2notmillclickable(true);
				}
			}
			else
			{
				p2clickable(false);
				dotsclickable(false);
				no_in_mill1 = calc_num_mill();
				//textblock12->Text += ("\nplaced1:" + placed1 + "\ncaptured1:" + captured1 + " nummill1" + no_in_mill1);

				if (9 - captured1 == no_in_mill1)
				{
					p1clickable(true);
				}
				else
				{
					p1notmillclickable(true);
				}
				move_situation22(com_cut);
			}
			hide_empty();
			select_pos = -1;
			return;
		}
		else
		{
			//textblock12->Text += "s12";
			turn = !turn;
			//textblock12->Text += " t " + turn.ToString() + " ";
			dotsclickable(false);
			p1clickable(turn);
			p2clickable(!turn);
			hide_empty();
			if (turn)
			{
				if (!is_valid_p1_moves())
				{
					//textblock12->Text = "Player 2 Won";
					disable_all_buttons();
					Sleep(2000);
					gameOver(false);

					hide_empty();
				}
			}
			else
			{
				if (!is_valid_p2_moves())
				{
					//textblock12->Text = "Player 1 Won";
					disable_all_buttons();
					Sleep(2000);
					gameOver(true);

					hide_empty();
				}
				string x = game->move(map1[player_move_from] + "-" + map1[player_move]);
				if (x.length() > 5)
				{
					com_move = what_move_num(x.substr(3, 2));
					com_cut = what_move_num(x.substr(6, 2));
				}
				else
					com_move = what_move_num(x.substr(3, 2));
				wstring ws;
				ws.assign(x.begin(), x.end());
				//textblock12->Text = "ah" + ref new Platform::String(ws.c_str()) + "h";
				move_situation2(what_move_num(x.substr(0, 2)));

			}
		}
		select_pos = -1;

	}
	else
	{
		if (turn)
		{
			for (int i = 0; i < 9; i++)
			{
				token1[i]->Height = 60;
				token1[i]->Width = 60;
			}
			token1[image_corr_button[index]]->Height = 75;
			token1[image_corr_button[index]]->Width = 75;
		}
		//textblock12->Text += "s2";
		select_pos = index;
		select_img_no = image_corr_button[index];
		if (turn == situation3_turn || situation34)
			dotsclickable(true);
		else
			enable_adjacent(select_pos);
		p1clickable(turn);
		p2clickable(!turn);
		if (turn)
			player_move_from = index;
		else
			move_situation2(com_move);
	}

}


void App2::MainPage::button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(0);
	}
	else if (situation == 11)
	{
		move_situation11(0);
	}
	else if (situation == 2)
	{
		move_situation2(0);
	}
	else if (situation == 22)
	{
		move_situation22(0);
	}

	else if (situation == 3)
	{
		move_situation3(0);
	}
}




void App2::MainPage::button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(1);
	}
	else if (situation == 11)
	{
		move_situation11(1);
	}
	else if (situation == 2)
	{
		move_situation2(1);

	}

	else if (situation == 22)
	{
		move_situation22(1);
	}
	else if (situation == 3)
	{
		move_situation3(1);
	}
}


void App2::MainPage::button2_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(2);
	}
	else if (situation == 11)
	{
		move_situation11(2);
	}
	else if (situation == 2)
	{
		move_situation2(2);
	}
	else if (situation == 22)
	{
		move_situation22(2);
	}
	else if (situation == 3)
	{
		move_situation3(2);
	}
}


void App2::MainPage::button3_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(3);
	}
	else if (situation == 11)
	{
		move_situation11(3);
	}
	else if (situation == 2)
	{
		move_situation2(3);

	}

	else if (situation == 22)
	{
		move_situation22(3);
	}
	else if (situation == 3)
	{
		move_situation3(3);
	}
}


void App2::MainPage::button4_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(4);
	}

	else if (situation == 11)
	{
		move_situation11(4);
	}
	else if (situation == 2)
	{
		move_situation2(4);

	}

	else if (situation == 22)
	{
		move_situation22(4);
	}

	else if (situation == 3)
	{
		move_situation3(4);
	}
}


void App2::MainPage::button5_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(5);
	}

	else if (situation == 11)
	{
		move_situation11(5);
	}
	else if (situation == 2)
	{
		move_situation2(5);

	}

	else if (situation == 22)
	{
		move_situation22(5);
	}
	else if (situation == 3)
	{
		move_situation3(5);
	}
}


void App2::MainPage::button6_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(6);
	}

	else if (situation == 11)
	{
		move_situation11(6);
	}
	else if (situation == 2)
	{
		move_situation2(6);

	}

	else if (situation == 22)
	{
		move_situation22(6);
	}
	else if (situation == 3)
	{
		move_situation3(6);
	}
}


void App2::MainPage::button7_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(7);
	}
	else if (situation == 11)
	{
		move_situation11(7);
	}
	else if (situation == 2)
	{
		move_situation2(7);

	}

	else if (situation == 22)
	{
		move_situation22(7);
	}

	else if (situation == 3)
	{
		move_situation3(7);
	}
}


void App2::MainPage::button8_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(8);
	}
	else if (situation == 11)
	{
		move_situation11(8);
	}
	else if (situation == 2)
	{
		move_situation2(8);

	}
	else if (situation == 22)
	{
		move_situation22(8);
	}
	else if (situation == 3)
	{
		move_situation3(8);
	}
}


void App2::MainPage::button9_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(9);
	}
	else if (situation == 11)
	{
		move_situation11(9);
	}
	else if (situation == 2)
	{
		move_situation2(9);

	}
	else if (situation == 22)
	{
		move_situation22(9);
	}
	else if (situation == 3)
	{
		move_situation3(9);
	}
}


void App2::MainPage::button10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(10);
	}
	else if (situation == 11)
	{
		move_situation11(10);
	}
	else if (situation == 2)
	{
		move_situation2(10);

	}
	else if (situation == 22)
	{
		move_situation22(10);
	}
	else if (situation == 3)
	{
		move_situation3(10);
	}
}


void App2::MainPage::button11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(11);
	}
	else if (situation == 11)
	{
		move_situation11(11);
	}
	else if (situation == 2)
	{
		move_situation2(11);

	}
	else if (situation == 22)
	{
		move_situation22(11);
	}
	else if (situation == 3)
	{
		move_situation3(11);
	}
}


void App2::MainPage::button12_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(12);
	}
	else if (situation == 11)
	{
		move_situation11(12);
	}
	else if (situation == 2)
	{
		move_situation2(12);

	}
	else if (situation == 22)
	{
		move_situation22(12);
	}
	else if (situation == 3)
	{
		move_situation3(12);
	}
}


void App2::MainPage::button13_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(13);
	}
	else if (situation == 11)
	{
		move_situation11(13);
	}
	else if (situation == 2)
	{
		move_situation2(13);

	}
	else if (situation == 22)
	{
		move_situation22(13);
	}
	else if (situation == 3)
	{
		move_situation3(13);
	}
}


void App2::MainPage::button14_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(14);
	}
	else if (situation == 11)
	{
		move_situation11(14);
	}
	else if (situation == 2)
	{
		move_situation2(14);

	}
	else if (situation == 22)
	{
		move_situation22(14);
	}
	else if (situation == 3)
	{
		move_situation3(14);
	}
}


void App2::MainPage::button15_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(15);
	}
	else if (situation == 11)
	{
		move_situation11(15);
	}
	else if (situation == 2)
	{
		move_situation2(15);

	}
	else if (situation == 22)
	{
		move_situation22(15);
	}
	else if (situation == 3)
	{
		move_situation3(15);
	}
}


void App2::MainPage::button16_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(16);
	}
	else if (situation == 11)
	{
		move_situation11(16);
	}
	else if (situation == 2)
	{
		move_situation2(16);

	}
	else if (situation == 22)
	{
		move_situation22(16);
	}
	else if (situation == 3)
	{
		move_situation3(16);
	}
}


void App2::MainPage::button17_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(17);
	}
	else if (situation == 11)
	{
		move_situation11(17);
	}
	else if (situation == 2)
	{
		move_situation2(17);

	}
	else if (situation == 22)
	{
		move_situation22(17);
	}
	else if (situation == 3)
	{
		move_situation3(17);
	}
}


void App2::MainPage::button18_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(18);
	}
	else if (situation == 11)
	{
		move_situation11(18);
	}
	else if (situation == 2)
	{
		move_situation2(18);

	}
	else if (situation == 22)
	{
		move_situation22(18);
	}
	else if (situation == 3)
	{
		move_situation3(18);
	}
}


void App2::MainPage::button19_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(19);
	}
	else if (situation == 11)
	{
		move_situation11(19);
	}
	else if (situation == 2)
	{
		move_situation2(19);

	}
	else if (situation == 22)
	{
		move_situation22(19);
	}
	else if (situation == 3)
	{
		move_situation3(19);
	}
}


void App2::MainPage::button20_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(20);
	}
	else if (situation == 11)
	{
		move_situation11(20);
	}
	else if (situation == 2)
	{
		move_situation2(20);

	}
	else if (situation == 22)
	{
		move_situation22(20);
	}
	else if (situation == 3)
	{
		move_situation3(20);
	}
}


void App2::MainPage::button21_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(21);
	}
	else if (situation == 11)
	{
		move_situation11(21);
	}
	else if (situation == 2)
	{
		move_situation2(21);

	}
	else if (situation == 22)
	{
		move_situation22(21);
	}
	else if (situation == 3)
	{
		move_situation3(21);
	}
}


void App2::MainPage::button22_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(22);
	}
	else if (situation == 11)
	{
		move_situation11(22);
	}
	else if (situation == 2)
	{
		move_situation2(22);

	}
	else if (situation == 22)
	{
		move_situation22(22);
	}
	else if (situation == 3)
	{
		move_situation3(22);
	}
}


void App2::MainPage::button23_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	if (situation == 1)
	{
		move_situation1(23);
	}
	else if (situation == 11)
	{
		move_situation11(23);
	}
	else if (situation == 2)
	{
		move_situation2(23);

	}
	else if (situation == 22)
	{
		move_situation22(23);
	}
	else if (situation == 3)
	{
		move_situation3(23);
	}
}
