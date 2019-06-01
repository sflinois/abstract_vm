/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.cpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:11:01 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 15:04:49 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "Vm.hpp"
#include <iostream>

Vm::Vm() {

}

Vm::~Vm() {
	for (IOperand const * i : this->_stack)
		delete i;
}

void	Vm::start_vm(std::list<Token> tkn_lst, int opt_flag){
	this->_tkn_v = tkn_lst;
	this->_opt_flag = opt_flag;
	while(!this->_tkn_v.empty() && this->_tkn_v.front().cmd != "exit"){
		if (Vm::opFncMap.find(this->_tkn_v.front().cmd) != Vm::opFncMap.end()){
			if (this->_opt_flag & OPT_VERB_OPERATOR)
				std::cout << "\033[1m" << "<Launching cmd: " << this->_tkn_v.front().cmd << ">" << "\033[0m" << std::endl;
			(this->*(Vm::opFncMap[this->_tkn_v.front().cmd]))();
		}
		else if	(Vm::opFncMapArg.find(this->_tkn_v.front().cmd) != Vm::opFncMapArg.end()){
			if (this->_opt_flag & OPT_VERB_OPERATOR) {
				std::cout << "\033[1m" << "<Launching cmd: " << this->_tkn_v.front().cmd << " type: " << this->_tkn_v.front().type
					<< " value: " << this->_tkn_v.front().value << ">" << "\033[0m" << std::endl;
			}
			(this->*(Vm::opFncMapArg[this->_tkn_v.front().cmd]))(this->_tkn_v.front().type, this->_tkn_v.front().value);
		}
		if (this->_opt_flag & OPT_VERB_STACK)
			this->print_stack();
		this->_tkn_v.pop_front();
	}
	if ((!this->_tkn_v.empty() && this->_tkn_v.front().cmd != "exit") || this->_tkn_v.empty()){
		throw Vm::NoExitException("runtime_error: Exit instruction not found");
	}
	while(!this->_tkn_v.empty()){
		this->_tkn_v.pop_front();
	}
}

//stack functions

std::string get_color(eOperandType type)
{
	std::string colors[5]= {
		"\033[35m",
		"\033[34m",
		"\033[36m",
		"\033[32m",
		"\033[33m"
	};
	return (colors[type]);
}

void	print_op(IOperand const * op){
	std::cout << op->toString() << std::endl;
}

void	print_op_color(IOperand const * op){
	std::cout << get_color(op->getType());
	std::cout << op->toString();
	std::cout << "\033[0m" << std::endl;
}

void	print_stack_color(IOperand const * op){
	std::cout << "\033[1m" << get_color(op->getType());
	std::cout << op->toString();
	std::cout << "\033[0m" << std::endl;
}

void	Vm::push(eOperandType type, std::string const &value){
	OperandFactory	facto;

	this->_stack.push_back(facto.createOperand(type, value));
}

void	Vm::pop(){
	if (this->_stack.size() == 0)
		throw Vm::EmptyStackException("runtime_error: pop operator used on empty stack");
	delete this->_stack.back();
	this->_stack.pop_back();
}

