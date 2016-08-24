//
// North.xaml.cpp
// Implementation of the North class
//

#include "pch.h"
#include "North.xaml.h"
#include <stdlib.h>
#include <time.h>
#include <math.h>

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

void end_check();
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238
bool turn1 = false;
Button ^buttonx[10][11];
int dist[10];
int test_dist[10];
int human_position[10];
int computer_position[10];
//TextBlock ^text1;
int comp_or_human = 1;
Image ^token[10][2];
double position[10][11][2];
Image ^starks[4];
Image ^lannisters[4];
int random = 1;
Shapes::Rectangle ^R12y;
Image ^p1y, ^p2y;
void gameOver2(bool player)
{
	R12y->Margin = Thickness(48, 406, 0, 0);
	if (player)
		p1y->Margin = Thickness(102, 500, 0, 0);
	else
		p2y->Margin = Thickness(102, 500, 0, 0);
}
void create_test_dist()
{
	for (int i = 0; i < 10; i++)
		test_dist[i] = dist[i];
}

void update_dist()
{
	for (int i = 0; i < 10; i++)
	{
		if (human_position[i] > computer_position[i])
			dist[i] = human_position[i] - computer_position[i] - 1;
		else
			dist[i] = computer_position[i] - human_position[i] - 1;
	}
}

void update_clickable()
{
	if (comp_or_human == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				buttonx[i][j]->IsEnabled = true;
			}

			if (human_position[i] > computer_position[i])
			{
				for (int j = 0; j <= computer_position[i]; j++)
				{
					buttonx[i][j]->IsEnabled = false;
				}
			}
			else
			{
				for (int j = computer_position[i]; j <11; j++)
				{
					buttonx[i][j]->IsEnabled = false;
				}
			}
			buttonx[i][human_position[i]]->IsEnabled = false;
		}
		//	turn1 = !turn1;
	}

	else
	{
		if (!turn1)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					buttonx[i][j]->IsEnabled = true;
				}

				if (human_position[i] > computer_position[i])
				{
					for (int j = 0; j <= computer_position[i]; j++)
					{
						buttonx[i][j]->IsEnabled = false;
					}
				}
				else
				{
					for (int j = computer_position[i]; j <11; j++)
					{
						buttonx[i][j]->IsEnabled = false;
					}
				}
				buttonx[i][human_position[i]]->IsEnabled = false;
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					buttonx[i][j]->IsEnabled = true;
				}

				if (human_position[i] > computer_position[i])
				{
					for (int j = human_position[i]; j <11; j++)
					{
						buttonx[i][j]->IsEnabled = false;
					}
				}
				else
				{
					for (int j = 0; j <= human_position[i]; j++)
					{
						buttonx[i][j]->IsEnabled = false;
					}
				}
				buttonx[i][computer_position[i]]->IsEnabled = false;
			}
		}
	}
}

void generate_random_board()
{
	memset(human_position, -1, 10);
	memset(computer_position, -1, 10);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			buttonx[i][j]->Content = "";
		}
	}
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		human_position[i] = rand() % 11;
		computer_position[i] = rand() % 11;

		bool x = false;
		if (human_position[i] == computer_position[i])
			x = true;
		while (x)
		{
			computer_position[i] = rand() % 11;
			if (computer_position[i] != human_position[i])
				x = false;
		}
		buttonx[i][human_position[i]]->Content = "H";
		token[i][0]->Margin = Thickness(position[i][human_position[i]][0], position[i][human_position[i]][1], 0, 0);
		buttonx[i][computer_position[i]]->Content = "C";
		token[i][1]->Margin = Thickness(position[i][computer_position[i]][0], position[i][computer_position[i]][1], 0, 0);
	}
	update_dist();
	update_clickable();
}

