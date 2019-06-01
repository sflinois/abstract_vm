/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 14:03:19 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 14:20:48 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "OperandFactory.hpp"
#include "Operand.tpp"
#include <iostream>

OperandFactory::OperandFactory()
{
}

OperandFactory::~OperandFactory()
{
}

IOperand const *	OperandFactory::createOperand(eOperandType type, std::string const &value) const{
	typedef IOperand const * (OperandFactory::*creatFnc) (std::string const &) const;
	static creatFnc fncTab[] = {&OperandFactory::createInt8,
								&OperandFactory::createInt16,
								&OperandFactory::createInt32,
								&OperandFactory::createFloat,
								&OperandFactory::createDouble};
	
	IOperand const * ret = (this->*fncTab[type])(value);
	return ret;
}

IOperand const *	OperandFactory::createInt8(std::string const &value) const{
	int val = 0;
	
	try
	{
		val = std::stoi(value);
	}
	catch (const std::exception& e)
	{
		throw std::out_of_range("runtime_error: int8 out of range");
	}

	if (val < INT8_MIN || val > INT8_MAX)
		throw std::out_of_range("runtime_error: int8 out of range");
	return (new Operand<int8_t>(static_cast<int8_t>(val)));
}
IOperand const *	OperandFactory::createInt16(std::string const &value) const{
	int val = 0;
	
	try
	{
		val = std::stoi(value);
	}
	catch (const std::exception& e)
	{
		throw std::out_of_range("runtime_error: int16 out of range");
	}

	if (val < INT16_MIN || val > INT16_MAX)
		throw std::out_of_range("runtime_error: int16 out of range");
	return new Operand<int16_t>(static_cast<int16_t>(val));
}
IOperand const *	OperandFactory::createInt32(std::string const &value) const{
	int val = 0;
	
	try
	{
		val = std::stoi(value);
	}
	catch (const std::exception& e)
	{
		throw std::out_of_range("runtime_error: int32 out of range");
	}

	return new Operand<int32_t>(static_cast<int32_t>(val));
}
IOperand const *	OperandFactory::createFloat(std::string const &value) const{
	double val = 0;
	
	try
	{
		val = std::stof(value);
	}
	catch (const std::exception& e)
	{
		throw std::out_of_range("runtime_error: float out of range");
	}
	
	if (val < FLT_MIN|| val > FLT_MAX)
		throw std::out_of_range("runtime_error: float out of range");
	return new Operand<float>(static_cast<float>(val));
}
IOperand const *	OperandFactory::createDouble(std::string const &value) const{
	double val = 0;
	
	try
	{
		val = std::stod(value);
	}
	catch (const std::exception& e)
	{
		throw std::out_of_range("runtime_error: double out of range");
	}
	
	return new Operand<double>(val);
}