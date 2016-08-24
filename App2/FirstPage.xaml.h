//
// FirstPage.xaml.h
// Declaration of the FirstPage class
//

#pragma once

#include "FirstPage.g.h"
#include "Mainfront.xaml.h"
#include "Northfront.xaml.h"

namespace App2
{
	/// <summary>
	/// An empty page that can be used on its own or navigated to within a Frame.
	/// </summary>
	[Windows::Foundation::Metadata::WebHostHidden]
	public ref class FirstPage sealed
	{
	public:
		FirstPage();
	private:
		void button_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
		void button1_Click(Platform::Object^ sender, Windows::UI::Xaml::RoutedEventArgs^ e);
	};
}
