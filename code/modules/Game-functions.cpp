#include "Game.hpp"
#include <time.h>
#include <random>
#include <string.h>



//-------Player-------


//konstruktor
Game::Player::Player():
   score(0), fleet(true), num_of_ships(0), s(nullptr), t(nullptr), sscr(nullptr), tscr(nullptr){}

Game::Player::Player(const bool f, const int num, const char* src, SDL_Renderer* ren):
   score(0), fleet(f), num_of_ships(num), sscr(nullptr), tscr(nullptr)
{
   s = IMG_Load(src);
   t = SDL_CreateTextureFromSurface(ren, s);
}
//operator
Game::Player & Game::Player::operator=(const Game::Player& p)
{
   score = p.score;
   fleet = p.fleet;
   num_of_ships = p.num_of_ships;
   s = p.s;
   t = p.t;
   sscr = p.sscr;
   tscr = p.tscr;

   return *this;
}




//-------Field-------


//konstruktor
Game::Field::Field(): x(0), y(0), number(0){}
Game::Field::Field(const int num, const int xx, const int yy):
   x(xx), y(yy), number(num){}

//operator
Game::Field & Game::Field::operator =(Game::Field& f)
{
   x = f.x;
   y = f.y;
   number  = f.number;
   outdoor = f.outdoor;
   hidden  = f.hidden;

   return *this;
}

//metody
void Game::Field::changeHidden(Game::Ship & s){ hidden = s; hidden.update_coordinates(x,y);}
void Game::Field::changeOutdoor(Game::Ship & s){ outdoor = s; outdoor.update_coordinates(x,y);}
void Game::Field::close()
{
   outdoor.close();
   hidden.close();
}




//-------Ship-------


//konstruktory
Game::Ship::Ship(): Game::Button(), field_num(0), bckgrd_src_l("no_image"), bckgrd_src_d("no_image"), rev(true), rev_src_l("no_image"), rev_src_d("no_image"), rot(0), show(false),fleet(-1), index(0), zero(true), able_to_move(false), score(0){}

Game::Ship::Ship(const int x, const int y, const int w, const int h, SDL_Renderer* r, char* src, const int numfield, char* dark_bckgrd, const bool _rev, char* rev_srcL, char* rev_srcD,const int fl, const int ind, const int scr)
   : Game::Button(x, y, w, h, r, rev_srcD), field_num(numfield), bckgrd_src_l(src), bckgrd_src_d(dark_bckgrd), rev(_rev), rev_src_l(rev_srcL), rev_src_d(rev_srcD), rot(0), show(true), fleet(fl), index(ind), zero(false), able_to_move(!_rev), score(scr)
      {}

//operator =
Game::Ship & Game::Ship::operator=(Game::Ship & s)
{
   x = s.x_g();
   y = s.y_g();
   rect = s.rect;
   height = s.height_g();
   width  = s.width_g();
   field_num    = s.field_num;
   bckgrd_src_l = s.bckgrd_src_l;
   bckgrd_src_d = s.bckgrd_src_d;
   rev = s.rev;
   rev_src_l = s.rev_src_l;
   rev_src_d = s.rev_src_d;
   rot    = s.rot;
   show   = s.show;
   fleet  = s.fleet;
   index  = s.index;
   zero   = s.zero;
   able_to_move = s.able_to_move;
   score = s.score;
   surf   = s.surf;
   render = s.render;
   text   = SDL_CreateTextureFromSurface(render, surf);

   return *this;
}

//metody
void Game::Ship::set_bckgrd(const char* src)
{
   //zanim nadpiszemy, musimy usunac
   SDL_FreeSurface(surf);
   SDL_DestroyTexture(text);
   //nadpisujemy
   surf = IMG_Load(src);
   text = SDL_CreateTextureFromSurface(render, surf);
}
//wprowadzenie koordynatow
void Game::Ship::update_coordinates(const int xx, const int yy)
{
   x = xx;
   y = yy;
}
//usuwanie statku
void Game::Ship::close()
{
   Window::Button::close();
   delete bckgrd_src_d;
   delete bckgrd_src_l;
   delete rev_src_d;
   delete rev_src_l;
}