North::North()
{
	InitializeComponent();
	//text1 = textBlock;
	R12y = R1y;
	p1y = imagep1y;
	p2y = imagep2y;
	starks[0] = quote1;
	starks[1] = quote2;
	starks[2] = quote3;
	starks[3] = quote4;

	lannisters[0] = quote5;
	lannisters[1] = quote6;
	lannisters[2] = quote7;
	lannisters[3] = quote8;

	buttonx[0][0] = button00;
	buttonx[0][1] = button01;
	buttonx[0][2] = button02;
	buttonx[0][3] = button03;
	buttonx[0][4] = button04;
	buttonx[0][5] = button05;
	buttonx[0][6] = button06;
	buttonx[0][7] = button07;
	buttonx[0][8] = button08;
	buttonx[0][9] = button09;
	buttonx[0][10] = button010;
	buttonx[1][0] = button10;
	buttonx[1][1] = button11;
	buttonx[1][2] = button12;
	buttonx[1][3] = button13;
	buttonx[1][4] = button14;
	buttonx[1][5] = button15;
	buttonx[1][6] = button16;
	buttonx[1][7] = button17;
	buttonx[1][8] = button18;
	buttonx[1][9] = button19;
	buttonx[1][10] = button110;
	buttonx[2][0] = button20;
	buttonx[2][1] = button21;
	buttonx[2][2] = button22;
	buttonx[2][3] = button23;
	buttonx[2][4] = button24;
	buttonx[2][5] = button25;
	buttonx[2][6] = button26;
	buttonx[2][7] = button27;
	buttonx[2][8] = button28;
	buttonx[2][9] = button29;
	buttonx[2][10] = button210;
	buttonx[3][0] = button30;
	buttonx[3][1] = button31;
	buttonx[3][2] = button32;
	buttonx[3][3] = button33;
	buttonx[3][4] = button34;
	buttonx[3][5] = button35;
	buttonx[3][6] = button36;
	buttonx[3][7] = button37;
	buttonx[3][8] = button38;
	buttonx[3][9] = button39;
	buttonx[3][10] = button310;
	buttonx[4][0] = button40;
	buttonx[4][1] = button41;
	buttonx[4][2] = button42;
	buttonx[4][3] = button43;
	buttonx[4][4] = button44;
	buttonx[4][5] = button45;
	buttonx[4][6] = button46;
	buttonx[4][7] = button47;
	buttonx[4][8] = button48;
	buttonx[4][9] = button49;
	buttonx[4][10] = button410;
	buttonx[5][0] = button50;
	buttonx[5][1] = button51;
	buttonx[5][2] = button52;
	buttonx[5][3] = button53;
	buttonx[5][4] = button54;
	buttonx[5][5] = button55;
	buttonx[5][6] = button56;
	buttonx[5][7] = button57;
	buttonx[5][8] = button58;
	buttonx[5][9] = button59;
	buttonx[5][10] = button510;
	buttonx[6][0] = button60;
	buttonx[6][1] = button61;
	buttonx[6][2] = button62;
	buttonx[6][3] = button63;
	buttonx[6][4] = button64;
	buttonx[6][5] = button65;
	buttonx[6][6] = button66;
	buttonx[6][7] = button67;
	buttonx[6][8] = button68;
	buttonx[6][9] = button69;
	buttonx[6][10] = button610;
	buttonx[7][0] = button70;
	buttonx[7][1] = button71;
	buttonx[7][2] = button72;
	buttonx[7][3] = button73;
	buttonx[7][4] = button74;
	buttonx[7][5] = button75;
	buttonx[7][6] = button76;
	buttonx[7][7] = button77;
	buttonx[7][8] = button78;
	buttonx[7][9] = button79;
	buttonx[7][10] = button710;
	buttonx[8][0] = button80;
	buttonx[8][1] = button81;
	buttonx[8][2] = button82;
	buttonx[8][3] = button83;
	buttonx[8][4] = button84;
	buttonx[8][5] = button85;
	buttonx[8][6] = button86;
	buttonx[8][7] = button87;
	buttonx[8][8] = button88;
	buttonx[8][9] = button89;
	buttonx[8][10] = button810;
	buttonx[9][0] = button90;
	buttonx[9][1] = button91;
	buttonx[9][2] = button92;
	buttonx[9][3] = button93;
	buttonx[9][4] = button94;
	buttonx[9][5] = button95;
	buttonx[9][6] = button96;
	buttonx[9][7] = button97;
	buttonx[9][8] = button98;
	buttonx[9][9] = button99;
	buttonx[9][10] = button910;
	//const COLORREF MYCOLOR = RGB(0, 0, 0);
	//HBRUSH brush = HBRUSH::brush.CreateSolidBrush(MYCOLOR);
	//button->Background= System::Drawing::Color::Green; 
	//	->Background=(HBRUSH)(RGB(1,2,10));
	token[0][0] = image_human0;
	token[1][0] = image_human1;
	token[2][0] = image_human2;
	token[3][0] = image_human3;
	token[4][0] = image_human4;
	token[5][0] = image_human5;
	token[6][0] = image_human6;
	token[7][0] = image_human7;
	token[8][0] = image_human8;
	token[9][0] = image_human9;
	token[0][1] = image_computer0;
	token[1][1] = image_computer1;
	token[2][1] = image_computer2;
	token[3][1] = image_computer3;
	token[4][1] = image_computer4;
	token[5][1] = image_computer5;
	token[6][1] = image_computer6;
	token[7][1] = image_computer7;
	token[8][1] = image_computer8;
	token[9][1] = image_computer9;

	//485,106,0,0
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			position[i][j][0] = 485 + (j * 50);
			position[i][j][1] = 106 + (i * 50);
		}
	}


	generate_random_board();
	//	turn1 = false;

}


