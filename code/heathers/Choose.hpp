#ifndef WYBOR_HPP_INCLUDED
#define WYBOR_HPP_INCLUDED
#include "Menu.hpp"

class Choose : public Window
{
private:
   //przyciski
   Button pirates;
   Button spanish;

public:
   //konstruktor
   Choose(const int h, const int w, const char* src);

   //metody
   bool show();
   void change_buttons(const int x, const int y );
   void close();
};


#endif // WYBOR_HPP_INCLUDED
