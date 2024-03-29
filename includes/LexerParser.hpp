/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   LexerParser.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 14:31:21 by sflinois          #+#    #+#             */
/*   Updated: 2019/06/01 13:31:04 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXERPARSER_HPP
#define LEXERPARSER_HPP

# include <list>
# include <sstream>
# include <regex>
# include "Token.hpp"

# define RGX_NO_ARG "^(\\;\\;|pop|dump|add|sub|mul|div|mod|print|exit|min|max|avg|pow|iand|ior|ixor)\\s*(\\;.*$)?(.*)?"
# define RGX_INT_ARG "^(push |assert )?(int8|int16|int32)?(\\(([-]?[0-9]+)\\))?(\\s*(\\;.*)?$)?(.*)?"
# define RGX_FLT_ARG "^(push |assert )?(float|double)?(\\(([-]?[0-9]+\\.[0-9]+)\\))?(\\s*(\\;.*)?$)?(.*)?"
# define RGX_EMPTY "()(\\s*)(.*)"
# define RGX_END "\\s*\\;\\;\\s*(\\;.*)?"

class LexerParser {
	public: 
		LexerParser();
		~LexerParser(); 

		void				pars_entry(std::istream& in);
		std::list<Token>	getTknLst(void) const;
		bool				getIsErrors(void) const;
		void				setIsCin(void);

	private:
		LexerParser(LexerParser const &src); 
		LexerParser	&operator=(LexerParser const &rhs);

		void			tokenise(std::string *line, std::cmatch *cm);
		void			handle_error(std::cmatch lexer_tkn, std::string line, int i_line);
		void			pars_tkn(std::cmatch lexer_tkn, std::string line, int i_line);

		bool						_is_cin;
		bool						_is_error;
		bool						_is_end;
		std::list<Token>			_tkn_lst;
		std::stringstream			_errors;
};

#endif