void remove_quote_stark()
{
	for (int i = 0; i < 4; i++)
	{
		starks[i]->Visibility = Visibility(true);
	}
}

void remove_quote_lannister()
{
	for (int i = 0; i < 4; i++)
	{
		lannisters[i]->Visibility = Visibility(true);
	}
}


int xor_without_row(int row)
{
	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == row)
			continue;
		else
			x = x^dist[i];

		return x;
	}
}

void disable_all()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			buttonx[i][j]->IsEnabled = false;
		}
	}
}
int i = 0;
void move_computer()
{
	i++;
	//text1->Text = i.ToString() + "CompMove";
	bool done = false;

	for (int row = 0; row < 10; row++)
	{
		int x = xor_without_row(row);
		if (x < dist[row])
		{
			done = true;
			int y = computer_position[row];
			if (computer_position[row]>human_position[row])
			{
				computer_position[row] = human_position[row] + x + 1;
				buttonx[row][y]->Content = "";
				buttonx[row][computer_position[row]]->Content = "C";
				token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
				update_clickable();
			}
			else
			{
				computer_position[row] = human_position[row] - x - 1;
				buttonx[row][y]->Content = "";
				buttonx[row][computer_position[row]]->Content = "C";
				token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
				update_clickable();
			}
			dist[row] = x;
			//text1->Text += "1. " + row.ToString() + " , " + x.ToString() + " ";
			break;
		}

	}

	if (!done)
	{
		for (int row = 0; row < 10; row++)
		{
			int x = xor_without_row(row);
			if (x > dist[row] && x<((computer_position[row]<human_position[row]) ? (human_position[row] - 1) : (10 - human_position[row] - 1)))
			{
				done = true;
				int y = computer_position[row];
				if (computer_position[row]>human_position[row])
				{
					computer_position[row] = human_position[row] + x + 1;
					buttonx[row][y]->Content = "";
					buttonx[row][computer_position[row]]->Content = "C";
					token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
					update_clickable();
				}
				else
				{
					computer_position[row] = human_position[row] - x - 1;
					buttonx[row][y]->Content = "";
					buttonx[row][computer_position[row]]->Content = "C";
					token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
					update_clickable();
				}
				dist[row] = x;
				//text1->Text += "2. " + row.ToString() + " , " + x.ToString() + " ";
				break;
			}
		}
	}
	if (!done)
	{
		for (int row = 0; row < 10; row++)
		{
			if (dist[row] > 0)
			{
				int x = dist[row] - 1;
				done = true;
				int y = computer_position[row];
				if (computer_position[row]>human_position[row])
				{
					computer_position[row] = human_position[row] + x + 1;
					buttonx[row][y]->Content = "";
					buttonx[row][computer_position[row]]->Content = "C";
					token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
					update_clickable();
				}
				else
				{
					computer_position[row] = human_position[row] - x - 1;
					buttonx[row][y]->Content = "";
					buttonx[row][computer_position[row]]->Content = "C";
					token[row][1]->Margin = Thickness(position[row][computer_position[row]][0], position[row][computer_position[row]][1], 0, 0);
					update_clickable();
				}
				dist[row] = x;
				//text1->Text += " 3." + row.ToString() + " , " + x.ToString() + " ";
				break;
			}
		}
	}

	bool check = true;
	
	/*for (int i = 0; i < 10; i++)
	{
		if (dist[i] != 0)
		{
			check = false;
			break;
		}
	}
	if (check)
	{
		disable_all();
		//computer wins
	}*/

	//text1->Text += "DONE";

	remove_quote_stark();
	remove_quote_lannister();
	if (random % 3 == 0)
	{
		srand(time(NULL));
		int a = rand() % 4;
		lannisters[a]->Visibility = Visibility(false);
	}
	end_check();
}

