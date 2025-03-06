//
// Created by lckde on 29/09/2024.



#ifndef ELABORATOLAB_MESSAGE_H
#define ELABORATOLAB_MESSAGE_H

#include <iostream>
#include <utility>
#include "User.h"

// Classe che rappresenta un messaggio tra due utenti

class Message {
public:
    Message(User  sender, std::string  content)
            : sender(std::move(sender)), content(std::move(content)) {}

    std::string getSenderName() const {
        return sender.getUsername();
    }

    std::string getContent() const {
        return content;
    }

    std::string displayMessage() const {
        return sender.getUsername() + ": " + content;
    }

    //aggiungere attributo letto
private:
    User sender;
    std::string content;
};
#endif //ELABORATOLAB_MESSAGE_H
