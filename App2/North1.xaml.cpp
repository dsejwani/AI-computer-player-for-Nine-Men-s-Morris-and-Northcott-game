//
// North1.xaml.cpp
// Implementation of the North class
//

#include "pch.h"
#include "North1.xaml.h"
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

void end_check3();
// The Blank Page item template is documented at http://go.microsoft.com/fwlink/?LinkId=234238
bool turn13 = false;
Button ^buttonx1[10][11];
int dist1[10];
int test_dist1[10];
int human_position1[10];
int computer_position1[10];
//TextBlock ^text11;
int comp_or_human1 = 2;
Image ^token1[10][2];
double position1[10][11][2];
Image ^starks1[4];
Image ^lannisters1[4];
int random3 = 1;
Shapes::Rectangle ^R12z;
Image ^p1z, ^p2z;
void gameOver3(bool player)
{
	R12z->Margin = Thickness(48, 406, 0, 0);
	if (player)
		p1z->Margin = Thickness(102, 500, 0, 0);
	else
		p2z->Margin = Thickness(102, 500, 0, 0);
}
void create_test_dist1()
{
	for (int i = 0; i < 10; i++)
		test_dist1[i] = dist1[i];
}

void update_dist1()
{
	for (int i = 0; i < 10; i++)
	{
		if (human_position1[i] > computer_position1[i])
			dist1[i] = human_position1[i] - computer_position1[i] - 1;
		else
			dist1[i] = computer_position1[i] - human_position1[i] - 1;
	}
}

void update_clickable3()
{
	if (comp_or_human1 == 1)
	{
		for (int i = 0; i < 10; i++)
		{
			for (int j = 0; j < 11; j++)
			{
				buttonx1[i][j]->IsEnabled = true;
			}

			if (human_position1[i] > computer_position1[i])
			{
				for (int j = 0; j <= computer_position1[i]; j++)
				{
					buttonx1[i][j]->IsEnabled = false;
				}
			}
			else
			{
				for (int j = computer_position1[i]; j <11; j++)
				{
					buttonx1[i][j]->IsEnabled = false;
				}
			}
			buttonx1[i][human_position1[i]]->IsEnabled = false;
		}
		//	turn13 = !turn13;
	}

	else
	{
		if (!turn13)
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					buttonx1[i][j]->IsEnabled = true;
				}

				if (human_position1[i] > computer_position1[i])
				{
					for (int j = 0; j <= computer_position1[i]; j++)
					{
						buttonx1[i][j]->IsEnabled = false;
					}
				}
				else
				{
					for (int j = computer_position1[i]; j <11; j++)
					{
						buttonx1[i][j]->IsEnabled = false;
					}
				}
				buttonx1[i][human_position1[i]]->IsEnabled = false;
			}
		}
		else
		{
			for (int i = 0; i < 10; i++)
			{
				for (int j = 0; j < 11; j++)
				{
					buttonx1[i][j]->IsEnabled = true;
				}

				if (human_position1[i] > computer_position1[i])
				{
					for (int j = human_position1[i]; j <11; j++)
					{
						buttonx1[i][j]->IsEnabled = false;
					}
				}
				else
				{
					for (int j = 0; j <= human_position1[i]; j++)
					{
						buttonx1[i][j]->IsEnabled = false;
					}
				}
				buttonx1[i][computer_position1[i]]->IsEnabled = false;
			}
		}
	}
}

void generate_random_board3()
{
	memset(human_position1, -1, 10);
	memset(computer_position1, -1, 10);
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			buttonx1[i][j]->Content = "";
		}
	}
	srand(time(NULL));
	for (int i = 0; i < 10; i++)
	{
		human_position1[i] = rand() % 11;
		computer_position1[i] = rand() % 11;

		bool x = false;
		if (human_position1[i] == computer_position1[i])
			x = true;
		while (x)
		{
			computer_position1[i] = rand() % 11;
			if (computer_position1[i] != human_position1[i])
				x = false;
		}
		buttonx1[i][human_position1[i]]->Content = "H";
		token1[i][0]->Margin = Thickness(position1[i][human_position1[i]][0], position1[i][human_position1[i]][1], 0, 0);
		buttonx1[i][computer_position1[i]]->Content = "C";
		token1[i][1]->Margin = Thickness(position1[i][computer_position1[i]][0], position1[i][computer_position1[i]][1], 0, 0);
	}
	update_dist1();
	update_clickable3();
}