void end_check()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (buttonx[i][j]->IsEnabled)
				return;
		}
	}
	if (!turn1)
	{
		//text1->Text = "Player 2 Wins";
		gameOver2(false);
	}
	else
	{
		//text1->Text = "Player 1 Wins";
		gameOver2(true);
	}
	return;
}


void chance(int x, int y)
{
	if (comp_or_human == 1)
	{
		random++;
		buttonx[x][human_position[x]]->IsEnabled = true;
		buttonx[x][human_position[x]]->Content = "";
		human_position[x] = y;
		buttonx[x][human_position[x]]->IsEnabled = false;
		buttonx[x][human_position[x]]->Content = "H";
		token[x][0]->Margin = Thickness(position[x][human_position[x]][0], position[x][human_position[x]][1], 0, 0);
		update_dist();
		bool check = true;
		for (int i = 0; i < 10; i++)
		{
			if (dist[i] != 0)
			{
				check = false;
				break;
			}
		}

		end_check();
		move_computer();
		//Sleep(1000);
	}
	else
	{
		turn1 = !turn1;
		random++;
		if (turn1)
		{
			buttonx[x][human_position[x]]->IsEnabled = true;
			buttonx[x][human_position[x]]->Content = "";
			human_position[x] = y;
			buttonx[x][human_position[x]]->IsEnabled = false;
			buttonx[x][human_position[x]]->Content = "H";
			token[x][0]->Margin = Thickness(position[x][human_position[x]][0], position[x][human_position[x]][1], 0, 0);
			update_dist();
			update_clickable();
			bool check = true;
			remove_quote_stark();
			remove_quote_lannister();
			if (random % 3 == 0)
			{
				srand(time(NULL));
				int a = rand() % 4;
				starks[a]->Visibility = Visibility(false);
			}
			end_check();
		}
		else
		{
			buttonx[x][computer_position[x]]->IsEnabled = true;
			buttonx[x][computer_position[x]]->Content = "";
			computer_position[x] = y;
			buttonx[x][computer_position[x]]->IsEnabled = false;
			buttonx[x][computer_position[x]]->Content = "C";
			token[x][1]->Margin = Thickness(position[x][computer_position[x]][0], position[x][computer_position[x]][1], 0, 0);
			update_dist();
			update_clickable();
			bool check = true;
			remove_quote_stark();
			remove_quote_lannister();
			if (random % 3 == 0)
			{
				srand(time(NULL));
				int a = rand() % 4;
				lannisters[a]->Visibility = Visibility(false);
			}
			end_check();
		}
		//	turn1 = !turn1;
	}


}


void App2::North::button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	generate_random_board();
}


void App2::North::button00_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 0);
}


void App2::North::button01_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 1);
}


void App2::North::button02_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 2);
}


void App2::North::button03_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 3);
}


void App2::North::button04_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 4);
}


void App2::North::button05_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 5);
}


void App2::North::button06_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 6);
}


void App2::North::button07_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 7);
}


void App2::North::button08_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 8);
}


void App2::North::button09_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 9);
}


void App2::North::button010_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(0, 10);
}


