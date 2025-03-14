//
// Created by lckde on 29/09/2024.
//

#ifndef ELABORATOLAB_CHATREGISTRY_H
#define ELABORATOLAB_CHATREGISTRY_H

#include "Chat.h"
#include <map>

// Classe che rappresenta il registro delle chat



class ChatRegistry {

public:

    void addChat(const Chat& chat);

    void addMessageToChat(const User& user1, const User& user2, const Message& message);


    void displayAllChats();

    int messagesToRead(User sender, User recipient) const;

    void readNthMessage(User sender, User recipient, int n) ;

private:
    std::map<std::string, Chat> chats;

    // Genera una chiave unica per identificare una chat tra due utenti
    static std::string generateChatKey(const std::string& user1, const std::string& user2) {
        if (user1 < user2)
            return user1 + "_" + user2;
        else return user2 + "_" + user1;
    }
};
#endif //ELABORATOLAB_CHATREGISTRY_H
