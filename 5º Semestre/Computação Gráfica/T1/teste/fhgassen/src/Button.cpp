/*********************************************************************
//  Esse arquivo é a classe responsável pela criação de um botão
// *********************************************************************/

using namespace std;

#include "gl_canvas2d.h"
#include "Button.hpp"

//struct do botão
Button::Button(const char* text, Point source){
   m_text = text;
   m_source = source;
   Point p2 = {source.x+(m_text.length()*11), source.y+20};
   m_design = {m_source, p2};
}