void App2::North::button10_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 0);
}


void App2::North::button11_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 1);
}


void App2::North::button12_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 2);
}


void App2::North::button13_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 3);
}


void App2::North::button14_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 4);
}


void App2::North::button15_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 5);
}


void App2::North::button16_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 6);
}


void App2::North::button17_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 7);
}


void App2::North::button18_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 8);
}


void App2::North::button19_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 9);
}


void App2::North::button110_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(1, 10);
}


void App2::North::button20_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 0);
}


void App2::North::button21_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 1);
}


void App2::North::button22_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 2);
}


void App2::North::button23_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 3);
}


void App2::North::button24_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 4);
}


void App2::North::button25_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 5);
}


void App2::North::button26_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 6);
}


void App2::North::button27_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 7);
}


void App2::North::button28_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 8);
}


void App2::North::button29_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 9);
}


void App2::North::button210_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(2, 10);
}


void App2::North::button30_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 0);
}


void App2::North::button31_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 1);
}


void App2::North::button32_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 2);
}


void App2::North::button33_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 3);
}


void App2::North::button34_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 4);
}


void App2::North::button35_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 5);
}


void App2::North::button36_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 6);
}


void App2::North::button37_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 7);
}


void App2::North::button38_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 8);
}


void App2::North::button39_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 9);
}


void App2::North::button310_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(3, 10);
}


void App2::North::button40_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 0);
}


void App2::North::button41_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 1);
}


void App2::North::button42_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 2);
}


void App2::North::button43_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 3);
}



void App2::North::button44_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 4);
}


void App2::North::button45_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 5);
}


void App2::North::button46_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 6);
}


void App2::North::button47_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 7);
}


void App2::North::button48_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 8);
}


void App2::North::button49_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 9);
}


void App2::North::button410_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(4, 10);
}


void App2::North::button50_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 0);
}


void App2::North::button51_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 1);
}


void App2::North::button52_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 2);
}


void App2::North::button53_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 3);
}


void App2::North::button54_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 4);
}


void App2::North::button55_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 5);
}


void App2::North::button56_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 6);
}


void App2::North::button57_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 7);
}


void App2::North::button58_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 8);
}


void App2::North::button59_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 9);
}


void App2::North::button510_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(5, 10);
}


void App2::North::button60_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 0);
}


void App2::North::button61_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 1);
}


void App2::North::button62_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 2);
}


void App2::North::button63_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 3);
}


void App2::North::button64_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 4);
}


void App2::North::button65_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 5);
}


void App2::North::button66_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 6);
}


void App2::North::button67_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 7);
}


void App2::North::button68_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 8);
}


void App2::North::button69_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 9);
}


void App2::North::button610_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(6, 10);
}


void App2::North::button70_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 0);
}


void App2::North::button71_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 1);
}


void App2::North::button72_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 2);
}


void App2::North::button73_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 3);
}


void App2::North::button74_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 4);
}


void App2::North::button75_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 5);
}


void App2::North::button76_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 6);
}


void App2::North::button77_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 7);
}


void App2::North::button78_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 8);
}


void App2::North::button79_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 9);
}


void App2::North::button710_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(7, 10);
}


void App2::North::button80_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 0);
}


void App2::North::button81_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 1);
}


void App2::North::button82_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 2);
}


void App2::North::button83_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 3);
}


void App2::North::button84_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 4);
}


void App2::North::button85_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 5);
}


void App2::North::button86_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 6);
}


void App2::North::button87_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 7);
}


void App2::North::button88_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 8);
}


void App2::North::button89_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 9);
}


void App2::North::button810_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(8, 10);
}


void App2::North::button90_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 0);
}


void App2::North::button91_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 1);
}


void App2::North::button92_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 2);
}


void App2::North::button93_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 3);
}


void App2::North::button94_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 4);
}


void App2::North::button95_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 5);
}


void App2::North::button96_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 6);
}


void App2::North::button97_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 7);
}


void App2::North::button98_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 8);
}


void App2::North::button99_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 9);
}


void App2::North::button910_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance(9, 10);
}


void App2::North::button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(FirstPage::typeid));
}