North1::North1()
{
	InitializeComponent();
	//text11 = textBlock3;
	R12z = R1z;
	p1z = imagep1z;
	p2z = imagep2z;
	starks1[0] = quote13;
	starks1[1] = quote23;
	starks1[2] = quote33;
	starks1[3] = quote43;

	lannisters1[0] = quote53;
	lannisters1[1] = quote63;
	lannisters1[2] = quote73;
	lannisters1[3] = quote83;

	buttonx1[0][0] = button003;
	buttonx1[0][1] = button013;
	buttonx1[0][2] = button023;
	buttonx1[0][3] = button033;
	buttonx1[0][4] = button043;
	buttonx1[0][5] = button053;
	buttonx1[0][6] = button063;
	buttonx1[0][7] = button073;
	buttonx1[0][8] = button083;
	buttonx1[0][9] = button093;
	buttonx1[0][10] = button0103;
	buttonx1[1][0] = button103;
	buttonx1[1][1] = button113;
	buttonx1[1][2] = button123;
	buttonx1[1][3] = button133;
	buttonx1[1][4] = button143;
	buttonx1[1][5] = button153;
	buttonx1[1][6] = button163;
	buttonx1[1][7] = button173;
	buttonx1[1][8] = button183;
	buttonx1[1][9] = button193;
	buttonx1[1][10] = button1103;
	buttonx1[2][0] = button203;
	buttonx1[2][1] = button213;
	buttonx1[2][2] = button223;
	buttonx1[2][3] = button233;
	buttonx1[2][4] = button243;
	buttonx1[2][5] = button253;
	buttonx1[2][6] = button263;
	buttonx1[2][7] = button273;
	buttonx1[2][8] = button283;
	buttonx1[2][9] = button293;
	buttonx1[2][10] = button2103;
	buttonx1[3][0] = button303;
	buttonx1[3][1] = button313;
	buttonx1[3][2] = button323;
	buttonx1[3][3] = button333;
	buttonx1[3][4] = button343;
	buttonx1[3][5] = button353;
	buttonx1[3][6] = button363;
	buttonx1[3][7] = button373;
	buttonx1[3][8] = button383;
	buttonx1[3][9] = button393;
	buttonx1[3][10] = button3103;
	buttonx1[4][0] = button403;
	buttonx1[4][1] = button413;
	buttonx1[4][2] = button423;
	buttonx1[4][3] = button433;
	buttonx1[4][4] = button443;
	buttonx1[4][5] = button453;
	buttonx1[4][6] = button463;
	buttonx1[4][7] = button473;
	buttonx1[4][8] = button483;
	buttonx1[4][9] = button493;
	buttonx1[4][10] = button4103;
	buttonx1[5][0] = button503;
	buttonx1[5][1] = button513;
	buttonx1[5][2] = button523;
	buttonx1[5][3] = button533;
	buttonx1[5][4] = button543;
	buttonx1[5][5] = button553;
	buttonx1[5][6] = button563;
	buttonx1[5][7] = button573;
	buttonx1[5][8] = button583;
	buttonx1[5][9] = button593;
	buttonx1[5][10] = button5103;
	buttonx1[6][0] = button603;
	buttonx1[6][1] = button613;
	buttonx1[6][2] = button623;
	buttonx1[6][3] = button633;
	buttonx1[6][4] = button643;
	buttonx1[6][5] = button653;
	buttonx1[6][6] = button663;
	buttonx1[6][7] = button673;
	buttonx1[6][8] = button683;
	buttonx1[6][9] = button693;
	buttonx1[6][10] = button6103;
	buttonx1[7][0] = button703;
	buttonx1[7][1] = button713;
	buttonx1[7][2] = button723;
	buttonx1[7][3] = button733;
	buttonx1[7][4] = button743;
	buttonx1[7][5] = button753;
	buttonx1[7][6] = button763;
	buttonx1[7][7] = button773;
	buttonx1[7][8] = button783;
	buttonx1[7][9] = button793;
	buttonx1[7][10] = button7103;
	buttonx1[8][0] = button803;
	buttonx1[8][1] = button813;
	buttonx1[8][2] = button823;
	buttonx1[8][3] = button833;
	buttonx1[8][4] = button843;
	buttonx1[8][5] = button853;
	buttonx1[8][6] = button863;
	buttonx1[8][7] = button873;
	buttonx1[8][8] = button883;
	buttonx1[8][9] = button893;
	buttonx1[8][10] = button8103;
	buttonx1[9][0] = button903;
	buttonx1[9][1] = button913;
	buttonx1[9][2] = button923;
	buttonx1[9][3] = button933;
	buttonx1[9][4] = button943;
	buttonx1[9][5] = button953;
	buttonx1[9][6] = button963;
	buttonx1[9][7] = button973;
	buttonx1[9][8] = button983;
	buttonx1[9][9] = button993;
	buttonx1[9][10] = button9103;
	//const COLORREF MYCOLOR = RGB(0, 0, 0);
	//HBRUSH brush = HBRUSH::brush.CreateSolidBrush(MYCOLOR);
	//button->Background= System::Drawing::Color::Green; 
	//	->Background=(HBRUSH)(RGB(1,2,10));
	token1[0][0] = image_human03;
	token1[1][0] = image_human13;
	token1[2][0] = image_human23;
	token1[3][0] = image_human33;
	token1[4][0] = image_human43;
	token1[5][0] = image_human53;
	token1[6][0] = image_human63;
	token1[7][0] = image_human73;
	token1[8][0] = image_human83;
	token1[9][0] = image_human93;
	token1[0][1] = image_computer03;
	token1[1][1] = image_computer13;
	token1[2][1] = image_computer23;
	token1[3][1] = image_computer33;
	token1[4][1] = image_computer43;
	token1[5][1] = image_computer53;
	token1[6][1] = image_computer63;
	token1[7][1] = image_computer73;
	token1[8][1] = image_computer83;
	token1[9][1] = image_computer93;
	//485,106,0,0
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			position1[i][j][0] = 485 + (j * 50);
			position1[i][j][1] = 106 + (i * 50);
		}
	}


	generate_random_board3();
	//	turn13 = false;

}


