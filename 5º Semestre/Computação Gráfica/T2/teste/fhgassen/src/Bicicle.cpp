/*********************************************************************
//  Esse arquivo é a classe responsável pela criação de uma bicicleta
//  A documentação das funções está no .hpp
// *********************************************************************/

#include "Bicicle.hpp"

using namespace std;


Bicicle::Bicicle(Point center_, double bicicle_scale_){
	// salva nas variaveis globais
	seat = center_;
	bicicle_scale = bicicle_scale_;

	// calcula os pontos da bicicleta, escalando os valores
	seat_coupler = {seat.x, seat.y-scale_value(5)};
	wheel_back_center = {seat_coupler.x-scale_value(100), seat_coupler.y-scale_value(50)};
	wheel_front_center = {seat_coupler.x+scale_value(130), seat_coupler.y-scale_value(50)};
	pedal_center = {wheel_back_center.x + (wheel_front_center.x-wheel_back_center.x)/2, seat_coupler.y-scale_value(60)};
	crossbar_coupler = {seat_coupler.x+scale_value(100), seat_coupler.y+scale_value(10)};
	handlebar_coupler = {crossbar_coupler.x-scale_value(25), crossbar_coupler.y+scale_value(30)};
	handlebar = {handlebar_coupler.x+scale_value(15), handlebar_coupler.y+scale_value(5)};
	pedal_outside.push_back({pedal_center.x+scale_value(20), pedal_center.y});
	pedal_outside.push_back({pedal_center.x-scale_value(20), pedal_center.y});
	wheel_back = new Wheel(wheel_back_center, bicicle_scale);
	wheel_front = new Wheel(wheel_front_center, bicicle_scale);

	// calcula os pontos do ciclista, escalando os pontos
	shoulder = {seat.x+scale_value(15), seat.y+scale_value(45)};
	head = {shoulder.x+scale_value(5), shoulder.y+scale_value(15)};
	left_elbow = {shoulder.x+scale_value(40), shoulder.y-scale_value(10)};
	right_elbow = {shoulder.x+scale_value(20), shoulder.y-scale_value(20)};
	leg_size = scale_value(50);
	calculate_knee(right_knee, pedal_outside[0]);
	calculate_knee(left_knee, pedal_outside[1]);
}

double Bicicle::scale_value(int value){
	return value*bicicle_scale;
}

void Bicicle::draw_bike(){

    //desenha a perna esquerda antes de tudo pra ficar "atrás" na tela
	color(0, 0, 0);
	draw_line(left_knee, seat);
	draw_line(left_knee, pedal_outside[1]);

	// desenha os pneus
	color(0.5, 0.5, 0.5);
	wheel_back->draw_wheel();
	wheel_front->draw_wheel();

	// desenha a estrutura geral da bicicleta
	draw_line(seat, seat_coupler);
	draw_line(seat_coupler, pedal_center);
	draw_line(seat_coupler, wheel_back_center);
	draw_line(seat_coupler, crossbar_coupler);
	draw_line(handlebar_coupler, crossbar_coupler);
	draw_line(crossbar_coupler, wheel_front_center);
	draw_line(handlebar_coupler, handlebar);
	draw_line(pedal_center, crossbar_coupler);
	draw_line(pedal_center, wheel_back_center);
	color(0, 1, 0);
	circleFill(pedal_outside[1].x, pedal_outside[1].y, scale_value(2), 100);
	color(0.54, 0, 0);
	draw_line(pedal_center, pedal_outside[1]);
	color(0.8, 0.8, 0.8);
	circleFill(pedal_center.x, pedal_center.y, scale_value(15), 100);
	color(0.5, 0.5, 0.5);
	circle(pedal_center.x, pedal_center.y, scale_value(15), 100);
	color(0.54, 0, 0);
	draw_line(pedal_center, pedal_outside[0]);
	color(0, 1, 0);
	circleFill(pedal_outside[0].x, pedal_outside[0].y, scale_value(2), 100);

	// desenha o resto do ciclista
	color(0, 0, 0);
	draw_line(seat, shoulder);
	draw_line(shoulder, head);
	draw_line(shoulder, left_elbow);
	draw_line(shoulder, right_elbow);
	draw_line(left_elbow, handlebar);
	draw_line(right_elbow, handlebar);
	draw_line(right_knee, seat);
	draw_line(right_knee, pedal_outside[0]);
	circleFill(head.x, head.y, scale_value(15), 100);

}

void Bicicle::move_bike(double speed){
	// movimenta os pneus
    wheel_back->rotate_wheel(speed);
    wheel_front->rotate_wheel(speed);

    // rotaciona os pedais
    rotate_pedal(speed, pedal_center, pedal_outside[0]);
    rotate_pedal(speed, pedal_center, pedal_outside[1]);

    // recalcula os joelhos
    calculate_knee(right_knee, pedal_outside[0]);
    calculate_knee(left_knee, pedal_outside[1]);
}

void Bicicle::draw_line(Point p1, Point p2){
	line(p1.x, p1.y, p2.x, p2.y);
}

void Bicicle::rotate_pedal(float rad, Point center, Point& pedal){
	float x_ = (pedal.x - center.x) * cos(rad) - (pedal.y - center.y) * sin(rad) + center.x;
	float y_ = (pedal.x - center.x) * sin(rad) + (pedal.y - center.y) * cos(rad) + center.y;
	pedal.x = x_;
	pedal.y = y_;
}

void Bicicle::calculate_knee(Point& knee, Point pedal){
	// álgebra necessária pra calcular os pontos dos joelhos. A grosso modo, 
	// calcula os dois pontos que distam o mesmo (leg_size) do pedal e do assento
	// e escolhe o de maior x pra ser o joelho
	float distance = sqrt(pow(seat.x-pedal.x, 2) + pow(seat.y-pedal.y, 2));
	float half_distance = distance/2;
	float h = sqrt(pow(leg_size, 2) - pow(half_distance, 2));
	float x2 = pedal.x + half_distance*(seat.x-pedal.x)/distance;
	float y2 = pedal.y + half_distance*(seat.y-pedal.y)/distance;
	float x3 = x2 + h*(seat.y-pedal.y)/distance;
	float y3 = y2 - h*(seat.x-pedal.x)/distance;
	knee.x = x3;
	knee.y = y3;
}
