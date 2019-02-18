/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:11:01 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/18 13:29:01 by sflinois         ###   ########.fr       */
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
			Vm::opFncMap[this->_tkn_v.front().cmd];
		else if	(Vm::opFncMapArg.find(this->_tkn_v.front().cmd) != Vm::opFncMapArg.end())
			;
	}
	
	if (!this->_tkn_v.empty())
		this->_tkn_v.pop_front();
	for(Token tkn : this->_tkn_v){
		std::cout << tkn.cmd << " | " << tkn.type << " | " << tkn.value << std::endl;
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

void	Vm::assert(eOperandType type, std::string const &value){
	OperandFactory	facto;

	if (this->_stack.back() == facto.createOperand(type, value))
		std::cout << "ASSERT OK" << std::endl;
	else
		std::cout << "ASSERT PAS OK" << std::endl;
	
}

void	Vm::dump(){
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
	{"push", &Vm::push}, {"assert", &Vm::assert}
};