void	Vm::add(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the add operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 + *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::sub(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the sub operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 - *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::mul(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mul operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 * *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::div(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the div operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 / *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::mod(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mod operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 % *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::assertVM(eOperandType type, std::string const &value){
	OperandFactory	facto;

	const IOperand		*tmp = facto.createOperand(type, value);
	if (this->_stack.back()->getType() == tmp->getType()
		&& !std::strcmp(this->_stack.back()->toString().c_str(), tmp->toString().c_str()))
	{
		delete tmp;
		return;
	}
	else
	{
		delete tmp;
		throw Vm::AssertFailedException("runtime_error : assert failed");
	}
	
}

void	Vm::dump(){
	this->_stack.reverse();
	if (this->_opt_flag & OPT_COLOR)
		std::for_each(this->_stack.begin(), this->_stack.end(), print_op_color);
	else
		std::for_each(this->_stack.begin(), this->_stack.end(), print_op);
	this->_stack.reverse();
}

void	Vm::print_stack(){
	std::cout << "\033[1m" << "--- Stack state ---" << std::endl;
	if (this->_opt_flag & OPT_COLOR)
		std::for_each(this->_stack.begin(), this->_stack.end(), print_stack_color);
	else
		std::for_each(this->_stack.begin(), this->_stack.end(), print_op);
	std::cout << "\033[1m---" << "\033[0m" << std::endl;
}

void	Vm::print(){
	if (this->_stack.back()->getType() != eOperandType::Int8)
		throw Vm::AssertFailedException("runtime_error : assert failed, you can only print int8 values");
	std::cout << this->_stack.back()->toString();
}

void	Vm::exit(){
	return;
}

/*
** Bonus
*/

void	Vm::min(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mod operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = (*val2).min(*val1);
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::max(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mod operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = (*val2).max(*val1);
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::avg(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mod operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = (*val2).avg(*val1);
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::pow(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mod operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = (*val2).pow(*val1);
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::iand(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mul operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 & *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::ior(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mul operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 | *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

void	Vm::ixor(){
	IOperand const *	tmp;
	IOperand const * 	val1;
	IOperand const * 	val2;


	if (this->_stack.size() < 2)
		throw Vm::StackTooSmallException("runtime_error: not enough elements on stack to use the mul operator");
	val1 = this->_stack.back();
	this->_stack.pop_back();
	val2 = this->_stack.back();
	this->_stack.pop_back();

	try{
		tmp = *val2 ^ *val1;
	}catch(const std::exception& e){
		delete val1;
		delete val2;
		throw e;
	}
	delete val1;
	delete val2;
	this->_stack.push_back(tmp);
}

typedef void (Vm::*opFunc) (void);
std::map<std::string, opFunc> Vm::opFncMap = {
	{"pop", &Vm::pop}, {"add", &Vm::add}, {"sub", &Vm::sub},
	{"mul", &Vm::mul}, {"div", &Vm::div}, {"mod", &Vm::mod},
	{"dump", &Vm::dump}, {"print", &Vm::print}, {"exit", &Vm::exit},
	{"min", &Vm::min}, {"max", &Vm::max}, {"avg", &Vm::avg}, {"pow", &Vm::pow},
	{"iand", &Vm::iand}, {"ior", &Vm::ior}, {"ixor", &Vm::ixor}

};
typedef void (Vm::*opFuncArg) (eOperandType type, std::string const &value);
std::map<std::string, opFuncArg> Vm::opFncMapArg = {
	{"push ", &Vm::push}, {"assert ", &Vm::assertVM}
};

Vm::NoExitException::NoExitException(const char *str) : std::runtime_error("NoExitException"){
	this->_msg = str;
}
Vm::NoExitException::~NoExitException() throw(){}
const char*	Vm::NoExitException::what() const throw(){
	return(this->_msg);
}

Vm::EmptyStackException::EmptyStackException(const char *str) : std::runtime_error("EmptyStackException"){
	this->_msg = str;
}
Vm::EmptyStackException::~EmptyStackException() throw(){}
const char*	Vm::EmptyStackException::what() const throw(){
	return(this->_msg);
}

Vm::StackTooSmallException::StackTooSmallException(const char *str) : std::runtime_error("StackTooSmallException"){
	this->_msg = str;
}
Vm::StackTooSmallException::~StackTooSmallException() throw(){}
const char*	Vm::StackTooSmallException::what() const throw(){
	return(this->_msg);
}

Vm::AssertFailedException::AssertFailedException(const char *str) : std::runtime_error("AssertFailedException"){
	this->_msg = str;
}
Vm::AssertFailedException::~AssertFailedException() throw(){}
const char*	Vm::AssertFailedException::what() const throw(){
	return(this->_msg);
}