void remove_quote_stark3()
{
	for (int i = 0; i < 4; i++)
	{
		starks1[i]->Visibility = Visibility(true);
	}
}

void remove_quote_lannister3()
{
	for (int i = 0; i < 4; i++)
	{
		lannisters1[i]->Visibility = Visibility(true);
	}
}


int xor_without_row3(int row)
{
	int x = 0;
	for (int i = 0; i < 10; i++)
	{
		if (i == row)
			continue;
		else
			x = x^dist1[i];

		return x;
	}
}

void disable_all3()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			buttonx1[i][j]->IsEnabled = false;
		}
	}
}
int iz1 = 0;
void move_computer3()
{
	iz1++;
	//text11->Text = iz1.ToString() + "CompMove";
	bool done = false;

	for (int row = 0; row < 10; row++)
	{
		int x = xor_without_row3(row);
		if (x < dist1[row])
		{
			done = true;
			int y = computer_position1[row];
			if (computer_position1[row]>human_position1[row])
			{
				computer_position1[row] = human_position1[row] + x + 1;
				buttonx1[row][y]->Content = "";
				buttonx1[row][computer_position1[row]]->Content = "C";
				token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
				update_clickable3();
			}
			else
			{
				computer_position1[row] = human_position1[row] - x - 1;
				buttonx1[row][y]->Content = "";
				buttonx1[row][computer_position1[row]]->Content = "C";
				token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
				update_clickable3();
			}
			dist1[row] = x;
			//text11->Text += "1. " + row.ToString() + " , " + x.ToString() + " ";
			break;
		}

	}

	if (!done)
	{
		for (int row = 0; row < 10; row++)
		{
			int x = xor_without_row3(row);
			if (x > dist1[row] && x<((computer_position1[row]<human_position1[row]) ? (human_position1[row] - 1) : (10 - human_position1[row] - 1)))
			{
				done = true;
				int y = computer_position1[row];
				if (computer_position1[row]>human_position1[row])
				{
					computer_position1[row] = human_position1[row] + x + 1;
					buttonx1[row][y]->Content = "";
					buttonx1[row][computer_position1[row]]->Content = "C";
					token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
					update_clickable3();
				}
				else
				{
					computer_position1[row] = human_position1[row] - x - 1;
					buttonx1[row][y]->Content = "";
					buttonx1[row][computer_position1[row]]->Content = "C";
					token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
					update_clickable3();
				}
				dist1[row] = x;
				//text11->Text += "2. " + row.ToString() + " , " + x.ToString() + " ";
				break;
			}
		}
	}
	if (!done)
	{
		for (int row = 0; row < 10; row++)
		{
			if (dist1[row] > 0)
			{
				int x = dist1[row] - 1;
				done = true;
				int y = computer_position1[row];
				if (computer_position1[row]>human_position1[row])
				{
					computer_position1[row] = human_position1[row] + x + 1;
					buttonx1[row][y]->Content = "";
					buttonx1[row][computer_position1[row]]->Content = "C";
					token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
					update_clickable3();
				}
				else
				{
					computer_position1[row] = human_position1[row] - x - 1;
					buttonx1[row][y]->Content = "";
					buttonx1[row][computer_position1[row]]->Content = "C";
					token1[row][1]->Margin = Thickness(position1[row][computer_position1[row]][0], position1[row][computer_position1[row]][1], 0, 0);
					update_clickable3();
				}
				dist1[row] = x;
				//text11->Text += " 3." + row.ToString() + " , " + x.ToString() + " ";
				break;
			}
		}
	}

	bool check = true;

	/*for (int i = 0; i < 10; i++)
	{
	if (dist1[i] != 0)
	{
	check = false;
	break;
	}
	}
	if (check)
	{
	disable_all3();
	//computer wins
	}*/

	//text11->Text += "DONE";

	remove_quote_stark3();
	remove_quote_lannister3();
	if (random3 % 3 == 0)
	{
		srand(time(NULL));
		int a = rand() % 4;
		lannisters1[a]->Visibility = Visibility(false);
	}
	end_check3();
}

