#include <iostream>
#include <limits>
#include <cassert>
#include <regression.h>
#include <matrix.h>

Regression2D::Regression2D(int s, const double* valuesX, const double* valuesY): size_(s){
	valuesX_ = new double[size_];
	valuesY_ = new double[size_];
	for(int i = 0; i != size_; ++i){
		valuesX_[i] = valuesX[i];
		valuesY_[i] = valuesY[i];
	}
}

Regression2D::~Regression2D(){
	delete[] valuesX_;
	delete[] valuesY_;
}

void Regression2D::Linear() const{
	double avalues[4] = {0, 0, 0, 0};
	double bvalues[2] = {0, 0};
	for(int i = 0; i != size_; ++i){
		avalues[0] += valuesX_[i] * valuesX_[i];
		avalues[1] += valuesX_[i];
		avalues[2] += valuesX_[i];
		bvalues[0] += valuesX_[i] * valuesY_[i];
		bvalues[1] += valuesY_[i];
	}
	avalues[3] = size_;
	Matrix a(2, 2, avalues);
	Matrix b(2, 1, bvalues);
	a.inv22() *= b;
	std::cout << "(a, b) = (" << a.getValue(0) << ", " << a.getValue(1) << ")" << std::endl;
}

void Regression2D::Parabolic() const{
	double bvalues[3] = {0, 0, 0};
	double x4sum = 0;
	double x3sum = 0;
	double x2sum = 0;
	double xsum = 0;
	for(int i = 0; i != size_; ++i){
		x4sum += valuesX_[i] * valuesX_[i] * valuesX_[i] * valuesX_[i];
		x3sum += valuesX_[i] * valuesX_[i] * valuesX_[i];
		x2sum += valuesX_[i] * valuesX_[i];
		xsum += valuesX_[i];
		bvalues[0] += valuesX_[i] * valuesX_[i] * valuesY_[i];
		bvalues[1] += valuesX_[i] * valuesY_[i];
		bvalues[2] += valuesY_[i];
	}
	double avalues[9] = {x4sum, x3sum, x2sum, x3sum, x2sum, xsum, x2sum, xsum, size_};
	Matrix a(3, 3, avalues);
    Matrix b(3, 1, bvalues);
    a.inv33();
    a *= b;
    std::cout << "(a, b, c) = (" << a.getValue(0) << ", " << a.getValue(1) << ", " << a.getValue(2) << ")" << std::endl;
}
