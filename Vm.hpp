/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:05:22 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/14 15:35:59 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
#define VM_HPP

# include <list>
# include <regex>
# include "IOperand.hpp"
# include "OperandFactory.hpp"
# include "Token.hpp"

class Vm {
	public: 
		Vm();
		~Vm(); 

		void	push(eOperandType type, std::string const &value);
		void	pop();
		void	add();
		void	sub();
		void	mul();
		void	div();
		void	mod();
		void	assertvm(eOperandType type, std::string const &value) const;
		void	dump() const;
		void	print() const;
		void	exit();

	private:
		Vm(Vm const &src); 
		Vm	&operator=(Vm const &rhs);

		std::list<Token>				_tkn_v;
		std::list<IOperand const *>	_stack;
};

#endif