void end_check3()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 11; j++)
		{
			if (buttonx1[i][j]->IsEnabled)
				return;
		}
	}
	if (!turn13)
	{
	//	text11->Text = "Player 2 Wins";
		gameOver3(false);
	}
	else
	{
	//	text11->Text = "Player 1 Wins";
		gameOver3(true);
	}
	return;
}


void chance3(int x, int y)
{
	if (comp_or_human1 == 1)
	{
		random3++;
		buttonx1[x][human_position1[x]]->IsEnabled = true;
		buttonx1[x][human_position1[x]]->Content = "";
		human_position1[x] = y;
		buttonx1[x][human_position1[x]]->IsEnabled = false;
		buttonx1[x][human_position1[x]]->Content = "H";
		token1[x][0]->Margin = Thickness(position1[x][human_position1[x]][0], position1[x][human_position1[x]][1], 0, 0);
		update_dist1();
		bool check = true;
		for (int i = 0; i < 10; i++)
		{
			if (dist1[i] != 0)
			{
				check = false;
				break;
			}
		}

		end_check3();
		move_computer3();
		//Sleep(1000);
	}
	else
	{
		turn13 = !turn13;
		random3++;
		if (turn13)
		{
			buttonx1[x][human_position1[x]]->IsEnabled = true;
			buttonx1[x][human_position1[x]]->Content = "";
			human_position1[x] = y;
			buttonx1[x][human_position1[x]]->IsEnabled = false;
			buttonx1[x][human_position1[x]]->Content = "H";
			token1[x][0]->Margin = Thickness(position1[x][human_position1[x]][0], position1[x][human_position1[x]][1], 0, 0);
			update_dist1();
			update_clickable3();
			bool check = true;
			remove_quote_stark3();
			remove_quote_lannister3();
			if (random3 % 3 == 0)
			{
				srand(time(NULL));
				int a = rand() % 4;
				starks1[a]->Visibility = Visibility(false);
			}
			end_check3();
		}
		else
		{
			buttonx1[x][computer_position1[x]]->IsEnabled = true;
			buttonx1[x][computer_position1[x]]->Content = "";
			computer_position1[x] = y;
			buttonx1[x][computer_position1[x]]->IsEnabled = false;
			buttonx1[x][computer_position1[x]]->Content = "C";
			token1[x][1]->Margin = Thickness(position1[x][computer_position1[x]][0], position1[x][computer_position1[x]][1], 0, 0);
			update_dist1();
			update_clickable3();
			bool check = true;
			remove_quote_stark3();
			remove_quote_lannister3();
			if (random3 % 3 == 0)
			{
				srand(time(NULL));
				int a = rand() % 4;
				lannisters1[a]->Visibility = Visibility(false);
			}
			end_check3();
		}
		//	turn13 = !turn13;
	}


}


void App2::North1::button_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	generate_random_board3();
}


void App2::North1::button00_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 0);
}


void App2::North1::button01_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 1);
}


void App2::North1::button02_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 2);
}


void App2::North1::button03_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 3);
}


void App2::North1::button04_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 4);
}


void App2::North1::button05_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 5);
}


void App2::North1::button06_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 6);
}


void App2::North1::button07_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 7);
}


void App2::North1::button08_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 8);
}


void App2::North1::button09_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 9);
}


void App2::North1::button010_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(0, 10);
}


