/*
 *
 *
 *  arquivo responsável pela implementação das funções explicadas no arquivo Object.hpp
 *
 *
 */

#include "Object.hpp"

Object::Object(vector<Point> vectorBezier_, Point source_, Point source_object_){
	vectorBezier = vectorBezier_;
    source_object = source_object_;
    source = source_;

    //inicia os angulos de rotação em 0
    angle_x = 0;
    angle_y = 0;
}

void Object::printaMatrix(){
    //printa os pontos de uma matriz
	printf("\n");
	for (int i=0;i<matrixPoints.size();i++){
		vector<Point> v = matrixPoints[i];
		printf("%d: ", i);
		for (int j=0;j<v.size();j++){
			Point p = v[j];
			printf("{%.0f, %.0f, %.0f}, ", p.x, p.y, p.z);
		}
		printf("\n");
	}
}

void Object::calculateBezierPoints(){
    //calcula os pontos gerados a partir da bezier para depois rotacioná-los
    matrixPoints.clear();
    vector<Point> bezierPoints;
	//parametriza o incremento
    float increment = 1/((float)num_camadas);
    for (float t=0;t<=1;t+=increment){
      float x = 0.0, y = 0.0;
      for (int i=0;i<vectorBezier.size();i++){
         x += vectorBezier[i].x * blendingFunction(t, i);
         y += vectorBezier[i].y * blendingFunction(t, i);
     }
     bezierPoints.push_back({x, y, 0});
 }
 matrixPoints.push_back(bezierPoints);
}

void Object::calculateObjectPoints(){
    //calcula os pontos do objeto, rotacionando a bezier em torno do y
	vector<Point> bezierPoints = matrixPoints[0];
	//parametriza o incremento
	float increment = PI_2/((float)num_fatias);
	for (float angle=0;angle<PI_2;angle+=increment){
		vector<Point> slicePoints;
		for (int i=0;i<bezierPoints.size();i++){
			Point p = bezierPoints[i];
			//rotação em torno do y
			Point rotated;
			rotated.x = p.z * sin(angle) + p.x * cos(angle);
			rotated.y = p.y;
			rotated.z = p.z * cos(angle) - p.x * sin(angle);
			slicePoints.push_back(rotated);
		}
		matrixPoints.push_back(slicePoints);
	}
}

int Object::getVectorBezierSize(){
	return vectorBezier.size();
}

void Object::setX(float x, int id){
	vectorBezier[id].x = x;
}

void Object::setY(float y, int id){
	vectorBezier[id].y = y;
}

void Object::drawPoints(){
	color(0, 0, 0);
	//desenha os pontos de controle e as linhas do grafo de controle
	for (int i=0;i<vectorBezier.size();i++){
		circleFill(vectorBezier[i].x+source.x, vectorBezier[i].y+source.y, BEZIER_POINT_RADIUS, 30);
		if (i>0){
			line(vectorBezier[i].x+source.x, vectorBezier[i].y+source.y, vectorBezier[i-1].x+source.x, vectorBezier[i-1].y+source.y);
		}
	}
}

float Object::blendingFunction(float t, int id){
	float result = pow(1-t, 3-id) * pow(t, id) * 3;
	return (id==3 || id==0 ? result/3 : result);
}

void Object::drawBezierCurve(){
	drawPoints();
	color(1, 0, 0);
	//desenha a curva de bezier
	for (float t=0;t<=1;t+=0.001){
		float x = 0.0, y = 0.0;
		for (int i=0;i<vectorBezier.size();i++){
			x += vectorBezier[i].x * blendingFunction(t, i);
			y += vectorBezier[i].y * blendingFunction(t, i);
		}
		circleFill(x+source.x, y+source.y, 1, 10);
	}
}

bool Object::clickedInsidePoint(int id, Point mouse){
	Point p = vectorBezier[id];
	if (distance(p, mouse)<=BEZIER_POINT_RADIUS){
		return true;
	}
	return false;
}

float Object::distance(Point p1, Point p2){
	return (float) sqrt(pow(p2.x-p1.x, 2) + pow(p2.y-p1.y, 2));
}

Point Object::translade(Point p){
    Point resp;

    resp.x = p.x;
    resp.y = p.y;
    resp.z = p.z - 300;

    return resp;
}

Point Object::project(Point p){
	float d = -200;
	Point resp;
	resp.x = (p.x*d) / p.z;
	resp.y = (p.y*d) / p.z;
	resp.z = 0;
	return resp;
}

Point Object::rotate_x(Point p){
	Point resp;
	resp.x = p.x;
	resp.y = p.y*cos(angle_x) - p.z*sin(angle_x);
	resp.z = p.y*sin(angle_x) + p.z*cos(angle_x);
	return resp;
}

Point Object::rotate_y(Point p){
	Point resp;
	resp.x = p.z*sin(angle_y) + p.x*cos(angle_y);
	resp.y = p.y;
	resp.z = p.z*cos(angle_y) - p.x*sin(angle_y);
	return resp;
}

void Object::calculate(){
    //calcula os pontos da bezier, depois calcula os pontos do objeto e após calcula os pontos pra projeção
    calculateBezierPoints();
    calculateObjectPoints();
    calculateProjectedObject();
}

void Object::calculateProjectedObject(){
    matrixTransformed.clear();
    for (int i=0;i<matrixPoints.size();i++){
        vector<Point> collumn = matrixPoints[i];
        vector<Point> transformed;
        for (int j=0;j<collumn.size();j++){
            Point p = collumn[j];
            //rotaciona em x e y conforme os WASD
            p = rotate_x(p);
            p = rotate_y(p);

            //translada pra longe da câmera
            p = translade(p);

            if (projection==0){
                //projeta o mesmo
                p = project(p);
            }
            transformed.push_back(p);
        }
        matrixTransformed.push_back(transformed);
    }
}

void Object::drawObject(){

    //desenha os pontos da matriz transformada
    for (int i=0;i<matrixTransformed.size();i++){
        vector<Point> collumn = matrixTransformed[i];
        for (int j=0;j<collumn.size();j++){
            Point p = collumn[j];
            point(p.x+source_object.x, p.y+source_object.y);
        }
    }

        //liga os pontos da matriz transformada
    for (int i=0;i<matrixTransformed.size();i++){
        vector<Point> collumn = matrixTransformed[i];
        for (int j=0;j<collumn.size();j++){
            if (i+1==matrixTransformed.size()){
                line(matrixTransformed[i][j].x+source_object.x, matrixTransformed[i][j].y+source_object.y, matrixTransformed[0][j].x+source_object.x, matrixTransformed[0][j].y+source_object.y);
            } else {
                line(matrixTransformed[i][j].x+source_object.x, matrixTransformed[i][j].y+source_object.y, matrixTransformed[i+1][j].x+source_object.x, matrixTransformed[i+1][j].y+source_object.y);
            }
            if (j+1<collumn.size()){
                line(matrixTransformed[i][j].x+source_object.x, matrixTransformed[i][j].y+source_object.y, matrixTransformed[i][j+1].x+source_object.x, matrixTransformed[i][j+1].y+source_object.y);
            }
        }
    }

}
