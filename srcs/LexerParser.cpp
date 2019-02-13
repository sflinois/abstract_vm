/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:14:27 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/13 16:22:19 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LexerParser.hpp"
#include <iostream>
#include <regex>
#include <iostream>

LexerParser::LexerParser() {
}

LexerParser::~LexerParser() {
}

void	LexerParser::pars_entry(std::istream& in){
	std::string		line;
	std::cmatch		lexer_cm;
	int				i_line = 1;

	while(std::getline(in, line)){
		lexer_cm = this->tokenise(line);
		this->pars_tkn(lexer_cm, i_line);

		i_line++;
	}	
}

std::cmatch		LexerParser::tokenise(std::string line){

	std::cmatch cm;
	std::regex	eno(RGX_NO_ARG);
	std::regex	eint(RGX_INT_ARG);
	std::regex	eflt(RGX_FLT_ARG);

	// std::regex_match(line.c_str(), cm, eint);
	// return cm;

	if (std::regex_match(line.c_str(), cm, eint) && cm[1].length() > 0){
		std::cout << "INT<<" << std::endl;
		return cm;
	}
	else if (std::regex_match(line.c_str(), cm, eflt) && cm[1].length() > 0){
		std::cout << "FLT<<" << std::endl;
		return cm;
	}
	else if (std::regex_match(line.c_str(), cm, eno) && cm[1].length() > 0){
		std::cout << "NO<<" << std::endl;
		return cm;
	}
	else
		std::cout << "NO MATCH LexerParser.cpp" << std::endl;
	return (cm);
}

void			LexerParser::pars_tkn(std::cmatch lexer_tkn, int line){
	std::cout << "the matches were: " << line << std::endl;
	for (unsigned i=0; i<lexer_tkn.size(); ++i) {
		std::cout << "[" << lexer_tkn[i] << "] ";
	}
}