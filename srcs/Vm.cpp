/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:11:01 by sflinois          #+#    #+#             */
/*   Updated: 2019/05/29 14:52:13 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Vm.hpp"
#include <iostream>

Vm::Vm() {

}

Vm::~Vm() {

}


void	Vm::start_vm(std::list<Token> tkn_lst){
	this->_tkn_v = tkn_lst;
	while(!this->_tkn_v.empty() && this->_tkn_v.front().cmd != "exit"){
		if (Vm::opFncMap.find(this->_tkn_v.front().cmd) != Vm::opFncMap.end())
		{
			(this->*(Vm::opFncMap[this->_tkn_v.front().cmd]))();
		}
		else if	(Vm::opFncMapArg.find(this->_tkn_v.front().cmd) != Vm::opFncMapArg.end())
		{
			(this->*(Vm::opFncMapArg[this->_tkn_v.front().cmd]))(this->_tkn_v.front().type, this->_tkn_v.front().value);
		}
		this->_tkn_v.pop_front();
	}
	if ((!this->_tkn_v.empty() && this->_tkn_v.front().cmd != "exit") || this->_tkn_v.empty()){
		throw std::runtime_error("Error : did not encounter any <exit> instruction");
	}
	while(!this->_tkn_v.empty()){
		this->_tkn_v.pop_front();
	}
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
	if (this->_stack.size() == 0)
		throw std::out_of_range("Error : Pop on empty stack");
	this->_stack.pop_back();
}

void	Vm::add(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw std::runtime_error("Error : stack size too small to perform operation");
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
		throw std::runtime_error("Error : stack size too small to perform operation");
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
		throw std::runtime_error("Error : stack size too small to perform operation");
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
		throw std::runtime_error("Error : stack size too small to perform operation");
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
		throw std::runtime_error("Error : stack size too small to perform operation");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	tmp = *val1 % *val2;
	this->_stack.push_back(tmp);
}

void	Vm::assertVM(eOperandType type, std::string const &value){
	OperandFactory	facto;

	const IOperand		*tmp = facto.createOperand(type, value);
	if (this->_stack.back()->getType() == tmp->getType()
		&& !std::strcmp(this->_stack.back()->toString().c_str(), tmp->toString().c_str()))
		return;
	else
		throw std::runtime_error("Error : assert failed");
	
}

void	Vm::dump(){
	this->_stack.reverse();
	std::for_each(this->_stack.begin(), this->_stack.end(), print_op);
	this->_stack.reverse();
}

void	Vm::print_stack(){
	std::for_each(this->_stack.begin(), this->_stack.end(), print_op);
}

void	Vm::print(){
	print_op(this->_stack.back());
}

void	Vm::exit(){

}

typedef void (Vm::*opFunc) (void);
std::map<std::string, opFunc> Vm::opFncMap = {
	{"pop", &Vm::pop}, {"add", &Vm::add}, {"sub", &Vm::sub},
	{"mul", &Vm::mul}, {"div", &Vm::div}, {"mod", &Vm::mod},
	{"dump", &Vm::dump}, {"print", &Vm::print}, {"exit", &Vm::exit}
};
typedef void (Vm::*opFuncArg) (eOperandType type, std::string const &value);
std::map<std::string, opFuncArg> Vm::opFncMapArg = {
	{"push ", &Vm::push}, {"assert ", &Vm::assertVM}
};