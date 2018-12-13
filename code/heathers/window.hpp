#ifndef WINDOW_HPP_INCLUDED
#define WINDOW_HPP_INCLUDED
#include "SDL.h"
#include "SDL_image.h"
#include "iostream"

//klasa abstrakcyjna zwierajaca niezbedne elementy do utworzenia okna
class Window
{
//klasa przycisków
protected:
   class Button
   {
      protected:
         //wymiary i polozenie
         int width  = 0;
         int height = 0;
         int x;
         int y;

      public:
         SDL_Surface* surf ;
         SDL_Texture* text ;
         SDL_Renderer*render ;
         //ustalamy miejsce i wielkosc prostokata w jakim ma znajdowac sie przycik
         SDL_Rect rect; //poprzez obiekt rectangle

      public:
         //konstruktory
         Button();
         Button(const int x, const int y, const int w, const int h, SDL_Renderer* r, const char* src);
         Button(const Button&);
         Button(Button&&);

         //operatory
         Button & operator = (Button&&);
         Button & operator = (const Button&);

         //gettery
         int width_g()  const;
         int height_g() const;
         int x_g() const;
         int y_g() const;

         //settery
         void set_bckgrd(const char* src);
         void x_s(const int xx);
         void y_s(const int yy);

         //usuniecie przycisku
         void close();
   };
   
public:
   //komponenty niezbedne do utworzenia danego okna i jego zawartosci
   SDL_Window    *window;
   SDL_Texture   *texture;
   SDL_Renderer  *renderer;
   SDL_Surface   *surface;

   //za pomoca tego obiektu beda wypatrywane zdarzenia myszki i klawiatury
   SDL_Event event;

   //rozmiar i tlo
   const int width;
   const int height;
   const char* bckgrd_src;

public:
   //konstruktor ustawiajacy pola ktore zostana dziedziczone
   Window(const int w, const int h, const char* s, const char* title);

public:
   //metody wirtualne
   virtual bool show() = 0;
   virtual void change_buttons(const int x, const int y) = 0;
   virtual void close() = 0;
};

void init();


#endif // WINDOW_HPP_INCLUDED
