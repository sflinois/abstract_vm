/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.tpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 17:01:05 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 13:40:17 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERAND_TPP
#define OPERAND_TPP

#include "IOperand.hpp"
#include "OperandFactory.hpp"
#include <iostream>
#include <cmath>
#include <sstream>
#include <algorithm> //Bonus

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

		if ((rhs_v > 0) && (this->_value > DBL_MAX - rhs_v)) /* `a + this->_value` would overflow */
			throw std::out_of_range("runtime_error: : double out of range (overflow)");
		else if ((rhs_v < 0) && (this->_value < DBL_MIN - rhs_v)) /* `a + this->_value` would underflow */
			throw std::out_of_range("runtime_error: : double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value + rhs_v)));
	}
	IOperand const *operator-(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if ((rhs_v < 0) && (this->_value > DBL_MAX + rhs_v)) /* `a - this->_value` would overflow */
			throw std::out_of_range("runtime_error: : double out of range (overflow)");
		else if ((rhs_v > 0) && (this->_value < DBL_MIN + rhs_v)) /* `a - this->_value` would underflow */
			throw std::out_of_range("runtime_error: : double out of range (underflow)");
		return (facto.createOperand(opType, std::to_string(this->_value - rhs_v)));
	}
	IOperand const *operator*(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (rhs_v > 0 && this->_value > DBL_MAX / rhs_v) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : double out of range (overflow)");
		if (rhs_v > 0 && this->_value < DBL_MIN / rhs_v) /* `rhs_v * this->_value` would underflow */
			throw std::out_of_range("runtime_error: : double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string(this->_value * rhs_v)));
	}
	IOperand const *operator/(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (rhs_v == 0)
			throw std::overflow_error("runtime_error: division by 0");
		if (rhs_v > 0 && rhs_v < 1 && this->_value > DBL_MAX * rhs_v) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : double out of range (overflow)");
		if (rhs_v > 0 && rhs_v < 1 && this->_value < DBL_MIN * rhs_v) /* `rhs_v * this->_value` would underflow */
			throw std::out_of_range("runtime_error: : double out of range (underflow)");

		return (facto.createOperand(opType, std::to_string( this->_value / rhs_v)));
	}
	IOperand const *operator%(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (rhs_v == 0)
			throw std::overflow_error("runtime_error: division by 0");

		return (facto.createOperand(opType, std::to_string(fmod(this->_value, rhs_v))));
	}

	bool			operator==(IOperand const &rhs) const
	{
		if (this->_type == rhs.getType() && !this->toString().compare(rhs.toString()))
			return true;
		return false;
	}

	std::string const &toString(void) const
	{
		std::ostringstream ss;
		if (this->_type == eOperandType::Int8)
			ss << static_cast<int>(this->_value);
		else
			ss << this->_value;
		return (*(new std::string(ss.str())));
	}

	/*
	** Bonus
	*/

	IOperand const *min(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		return (facto.createOperand(opType, std::to_string(this->_value <= rhs_v ? this->_value : rhs_v)));
	}
	
	IOperand const *max(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		return (facto.createOperand(opType, std::to_string(this->_value >= rhs_v ? this->_value : rhs_v)));
	}

	IOperand const *avg(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		return (facto.createOperand(opType, std::to_string((this->_value / 2) + (rhs_v / 2))));
	}

	IOperand const *pow(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (rhs_v * std::log(this->_value) < std::log(DBL_MAX)) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : double out of range (overflow)");
		return (facto.createOperand(opType, std::to_string(std::pow(this->_value, rhs_v))));
	}

	IOperand const *operator&(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (this->_type > eOperandType::Int32 || rhs.getType() > eOperandType::Int32) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : can't use bitwise oparators on floating point number");
		return (facto.createOperand(opType, std::to_string(static_cast<int>(this->_value) & static_cast<int>(rhs_v))));
	}

	IOperand const *operator|(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (this->_type > eOperandType::Int32 || rhs.getType() > eOperandType::Int32) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : can't use bitwise oparators on floating point number");
		return (facto.createOperand(opType, std::to_string(static_cast<int>(this->_value) | static_cast<int>(rhs_v))));
	}

	IOperand const *operator^(IOperand const &rhs) const
	{
		OperandFactory	facto;
		eOperandType	opType;
		double			rhs_v;

		opType = this->_type > rhs.getType() ? this->_type : rhs.getType();
		rhs_v = std::atof(rhs.toString().c_str());

		if (this->_type > eOperandType::Int32 || rhs.getType() > eOperandType::Int32) /* `rhs_v * this->_value` would overflow */
			throw std::out_of_range("runtime_error: : can't use bitwise oparators on floating point number");
		return (facto.createOperand(opType, std::to_string(static_cast<int>(this->_value) ^ static_cast<int>(rhs_v))));
	}


  private:
	Operand();
	Operand(Operand const &src);
	Operand &operator=(Operand const &rhs);

	int _precision;
	eOperandType _type;
	T _value;
};

#endif