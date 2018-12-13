#include "Menu.hpp"

using namespace std;

//MENU

//konstruktor
Menu::Menu(const int w, const int h, const char* src): Window(w,h,src,"Bitwa O Tortuge!")
{
   Button* b = new Button(250, 200, 200, 70, renderer, "grafika/start2-2.jpg");
   start = *b;
   delete b;
   b = new Button(250, 300, 200, 70, renderer, "grafika/autorzy2.jpg");
   authors = *b;
   delete b;
   b = new Button(250, 400, 200, 70, renderer, "grafika/wyjscie2-2.jpg");
   exit  = *b;
   delete b;
}

//metody

//zmiana przyciskow na "wcisniete"
void Menu::change_buttons(const int x, const int y)
{
   //START
   if(x>=start.x_g() && x<start.x_g()+start.width_g() &&
      y>=start.y_g() && y<start.y_g()+start.height_g())
      start.set_bckgrd("grafika/start2-1.jpg");
   else
      start.set_bckgrd("grafika/start2-2.jpg");

   //AUTORZY
   if(x>=authors.x_g() && x<authors.x_g()+authors.width_g() &&
      y>=authors.y_g() && y<authors.y_g()+authors.height_g())
      authors.set_bckgrd("grafika/autorzy2-1.jpg");
   else
      authors.set_bckgrd("grafika/autorzy2.jpg");

   //WYJSCIE
   if(x>=exit.x_g() && x<exit.x_g()+exit.width_g() &&
      y>=exit.y_g() && y<exit.y_g()+exit.height_g())
      exit.set_bckgrd("grafika/wyjscie2-1.jpg");
   else
      exit.set_bckgrd("grafika/wyjscie2-2.jpg");
}
//zamykanie i niszczenie okna
void Menu::close()
{
   //destrukcja okna
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   //destrukcja przyciskow
   start.close();
   exit.close();
   authors.close();
}
//pokazywanie okna
//na wyjsciu otrzymamy  |  'true - jesli gra ma sie rozpoczac |  'false - jesli mamy zakonczyc program  |
bool Menu::show()
{
   //wyswietlanie, az do klikniecia opcji wyjscia badz zamkniecia okna
   while(true)
   {
      //pobieranie wydarzenia
      if(SDL_PollEvent(&event))
       {
         //pobieranie polozenia myszki
         int x = event.motion.x;
         int y = event.motion.y;

         //zmiana przyciskow na "wcisniete"
         change_buttons(x, y);

         //czyszczenie i dodawanie do renderera obiektow
         SDL_RenderClear(renderer);
         SDL_RenderCopy(renderer, texture, nullptr, nullptr);
         SDL_RenderCopy(renderer, start.text, nullptr, &start.rect);
         SDL_RenderCopy(renderer, authors.text, nullptr, &authors.rect);
         SDL_RenderCopy(renderer, exit.text, nullptr, &exit.rect);
         SDL_RenderPresent(renderer);

         //po kliknieciu myszki
         if (event.type == SDL_MOUSEBUTTONDOWN)
         {
            //przycisk START
            if(x>=start.x_g() && x<start.x_g()+start.width_g() &&
               y>=start.y_g() && y<start.y_g()+start.height_g())
               {
                  close();
                  return true;
               }

            //przycisk AUTORZY
            if(x>=authors.x_g() && x<authors.x_g()+authors.width_g() &&
               y>=authors.y_g() && y<authors.y_g()+authors.height_g())
               {
                  //czysczenie rendera i wstawienie informacji o autorach
                  SDL_RenderClear(renderer);
                  SDL_Surface* ss = IMG_Load("grafika/aut.jpg");
                  SDL_Texture* tt = SDL_CreateTextureFromSurface(renderer, ss);
                  SDL_RenderCopy(renderer, tt, nullptr, nullptr);
                  SDL_RenderPresent(renderer);
                  //az do wcisniecia ESC wyswietlany jest dany tekst
                  do
                  {
                     SDL_WaitEvent(&event);
                  }
                  while(event.key.keysym.sym != SDLK_ESCAPE);
                  //niszczenie komponentow nieuzywanych
                  SDL_DestroyTexture(tt);
                  SDL_FreeSurface(ss);
               }

            //przycisk WYJSCIE
            if(x>=exit.x_g() && x<exit.x_g()+exit.width_g() &&
               y>=exit.y_g() && y<exit.y_g()+exit.height_g())
               {
                  close();
                  return false;
               }
         }
         //po kliknieciu na "X" - zamkniecie okna
         else if(event.type==SDL_QUIT)
         {
            close();
            return false;
         }
       }

      SDL_Delay(1000/60);
   }
   close();
   return false;
}