//-------Game-------


int Game::selected;

//konstruktor
Game::Game(const int w, const int h, const char* src, const bool Player1_fleet): Window(w,h,src,"Pokonaj Flote Przeciwnika!")
{
   //inicjalizacja pozycji pol
   X[0] = 185,
   X[1] = 282,
   X[2] = 86,
   X[3] = 184,
   X[4] = 282,
   X[5] = 379,
   X[6] = 86,
   X[7] = 183,
   X[8] = 281,
   X[9] = 379,
   X[10] = 183,
   X[11] = 281;

   Y[0] = 88,
   Y[1] = 87,
   Y[2] = 185,
   Y[3] = 183,
   Y[4] = 183,
   Y[5] = 183,
   Y[6] = 282,
   Y[7] = 282,
   Y[8] = 282,
   Y[9] = 281,
   Y[10] = 381,
   Y[11] = 379;

   //flota akttualnego gracza
   current_fleet = Player1_fleet;

   //wyswietlanie obrazka aktualnej floty
   Button* b = new Button(248, 15, 50, 50, renderer,"grafika/small-Piraci.jpg");
   img_fleet = *b;
   delete b;

   //tworzymy gracza 1
   Player* p = new Player(Player1_fleet, 8, "grafika/P1.png", renderer);
   player1 = *p;
   delete p;
   //tworzymy gracza 2
   p = new Player(!Player1_fleet, 8,"grafika/P2.png", renderer);
   player2 = *p;
   delete p;

   //losowanie rozmieszczenia
   int* index = randomize();

   int score=1; //wartosc punktowa danego okretu

   Ship* s;
   for (int i=0; i<6; i++)
   {
      //ustawiamy wartosc punktowa
      if(i==2 || i==4) score++;
      //tworzenie okretow bez zrodel
      s = new Ship( X[index[i]], Y[index[i]], 79, 82, renderer, "", index[i], "", true, "", "",1, i, score);
      ship[i] = *s;
      delete s;
   }

   score=1;
   for (int i=6; i<12; i++)
   {
      //ustawiamy wartosc punktowa
      if(i==8 || i==10) score++;
      //tworzenie okretow bez zrodel
      s = new Ship( X[index[i]], Y[index[i]], 79, 82, renderer, "", index[i], "", true, "", "",0, i, score);
      ship[i] = *s;
      delete s;
   }

   //ustawianie zrodel statkow
   sources();

   //przypisywanie polom danych okretow

   Field* f;
   for (int i=0; i<12; i++)
   {
      //tworzenie pol na planszy
      f = new Field(i, X[i], Y[i]);
      field[i] = *f;
      delete f;

   }
   for (int i=0; i<12; i++)
   {
      //nadajemy polom widoczne pionki i ustawiamy ukryte jako "zerowe"
      field[ship[i].field_num].changeOutdoor(ship[i]);
      field[ship[i].field_num].changeHidden(zero_ship);
   }

   //ustawienie poczatkowych tekstur
   change_buttons(0, 0);

   //zadne pole nie zostalo zaznaczone
   selected = -1;
}

