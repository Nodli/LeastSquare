#include <iostream>
#include <cassert>
#include <matrix.h>

Matrix::Matrix(int sizeL, int sizeC): size_(sizeL * sizeC), sizeL_(sizeL), sizeC_(sizeC){
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){
		values_[i] = 0;
	}
}

Matrix::Matrix(int sizeL, int sizeC, const double* values): size_(sizeL * sizeC), sizeL_(sizeL), sizeC_(sizeC){
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){ //Dynamic copy of the values
		values_[i] = values[i];
	}
}

Matrix::Matrix(const Matrix& m): size_(m.size_), sizeL_(m.sizeL_), sizeC_(m.sizeC_){
	values_ = new double[size_];
	for(int i = 0; i != size_; ++i){ //Dynamic copy of the values
		values_[i] = m.values_[i];
	}
}

Matrix::~Matrix(){
	delete[] values_; //Dynamic allocation must be freed
}

void Matrix::setValue(int n, double v){
	assert(n < size_);

	values_[n] = v;
}

void Matrix::setValue(int l, int c, double v){
	assert(l < sizeL_);
	assert(c < sizeC_);

	values_[l * sizeC_ + c] = v;
}

void Matrix::removeL(int l){
	assert(l < sizeL_);

	size_ -= sizeC_;
	double* newvalues = new double[size_];
	for(int li = 0; li != sizeL_; ++li){ //Line index in the former Matrix
		if(li != l){
			for(int c = 0; c != sizeC_; ++c){
				int nli = (li < l) ? li : (li - 1); //Line index in the new Matrix
				newvalues[nli * sizeC_ + c] = values_[li * sizeC_ + c];
			}
		}
	}
	delete[] values_; //Dynamic allocation must be freed
	values_ = newvalues;
	sizeL_ -= 1;
}

void Matrix::removeC(int c){

	size_ -= sizeL_;
	double* newvalues = new double[size_];
	for(int l = 0; l != sizeL_; ++l){
		for(int ci = 0; ci != sizeC_; ++ci){ //Column index in the former Matrix
			if(ci != c){
				int nci = (ci < c) ? ci : (ci - 1); //Column index in the new Matrix
				newvalues[l * (sizeC_ - 1) + nci] = values_[l * sizeC_ + ci];
			}
		}
	}
	delete[] values_; //Dynamic allocation must be freed
	values_ = newvalues;
	sizeC_ -= 1;
}

double Matrix::getValue(int n) const{
	assert(n < size_);

	return values_[n];
}

double Matrix::getValue(int l, int c) const{
	assert(l < sizeL_);
	assert(c < sizeC_);

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
	for(int i = 0; i != size_; ++i){
		std::cout << values_[i] << " ";
		if(!((i + 1) % sizeC_)){ //Line formating
			std::cout << std::endl;
		}
	}
}

Matrix& Matrix::operator*=(double d){
	for(int i = 0; i != size_; ++i){
        values_[i] *= d;
	}

	return *this;
}

Matrix& Matrix::operator*=(const Matrix& m){
	assert(sizeC_ == m.sizeL_);

	int newsize_ = sizeL_ * m.sizeC_;
	double* newvalues_ = new double[newsize_];
	for(int l = 0; l != sizeL_; ++l){ //Line index in the left matrix
		for(int c = 0; c != m.sizeC_; ++c){ //Column index in the right matrix
			double value = 0;
			for(int i = 0; i != sizeC_; ++i){ //Value selection in the column
				value += values_[l * sizeC_ + i] * m.values_[i * m.sizeC_ + c];
			}
			newvalues_[l * m.sizeC_ + c] = value;
		}
	}
	delete[] values_;
	values_ = newvalues_;
	size_ = newsize_;
	sizeC_ = m.sizeC_;

	return *this;
}

double Matrix::det(){
	assert(sizeL_ == sizeC_);

	if(sizeC_ == 2){ //End of the recursion
		return values_[0] * values_[3] - values_[1] * values_[2];
	}else{
		int det = 0;
		int l = 0; //Line to use for the recursive decomposition
		for(int i = 0; i != sizeC_; ++i){
			Matrix subMat(*this);
			subMat.removeL(l);
			subMat.removeC(i);
			det += pow(-1, i) * values_[i] * subMat.det();
		}

		return det;
	}
}

Matrix& Matrix::trans(){
	double* newvalues_ = new double[size_];
	int newindex = 0;
	for(int c = 0; c != sizeC_; ++c){
		for(int l = 0; l != sizeL_; ++l){
			newvalues_[newindex] = values_[l * sizeC_ + c];
			newindex += 1;
		}
	}
	delete[] values_; //Dynamic allocation must be freed
	values_ = newvalues_;
	int buffer = sizeL_; //Buffer for switching sizes
	sizeL_ = sizeC_;
	sizeC_ = buffer;

	return *this;
}

Matrix& Matrix::comat(Matrix& comat){
	assert(sizeL_ == sizeC_);

	double* cofValues = new double[size_];
	for(int l = 0; l != sizeL_; ++l){
		for(int c = 0; c != sizeC_; ++c){
			Matrix cofMat(*this); //Submatrix to compute the determinant on
			cofMat.removeL(l);
			cofMat.removeC(c);
			cofValues[l * sizeC_ + c] = pow(-1, l + c) * cofMat.det();
		}
	}
	comat.size_ = size_;
	comat.sizeL_ = sizeL_;
	comat.sizeC_ = sizeC_;
	delete[] comat.values_;
	comat.values_ = cofValues;

	return comat;
}

Matrix& Matrix::inv22(){
	assert(sizeL_ == sizeC_);

	operator*=(1 / (values_[0] * values_[3] - values_[1] * values_[2]));
	double tempval = values_[0]; //Buffer for switching values
	values_[0] = values_[3];
	values_[3] = tempval;
	values_[1] = - values_[1];
	values_[2] = - values_[2];

	return *this;
}

Matrix& Matrix::inv33(){
	assert(sizeL_ == sizeC_);

	Matrix adjMat(0, 0);
	comat(adjMat).trans();
	adjMat *= 1 / det();
	double* tempValues = adjMat.values_; //Buffer for switching values
	adjMat.values_ = values_; //Dynamic allocation will be freed on adjMat deletion at then end of the block
	values_ = tempValues;

	return *this;
}
