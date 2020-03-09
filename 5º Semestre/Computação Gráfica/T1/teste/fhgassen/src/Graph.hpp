/*********************************************************************
//  Esse arquivo é o cabeçalho do Graph.cpp
// *********************************************************************/

#pragma once

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include "Structs.hpp"

#include <vector>
#include <cmath>
#include <iostream>

using namespace std;

class Graph {

   private:

      float returnMaiorInputInModule();

   public:
      int dimension_x; // largura do gráfico, calculável
      int dimension_y = 250; // altura do gráfico
      string m_title; // título do gráfico
      Point m_source; // ponto inicial do gráfico, esquerda inferior
      vector<float> m_input; // vetor de dados pro gráfico
      Rectangol border; // retângulo com a borda do gráfico
      Line axis_x; // eixo x
      Line axis_y; // eixo y
      vector<Line> marks; // marcas horizontais do gráfico
      vector<Line> marks_vertical; // marcas verticais do gráfico
      vector<Point> input_points; // pontos do gráfico
      Point title_locate; // localização do título
      float maiorInputInModule; // maior valor absoluto dos dados de entrada

      Graph(const char* title, Point source, vector<float> input);
};
