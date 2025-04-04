//
// Created by lckde on 29/09/2024.
//

#ifndef ELABORATOLAB_CHAT_H
#define ELABORATOLAB_CHAT_H

#include <iostream>
#include <utility>
#include <vector>
#include <list>
#include "User.h"
#include "Message.h"


class Chat {
public:
    Chat(User  user1, User  user2) : user1(std::move(user1)), user2(std::move(user2)) {}


    std::string getUser1() const {
        return user1.getUsername();
    }

    std::string getUser2() const {
        return user2.getUsername();
    }


    void addMessage(const Message& message) {
        messages.push_back(message);
    }

    std::string displayChat() {
        std::string chat = "Message from " + user1.getUsername() + " to " + user2.getUsername() + ":\n";
        for ( auto& msg : messages) {
            chat += msg.displayMessage() + "\n";
            msg.setRead(true);
        }
        return chat;
    }

    int messagesCounter(const User& sender) const {
        int count=0;
        for(auto const&  it : messages){
            if (it.getSenderName()==sender.getUsername()){
                if(!it.isRead()){
                    count+=1;
                }
            }
        }
        return count;
    }

    std::string readMessage(int n) {
        if (n >= 0 && n < messages.size()) {
            auto& it = messages[n];
            it.setRead(true);
            return it.displayMessage();
        }
        throw std::out_of_range("MESSAGE DOES NOT EXIST!");
    }


    std::list<Message> findMessage(const std::string& content){
        std::list<Message> foundMessages;
        for(auto &  it : messages){
            if(it.getContent().find(content) != std::string::npos){
                foundMessages.push_back(it);
            }
        }
        if(!foundMessages.empty()){
            std::cout<< "Messages found! Returning list of messages..." <<std::endl;
            return foundMessages;
        }
        throw std::invalid_argument("NO MESSAGES CONTAINING THE SPECIFIED CONTENT WERE FOUND!");
    }



private:
    User user1;
    User user2;
    std::vector<Message> messages;
};

#endif //ELABORATOLAB_CHAT_H
