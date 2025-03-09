//
// Created by lckde on 29/09/2024.
//

#include "ChatRegistry.h"

void ChatRegistry::addChat(const Chat &chat) {
    std::string key = generateChatKey(chat.getUser1(), chat.getUser2());
    chats.insert(std::pair<std::string, Chat>(key, chat));
}

void ChatRegistry::addMessageToChat(const User &user1, const User &user2, const Message &message) {
    if(user1.getUsername()!=user2.getUsername()){
        std::string key = generateChatKey(user1.getUsername(), user2.getUsername());

        // Si constrolla se la chat esiste già tramite find()

        auto it = chats.find(key);

        if (it != chats.end()) {
            it->second.addMessage(message); //si aggiunge il messaggio alla chat
        }
        else {
            // Si crea una nuova chat se non esiste
            Chat newChat(user1, user2);
            newChat.addMessage(message);
            chats.insert(std::pair<std::string, Chat>(key, newChat));
        }
    }
}

void ChatRegistry::displayAllChats() const {
    for (const auto& pair : chats) {
        std::cout << pair.second.displayChat() << std::endl;
    }
}
