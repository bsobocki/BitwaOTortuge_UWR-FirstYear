#ifndef MENU_HPP_INCLUDED
#define MENU_HPP_INCLUDED
#include "window.hpp"

using namespace std;

class Menu :public Window
{
private:
   //przyciski
   Button start;
   Button authors;
   Button exit;

public:
   //konstruktor (wystarczy jeden)
   Menu(const int w, const int h, const char* src);

   //metody
   bool show();
   void change_buttons(const int x, const int y);
   void close();
};

#endif // MENU_HPP_INCLUDED
