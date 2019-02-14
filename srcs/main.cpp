/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/06 10:32:52 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/14 15:41:33 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Vm.hpp"
#include "../LexerParser.hpp"
#include "../Token.hpp"
#include <fstream>
#include <iostream>
#include <regex>
#include <list>

int		main(int argc, char **argv){

	LexerParser			lp;
	Vm					vm;
	std::list<Token>	lst;
	std::ifstream		file; 

	if (argc > 1)
	{
		file.open(argv[1]);
		if (file.fail())
			std::cerr << "Error: " << std::strerror(errno) << std::endl;
		else
			lp.pars_entry(file);
	} else {
		lp.setIsCin();
		lp.pars_entry(std::cin);
	}


	return (0);
}
