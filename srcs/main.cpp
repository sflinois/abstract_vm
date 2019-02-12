/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/12 18:29:59 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Operand.tpp"
#include "../OperandFactory.hpp"
#include <regex>
#include <map>

void	foo(){
	std::cout << "FOO" << std::endl;
}

void	bar(){
	std::cout << "BAR" << std::endl;
}

int		main(int argc, char **argv){

	(void)argc;
	(void)argv;
	OperandFactory	factory;
	IOperand const	*op1;
	IOperand const	*op2;
	IOperand const	*op3;

	std::string str = "push Int8(1)";
std::regex regex("^[\\s]*push\\s*$");
std::smatch m;
// (\;.*)
//(;+)(^push)\s+(Int8|Int16)\(([-+]?[0-9]*\.?[0-9]*)\)[;]
// (^push)\s+((Float|Double)\(([-+]?[0-9]*\.?[0-9]*)\))|((Int8|Int16|Int32)\(([-+]?[0-9]*)\))
// (^push)\s+(Int8|Int16|Int32|Float|Double)\(([-+]?[0-9]*\.?[0-9]*)\)

// ^(pop|dump|ad|sub|mul|div|mod|print|exit)(?=(\s{0,}$|\s{0,}\;)) SIMPLE FUNC REGEX
// ^(push|assert)\s+((Float|Double)\(([-+]?[0-9]*\.?[0-9]*)\)|(Int8|Int16|Int32)\(([-+]?[0-9]*)\))(?=(\s{0,}$|\s{0,}\;)) REGEX NB 2

	void (*test)();
	test = &foo;
	(************************test)();

	std::cout << (&bar) << (&foo) <<std::endl;

std::cout << std::regex_match(str, m, regex) << std::endl;
for (auto result : m) {
    std::cout << result << std::endl;
}

	op1 = factory.createOperand(Int8, "3");
	op2 = factory.createOperand(Int32, "8");
	std::cout << op1->toString() << " -- " << op1->getPrecision() << " " << op1->getType() << std::endl;
	std::cout << op2->toString() << " -- " << op2->getPrecision() << " " << op2->getType() << std::endl;
	op3 = *op1 + *op2;
	std::cout << op3->toString() << " -- " << op3->getPrecision() << " " << op3->getType() << std::endl;
	op3 = *op1 - *op2;
	std::cout << op3->toString() << " -- " << op3->getPrecision() << " " << op3->getType() << std::endl;
	op3 = *op1 * *op2;
	std::cout << op3->toString() << " -- " << op3->getPrecision() << " " << op3->getType() << std::endl;
	op3 = *op1 / *op2;
	std::cout << op3->toString() << " -- " << op3->getPrecision() << " " << op3->getType() << std::endl;
	op3 = *op1 % *op2;
	std::cout << op3->toString() << " -- " << op3->getPrecision() << " " << op3->getType() << std::endl;
	return (0);
}
