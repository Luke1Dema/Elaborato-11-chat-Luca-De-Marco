//
// Created by lckde on 29/09/2024.
//

#ifndef ELABORATOLAB_CHAT_H
#define ELABORATOLAB_CHAT_H

#include <iostream>
#include <vector>
#include "User.h"
#include "Message.h"

// Classe che rappresenta una chat tra due utenti

class Chat {
public:
    Chat(const User& user1, const User& user2) : user1(user1), user2(user2) {}

    void addMessage(const Message& message) {
        messages.push_back(message);
    }

    void displayChat() const {   //restituisce stringa
        std::cout << "Chat between " << user1.getUsername() << " and " << user2.getUsername() << ":\n";
        for (const auto& msg : messages) {
            msg.displayMessage();
        }
    }
//funzione per leggere messaggio i-esimo
//funzione che rstituisce chat a partire da nome utente
//funzione che cerca messaggio
    std::string getUser1() const {
        return user1.getUsername();
    }

    std::string getUser2() const {
        return user2.getUsername();
    }

private:
    User user1;
    User user2;
    std::vector<Message> messages;
};
#endif //ELABORATOLAB_CHAT_H
