/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   IOperand.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/07 13:52:11 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/14 14:38:32 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef IOPERAND_HPP
# define IOPERAND_HPP

# include <string>

# define  FLT_MAX __FLT_MAX__
# define  FLT_MIN __FLT_MAX__*-1
# define  DBL_MAX __DBL_MAX__
# define  DBL_MIN __DBL_MAX__*-1

enum eOperandType {
	Int8,
	Int16,
	Int32,
	Float,
	Double
};

class IOperand
{
  public:
	virtual int getPrecision(void) const = 0;						  // Precision of the type of the instance
	virtual eOperandType getType(void) const = 0;					  // Type of the instance
	virtual IOperand const *operator+(IOperand const &rhs) const = 0; // Sum
	virtual IOperand const *operator-(IOperand const &rhs) const = 0; // Difference
	virtual IOperand const *operator*(IOperand const &rhs) const = 0; // Product
	virtual IOperand const *operator/(IOperand const &rhs) const = 0; // Quotient
	virtual IOperand const *operator%(IOperand const &rhs) const = 0; // Modulo
	virtual bool 			operator==(IOperand const &rhs) const = 0; // Equal
	virtual std::string const &toString(void) const = 0;			  // String representation of the instance
	virtual ~IOperand(void) {}
};
#endif