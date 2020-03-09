/*********************************************************************
//  Esse arquivo é a classe responsável pela criação de um pneu
// *********************************************************************/

#include "Wheel.hpp"

using namespace std;

Wheel::Wheel(Point center_, double bicicle_scale_){
	// salva nas variaveis globais
	center = center_;
	bicicle_scale = bicicle_scale_;

	// cria os aros do pneu
	instantiate_hoops();
}

void Wheel::rotate_hoop(float rad, Line& hoop){
	float x_ = (hoop.p2.x - hoop.p1.x) * cos(rad) - (hoop.p2.y - hoop.p1.y) * sin(rad) + hoop.p1.x;
	float y_ = (hoop.p2.x - hoop.p1.x) * sin(rad) + (hoop.p2.y - hoop.p1.y) * cos(rad) + hoop.p1.y;
	hoop.p2.x = x_;
	hoop.p2.y = y_;
}

void Wheel::instantiate_hoops(){
	// calcula o raio entre cada aro
	float radius_between_hoops = PI_2/NUMBER_OF_HOOPS;

	// cria os NUMBER_OF_HOOPS aros e rotaciona o mesmo pra sua posição inicial
	for (int i=0;i<NUMBER_OF_HOOPS;i++){
		hoops.push_back({center, {center.x+scale_value(WHEEL_RADIUS), center.y}});
		rotate_hoop(i*radius_between_hoops, hoops[i]);
	}
}

void Wheel::rotate_wheel(double speed){
	// rotaciona cada um dos aros
	for (int i=0;i<hoops.size();i++){
		rotate_hoop(speed, hoops[i]);
	}
}

void Wheel::draw_wheel(){
	// desenha o pneu um pouco mais espesso
    for (int i=-2;i<=2;i++){
        circle(center.x, center.y, scale_value(WHEEL_RADIUS)+i, 100);
    }

    // desenha os aros
	for (int i=0;i<hoops.size();i++){
		line(hoops[i].p1.x, hoops[i].p1.y, hoops[i].p2.x, hoops[i].p2.y);
	}
}

double Wheel::scale_value(int value){
	return value*bicicle_scale;
}
