//
// Created by lckde on 23/02/2025.
//

//EDIT a little bit

#include "ChatRegistry.h"
#include <gtest/gtest.h>

// Test per aggiungere una chat tra due utenti
TEST(ChatRegistryTest, AddChat) {
    ChatRegistry registry;
    User user1("UserA"), user2("UserB");
    Chat chat(user1, user2);

    registry.addChat(chat);

    testing::internal::CaptureStdout();
    registry.displayAllChats();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_FALSE(output.empty());  // Controlla che ci sia almeno una chat
}

// Test per aggiungere un messaggio in una chat tra utenti
TEST(ChatRegistryTest, AddMessageToChat) {
    ChatRegistry registry;
    User user1("User1"), user2("User2");
    Message msg(user1 ,"Test message");

    registry.addMessageToChat(user1, user2, msg);

    testing::internal::CaptureStdout();
    registry.displayAllChats();
    std::string output = testing::internal::GetCapturedStdout();

    EXPECT_NE(output.find("Test message"), std::string::npos); // Controlla se il messaggio è stato salvato
}





int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}