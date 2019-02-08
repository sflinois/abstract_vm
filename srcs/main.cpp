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

	op1 = factory.createOperand(Int8, "10");
	std::cout << op1->toString() << " -- " << op1->getPrecision() << " " << op1->getType() << std::endl;
	return (0);
}
