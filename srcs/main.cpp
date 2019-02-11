/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/08 15:58:37 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Operand.tpp"
#include "../OperandFactory.hpp"

int		main(int argc, char **argv){

	(void)argc;
	(void)argv;
	OperandFactory	factory;
	IOperand const	*op1;
	IOperand const	*op2;
	IOperand const	*op3;

	op1 = factory.createOperand(Int8, "3");
	op2 = factory.createOperand(Int8, "8");
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
