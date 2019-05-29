/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:05:22 by sflinois          #+#    #+#             */
/*   Updated: 2019/05/29 14:23:56 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VM_HPP
#define VM_HPP

# include <list>
# include <map>
# include <regex>
# include "IOperand.hpp"
# include "OperandFactory.hpp"
# include "Token.hpp"

class Vm {
	public: 
		Vm();
		~Vm(); 

		void	start_vm(std::list<Token> tkn_lst);

		void	push(eOperandType type, std::string const &value);
		void	pop();
		void	add();
		void	sub();
		void	mul();
		void	div();
		void	mod();
		void	assertVM(eOperandType type, std::string const &value);
		void	dump();
		void	print_stack();
		void	print();
		void	exit();

	private:
		Vm(Vm const &src); 
		Vm	&operator=(Vm const &rhs);

		std::list<Token>				_tkn_v;
		std::list<IOperand const *>	_stack;

		typedef void (Vm::*opFunc) (void);
		static std::map<std::string, opFunc> opFncMap;
		typedef void (Vm::*opFuncArg) (eOperandType type, std::string const &value);
		static std::map<std::string, opFuncArg> opFncMapArg;
};

#endif