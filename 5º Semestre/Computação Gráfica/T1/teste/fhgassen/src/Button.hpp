/*********************************************************************
//  Esse arquivo é o cabeçalho do Button.cpp
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
#include <string>

using namespace std;

class Button {

   public:
      string m_text;
      Point m_source;
      Rectangol m_design;

      Button(const char* text, Point source);
};
