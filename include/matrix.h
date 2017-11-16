#ifndef MATRIX_H
#define MATRIX_H

inline double pow(double d, int e){
	double r = 1.;
	for(int i = 0; i != e; ++i){
		r *= d;
	}
	return r;
}

class Matrix{
public:
	Matrix(int sizeX, int sizeY);
	Matrix(int sizeX, int sizeY, double* values);
	Matrix(const Matrix& m);
	~Matrix();

	//Modifiers
	void setValue(double v, int n); //value to set at values_[n]
	void setValue(double v, int l, int c); //value to set at coordinates (l, c) in the matrix
	void removeL(int l);
	void removeC(int c);

	double getValue(int n) const; //value at values_[n]
	double getValue(int l, int c) const; //value at coordinates (l, c) in the matrix

	int getSize() const;
	int getSizeL() const;
	int getSizeC() const;

	void display() const;

	void trans();
	double det22();
	double detnn(double sum = 0);
	void mul(double d);
	void mul(Matrix& m); //TODO: Change this to an operator overload *
	void comat();
	void inv22();
	void inv33();

private:
	int size_;
	int sizeL_;
	int sizeC_;
	double* values_;
};

#endif
