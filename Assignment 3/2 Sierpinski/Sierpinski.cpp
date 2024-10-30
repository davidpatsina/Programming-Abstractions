/*
 * File: Sierpinski.cpp
 * --------------------------
 * Name: [TODO: enter name here]
 * Section: [TODO: enter section leader here]
 * This file is the starter project for the Sierpinski problem
 * on Assignment #3.
 * [TODO: extend the documentation]
 */

#include <iostream>
#include "gwindow.h"
#include "console.h"
#include "gobjects.h"
#include <cmath> 
using namespace std;

double const sin60 = sqrt(3.0)/2;////~0.86602540378443865;


void solution();
void drwaSierpinskiTriangle(GWindow gw, GPoint orientalPoint, double length, int order);
void drawTriangle(GWindow gw, GPoint orientalPoint, double length);

int main() {

	solution();
    return 0;
}

void solution(){
	double length;
	int order;

	GWindow gw;
	double xCoordinateOfOrientalPoint = gw.getWidth()/2.0;
	double yCoordinateOfOrientalPoint = gw.getHeight()/2.0;
	GPoint orientatalPoint(xCoordinateOfOrientalPoint, yCoordinateOfOrientalPoint);

	cout<<"Enter the length of triangle: "<<endl;
	cin>>length;
	cout<<"Enter the order: "<<endl;
	cin>>order;
	drwaSierpinskiTriangle(gw, orientatalPoint, length, order);
	
}

void drwaSierpinskiTriangle(GWindow gw, GPoint orientalPoint, double length, int order){
	if (order == 0){
		drawTriangle(gw, orientalPoint, length);
		return;
	}
	
	double median = length*sin60;
	
	double newLength = length/2.0;
	GPoint newOrientalPoint1(orientalPoint.getX(), orientalPoint.getY()-median/3);
	GPoint newOrientalPoint2(orientalPoint.getX() - length/4.0, orientalPoint.getY() + median/6);
	GPoint newOrientalPoint3(orientalPoint.getX() + length/4.0, orientalPoint.getY() + median/6);

	drwaSierpinskiTriangle(gw, newOrientalPoint1, newLength, order-1);
	drwaSierpinskiTriangle(gw, newOrientalPoint2, newLength, order-1);
	drwaSierpinskiTriangle(gw, newOrientalPoint3, newLength, order-1);

}

void drawTriangle(GWindow gw, GPoint orientalPoint, double length){
	double median = length*sin60;
	double x1 = orientalPoint.getX();
	double y1 = orientalPoint.getY() - (2.0*median/3.0);
	GPoint point1(x1,y1); 
	
	double x2 = orientalPoint.getX() - length/2.0;
	double y2 = orientalPoint.getY() + median/3.0;
	GPoint point2(x2,y2);
	
	double x3 = orientalPoint.getX() + length/2.0;
	double y3 = orientalPoint.getY() + median/3.0;
	GPoint point3(x3,y3);

	gw.drawLine(point1, point2);
	gw.drawLine(point1, point3);
	gw.drawLine(point3, point2);
}



