#ifndef REG_H
#define REG_H

/**
* \class Provides easy access to 2D regression functions
*/
class Regression2D{
public:
	/**
	* \brief Constructor of a Regression object
	* \details The Regression instance holds copies of valuesX and valuesY
	* \param[in] s Number of data points to use for the regression
	* \param[in] valuesX X-Axis values of the data points
	* \param[in] valuesY Y-Axis values of the data points
	*/
	Regression2D(int s, const double* valuesX, const double* valuesY);
	/**
	* \brief Destructor of a Regression object
	* \details Deletes the dynamically allocated valuesX_ and valuesY_
	*/
	~Regression2D();

	/**
	* \brief Computes a linear regression using the data points
	* \details Displays the (a, b) coefficients for the Y = aX + b equation
	*/
	void Linear() const;
	/**
	* \brief Computes a parabolic regresiion using the data points
	* \details Displays the (a, b, c) coefficients for the Y = aX^2 + bX + c equation
	*/
	void Parabolic() const;

private:
	int size_; //Raw size of the Matrix
	double* valuesX_; //Points towards the X-Axis value table of the data points
	double* valuesY_; //Points towards the Y-Axis value table of the data points
};

#endif
