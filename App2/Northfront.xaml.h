//
// Northfront.xaml.h
// Declaration of the Northfront class
//

#pragma once

#include "Northfront.g.h"
#include "North.xaml.h"
#include "North1.xaml.h"

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class Northfront sealed
	{
	public:
		Northfront();
	private:
		void button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void button_Click_1(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
