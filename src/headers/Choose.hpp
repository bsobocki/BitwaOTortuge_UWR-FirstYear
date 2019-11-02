#ifndef CHOOSE_HPP_INCLUDED
#define CHOOSE_HPP_INCLUDED
#include "Menu.hpp"

class Choose : public Window
{
private:
   // buttons
   Button pirates;
   Button spanish;

public:
   // constructor
   Choose(const int h, const int w, const char* src);

   // methods
   bool show();
   void change_buttons(const int x, const int y );
   void close();
};

#endif // CHOOSE_HPP_INCLUDED
