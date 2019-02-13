/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:05:22 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/13 14:49:31 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
#define VM_HPP

# include <vector>
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
		void	assert(eOperandType type, std::string const &value) const;
		void	dump() const;
		void	print() const;
		void	exit();

	private:
		Vm(Vm const &src); 
		Vm	&operator=(Vm const &rhs);

		std::vector<Token>				_tkn_v;
		std::vector<IOperand const *>	_stack;
};

#endif
