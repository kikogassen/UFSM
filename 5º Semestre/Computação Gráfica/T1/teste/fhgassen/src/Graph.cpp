/*********************************************************************
//  Esse arquivo é a classe responsável pela criação de um gráfico
// *********************************************************************/

using namespace std;

#include "gl_canvas2d.h"
#include "Graph.hpp"

//construtor do gráfico
Graph::Graph(const char* title, Point source, vector<float> input){
   m_title = title;
   m_source = source;
   m_input = input;

   //calcula a largura do gráfico
   dimension_x = input.size()*7 + 50;

   //calcula as retas e bordas dele
   border = {m_source, {m_source.x+dimension_x, m_source.y+dimension_y}};
   axis_x = {{m_source.x+5, m_source.y+(dimension_y/2)}, {m_source.x+(dimension_x-5), m_source.y+(dimension_y/2)}};
   axis_y = {{m_source.x+50, m_source.y+5}, {m_source.x+50, m_source.y+(dimension_y-5)}};
   title_locate = {source.x, source.y+dimension_y+10};

   //calcula a distância entre as marcas e as coordenadas das mesmas
   float x_source_axis = axis_y.p1.x;
   float distance_between_marks = (axis_x.p2.x - axis_y.p1.x)/input.size();
   for (int i=0;i<input.size();i++){
      marks.push_back({{x_source_axis+(i*distance_between_marks), axis_x.p1.y+5}, {x_source_axis+(i*distance_between_marks), axis_x.p1.y-5}});
   }

   //escala as alturas
   maiorInputInModule = returnMaiorInputInModule();
   if (maiorInputInModule>=1){
      float distanceFrom0ToLimit = dimension_y/2 - 5;
      float coeficient = distanceFrom0ToLimit/maiorInputInModule;
      for (int i=0;i<input.size();i++){
         input_points.push_back({marks[i].p1.x, input[i]*coeficient + axis_x.p1.y});
      }
      for (int i=-5;i<=5;i++){
         marks_vertical.push_back({{axis_y.p1.x-5, axis_x.p1.y + i*((dimension_y-10)/10)}, {axis_y.p1.x+5, axis_x.p1.y + i*((dimension_y-10)/10)}});
      }
   } else {
      for (int i=0;i<input.size();i++){
         input_points.push_back({marks[i].p1.x, axis_x.p1.y});
      }
   }
}

float Graph::returnMaiorInputInModule(){
   float maior = m_input[0], menor = m_input[0];
   for (int i=0;i<m_input.size();i++){
      if (m_input[i]>maior){
         maior = m_input[i];
      } else if (m_input[i]<menor){
         menor = m_input[i];
      }
   }
   return (abs(maior)>abs(menor)?abs(maior):abs(menor));
}