bool Game::winner()
{
   //gy jeden z graczy zdobedzie 6 pkt to rozgrywka jest zakonczona
   if(player1.score>=6 || player2.score>=6)
   {
      SDL_Surface* s;
      SDL_RenderClear(renderer);
      SDL_RenderCopy(renderer, texture, nullptr, nullptr);
      bool win;

      //sprawdzamy, ktory gracz wygral
      if (player1.score > player2.score)
      {
         win = player1.fleet;
         s = IMG_Load("grafika/pl1win.png");
      }
      else
      {
         win = player2.fleet;
         s = IMG_Load("grafika/pl2win.png");
      }

      //dodajemy do okna napis informujacy kto jest zwyciesca
      SDL_Texture* t = SDL_CreateTextureFromSurface(renderer, s);
      SDL_Rect r1     = {field[3].x-40, field[3].y-70, 286, 59};
      SDL_RenderCopy(renderer, t, nullptr, &r1);

      SDL_FreeSurface(s);
      if(!win)
         s = IMG_Load("grafika/Hiszpanie3.jpg");
      else
         s = IMG_Load("grafika/Piraci3.jpg");

      //dodajemy do okna grafike floty wygranego gracza
      SDL_DestroyTexture(t);
      t = SDL_CreateTextureFromSurface(renderer, s);

      SDL_Rect r     = {field[3].x-10, field[3].y-7, 2*ship[0].height_g()+30, 2*ship[0].height_g()+30};
      SDL_RenderCopy(renderer, t, nullptr, &r);
      SDL_RenderPresent(renderer);
      //komunikat bedzie trwal 2 sekundy
      SDL_Delay(5000);
      //usuwane jest tylko to stworzone w tym bloku, poniewaz reszta zostanie
      //usunieta poprzez wywolanie funkcji close()
      SDL_FreeSurface(s);
      SDL_DestroyTexture(t);
      return true;
   }
   return false;
}


//metody
bool Game::show()
{
   while(true)
   {
      if(SDL_WaitEvent(&event))
      {
         //zamkniecie okna
         if(event.type == SDL_QUIT)
            return false;

         //sprawdzamy, czy gra nie zostala zakonczona poprzez zwyciestwo ktoregos z graczy
         if(winner())
            return true;

         //czyszczenie i dodawanie do renderera obiektow
         SDL_RenderClear(renderer);

         //zaznaczanie statku, obroty, zmiana tekstur...
         change_buttons(event.motion.x, event.motion.y);
         action();

         //najpierw na render nakladane jest tlo (plansza)
         SDL_RenderCopy(renderer, texture, nullptr, nullptr);

         //pokazujemy aktualny kolor floty
         if(!current_fleet)
            img_fleet.set_bckgrd("grafika/small-Hiszpanie.jpg");
         else
            img_fleet.set_bckgrd("grafika/small-Piraci.jpg");
         SDL_RenderCopy(renderer, img_fleet.text, nullptr, &img_fleet.rect);

         //nakladamy zaznaczenie
         if(selected>=0)
            SDL_RenderCopy(renderer, stroke.text, nullptr, &stroke.rect);

         //nakladamy okrety na plansze wedlug tego, czy maja byc widoczne
         for(int i=0; i<12; i++)
         {
            if (ship[i].show)
            {

               SDL_Rect r = {field[i].outdoor.x_g(), field[i].outdoor.y_g(), field[i].outdoor.height_g(), field[i].outdoor.width_g()};

               //ustawiamy przerzut obrazu
               SDL_RendererFlip flip;

               //gdy obracamy o 180* to chcemy miec obraz przerzucony pionowo, a nie do gory nogami
               if(field[i].outdoor.rot==2)
                  flip = SDL_FLIP_VERTICAL;
               else
                  flip = SDL_FLIP_NONE;

               //do rendera dorzucamy pionki
               SDL_RenderCopyEx(renderer, field[i].outdoor.text, nullptr, &r, 90.0*field[i].outdoor.rot, nullptr, flip);
            }
         }
         //pokazanie punktow
         players_scores();
         //wyswietlenie zawartosci rendera
         SDL_RenderPresent(renderer);
      }
   }
}


