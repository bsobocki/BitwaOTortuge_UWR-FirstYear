#ifndef GAME_HPP_INCLUDED
#define GAME_HPP_INCLUDED
#include "Choose.hpp"

class Game: public Window
{
public:
   //klasa gracza
   class Player
   {
   public:
      //pola
      int score; //punkty
      bool fleet; //flote gracza | true - piraci | false - hiszpanie
      int num_of_ships; //liczba odkrytych statkow
      //wyswietlanie punktacji
      SDL_Surface* s;
      SDL_Texture* t;
      SDL_Surface* sscr;
      SDL_Texture* tscr;

      //konstruktory
      Player();
      Player(const bool f, const int num, const char* src, SDL_Renderer* ren);

      //operator
      Player & operator = (const Player& p);
   };

public:
   //klasa okretu - pionka
   class Ship: public Button
   {
   public:
      //pola
      int field_num;                        //numer pola na ktorym znajduje sie obecnie
      const char* bckgrd_src_l = nullptr;   //sciezka do jasnego obrazu pionka
      const char* bckgrd_src_d = nullptr;   //sciezka do ciemnego obrazu pionka
      bool rev;                             //informacja czy ma byc wyswietlony rewers
      const char* rev_src_l = nullptr;      //sciezka do rewersu (jasnego)
      const char* rev_src_d = nullptr;      //sciezka do rewersu (ciemnego)
      int rot;                              //ilosc obrotow w prawo
      bool show;                            //czy pokazac go (czy nie jest zatopiony)
      int fleet;                            //flota: 1-piraci | 0-hiszpanie | -1-nikt
      int index;                            //indeks statku w tablicy okretow
      bool zero;                            //czy jest to "zerowy" okret (czyli okret zbity)
      bool able_to_move;                    //mozna dany okret obrocic
      int score;                            //wartosc punktowa okretu

   public:
      //konstruktory
      Ship();
      Ship(const int x, const int y, const int w, const int h, SDL_Renderer* r, char* src, const int numfield, char* dark_bckgrd, const bool _rev, char* rev_srcL, char* rev_srcD, const int fl, const int ind, const int scr);
      Ship(const Ship&);

      //operator
      Ship & operator = (Ship &);

      //metody
      void set_bckgrd(const char* src);
      void update_coordinates(const int xx, const int yy);
      void close();
   };

public:
   //klasa pojedynczego pola
   class Field
   {
   public:
      //pola
      int x;
      int y;
      int number;     //numer pola na planszy (numerowane od lewego pola na samej gorze od 0 kolejne numerowane w prawo)
      Ship outdoor;   //odkryty statek
      Ship hidden;    //ukryty statek (przykryty przez inny statek)

      //konstruktory
      Field();
      Field(const int num, const int xx, const int yy);

      //operator
      Field & operator = (Field& f);

      //metody
      void changeHidden(Game::Ship & s);   //zmiana ukrytego statku
      void changeOutdoor(Game::Ship & s);  //zmiana odkrytego statku
      void close();
   };

public:
   //Obiekty gry: gracze, pionki (okrety), pola planszy,
   Player player1;
   Player player2;
private:
   Ship   zero_ship;          //"zerowy statek" sluzacy do usuwania istniejacych zbitych statkow (poprzez napisanie tym statkiem)
   Button zero_stroke;        //"zerowe zaznaczenie" sluzace do usuwania zaznaczenia
   Button img_fleet;          //obrazek floty aktualnie wyswietlanej
   Ship   ship[12];           //osiem pionkow statkow bedacych reprezentowanymi poprzez klase Button
   Field  field[12];          //osiem pol na planszy
   Button stroke;             //zaznaczenie danego pola
   static int selected;       //numer zaznaczonego obiektu
   bool current_fleet;        //flota aktualnego gracza

   //tablica polozenia pol na planszy wzgledem wspolzednej x
   int X[12];

   //tablica polozenia pol na planszy wzgledem wspolzednej y
   int Y[12];

public:
   //konstruktor
   Game(const int w, const int h, const char* src, const bool Player1_fleet);

   //metody
   bool show();
   void change_buttons(const int x, const int y);   //zmiana tekstur w zaleznosci
   void change(Ship & b, const int i, const int x, const int y); //od najechania czy klikniecia
   void close(); //zamyka i usuwa okno
   int* randomize(); //sluzy do losowania rozmieszczenia okretow na poczatku gry
   void sources(); //inicjuje zrodla statkow
   void action(); //wykonanywanie akcji na okretach
   bool winner(); //sprawdzenie wygranego oraz wyswietlenie informacji o wygranej
   bool click; //po zaznaczeniu nie trzeba na nowo robic ciagle nowych stroke'ow

   //poruszanie sie okretow
   bool move_up(Field& f);
   bool move_down(Field& f);
   bool move_left(Field& f);
   bool move_right(Field& f);
   bool move_up_left(Field& f);
   bool move_up_right(Field& f);
   bool move_down_left(Field& f);
   bool move_down_right(Field& f);

   //wplyniecie statku z pola f na pole s
   void attack(Field& f, Field& s);
   //pokazywanie wynikow
   void show_scores(SDL_Rect& r, Player& p);
   void players_scores();
};

#endif // GAME_HPP_INCLUDED
