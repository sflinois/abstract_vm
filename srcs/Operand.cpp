/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Operand.cpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 15:22:06 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/08 15:25:30 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Operand.tpp"
#include <iostream>

template<> Operand<int8_t>::Operand(int8_t value) :
	_precision(Int8), _type(Int8), _value(value){}

template<> Operand<int16_t>::Operand(int16_t value) :
	_precision(Int16), _type(Int16), _value(value){}

template<> Operand<int32_t>::Operand(int32_t value) :
	_precision(Int32), _type(Int32), _value(value){}

template<> Operand<float>::Operand(float value) :
	_precision(Float), _type(Float), _value(value){}

template<> Operand<double>::Operand(double value) :
	_precision(Double), _type(Double), _value(value){}