//wykonywanie akcji na obiektach
void Game::action()
{
   if(selected != -1)
   {
      //gdy moze sie przemieszczac to obracac sie rowniez moze tylko raz, w przeciwnym wypadku moze ile razy chce (do klikniecia PPM lub SPACJI)
      bool _move = field[selected].outdoor.able_to_move;

      //gdy klikniemy na okret z przeciwnej floty
      if((field[selected].outdoor.fleet==(int)current_fleet) && _move)
      {
         selected = -1;
         return ;
      }

      //sprawdzamy czy przed wykonaniem tej iteracji bylo klikniecie
      if(!click)
      {
         //tworzymy zaznaczenie (zolta obwodke dookola pionka)
         Button* b = new Button(field[selected].outdoor.x_g()-5, field[selected].outdoor.y_g()-5, field[selected].outdoor.height_g()+10, field[selected].outdoor.width_g()+10, renderer, "grafika/stroke.jpg");
         stroke = *b;
         free(b);
      }

      click = true;

      //klawiatura obslugujemy ruch i obrot okretu
      if (event.type == SDL_KEYDOWN)
      {
         //w zaleznosci od przycisku na klawiaturze
         switch(event.key.keysym.sym)
         {

         //obroty

         //prawa strzalka obraca o 90* w prawo
         case SDLK_RIGHT:
            {
               field[selected].outdoor.rot += 1;
               if (field[selected].outdoor.rot > 3)
                  field[selected].outdoor.rot = 0;

               //gdy moze sie przemieszczac to obrocic sie moze tylko raz
               if(_move)
               {
                  selected = -1;
                  stroke = zero_stroke;
                  current_fleet = !current_fleet;
               }
               break;
            }
         //lewa strzalka obraca o 90* w lewo
         case SDLK_LEFT:
            {
               field[selected].outdoor.rot -= 1;
               if (field[selected].outdoor.rot < 0)
                  field[selected].outdoor.rot = 3;

               //gdy moze sie przemieszczac to obrocic sie moze tylko raz
               if(_move)
               {
                  selected = -1;
                  stroke = zero_stroke;
                  current_fleet = !current_fleet;
               }
               break;
            }

         //przemieszczanie (zmieniany jest gracz po przemieszczeniu)

         case SDLK_KP_1:
            {
               //tylko dla okretow obroconych w lewo badz w dol i z wartoscia wieksza niz 1
               if ((field[selected].outdoor.rot == 0 || field[selected].outdoor.rot == 3 )  &&  field[selected].outdoor.index % 6 > 1 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_down_left(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_2:
            {
               //tylko dla okretow obroconych w dol
               if (field[selected].outdoor.rot == 3 && field[selected].outdoor.index % 6 != 2 && field[selected].outdoor.index % 6 != 3 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_down(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_3:
            {
               //tylko dla okretow obroconych w prawo badz w dol i z wartoscia wieksza niz 1
               if ((field[selected].outdoor.rot == 2 || field[selected].outdoor.rot == 3 )  &&  field[selected].outdoor.index % 6 > 1 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_down_right(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_4:
            {
               //tylko dla okretow obroconych w lewo
               if (field[selected].outdoor.rot == 0 && field[selected].outdoor.index % 6 != 2 && field[selected].outdoor.index % 6 != 3 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_left(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_6:
            {
               //tylko dla okretow obroconych w prawo
               if (field[selected].outdoor.rot == 2 && field[selected].outdoor.index % 6 != 2 && field[selected].outdoor.index % 6 != 3 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                    if(move_right(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_7:
            {
               //tylko dla okretow obroconych w lewo badz w gore i z wartoscia wieksza niz 1
               if ((field[selected].outdoor.rot == 0 || field[selected].outdoor.rot == 1 )  &&  field[selected].outdoor.index % 6 > 1 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_up_left(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_8:
            {
               //tylko dla okretow obroconych w gore
               if (field[selected].outdoor.rot == 1 && field[selected].outdoor.index % 6 != 2 && field[selected].outdoor.index % 6 != 3 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_up(field[selected]))
                        current_fleet = !current_fleet;
                  }
               break;
            }
         case SDLK_KP_9:
            {
               //tylko dla okretow obroconych w prawo badz w gore i z wartoscia wieksza niz 1
               if ((field[selected].outdoor.rot == 1 || field[selected].outdoor.rot == 2 )  &&  field[selected].outdoor.index % 6 > 1 && _move)
                  {
                     //tylko gdy udalo sie przemiescic mozemy zmienic gracza
                     if(move_up_right(field[selected]))
                        current_fleet = !current_fleet;
                  }

               break;
            }

         //anulowanie zaznaczenia statku (zmiana gracza)

         case SDLK_SPACE:
            {
               selected = -1;
               stroke = zero_stroke;
               current_fleet = !current_fleet;
               break;
            }
         }
      }

      //gdy nie zostal nacisniety klawisz z klawiatury (zmiana gracza)
      else if (event.type == SDL_MOUSEBUTTONDOWN)
      {
         if(event.button.button == SDL_BUTTON_RIGHT)
         {
            selected = -1;
            stroke = zero_stroke;
            current_fleet = !current_fleet;
         }
      }
   }
   else
      click = false;
}


//zamykanie okna i niszczenie go
void Game::close()
{
   SDL_DestroyWindow(window);
   SDL_DestroyRenderer(renderer);
   SDL_DestroyTexture(texture);
   SDL_FreeSurface(surface);
   for(int i=0; i<12; i++)
   {
      ship[i].close();
      field[i].close();
   }
   zero_ship.close();
   zero_stroke.close();
   img_fleet.close();
   stroke.close();

   //Usuwanie Graczy
   SDL_DestroyTexture(player1.t);
   SDL_DestroyTexture(player2.t);
   SDL_FreeSurface(player1.s);
   SDL_FreeSurface(player2.s);
   SDL_DestroyTexture(player1.tscr);
   SDL_FreeSurface(player1.sscr);
   SDL_DestroyTexture(player2.tscr);
   SDL_FreeSurface(player2.sscr);
}


//funkcja zwraca tablice z niepowtarzajacymi sie losowymi liczbami
//potrzebna do losowego poczatkowego rozmieszczenia okretow
int* Game::randomize()
{
   srand(time(0));

   int bufor, a;
   int *tmp = new int[12];

   //nadajemy poczatkowe wartosci tablicy
   for(int i=0; i<=11; i++)
      tmp[i] = i;

   for(int j=0; j<=11; j++)
   {
      a = rand()%(12-j)+j;
      bufor  = tmp[a];
      tmp[a] = tmp[j];
      tmp[j] = bufor;
   }

   return tmp;
}


//zmiana tekstury okrety na ktory najedziemy
void Game::change_buttons(const int x, const int y)
{
   for(int i=0; i<12; i++)
      change(field[i].outdoor, i, x, y);
}
//funkcja zamienia wyswietlany obraz pojedynczego statku
void Game::change(Game::Ship & b, const int i, const int x, const int y)
{
   //gdy kursor myszki znajduje sie na obiekcie
   if(x>=b.x_g() && x<b.x_g()+b.width_g() &&
      y>=b.y_g() && y<b.y_g()+b.height_g())
   {
      //gdy obiekt zostanie klikniety
      if(event.type == SDL_MOUSEBUTTONDOWN)
      {
        //jesli nacisniemy lewym przyciskiem myszy na obiektu to odwracamy go na strone z okretem
        if (event.button.button == SDL_BUTTON_LEFT)
         {
            //jesli klikamy na obiekt ktory nie byl zaznaczony
            if(selected != i && selected > -1)
               current_fleet = !current_fleet;

            //gdy statek byl juz obrocony to moze sie przemieszczac
            if(!b.rev && selected!=i)
               b.able_to_move = true;
            //w przciwnym razie obracamy pionek i gracz traci ture
            else
               {
                  //nie bedzie wyswietlany rewersem go gory
                  b.rev = false;
               }

            //zostanie on zaznaczony
            Game::selected = i;
            click = false;
         }
      }

      if(b.rev)
         b.set_bckgrd(b.rev_src_d);
      else
         b.set_bckgrd(b.bckgrd_src_d);
   }
   else
   {
      if(b.rev)
         b.set_bckgrd(b.rev_src_l);
      else
         b.set_bckgrd(b.bckgrd_src_l);
   }
}


//poruszanie sie okretow
bool Game::move_up(Game::Field& f)
{
   //w zaleznosci od pola na ktorym znajduje sie okret sprawdzamy
   //czy moze on przemiescic sie w gore
   //oraz czy jesli moze to czy okret bedacy na widoku nie ma tej samej floty
   switch (f.number)
   {
   case 0:
   case 1:
   case 2:
   case 5:
      {
         //nie moze
         return false;
      }
   case 3:
   case 4:
   case 10:
   case 11:
      {
         if(field[f.number - 3].outdoor.fleet == -1 || field[f.number - 3].outdoor.fleet != f.outdoor.fleet || field[f.number - 3].outdoor.rev)
            {
               attack(f, field[f.number - 3]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 6:
   case 7:
   case 8:
   case 9:
      {
         if(field[f.number - 4].outdoor.fleet == -1 || field[f.number - 4].outdoor.fleet != f.outdoor.fleet || field[f.number - 4].outdoor.rev)
            {
               attack(f, field[f.number - 4]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_down(Game::Field& f)
{
   //w zaleznosci od pola na ktorym znajduje sie okret sprawdzamy
   //czy moze on przemiescic sie w dol
   //oraz czy jesli moze to czy okret bedacy na widoku nie ma tej samej floty
   switch (f.number)
   {
   case 11:
   case 10:
   case 9:
   case 6:
      {
         //nie moze
         return false;
      }
   case 8:
   case 7:
   case 0:
   case 1:
      {
         if(field[f.number + 3].outdoor.fleet == -1 || field[f.number + 3].outdoor.fleet != f.outdoor.fleet || field[f.number + 3].outdoor.rev)
            {
               attack(f, field[f.number + 3]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 2:
   case 3:
   case 4:
   case 5:
      {
         if(field[f.number + 4].outdoor.fleet == -1 || field[f.number + 4].outdoor.fleet != f.outdoor.fleet || field[f.number + 4].outdoor.rev)
            {
               attack(f, field[f.number + 4]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_left(Game::Field& f)
{
   //w zaleznosci od pola sprawdzane jest czy okret moze w ogole przemiescic sie w lewo
   switch(f.number)
   {
   case 0:
   case 2:
   case 6:
   case 10:
      {
         //nie moze
         return false;
      }
   default :
      {
          if(field[f.number - 1].outdoor.fleet == -1 || field[f.number - 1].outdoor.fleet != f.outdoor.fleet || field[f.number - 1].outdoor.rev)
            {
               attack(f, field[f.number - 1]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_right(Game::Field& f)
{
   //w zaleznosci od pola sprawdzane jest czy okret moze w ogole przemiescic sie w prawo
   switch(f.number)
   {
   case 1:
   case 5:
   case 9:
   case 11:
      {
         //nie moze
         return false;
      }
   default :
      {
          if(field[f.number + 1].outdoor.fleet == -1 || field[f.number + 1].outdoor.fleet != f.outdoor.fleet || field[f.number + 1].outdoor.rev)
            {
               attack(f, field[f.number + 1]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_up_left(Game::Field& f)
{
   //sprawdzamy czy okret moze ruszyc w gore i w lewo
   switch(f.number)
   {
   case 0:
   case 1:
   case 2:
   case 3:
   case 6:
      {
         //nie moze
         return false;
      }
   case 4:
   case 5:
   case 10:
   case 11:
      {
         if(field[f.number - 4].outdoor.fleet == -1 || field[f.number - 4].outdoor.fleet != f.outdoor.fleet || field[f.number - 4].outdoor.rev)
            {
               attack(f, field[f.number - 4]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 7:
   case 8:
   case 9:
      {
         if(field[f.number - 5].outdoor.fleet == -1 || field[f.number - 5].outdoor.fleet != f.outdoor.fleet || field[f.number - 5].outdoor.rev)
            {
               attack(f, field[f.number - 5]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_up_right(Game::Field& f)
{
   //sprawdzamy czy okret moze ruszyc w gore i w prawo
   switch(f.number)
   {
   case 0:
   case 1:
   case 4:
   case 5:
   case 9:
      {
         //nie moze
         return false;
      }
   case 3:
   case 2:
   case 10:
   case 11:
      {
         if(field[f.number - 2].outdoor.fleet == -1 || field[f.number - 2].outdoor.fleet != f.outdoor.fleet || field[f.number - 2].outdoor.rev)
            {
               attack(f, field[f.number - 2]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 6:
   case 7:
   case 8:
      {
         if(field[f.number - 3].outdoor.fleet == -1 || field[f.number - 3].outdoor.fleet != f.outdoor.fleet || field[f.number - 3].outdoor.rev)
            {
               attack(f, field[f.number - 3]);
               return true;
            }
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_down_left(Game::Field& f)
{
   //sprawdzamy czy okret moze ruszyc w dol i w lewo
   switch(f.number)
   {
   case 2:
   case 6:
   case 7:
   case 10:
   case 11:
      {
         //nie moze
         return false;
      }
   case 0:
   case 1:
   case 8:
   case 9:
      {
         if(field[f.number + 2].outdoor.fleet == -1 || field[f.number + 2].outdoor.fleet != f.outdoor.fleet || field[f.number + 2].outdoor.rev)
            attack(f, field[f.number + 2]);
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 3:
   case 4:
   case 5:
      {
         if(field[f.number + 3].outdoor.fleet == -1 || field[f.number + 3].outdoor.fleet != f.outdoor.fleet || field[f.number + 3].outdoor.rev)
            attack(f, field[f.number + 3]);
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}
bool Game::move_down_right(Game::Field& f)
{
   //sprawdzamy czy okret moze ruszyc w dol i w prawo
   switch(f.number)
   {
   case 5:
   case 8:
   case 9:
   case 10:
   case 11:
      {
         //nie moze
         return false;
      }
   case 0:
   case 1:
   case 6:
   case 7:
      {
         if(field[f.number + 4].outdoor.fleet == -1 || field[f.number + 4].outdoor.fleet != f.outdoor.fleet || field[f.number + 4].outdoor.rev)
            attack(f, field[f.number + 4]);
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   case 2:
   case 3:
   case 4:
      {
         if(field[f.number + 5].outdoor.fleet == -1 || field[f.number + 5].outdoor.fleet != f.outdoor.fleet || field[f.number + 5].outdoor.rev)
            attack(f, field[f.number + 5]);
         else
            {
               //nie wplynie na swojego
               return false;
            }
         break;
      }
   }
   return true;
}


//wplyniecie statku z pola f na pole s
void Game::attack(Game::Field& f, Game::Field& s)
{
   //usuwamy zaznaczenie
   Game::selected = -1;

   //w przypadku gdy nie ma okretu na polu
   if(s.outdoor.zero)
   {
      f.outdoor.field_num = s.number;
      s.changeOutdoor(f.outdoor);
   }
   //gdy jest zakryty okret
   else if(s.outdoor.rev)
   {
      s.changeHidden(s.outdoor);
      f.outdoor.field_num = s.number;
      s.changeOutdoor(f.outdoor);
   }
   //gdy jest odkryty okret
   else
   {
      //dodajemy do punktów
      if ((int)current_fleet == player1.fleet)
         player1.score += s.outdoor.score;
      else
         player2.score += s.outdoor.score;

      //przemieszczamy
      f.outdoor.field_num = s.number;
      s.changeOutdoor(f.outdoor);
   }

   //po przeniesieniu z pola f na gore wchodzi okret ukryty, a na dole jest zerowy
   f.changeOutdoor(f.hidden);
   f.changeHidden(zero_ship);
}

//pokazanie punktow przez obu graczy
void Game::players_scores()
{
   //Player1
   SDL_Rect rP1   = {194, 20, 40, 20};
   SDL_RenderCopy(renderer, player1.t, nullptr, &rP1);
   SDL_Rect rP1s  = {198, 50, 30, 30};
   show_scores(rP1s, player1);

   //Player2
   SDL_Rect rP2   = {312, 20, 40, 20};
   SDL_RenderCopy(renderer, player2.t, nullptr, &rP2);
   SDL_Rect rP2s  = {316, 50, 30, 30};
   show_scores(rP2s, player2);
}

//pokazanie punktow aktualnie zdobytych przez gracza
void Game::show_scores(SDL_Rect& r, Game::Player& p)
{
   //ustawiana jest liczba na znak
   char dig = static_cast<char>(p.score+48);
   //tworzona zostaje sciezka
   char* src = (char*)malloc(14*sizeof(char));
   src = strcpy(src, "grafika/");
   src = strncat(src, &dig,sizeof(char));
   src = strncat(src,".png",4*sizeof(char));

   //zanim nadpiszemy, musimy usunac
   SDL_FreeSurface(p.sscr);
   SDL_DestroyTexture(p.tscr);
   //wstawianie tekstur na render
   p.sscr = IMG_Load(src);
   p.tscr  = SDL_CreateTextureFromSurface(renderer, p.sscr);
   SDL_RenderCopy(renderer, p.tscr, nullptr, &r);
}


//ustawianie zrodel statkow
void Game::sources()
{
   ship[0].bckgrd_src_l = "grafika/r1.jpg";
   ship[0].bckgrd_src_d = "grafika/r1d.jpg";
   ship[0].rev_src_l = "grafika/rewers.jpg";
   ship[0].rev_src_d = "grafika/rewers2.jpg";

   ship[1].bckgrd_src_l = "grafika/r1.jpg";
   ship[1].bckgrd_src_d = "grafika/r1d.jpg";
   ship[1].rev_src_l = "grafika/rewers.jpg";
   ship[1].rev_src_d = "grafika/rewers2.jpg";

   ship[2].bckgrd_src_l = "grafika/r2.jpg";
   ship[2].bckgrd_src_d = "grafika/r2d.jpg";
   ship[2].rev_src_l = "grafika/rewers.jpg";
   ship[2].rev_src_d = "grafika/rewers2.jpg";

   ship[3].bckgrd_src_l = "grafika/r2.jpg";
   ship[3].bckgrd_src_d = "grafika/r2d.jpg";
   ship[3].rev_src_l = "grafika/rewers.jpg";
   ship[3].rev_src_d = "grafika/rewers2.jpg";

   ship[4].bckgrd_src_l = "grafika/r3.jpg";
   ship[4].bckgrd_src_d = "grafika/r3d.jpg";
   ship[4].rev_src_l = "grafika/rewers.jpg";
   ship[4].rev_src_d = "grafika/rewers2.jpg";

   ship[5].bckgrd_src_l = "grafika/r3.jpg";
   ship[5].bckgrd_src_d = "grafika/r3d.jpg";
   ship[5].rev_src_l = "grafika/rewers.jpg";
   ship[5].rev_src_d = "grafika/rewers2.jpg";

   ship[6].bckgrd_src_l = "grafika/b1.jpg";
   ship[6].bckgrd_src_d = "grafika/b1d.jpg";
   ship[6].rev_src_l = "grafika/rewers.jpg";
   ship[6].rev_src_d = "grafika/rewers2.jpg";

   ship[7].bckgrd_src_l = "grafika/b1.jpg";
   ship[7].bckgrd_src_d = "grafika/b1d.jpg";
   ship[7].rev_src_l = "grafika/rewers.jpg";
   ship[7].rev_src_d = "grafika/rewers2.jpg";

   ship[8].bckgrd_src_l = "grafika/b2.jpg";
   ship[8].bckgrd_src_d = "grafika/b2d.jpg";
   ship[8].rev_src_l = "grafika/rewers.jpg";
   ship[8].rev_src_d = "grafika/rewers2.jpg";

   ship[9].bckgrd_src_l = "grafika/b2.jpg";
   ship[9].bckgrd_src_d = "grafika/b2d.jpg";
   ship[9].rev_src_l = "grafika/rewers.jpg";
   ship[9].rev_src_d = "grafika/rewers2.jpg";

   ship[10].bckgrd_src_l = "grafika/b3.jpg";
   ship[10].bckgrd_src_d = "grafika/b3d.jpg";
   ship[10].rev_src_l = "grafika/rewers.jpg";
   ship[10].rev_src_d = "grafika/rewers2.jpg";

   ship[11].bckgrd_src_l = "grafika/b3.jpg";
   ship[11].bckgrd_src_d = "grafika/b3d.jpg";
   ship[11].rev_src_l = "grafika/rewers.jpg";
   ship[11].rev_src_d = "grafika/rewers2.jpg";
}


