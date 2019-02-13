/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:31:21 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/13 16:20:22 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_HPP
#define LEXERPARSER_HPP

# include <vector>
# include <map>
# include <regex>
# include "Token.hpp"

# define RGX_NO_ARG "^(pop|dump|ad|sub|mul|div|mod|print|exit)\\s*(\\;.*$)?(.*)?"
//# define RGX_INT_ARG "^(push|assert)\\s+(int8|int16|int32)\\(([-+]?[0-9]*)\\)\\s*(\\;.*)?$"
# define RGX_INT_ARG "^(push|assert)?(\\s+int8|\\s+int16|\\s+int32)?(\\(([-+]?[0-9]*)\\))?(\\s*(\\;.*)?$)?(.*)?"
# define RGX_FLT_ARG "^(push|assert)?(\\s+float|\\s+double)?(\\(([-+]?[0-9]*\\.?[0-9]*)\\))?(\\s*(\\;.*)?$)?(.*)?"

class LexerParser {
	public: 
		LexerParser();
		~LexerParser(); 

		void	pars_entry(std::istream& in);

	private:
		LexerParser(LexerParser const &src); 
		LexerParser	&operator=(LexerParser const &rhs);

		std::cmatch		tokenise(std::string line);
		void			pars_tkn(std::cmatch lexer_tkn, int line);

		std::vector<Token>			_tkn_lst;
		std::map<int, int>			_error_map;
};

#endif
