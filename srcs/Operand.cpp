/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:22:06 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 13:24:46 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Operand.tpp"
#include <iostream>

template<> Operand<int8_t>::Operand(int8_t value) :
	_precision(Int8), _type(Int8), _value(value){
		// std::cout << "Operand<Int8> " << value << std::endl;
}

template<> Operand<int16_t>::Operand(int16_t value) :
	_precision(Int16), _type(Int16), _value(value){
		// std::cout << "Operand<Int16> " << value << std::endl;
}

template<> Operand<int32_t>::Operand(int32_t value) :
	_precision(Int32), _type(Int32), _value(value){
		// std::cout << "Operand<Int32> " << value << std::endl;
}

template<> Operand<float>::Operand(float value) :
	_precision(Float), _type(Float), _value(value){
		// std::cout << "Operand<Float> " << value << std::endl;
}

template<> Operand<double>::Operand(double value) :
	_precision(Double), _type(Double), _value(value){
		// std::cout << "Operand<Double> " << value << std::endl;
}