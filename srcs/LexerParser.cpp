/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 10:14:27 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/18 11:42:49 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../LexerParser.hpp"
#include <iostream>
#include <regex>
#include <map>
#include <iostream>

// # define RGX_INT_ARG "^(push|assert)?(\\s+int8|\\s+int16|\\s+int32)?(\\(([-+]?[0-9]*)\\))?(\\s*(\\;.*)?$)?(.*)?"
// # define RGX_FLT_ARG "^(push|assert)?(\\s+float|\\s+double)?(\\(([-+]?[0-9]*\\.?[0-9]*)\\))?(\\s*(\\;.*)?$)?(.*)?"

LexerParser::LexerParser() : _is_cin(false), _is_error(false) {
}

LexerParser::~LexerParser() {
}

std::list<Token>	LexerParser::getTknLst(void) const{
	return(this->_tkn_lst);
}
bool	LexerParser::getIsErrors(void) const{
	return(this->_is_error);
}

void	LexerParser::setIsCin(void){
	this->_is_cin = true;
}

void	LexerParser::pars_entry(std::istream& in){
	std::string		line;
	std::cmatch		lexer_cm;
	std::regex		eend(RGX_END);
	int				i_line = 1;

	while(std::getline(in, line)){
		if (this->_is_cin && std::regex_match(line.c_str(), lexer_cm, eend))
			break ;
		lexer_cm = this->tokenise(line);
		this->pars_tkn(lexer_cm, line, i_line);
		i_line++;
	}
	if (this->_is_error)
		std::cerr << this->_errors.str();
}

std::cmatch		LexerParser::tokenise(std::string line){

	std::cmatch cm;
	std::regex	eno(RGX_NO_ARG);
	std::regex	eint(RGX_INT_ARG);
	std::regex	eflt(RGX_FLT_ARG);
	std::regex	eempty(RGX_EMPTY);

	// std::regex_match(line.c_str(), cm, eint);
	// return cm;

	if (std::regex_match(line.c_str(), cm, eint) && cm[1].length() > 0 && cm[2].length() > 0){
	}
	else if (std::regex_match(line.c_str(), cm, eflt) && cm[1].length() > 0){
	}
	else if (std::regex_match(line.c_str(), cm, eno) && cm[1].length() > 0){
	}
	else if (std::regex_match(line.c_str(), cm, eempty)){
	}
	return (cm);
}

void			LexerParser::handle_error(std::cmatch lexer_tkn, std::string line, int i_line){
	if (lexer_tkn[0].length() > 0 && lexer_tkn[1].length() == 0 && lexer_tkn[3].length() > 0){
		if (!std::strcmp(lexer_tkn[3].str().c_str(), "push") || !std::strcmp(lexer_tkn[3].str().c_str(), "assert")){
			this->_errors << "line " << i_line << "\t> " << line << std::endl;
			this->_errors << "Syntax error: missing argument at line " << i_line << std::endl;			
		}else{
			this->_errors << "line " << i_line << "\t> " << line << std::endl;
			this->_errors << "Syntax error: unknown command at line " << i_line << std::endl;
		}
		this->_is_error = true;
	}
	else if ((lexer_tkn.size() == 4 && lexer_tkn[3].length() > 0) && (std::strcmp(lexer_tkn[1].str().c_str(), ";;") || this->_is_cin)){
		this->_errors << "line " << i_line << "\t> " << line << std::endl;
		this->_errors << "Syntax error: wrong param after command at line " << i_line << std::endl;
		this->_is_error = true;
	}
	if (lexer_tkn.size() == 8 && (lexer_tkn[2].length() == 0 || lexer_tkn[3].length() == 0)){
		this->_errors << "line " << i_line << "\t> " << line << std::endl;
		this->_errors << "Syntax error: wrong param after command at line " << i_line << std::endl;
		if (lexer_tkn[2].length() == 0)
			this->_errors << " Valid arguments are int8|int16|int32|float|double" << std::endl;
		else if (!std::strcmp(lexer_tkn[2].str().c_str(), "float") || !std::strcmp(lexer_tkn[3].str().c_str(), "double"))
			this->_errors << " Valid type formating is " << lexer_tkn[2] << "([-]?[0..9]+.[0..9]+)" << std::endl;
		else
			this->_errors << " Valid type formating is " << lexer_tkn[2] << "([-]?[0..9]+)" << std::endl;
		this->_is_error = true;		
	}
}

void			LexerParser::pars_tkn(std::cmatch lexer_tkn, std::string line, int i_line){
	Token 								tkn;
	std::map<std::string, eOperandType>	type_map = {
		{"int8", Int8},
		{"int16", Int16},
		{"int32", Int32},
		{"float", Float},
		{"double", Double}
	};

	this->handle_error(lexer_tkn, line, i_line);
	if (this->_is_error)
		return;

	if (!std::strcmp(lexer_tkn[1].str().c_str(), "push ") || !std::strcmp(lexer_tkn[1].str().c_str(), "assert "))
	{
		tkn.cmd = lexer_tkn[1].str();
		tkn.type = type_map[lexer_tkn[2].str()];
		tkn.value = lexer_tkn[4].str();
	} else {
		tkn.cmd = lexer_tkn[1].str();
		tkn.type = Int8;
		tkn.value = "0";
	}
	if (std::strcmp(lexer_tkn[1].str().c_str(), ";;") && std::strcmp(lexer_tkn[1].str().c_str(), ""))
		this->_tkn_lst.push_front(tkn);
	// std::cout << "the matches were: " << line << std::endl;
	// for (unsigned i=0; i<lexer_tkn.size(); ++i) {
	// 	std::cout << "[" << lexer_tkn[i] << "] ";
	// }
	// std::cout << std::endl;
}