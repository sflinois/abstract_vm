/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/05/31 18:34:37 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Vm.hpp"
#include "../LexerParser.hpp"
#include "../Token.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <list>

#include <iomanip>

static int	set_opt_flag(int argc, char **argv, int *opt_flag)
{
	int		iter_argv;

	iter_argv = 1;
	*opt_flag = 0;
	while (argc > iter_argv)
	{
		if (std::strcmp(argv[iter_argv], "-h") == 0)
			*opt_flag |= OPT_HELP;
		else if (std::strcmp(argv[iter_argv], "-c") == 0)
			*opt_flag |= OPT_COLOR;
		else if (std::strcmp(argv[iter_argv], "-v") == 0)
			*opt_flag |= OPT_VERB_OPERATOR | OPT_VERB_STACK;
		else if (std::strcmp(argv[iter_argv], "-v1") == 0)
			*opt_flag |= OPT_VERB_OPERATOR;
		else if (std::strcmp(argv[iter_argv], "-v2") == 0)
			*opt_flag |= OPT_VERB_STACK;
		else
			break;
		iter_argv++;
	}
	return (iter_argv);
}

static int	print_help()
{
	std::cout << "AbstractVM is a machine that uses a stack to compute simple arithmetic expressions." << std::endl
		<< "These arithmetic expressions are provided to the machine as basic assembly programs." << std::endl << std::endl;
	std::cout << "Options:" << std::endl;
	std::cout << "-h \tdisplay help" << std::endl;
	std::cout << "-c \tactivate colors" << std::endl;
	std::cout << "-v1 \tdisplay a message before launching a command in the vm" << std::endl;
	std::cout << "-v2 \tdisplay the stack status after each command" << std::endl;
	std::cout << "-v \tsame as using -v1 and -v2" << std::endl << std::endl;
	std::cout << "Grammar:" << std::endl;
	std::cout << "S := INSTR [SEP INSTR]* # " << std::endl
	<< "INSTR :=" << std::endl
	<< "     push VALUE" << std::endl
	<< "   | pop" << std::endl
	<< "   | dump" << std::endl
	<< "   | assert VALUE" << std::endl
	<< "   | add" << std::endl
	<< "   | sub" << std::endl
	<< "   | mul" << std::endl
	<< "   | div" << std::endl
	<< "   | mod" << std::endl
	<< "   | print" << std::endl
	<< "   | exit" << std::endl << std::endl
	<< "VALUE :=" << std::endl
	<< "     int8(N)" << std::endl
	<< "   | int16(N)" << std::endl
	<< "   | int32(N)" << std::endl
	<< "   | float(Z)" << std::endl
	<< "   | double(Z)" << std::endl << std::endl
	<< "N := [-]?[0..9]+" << std::endl << std::endl
	<< "Z := [-]?[0..9]+.[0..9]+" << std::endl << std::endl
	<< "SEP := '\\n'+" << std::endl;
	return (0);
}

int		main(int argc, char **argv){

	LexerParser			lp;
	Vm					vm;
	std::ifstream		file;
	int					opt_flag;
	int					iter_argv;

/*
** Parsing
*/
	iter_argv = set_opt_flag(argc, argv, &opt_flag);
	if (opt_flag & OPT_HELP)
		return(print_help());
	if (argc > iter_argv)
	{
		file.open(argv[iter_argv]);
		if (file.fail())
		{
			std::cerr << "Error: " << std::strerror(errno) << std::endl;
			return(1);
		}
		else
			lp.pars_entry(file);
	} else {
		lp.setIsCin();
		lp.pars_entry(std::cin);
	}
/*
** Exec
*/
	if (!lp.getIsErrors())
	{
		try
		{
			vm.start_vm(lp.getTknLst(), opt_flag);
		}
		catch (const std::exception& e)
		{
			std::cerr << e.what() << std::endl;
			return (1);
		}
	}
	return (0);
}