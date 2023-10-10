/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exceptions.hpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: stepis <stepis@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/10 18:30:19 by stepis            #+#    #+#             */
/*   Updated: 2023/10/10 18:30:22 by stepis           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include "libraries.hpp"

class SyntaxError : public std::exception {
public:
    const char* what() const throw() {
        return "Errore di sintassi\n";
    }
};

#endif