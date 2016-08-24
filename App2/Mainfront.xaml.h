//
// Mainfront.xaml.h
// Declaration of the Mainfront class
//

#pragma once

#include "Mainfront.g.h"
#include "MainPage.xaml.h"
#include "MainPage1.xaml.h"

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Mainfront sealed
	{
	public:
		Mainfront();
	private:
		void button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
