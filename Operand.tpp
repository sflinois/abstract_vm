/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:01:05 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/08 17:13:36 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TPP
#define OPERAND_TPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <iostream>

template <typename T>
class Operand : public IOperand
{
  public:

	//Constructor
	Operand(T value);

	//Destructor
	~Operand()
	{
		std::cout << "Destructor" << std::endl;
	}

	//Getter
	int				getPrecision(void) const { return this->_precision; }
	eOperandType	getType(void) const { return this->_type; }
	T 				getValue(void) const { return this->_value; }

	//Operators overload
	IOperand const *operator+(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if ((this->_value > 0) && (rhs_v > __DBL_MAX__ - this->_value)) /* `a + this->_value` would overflow */
			throw std::out_of_range("EXCEPTION: double out of range (overflow)");
		else if ((this->_value < 0) && (rhs_v < __DBL_MIN__ - this->_value)) /* `a + this->_value` would underflow */
			throw std::out_of_range("EXCEPTION: double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value + rhs_v)));
	}
	IOperand const *operator-(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if ((this->_value < 0) && (rhs_v > __DBL_MAX__ + this->_value)) /* `a - this->_value` would overflow */
			throw std::out_of_range("EXCEPTION: double out of range (overflow)");
		else if ((this->_value > 0) && (rhs_v < __DBL_MIN__ + this->_value)) /* `a - this->_value` would underflow */
			throw std::out_of_range("EXCEPTION: double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value - rhs_v)));
	}
	IOperand const *operator*(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (this->_value > 0 && rhs_v > __DBL_MAX__ / this->_value) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("EXCEPTION: double out of range (overflow)");
		if (this->value > 0 && rhs_v < __DBL_MIN__ / this->_value) /* `rhs_v * this->_value` would underflow */
			throw std::out_of_range("EXCEPTION: double out of range (underflow)");
		// there may be need to check for -1 for two's complement machines
		if ((rhs_v == -1) && (this->_value == __DBL_MIN__)) /* `rhs_v * this->_value` can overflow */
			throw std::out_of_range("EXCEPTION: double out of range (overflow)");
		if ((this->_value == -1) && (rhs_v == __DBL_MIN__)) /* `rhs_v * this->_value` (or `rhs_v / this->_value`) can overflow */
			throw std::out_of_range("EXCEPTION: double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value * rhs_v)));
	}
	IOperand const *operator/(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if ((this->_value > 0) && (rhs_v > __DBL_MAX__ - this->_value)) /* `a + this->_value` would overflow */
			throw std::out_of_range("EXCEPTION: double out of range (overflow)");
		else if ((this->_value < 0) && (rhs_v < __DBL_MAX__ - this->_value)) /* `a + this->_value` would underflow */
			throw std::out_of_range("EXCEPTION: double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value / rhs_v)));
	}
	IOperand const *operator%(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		return (facto.createOperand(opType, std::to_string(this->_value % rhs_v)));
	}

	//toString
	std::string const &toString(void) const
	{
		return (*(new std::string(std::to_string(this->_value))));
	}

  private:
	Operand();
	Operand(Operand const &src);
	Operand &operator=(Operand const &rhs);

	int _precision;
	eOperandType _type;
	T _value;
};

// //Constructors

// template<> Operand<int8_t>::Operand(int8_t value) :
// 	_precision(Int8), _type(Int8), _value(value){}
// template<> Operand<int16_t>::Operand(int16_t value) :
// 	_precision(Int16), _type(Int16), _value(value){}
// template<> Operand<int32_t>::Operand(int32_t value) :
// 	_precision(Int32), _type(Int32), _value(value){}
// template<> Operand<float>::Operand(float value) :
// 	_precision(Float), _type(Float), _value(value){}
// template<> Operand<double>::Operand(double value) :
// 	_precision(Double), _type(Double), _value(value){}

//Destructor

// template <typename T>
// Operand<T>::~Operand()
// {
// 	std::cout << "Destructor" << std::endl;
// }

// //Getter

// template <typename T>
// int Operand<T>::getPrecision(void) const { return this->_precision; }
// template <typename T>
// eOperandType Operand<T>::getType(void) const { return this->_type; }
// template <typename T>
// T Operand<T>::getValue(void) const { return this->_value; }

// //Operators overload

// template <typename T>
// IOperand const *Operand<T>::operator+(IOperand const &rhs) const
// {
// 	return (&rhs);
// }
// template <typename T>
// IOperand const *Operand<T>::operator-(IOperand const &rhs) const
// {
// 	return (&rhs);
// }
// template <typename T>
// IOperand const *Operand<T>::operator*(IOperand const &rhs) const
// {
// 	return (&rhs);
// }
// template <typename T>
// IOperand const *Operand<T>::operator/(IOperand const &rhs) const
// {
// 	return (&rhs);
// }
// template <typename T>
// IOperand const *Operand<T>::operator%(IOperand const &rhs) const
// {
// 	return (&rhs);
// }

// //toString

// template <typename T>
// std::string const &Operand<T>::toString(void) const
// {
// 	return (*(new std::string(std::to_string(this->_value))));
// }

#endif