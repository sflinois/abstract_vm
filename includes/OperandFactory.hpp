/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   OperandFactory.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/08 11:25:56 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 12:33:08 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef OPERANDFACTORY_HPP
#define OPERANDFACTORY_HPP

#include "IOperand.hpp"

class OperandFactory {
	public: 
		OperandFactory();
		~OperandFactory(); 

		IOperand const * createOperand( eOperandType type, std::string const & value ) const;
	private:
		OperandFactory(OperandFactory const &src); 
		OperandFactory	&operator=(OperandFactory const &rhs);

		IOperand const * createInt8( std::string const & value ) const;
		IOperand const * createInt16( std::string const & value ) const;
		IOperand const * createInt32( std::string const & value ) const;
		IOperand const * createFloat( std::string const & value ) const;
		IOperand const * createDouble( std::string const & value ) const;
};

#endif
