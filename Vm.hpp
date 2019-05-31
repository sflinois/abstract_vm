/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Vm.hpp                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/12 10:05:22 by sflinois          #+#    #+#             */
/*   Updated: 2019/05/31 17:53:56 by sflinois         ###   ########.fr       */
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

# define OPT_HELP 1
# define OPT_COLOR 2
# define OPT_VERB_OPERATOR 4
# define OPT_VERB_STACK 8

class Vm {
	public: 
		Vm();
		~Vm(); 

		void	start_vm(std::list<Token> tkn_lst, int opt_flag);

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

		class NoExitException : public std::runtime_error{
			public:
				NoExitException(const char *str);
				~NoExitException() throw();

				const char* what() const throw();
			private:
				const char*	_msg;
		};
		class EmptyStackException : public std::runtime_error{
			public:
				EmptyStackException(const char *str);
				~EmptyStackException() throw();

				const char* what() const throw();
			private:
				const char*	_msg;
		};
		class StackTooSmallException : public std::runtime_error{
			public:
				StackTooSmallException(const char *str);
				~StackTooSmallException() throw();

				const char* what() const throw();
			private:
				const char*	_msg;
		};
		class AssertFailedException : public std::runtime_error{
			public:
				AssertFailedException(const char *str);
				~AssertFailedException() throw();

				const char* what() const throw();
			private:
				const char*	_msg;
		};

	private:
		Vm(Vm const &src); 
		Vm	&operator=(Vm const &rhs);

		std::list<Token>				_tkn_v;
		std::list<IOperand const *>		_stack;
		int								_opt_flag;

		typedef void (Vm::*opFunc) (void);
		static std::map<std::string, opFunc> opFncMap;
		typedef void (Vm::*opFuncArg) (eOperandType type, std::string const &value);
		static std::map<std::string, opFuncArg> opFncMapArg;
};

#endif