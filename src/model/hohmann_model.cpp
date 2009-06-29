// -*- Mode: c++; Coding: utf-8; tab-width: 4; -*-
#include <iostream>
#include <GL/gl.h>
#include <GL/glu.h>
#include "hohmann_model.hpp"
#include "../vm/obf_vm.hpp"
#include "../vm/mapped_port.hpp"

const double HohmannModel::G = 6.67428e-11;
const double HohmannModel::M = 6.0e+24;

HohmannModel::HohmannModel() 
	: score_(0.0), fuel_(0.0), vec_(0.0, 0.0), prevVec_(0.0, 0.0),
	  radius_(0.0), velocity_(0.0, 0.0), step_(0)
{
}

HohmannModel::~HohmannModel() {
}

void HohmannModel::initialize(boost::shared_ptr<ObfVM> vm) {
	MappedPort& outPort = vm->getOutputPort();

	score_ = outPort[0];
	fuel_ = outPort[1];
	vec_.setX(outPort[2]);
	vec_.setY(outPort[3]);
	radius_ = outPort[4];
	initRadius_ = vec_.length();

	std::cout << "now radius: " << initRadius_ << std::endl;
	std::cout << "now velocity: " << velocity_ << std::endl;
	std::cout << "need v: " << ::sqrt(G*M/initRadius_) << std::endl;
}

void HohmannModel::updateEnv(boost::shared_ptr<ObfVM> vm) {
	MappedPort& outPort = vm->getOutputPort();
	prevVec_ = vec_;

	score_ = outPort[0];
	fuel_ = outPort[1];
	vec_.setX(outPort[2]);
	vec_.setY(outPort[3]);
	radius_ = outPort[4];

	velocity_ = (prevVec_ - vec_);
	std::cout << "now radius: " << vec_.length() << std::endl;
	std::cout << "now velocity: " << velocity_ << std::endl;
	std::cout << "need v: " << ::sqrt(G*M/vec_.length()) << std::endl;
}

void HohmannModel::draw() {
	drawSatellite();
	drawEarth();
}

static void drawRect(double x1, double y1, double x2, double y2) {
//	std::cout << "drawRect:" << x1 << "," << y1 <<", "
//			  << x2 <<","<< y2 << std::endl;
	::glBegin(GL_LINE_LOOP); {
		::glVertex2d(x1, y1);
		::glVertex2d(x1, y2);
		::glVertex2d(x2, y2);
		::glVertex2d(x2, y1);
	} :: glEnd();
}

void HohmannModel::drawSatellite() {
	double w = 600;
	double h = 480;
	double x1 = (w / 2) - 5;
	double y1 = (h / 2) - 5;
	double x2 = (w / 2) + 5;
	double y2 = (h / 2) + 5;

	if ( ::fabs(vec_.length() - radius_) < 1000) {
		::glColor3f(1.0, 0.5, 0.5);
	} else {
		::glColor3f(1.0, 1.0, 1.0);
	}
	drawRect(x1, y1, x2, y2);
}

void HohmannModel::drawEarth() {
	double r = getTargetRadius();
	double w = 600;
	double h = 480;

	double userWidth = r * 3;
	double userHeight = (w / h) * userWidth;

	vector_t& now = getRelative();
	vector_t satellite = vector_t(userWidth / 2, userHeight / 2);
	vector_t earthPos = satellite - now;
	double posX = earthPos.getX() * 600 / userWidth;
	double posY = earthPos.getY() * 480 / userHeight;

	::glColor3f(1.0, 1.0, 1.0);
	drawRect(posX - 5, posY - 5, posX + 5, posY + 5);
}


//------------------------------------------------------------------------------
// getter methods.
//------------------------------------------------------------------------------
double HohmannModel::getScore() {
	return score_;
}

double HohmannModel::getFuel() {
	return fuel_;
}

HohmannModel::vector_t& HohmannModel::getRelative() {
	return vec_;
}

HohmannModel::vector_t& HohmannModel::getPrevRelative() {
	return prevVec_;
}

HohmannModel::vector_t& HohmannModel::getVelocity() {
	return velocity_;
}

double HohmannModel::getInitRadius() {
	return initRadius_;
}

double HohmannModel::getTargetRadius() {
	return radius_;
}
