/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Token.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: sflinois <sflinois@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/13 09:26:59 by sflinois          #+#    #+#             */
/*   Updated: 2019/02/13 14:47:50 by sflinois         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TOKEN_HPP
#define TOKEN_HPP

# include <iostream>
# include "IOperand.hpp"

struct Token {
		std::string		cmd;
		eOperandType	type;
		std::string		value;
};

#endif