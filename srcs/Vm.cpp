/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:11:01 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/13 14:50:27 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Vm.hpp"
#include <iostream>

Vm::Vm() {

}

Vm::~Vm() {

}

//stack functions

void	print_op(IOperand const * op){
	std::cout << op->toString() << std::endl;
}

void	Vm::push(eOperandType type, std::string const &value){
	OperandFactory	facto;

	this->_stack.push_back(facto.createOperand(type, value));
}

void	Vm::pop(){
	this->_stack.pop_back();
}

void	Vm::add(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		std::cout << "ERROR ADD" << std::endl;	
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 + *val2;
	this->_stack.push_back(tmp);
}

void	Vm::sub(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		std::cout << "ERROR ADD" << std::endl;	
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 - *val2;
	this->_stack.push_back(tmp);
}

void	Vm::mul(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		std::cout << "ERROR ADD" << std::endl;	
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 * *val2;
	this->_stack.push_back(tmp);
}

void	Vm::div(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		std::cout << "ERROR ADD" << std::endl;	
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 / *val2;
	this->_stack.push_back(tmp);
}

void	Vm::mod(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		std::cout << "ERROR ADD" << std::endl;	
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 % *val2;
	this->_stack.push_back(tmp);
}

void	Vm::assert(eOperandType type, std::string const &value) const{
	OperandFactory	facto;

	if (this->_stack.back() == facto.createOperand(type, value))
		std::cout << "ASSERT OK" << std::endl;
	else
		std::cout << "ASSERT PAS OK" << std::endl;
	
}

void	Vm::dump() const{
	std::for_each(this->_stack.begin(), this->_stack.end(), print_op);
}

void	Vm::print() const{
	print_op(this->_stack.back());
}

void	Vm::exit(){

}