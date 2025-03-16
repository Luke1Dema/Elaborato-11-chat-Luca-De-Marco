//
// Created by lckde on 23/02/2025.
//

#include <gtest/gtest.h>
#include "ChatRegistry.h"
#include "Chat.h"
#include "User.h"
#include "Message.h"


class ChatRegistryTest : public ::testing::Test {
protected:
    ChatRegistry chatRegistry;
};

// Test per aggiungere una chat
TEST_F(ChatRegistryTest, AddChat) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);

    ASSERT_NO_THROW(chatRegistry.ReturnChatWithUser(user1, user2));
}

// Test per aggiungere un messaggio a una nuova chat
TEST_F(ChatRegistryTest, AddMessageToChat_New) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    Chat chat = chatRegistry.ReturnChatWithUser(user1, user2);
    ASSERT_EQ(chat.readMessage(1), "Alice: Hello, Bob!");
}

// Test per aggiungere un messaggio a una chat esistente
TEST_F(ChatRegistryTest, AddMessageToChat_Existing) {
    User user1("Alice");
    User user2("Bob");
    Message message1(user1, "Hello, Bob!");
    Message message2(user1, "How are you?");

    chatRegistry.addMessageToChat(user1, user2, message1);
    chatRegistry.addMessageToChat(user1, user2, message2);

    Chat chat = chatRegistry.ReturnChatWithUser(user1, user2);
    ASSERT_EQ(chat.readMessage(2), "Alice: How are you?");
}

// Test per visualizzare tutte le chat
TEST_F(ChatRegistryTest, DisplayAllChats) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);


    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    chatRegistry.displayAllChats();

    std::cout.rdbuf(old);
    ASSERT_FALSE(buffer.str().empty());
}

// Test per contare i messaggi non letti in una chat
TEST_F(ChatRegistryTest, MessagesToRead) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    ASSERT_EQ(chatRegistry.messagesToRead(user1, user2), 1);
}

// Test per leggere l'n-esimo messaggio in una chat
TEST_F(ChatRegistryTest, ReadNthMessage) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    // Redirect cout to a stringstream to capture the output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    chatRegistry.readNthMessage(user1, user2, 1);

    std::cout.rdbuf(old);
    ASSERT_EQ(buffer.str(), "Alice: Hello, Bob!\n");
}

// Test per ritornare una chat con un utente
TEST_F(ChatRegistryTest, ReturnChatWithUser) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);

    ASSERT_NO_THROW(chatRegistry.ReturnChatWithUser(user1, user2));
}

// Test per cercare un messaggio con un utente valido
TEST_F(ChatRegistryTest, SearchMessage) {
    User user("Alice");
    User user2("Bob");
    Message message(user, "Find me!");

    chatRegistry.addMessageToChat(user, user2, message);

    Message foundMessage = chatRegistry.SearchMessage(user, "Find me!");
    ASSERT_EQ(foundMessage.getContent(), "Find me!");
}

// Test per cercare un messaggio con un utente non valido
TEST_F(ChatRegistryTest, SearchMessage_Invalid) {
    User user("Alice");
    User user2("Bob");
    Message message(user, "Hello, Bob!");

    chatRegistry.addMessageToChat(user, user2, message);

    ASSERT_THROW(chatRegistry.SearchMessage(User("Charlie"), "Hello, Bob!"), std::invalid_argument);
}

// Test per eccezione utente e mittente con lo stesso nome
TEST_F(ChatRegistryTest, AddMessageToChat_SameUsernames) {
    User user1("Alice");
    User user2("Alice");
    Message message(user1, "Hello, Alice!");

    ASSERT_THROW(chatRegistry.addMessageToChat(user1, user2, message), std::invalid_argument);
}

// Test per eccezione chat inesistente
TEST_F(ChatRegistryTest, ReadNthMessage_NonExistentChat) {
    User user1("Alice");
    User user2("Bob");

    ASSERT_THROW(chatRegistry.readNthMessage(user1, user2, 1), std::invalid_argument);
}

// Test per eccezione messaggio inesistente
TEST_F(ChatRegistryTest, ReadNthMessage_NonExistentMessage) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    ASSERT_THROW(chatRegistry.readNthMessage(user1, user2, 2), std::invalid_argument);
}

