//
// Created by lckde on 29/09/2024.
//

#ifndef ELABORATOLAB_CHATREGISTRY_H
#define ELABORATOLAB_CHATREGISTRY_H

#include "Chat.h"
#include <map>


class ChatRegistry {

public:

    void addChat(const Chat& chat);

    void addMessageToChat(const User& user1, const User& user2, const Message& message);


    void displayAllChats();

    int messagesToRead(const User& sender, const User& recipient) const;

    void readNthMessage(const User& sender, const User& recipient, int n);

    Chat returnChatWithUser(const User& you, const User& recipient);

    std::list<Message> searchMessage (const User& self, const std::string& content);

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
