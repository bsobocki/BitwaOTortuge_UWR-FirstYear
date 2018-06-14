#include "Choose.hpp"



//-------Choose-------

//konstruktor
Choose::Choose(const int h, const int w, const char* src): Window(w,h,src,"Wybor Floty Gracza 1!")
{
   pirates = *new Button(100, 100, 200, 200, renderer, "grafika/Piraci.jpg");
   spanish = *new Button(400, 100, 200, 200, renderer, "grafika/Hiszpanie.jpg");
}

//metody

//zamykanie i niszczenie okna
void Choose::close()
{
   //destrukcja okna
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   //destrukcja przyciskow
   pirates.close();
   spanish.close();
}

//wyswietlanie okna wyobru floty i odczytanie wyboru
bool Choose::show()
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
         SDL_RenderCopy(renderer, pirates.text, nullptr, &pirates.rect);
         SDL_RenderCopy(renderer, spanish.text, nullptr, &spanish.rect);
         SDL_RenderPresent(renderer);


         //po kliknieciu myszki
         if (event.type == SDL_MOUSEBUTTONDOWN)
         {
            //przycisk PIRATES
            if(x>=pirates.x_g() && x<pirates.x_g()+pirates.width_g() &&
               y>=pirates.y_g() && y<pirates.y_g()+pirates.height_g())
               {close(); return true;}

            //przycisk SPANISH
            if(x>=spanish.x_g() && x<spanish.x_g()+spanish.width_g() &&
               y>=spanish.y_g() && y<spanish.y_g()+spanish.height_g())
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

//zmiana tekstury przycisku na ktory najedziemy
void Choose::change_buttons(const int x, const int y)
{
   //PIRACI
   if(x>=pirates.x_g() && x<pirates.x_g()+pirates.width_g() &&
      y>=pirates.y_g() && y<pirates.y_g()+pirates.height_g())
      pirates.set_bckgrd("grafika/Piraci2.jpg");
   else
      pirates.set_bckgrd("grafika/Piraci.jpg");

   //HISZPANIE
   if(x>=spanish.x_g() && x<spanish.x_g()+spanish.width_g() &&
      y>=spanish.y_g() && y<spanish.y_g()+spanish.height_g())
      spanish.set_bckgrd("grafika/Hiszpanie2.jpg");
   else
      spanish.set_bckgrd("grafika/Hiszpanie.jpg");
}
