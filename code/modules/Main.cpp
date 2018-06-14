#include "Game.hpp"

using namespace std;

int main(int argv, char** args)
{
   //inicjalizacja SDL
   init();

   //zmienna przechowuje informacje o stanie przejscie (wyjscie z programu lub przejscie do gry)
   //oraz flote gracza 1
   bool boo = true;

   while(boo)
   {
      //tworzenie okna Menu
      Menu menu(700, 700, "grafika/MENU.jpg");

      //wyswietlanie okna Menu i sprawdzanie wyboru
      if (menu.show())
      {
         //tworzymy okno wyboru floty i wyswietlamy je
         Choose choose(400, 700, "grafika/background3.jpg");

         //wybor floty
         boo = choose.show();

         //tworzenie okna gry i wyswietlanie go
         Game game(546,550,"grafika/plansza.jpg",boo);

         //sprawdzamy, czy gra zakonczyla sie zywciestwem czy zamknieciem
         boo = game.show();

         //zamykamy i niszczymy okno
         game.close();
      }
      //jesli w MENU klikniemy "wyjscie"
      else
         boo = false;
   }

   //cout<<endl<<"Dziekuje za skorzystanie z programy \" Bitwa o Tortuge\" "<<endl;
   SDL_Quit();
   return 0;
}
