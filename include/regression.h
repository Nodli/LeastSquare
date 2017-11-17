#ifndef REG_H
#define REG_H

class Regression{
public:
	Regression(int size, double* valuesX, double* valuesY);
	~Regression();

	double regLin();
	double regParab();
	
private:
	double size_;
	double* valuesX_;
	double* valuesY_;
};

#endif
