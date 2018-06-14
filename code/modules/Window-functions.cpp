#include "window.hpp"

using namespace std;


//-------Inicjalizacja-------


void init()
{
   SDL_Init(SDL_INIT_EVERYTHING);
   IMG_Init(IMG_INIT_JPG);
}



//-------Window-------

//konstruktor
Window::Window(const int w, const int h, const char* s, const char* title): width(w), height(h), bckgrd_src(s)
{
   //inicjalizaca: SDL, IMG, okno i render

   window  = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
   renderer= SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
   surface = IMG_Load(bckgrd_src);
   texture = SDL_CreateTextureFromSurface(renderer, surface);
}


//-------Button-------


//konstruktory
Window::Button::Button(): width(0), height(0), x(0), y(0)
{
   surf = nullptr;
   text = nullptr;
   render = nullptr;
}
Window::Button::Button(const int x, const int y, const int w, const int h, SDL_Renderer* r, const char* src): width(w), height(h), x(x), y(y)
{
   surf = IMG_Load(src);
   render = r;
   text = SDL_CreateTextureFromSurface(r, surf);
   render = r;
   rect.x = x;
   rect.y = y;
   rect.w = w;
   rect.h = h;
}
//operator przypisania
Window::Button & Window::Button::operator=(const Button& b)
{
   x = b.x;
   y = b.y;
   width = b.width;
   height= b.height;
   surf  = b.surf;
   render = b.render;
   text  = SDL_CreateTextureFromSurface(render, surf);
   rect = b.rect;

   return *this;
}
//gettery i setter
int Window::Button::height_g()const {return height;}
int Window::Button::width_g() const {return width;}
int Window::Button::x_g()     const {return x;}
int Window::Button::y_g()     const {return y;}
void Window::Button::set_bckgrd(const char* src)
{
   //zanim nadpiszemy, musimy usunac
   SDL_FreeSurface(surf);
   SDL_DestroyTexture(text);
   //nadpisujemy
   surf = IMG_Load(src);
   text = SDL_CreateTextureFromSurface(render, surf);
}
void Window::Button::x_s(const int xx){x=xx;}
void Window::Button::y_s(const int yy){y=yy;}
//usuwanie okna
void Window::Button::close()
{
   SDL_DestroyRenderer(render);
   SDL_DestroyTexture(text);
   SDL_FreeSurface(surf);
}


