#ifndef MATRIX_H
#define MATRIX_H

class Matrix{
public:
	/**
	* \brief Constructor of an empty Matrix
	* \param[in] sizeL Number of lines in the Matrix
	* \param[in] sizeC Number of columns in the Matrix
	*/
	Matrix(int sizeL, int sizeC);
	/**
	* \brief Constructor of a filled Matrix
	* \param[in] sizeL Number of lines in the Matrix
	* \param[in] sizeC Number of columns in the Matrix
	* \param[in] values Table holding the values of the Matrix such as
	*  values_[n] = l * sizeL_ + c with (l, c) the coordinates of the cell in
	*  the Matrix
	*/
	Matrix(int sizeL, int sizeC, const double* values);
	/*
	* \brief Copy constructor of a Matrix
	* \param[in] m Matrix to copy
	*/
	Matrix(const Matrix& m);
	/*
	* \brief Destructor of a Matrix
	*/
	~Matrix();


	/**
	* \brief Sets a value in the Matrix using raw coordinates
	* \param[in] n Raw index of the cell to modify [0, size_ - 1]
	*  n = l * sizeL_ + c with (l, c) the coordinates of the cell in the Matrix
	* \param[in] v Value to be set in the Matrix
	*/
	void setValue(int n, double v);
	/**
	* \brief Sets a value in the Matrix using matrix coordinates
	* \param[in] l Line index of the cell to modify [0, sizeL_ - 1]
	* \param[in] c Column index of the cell to modify [0, sizeC_ - 1]
	* \param[in] v Value to be set in the Matrix
	*/
	void setValue(int l, int c, double v);
	/**
	* \brief Removes a line from the Matrix
	* \param[in] l Index of the line to remove [0, sizeL_ - 1]
	*/
	void removeL(int l);
	/**
	* \brief Removes a column from the Matrix
	* \param[in] c Index of the column to remove [0, sizeC_ - 1]
	*/
	void removeC(int c);
	

	/**
	* \brief Gets a value in the Matrix using raw coordinates
	* \param[in] n Raw index of the cell to read; n = l * sizeL_ + c with (l, c)
	*  the coordinates of the cell in the Matrix
	*/
	double getValue(int n) const;
	/**
	* \brief Gets a value in the Matrix using matrix coordinates
	* \param[in] l Line index of the cell to read
	* \param[in] c Column index of the cell to read
	*/
	double getValue(int l, int c) const;
	/**
	* \brief Returns the value of the size_ attribute
	*/
	int getSize() const;
	/**
	* \brief Returns the value of the sizeL_ attribute
	*/
	int getSizeL() const;
	/**
	* \brief Returns the value of the sizeC_ attribute
	*/
	int getSizeC() const;
	/**
	* \brief Displays the matrix with appropriate format using the size
	*/
	void display() const;


	/**
	* \brief Scalar multiplication of the Matrix
	* \param[in] d Value of the scalar to multiply the Matrix by
	*/
	Matrix& operator*=(double d);
	/**
	* \brief Matrix multiplication of the Matrix
	* \param[in] m Matrix to multiply the Matrix
	*/
	Matrix& operator*=(const Matrix& m);
	/**
	* \brief Computes the value of the Matrix determinant
	* \param sum Recursive parameter, 
	*/
	double det();
	/**
	* \brief Transposes the Matrix
	*/
	void trans();
	/**
	* \brief Computes the comatrix of the Matrix
	*/
	void comat();
	/**
	* \brief Inverses the square Matrix of size 2
	* \details Implementation of the Kramer inversion formula for 2x2 Matrix
	*/
	void inv22();
	/**
	* \brief Inverses the square Matrix of size 3
	* \details Implementation of the Kramer inversion formula for 3x3 Matrix
	*/
	void inv33();

private:
	int size_;
	int sizeL_;
	int sizeC_;
	double* values_;
};

/*
* \brief Returns the power multiplication of a number
* \param[in] d Number to multiply
* \param[in] e Exponant
*/
inline double pow(double d, int e){
	double r = 1.;
	for(int i = 0; i != e; ++i){
		r *= d;
	}
	return r;
}

#endif
