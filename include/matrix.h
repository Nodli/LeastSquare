#ifndef MATRIX_H
#define MATRIX_H

/**
* \class Models a Matrix with values stored as double
*/
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
	/**
	* \brief Copy constructor of a Matrix object
	* \param[in] m Matrix to copy
	*/
	Matrix(const Matrix& m);
	/**
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
	* \brief Returns a value in the Matrix using raw coordinates
	* \param[in] n Raw index of the cell to read; n = l * sizeL_ + c with (l, c)
	*  the coordinates of the cell in the Matrix
	*/
	double getValue(int n) const;
	/**
	* \brief Returns a value in the Matrix using matrix coordinates
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
	* \returns Reference to the multiplied Matrix
	*/
	Matrix& operator*=(double d);
	/**
	* \brief Matrix multiplication of the Matrix
	* \param[in] m Matrix to multiply the Matrix
	* \returns Reference to the multiplied Matrix
	*/
	Matrix& operator*=(const Matrix& m);
	/**
	* \brief Returns the value of the Matrix determinant
	* \param sum Recursive parameter,
	*/
	double det();
	/**
	* \brief In-place transposition of the Matrix
	* \returns Reference to the transposed Matrix
	*/
	Matrix& trans();
	/**
	* \brief Returns the comatrix of the Matrix
	* \param[out] comat Matrix to store the comatrix
	* \returns Reference to the comatrix instance of Matrix
	*/
	Matrix& comat(Matrix& comat);
	/**
	* \brief In-place inversion of square Matrix of size 2
	* \details Implementation of the Kramer inversion formula for 2x2 Matrix
	* \returns Reference to the inversed Matrix
	*/
	Matrix& inv22();
	/**
	* \brief In-place inversion of square Matrix of size 3
	* \details Implementation of the Kramer inversion formula for 3x3 Matrix
	* \returns Reference to the inversed Matrix
	*/
	Matrix& inv33();

private:
	int size_; //Raw size of the Matrix
	int sizeL_; //Number of lines in the Matrix
	int sizeC_; //Number of columns in the Matrix
	double* values_; //Points towards the value table of the Matrix
};

/**
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
