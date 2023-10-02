#ifndef EXCEPTIONS_HPP
# define EXCEPTIONS_HPP

#include <iostream>
#include <stdexcept>

class SyntaxError : public std::exception {
public:
    const char* what() const throw() {
        return "Errore di sintassi\n";
    }
};

#endif