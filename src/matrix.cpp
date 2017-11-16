#include <iostream>
#include <Matrix.h>

Matrix::Matrix(int sizeL, int sizeC): size_(sizeL * sizeC), sizeL_(sizeL), sizeC_(sizeC){
	//std::cout << "Matrix(int, int) at " << this << std::endl;
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){
		values_[i] = 0;
	}
}

Matrix::Matrix(int sizeL, int sizeC, double* values): size_(sizeL * sizeC), sizeL_(sizeL), sizeC_(sizeC){
	//std::cout << "Matrix(int, int, double*) at " << this << std::endl;
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){ //Because of the deletion of the table in ~Matrix
		values_[i] = values[i];
	}
}

Matrix::Matrix(const Matrix& m): size_(m.getSize()), sizeL_(m.getSizeL()), sizeC_(m.getSizeC()){
	//std::cout << "Matrix(Matrix) from " << &m << " at " << this << std::endl;
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){
		values_[i] = m.getValue(i);
	}
}

Matrix::~Matrix(){
	//std::cout << "~Matrix(int) at " << this << std::endl;
	delete[] values_;
}

void Matrix::setValue(double v, int n){
	std::cout << "setValue(double, int) from Matrix at " << this << std::endl;
	values_[n] = v;
}

void Matrix::setValue(double v, int l, int c){
	std::cout << "setValue(double, int, int) from Matrix at " << this << std::endl;
	values_[l * sizeC_ + c] = v;
}

void Matrix::removeL(int l){
	//std::cout << "removeL(int) from Matrix at " << this << std::endl;
	size_ -= sizeC_;
	double* newvalues = new double[size_];
	for(int li = 0; li != sizeL_; ++li){
		if(li != l){
			for(int c = 0; c != sizeC_; ++c){
				int nli = (li < l) ? li : (li - 1);
				newvalues[nli * sizeC_ + c] = values_[li * sizeC_ + c];
			}
		}
	}
	delete[] values_;
	values_ = newvalues;
	sizeL_ -= 1;
}

void Matrix::removeC(int c){
	//std::cout << "removeC(int) from Matrix at " << this << std::endl;
	size_ -= sizeL_;
	double* newvalues = new double[size_];
	for(int l = 0; l != sizeL_; ++l){
		for(int ci = 0; ci != sizeC_; ++ci){
			if(ci != c){
				int nci = (ci < c) ? ci : (ci - 1);
				newvalues[l * (sizeC_ - 1) + nci] = values_[l * sizeC_ + ci];
			}
		}
	}
	delete[] values_;
	values_ = newvalues;
	sizeC_ -= 1;
}

double Matrix::getValue(int n) const{
	return values_[n];
}

double Matrix::getValue(int l, int c) const{
	return values_[l * sizeC_ + c];
}

int Matrix::getSize() const{
	return size_;
}

int Matrix::getSizeL() const{
	return sizeL_;
}

int Matrix::getSizeC() const{
	return sizeC_;
}

void Matrix::display() const{
	//std::cout << "Displaying Matrix at " << this << std::endl;
	for(int i = 0; i != size_; ++i){
		std::cout << values_[i] << " ";
		if(!((i + 1) % sizeC_)){
			std::cout << std::endl;
		}
	}
}

void Matrix::trans(){
	//std::cout << "Transposing Matrix at " << this << std::endl;
	double* newvalues_ = new double[size_];
	int newindex = 0;
	for(int c = 0; c != sizeC_; ++c){
		for(int l = 0; l != sizeL_; ++l){
			newvalues_[newindex] = values_[l * sizeC_ + c];
			newindex += 1;
		}
	}
	delete[] values_;
	values_ = newvalues_;
	int newsizeC = sizeL_;
	sizeL_ = sizeC_;
	sizeC_ = newsizeC;
}

double Matrix::det22(){
    return values_[0] * values_[3] - values_[1] * values_[2];
}

double Matrix::detnn(double sum){
	//std::cout << "within detnn" << std::endl;
	if(sizeC_ == 2){
		return values_[0] * values_[3] - values_[1] * values_[2];
	}else{
		int l = 0; //Row to use for the decomposition
		for(int i = 0; i != sizeC_; ++i){
			Matrix detMat(*this);
			detMat.removeL(l);
			detMat.removeC(i);
			sum += pow(-1, i) * values_[i] * detMat.detnn(sum);
		}
		return sum;
	}
}

void Matrix::mul(double d){
	std::cout << "mul(double) at " << this << std::endl;
	for(int i = 0; i != size_; ++i){
        values_[i] *= d;
	}
}

void Matrix::mul(Matrix& m){
	std::cout << "Multiplying Matrix at " << this << " by Matrix at " << &m << std::endl;
	int newsize_ = sizeL_ * m.sizeC_;
	double* newvalues_ = new double[newsize_];
	for(int l = 0; l != sizeL_; ++l){ //Line index in the left matrix
		for(int c = 0; c != m.getSizeC(); ++c){ //Column index in the right matrix
			double value = 0;
			for(int i = 0; i != sizeC_; ++i){ //Value selection
				value += getValue(l, i) * m.getValue(i, c);
			}
			newvalues_[l * m.getSizeC() + c] = value;
		}
	}
	delete[] values_;
	values_ = newvalues_;
	size_ = newsize_;
	sizeC_ = m.getSizeC();
}

void Matrix::comat(){
	//std::cout << "Comatrix of Matrix at " << this << std::endl;
	double* newvalues = new double[size_];
	for(int l = 0; l != sizeL_; ++l){
		for(int c = 0; c != sizeC_; ++c){
			Matrix m(*this);
			m.removeL(l);
			m.removeC(c);
			newvalues[l * sizeC_ + c] = pow(-1, l + c) * m.detnn();
		}
	}
	delete[] values_;
	values_ = newvalues;
}

void Matrix::inv22(){
	std::cout << "Inverting 2x2 Matrix at " << this << std::endl;
	mul(1 / (values_[0] * values_[3] - values_[1] * values_[2]));
	double tempval = values_[0];
	values_[0] = values_[3];
	values_[3] = tempval;
	values_[1] = - values_[1];
	values_[2] = - values_[2];
}

//TODO
void Matrix::inv33(){
	//http://mathworld.wolfram.com/images/equations/MatrixInverse/NumberedEquation4.gif
	std::cout << "Inverting 3x3 Matrix at " << this << std::endl;
	double detMat = detnn();
	double* newvalues = new double[size_];
	comat();
	trans();
	mul(1 / detMat);
}
