/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:31:21 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/14 15:59:35 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_HPP
#define LEXERPARSER_HPP

# include <list>
# include <sstream>
# include <regex>
# include "Token.hpp"

# define RGX_NO_ARG "^(\\;\\;|pop|dump|ad|sub|mul|div|mod|print|exit)\\s*(\\;.*$)?(.*)?"
//# define RGX_INT_ARG "^(push|assert)\\s+(int8|int16|int32)\\(([-+]?[0-9]*)\\)\\s*(\\;.*)?$"
# define RGX_INT_ARG "^(push |assert )?(int8|int16|int32)?(\\(([-]?[0-9]+)\\))?(\\s*(\\;.*)?$)?(.*)?"
# define RGX_FLT_ARG "^(push |assert )?(float|double)?(\\(([-]?[0-9]+\\.[0-9]+)\\))?(\\s*(\\;.*)?$)?(.*)?"
# define RGX_EMPTY "()(\\s*)(.*)"
# define RGX_END "\\s*\\;\\;\\s*(\\;.*)?"

class LexerParser {
	public: 
		LexerParser();
		~LexerParser(); 

		void	pars_entry(std::istream& in);
		void	setIsCin(void);

	private:
		LexerParser(LexerParser const &src); 
		LexerParser	&operator=(LexerParser const &rhs);

		std::cmatch		tokenise(std::string line);
		void			handle_error(std::cmatch lexer_tkn, std::string line, int i_line);
		void			pars_tkn(std::cmatch lexer_tkn, std::string line, int i_line);

		bool						_is_cin;
		bool						_is_error;
		std::list<Token>			_tkn_lst;
		std::stringstream			_errors;
};

#endif
