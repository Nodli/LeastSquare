#include <iostream>
#include <matrix.h>
#include <regression.h>

bool test_Matrix(){
	std::cout << "test_Matrix" << std::endl;
	Matrix m0(1, 5);
	m0.display();

	double v1[4] = {1., 5., 2., 7.};
	Matrix m1(2, 2, v1);
	m1.display();

	Matrix m2(m0);
	m2.display();

	m2.setValue(1, 7.);
	m2.display();
	m2.setValue(0, 4, 10.);
	m2.display();

	double v3[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
	Matrix m3(3, 3, v3);
	m3.display();
	m3.removeL(2);
	m3.display();
	m3.removeC(2);
	m3.display();

	std::cout << m3.getValue(1) << std::endl;
	std::cout << m3.getValue(1, 1) << std::endl;
	std::cout << m3.getSize() << std::endl;
	std::cout << m0.getSizeL() << std::endl;
	std::cout << m0.getSizeC() << std::endl;

	double v4[9] = {1., 2., 3., 4., 5., 6., 7., 8., 9.};
	Matrix m4(3, 3, v4);
	m4.display();
	(m4 *= 2.).display();

	double v5[3] = {10., 11., 12.};
	Matrix m5(3, 1, v5);
	m5.display();
	(m4 *= m5).display();

	double v6[9] = {1., 9., 2., 8., 3., 7., 4., 6., 5.};
	Matrix m6(3, 3, v6);
	m6.display();
	std::cout << m6.det() << std::endl;

	m4.display();
	m4.trans().display();

	double v7[9] = {3., 4., 5., -1., 3., 6., 3., 4., -5.};
	Matrix m7(3, 3, v7);
	Matrix m8(0, 0);
	m7.comat(m8).display();

	double v9[4] = {4., 3., 3., 2.};
	Matrix m9(2, 2, v9);
	m9.inv22().display();

	double v10[9] = {7., 2., 1., 0., 3., -1., -3., 4., -2.};
    Matrix m10(3, 3, v10);
    m10.display();
    m10.inv33().display();

	return true;
}

bool test_Regression2D(){
	double x[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	double y[16] = {1, 1, 2, 4, 6, 7, 6, 9, 6, 8, 10, 12, 14, 16, 19, 25};
	Regression2D r(16, x, y);
	r.Linear();
	r.Parabolic();

	return true;
}

int main()
{
	test_Matrix();
	test_Regression2D();

    return 0;
}