void App2::North1::button10_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 0);
}


void App2::North1::button11_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 1);
}


void App2::North1::button12_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 2);
}


void App2::North1::button13_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 3);
}


void App2::North1::button14_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 4);
}


void App2::North1::button15_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 5);
}


void App2::North1::button16_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 6);
}


void App2::North1::button17_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 7);
}


void App2::North1::button18_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 8);
}


void App2::North1::button19_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 9);
}


void App2::North1::button110_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(1, 10);
}


void App2::North1::button20_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 0);
}


void App2::North1::button21_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 1);
}


void App2::North1::button22_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 2);
}


void App2::North1::button23_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 3);
}


void App2::North1::button24_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 4);
}


void App2::North1::button25_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 5);
}


void App2::North1::button26_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 6);
}


void App2::North1::button27_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 7);
}


void App2::North1::button28_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 8);
}


void App2::North1::button29_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 9);
}


void App2::North1::button210_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(2, 10);
}


void App2::North1::button30_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 0);
}


void App2::North1::button31_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 1);
}


void App2::North1::button32_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 2);
}


void App2::North1::button33_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 3);
}


void App2::North1::button34_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 4);
}


void App2::North1::button35_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 5);
}


void App2::North1::button36_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 6);
}


void App2::North1::button37_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 7);
}


void App2::North1::button38_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 8);
}


void App2::North1::button39_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 9);
}


void App2::North1::button310_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(3, 10);
}


void App2::North1::button40_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 0);
}


void App2::North1::button41_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 1);
}


void App2::North1::button42_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 2);
}


void App2::North1::button43_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 3);
}



void App2::North1::button44_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 4);
}


void App2::North1::button45_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 5);
}


void App2::North1::button46_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 6);
}


void App2::North1::button47_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 7);
}


void App2::North1::button48_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 8);
}


void App2::North1::button49_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 9);
}


void App2::North1::button410_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(4, 10);
}


void App2::North1::button50_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 0);
}


void App2::North1::button51_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 1);
}


void App2::North1::button52_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 2);
}


void App2::North1::button53_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 3);
}


void App2::North1::button54_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 4);
}


void App2::North1::button55_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 5);
}


void App2::North1::button56_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 6);
}


void App2::North1::button57_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 7);
}


void App2::North1::button58_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 8);
}


void App2::North1::button59_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 9);
}


void App2::North1::button510_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(5, 10);
}


void App2::North1::button60_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 0);
}


void App2::North1::button61_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 1);
}


void App2::North1::button62_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 2);
}


void App2::North1::button63_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 3);
}


void App2::North1::button64_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 4);
}


void App2::North1::button65_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 5);
}


void App2::North1::button66_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 6);
}


void App2::North1::button67_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 7);
}


void App2::North1::button68_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 8);
}


void App2::North1::button69_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 9);
}


void App2::North1::button610_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(6, 10);
}


void App2::North1::button70_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 0);
}


void App2::North1::button71_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 1);
}


void App2::North1::button72_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 2);
}


void App2::North1::button73_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 3);
}


void App2::North1::button74_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 4);
}


void App2::North1::button75_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 5);
}


void App2::North1::button76_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 6);
}


void App2::North1::button77_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 7);
}


void App2::North1::button78_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 8);
}


void App2::North1::button79_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 9);
}


void App2::North1::button710_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(7, 10);
}


void App2::North1::button80_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 0);
}


void App2::North1::button81_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 1);
}


void App2::North1::button82_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 2);
}


void App2::North1::button83_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 3);
}


void App2::North1::button84_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 4);
}


void App2::North1::button85_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 5);
}


void App2::North1::button86_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 6);
}


void App2::North1::button87_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 7);
}


void App2::North1::button88_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 8);
}


void App2::North1::button89_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 9);
}


void App2::North1::button810_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(8, 10);
}


void App2::North1::button90_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 0);
}


void App2::North1::button91_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 1);
}


void App2::North1::button92_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 2);
}


void App2::North1::button93_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 3);
}


void App2::North1::button94_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 4);
}


void App2::North1::button95_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 5);
}


void App2::North1::button96_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 6);
}


void App2::North1::button97_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 7);
}


void App2::North1::button98_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 8);
}


void App2::North1::button99_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 9);
}


void App2::North1::button910_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	chance3(9, 10);
}


void App2::North1::button1_Click3(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e)
{
	this->Frame->Navigate(Windows::UI::Xaml::Interop::TypeName(FirstPage::typeid));
}
