#include <iostream>
#include <matrix.h>


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
	
/*
	Determinant of matrix is calculated only for square matrices.

For non-square matrices, there’s no determinant value.

Same is the case for Inverse of matrix.
*/
/*
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
*/
}

bool test_reg(){
	double x[16] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15};
	double y[16] = {1, 1, 2, 4, 6, 7, 6, 9, 6, 8, 10, 12, 14, 16, 19, 25};
	//regLin(x, y, 16);
	//regParab(x, y, 16);
}

int main()
{
	test_Matrix();
	//test_reg;


    return 0;
}
