#include <iostream>
#include <Matrix.h>

bool test_Matrix(){
	std::cout << "test_Matrix" << std::endl;

	Matrix m(3, 2);
	m.display();
	m.setValue(5., 1);
	m.setValue(3., 1, 0);
	m.display();
	std::cout << m.getValue(1) << std::endl;
	std::cout << m.getValue(1, 0) << std::endl;
	m.trans();
	m.display();

	double v0[4] = {2, 5, 3, 1};
	Matrix m0(2, 2, v0);
	m0.display();
	std::cout << "det22: " << m0.det22() << std::endl;
	//std::cout << "detnn: " << m0.detnn() << std::endl;
	m0.inv22();
	m0.display();

	double v1[3] = {8, 4, 3};
	Matrix m1(3, 1, v1);
	m1.display();

	m.mul(m1);
	m.display();
	m.mul(2.);
	m.display();

	double v2[9] = {1, 1, 2, 3, 4, -7, 6, 8, 2};
	Matrix m2(3, 3, v2);
	//m2.display();
	std::cout << "detnn: " << m2.detnn() << std::endl;
	//m2.removeL(1);
	//m2.removeC(1);
	//m2.display();

	double v4[9] = {0, 1, 2, -2, 3, -1, 4, 0, 1};
	Matrix m4(3, 3, v4);
	m4.display();
	//Matrix m5 = m4.comat();
	//m5.trans();
	//m5.display();
	m4.inv33();
	//m4.display();
}

double regLin(double* xvalues, double* yvalues, int size){
	double avalues[4] = {0, 0, 0, 0};
	double bvalues[2] = {0, 0};
	for(int i = 0; i != size; ++i){
		avalues[0] += xvalues[i] * xvalues[i];
		avalues[1] += xvalues[i];
		avalues[2] += xvalues[i];
		bvalues[0] += xvalues[i] * yvalues[i];
		bvalues[1] += yvalues[i];
	}
	avalues[3] = size;
    Matrix a(2, 2, avalues);
    a.display();
    Matrix b(2, 1, bvalues);
    b.display();
    a.inv22();
    a.display();
    a.mul(b);
    a.display();
}

double regParab(double* xvalues, double* yvalues, int size){
	double bvalues[3] = {0, 0, 0};
	double x3sum = 0;
	double x2sum = 0;
	double xsum = 0;
	for(int i = 0; i != size; ++i){
		avalues[0] += xvalues[i] * xvalues[i] * xvalues[i] * xvalues[i];
		x3sum += xvalues[i] * xvalues[i] * xvalues[i];
		x2sum += xvalues[i] * xvalues[i];
		xsum += xvalues[i];
		bvalues[0] += xvalues[i] * xvalues[i] * yvalues[i];
		bvalues[1] += xvalues[i] * yvalues[i];
		bvalues[2] += yvalues[i];
	}
	double avalues[9] = {x4sum, x3sum, x2sum, x3sum, x2sum, xsum, x2sum, xsum, size};
	Matrix a(3, 3, avalues);
    Matrix b(3, 1, bvalues);
	std::cout << "Matrix A: ";
	a.display();
    std::cout << "Matrix B: ";
    b.display();
    a.inv33();
    a.mul(b);
    a.display();
}

int main()
{
	//test_Matrix();
	double x[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	double y[16] = {1, 1, 2, 4, 6, 7, 6, 9, 6, 8, 10, 12, 14, 16, 19, 25};
	regLin(x, y, 16);
	regParab(x, y, 16);


    return 0;
}
