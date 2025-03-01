//
// Created by lckde on 29/09/2024.
//


#ifndef ELABORATOLAB_USER_H
#define ELABORATOLAB_USER_H

#include <string>
#include <utility>

// Classe che rappresenta un utente

class User {
public:
    explicit User(std::string username) : username(std::move(username)) {}

    std::string getUsername() const {
        return username;
    }

private:
    std::string username;
};
#endif //ELABORATOLAB_USER_H
