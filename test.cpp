//
// Created by lckde on 23/02/2025.
//

#include <gtest/gtest.h>
#include "ChatRegistry.h"
#include "Chat.h"
#include "User.h"
#include "Message.h"

// Test di ChatRegistry
class ChatRegistryTest : public ::testing::Test {
protected:

    ChatRegistry chatRegistry;
};

TEST_F(ChatRegistryTest, AddChat) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);

    ASSERT_NO_THROW(chatRegistry.ReturnChatWithUser(user1, user2));
}

TEST_F(ChatRegistryTest, AddMessageToChat_NewChat) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    Chat chat = chatRegistry.ReturnChatWithUser(user1, user2);
    ASSERT_EQ(chat.readMessage(0), "Alice: Hello, Bob!");
}

TEST_F(ChatRegistryTest, AddMessageToChat_ExistingChat) {
    User user1("Alice");
    User user2("Bob");
    Message message1(user1, "Hello, Bob!");
    Message message2(user1, "How are you?");

    chatRegistry.addMessageToChat(user1, user2, message1);
    chatRegistry.addMessageToChat(user1, user2, message2);

    Chat chat = chatRegistry.ReturnChatWithUser(user1, user2);
    ASSERT_EQ(chat.readMessage(1), "Alice: How are you?");
}

TEST_F(ChatRegistryTest, DisplayAllChats) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);

    // Redirect cout to a stringstream to capture the output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    chatRegistry.displayAllChats();

    std::cout.rdbuf(old);
    ASSERT_FALSE(buffer.str().empty());
}

TEST_F(ChatRegistryTest, MessagesToRead_ExistingChat) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    ASSERT_EQ(chatRegistry.messagesToRead(user1, user2), 1);
}

TEST_F(ChatRegistryTest, ReadNthMessage_ExistingChat) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    // Redirect cout to a stringstream to capture the output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    chatRegistry.readNthMessage(user1, user2, 0);

    std::cout.rdbuf(old);
    ASSERT_EQ(buffer.str(), "Alice: Hello, Bob!\n");
}

TEST_F(ChatRegistryTest, ReturnChatWithUser_ExistingChat) {
    User user1("Alice");
    User user2("Bob");
    Chat chat(user1, user2);

    chatRegistry.addChat(chat);

    ASSERT_NO_THROW(chatRegistry.ReturnChatWithUser(user1, user2));
}

TEST_F(ChatRegistryTest, SearchMessage_ValidUser) {
    User user("Alice");
    User user2("Bob");
    Message message(user, "Find me!");

    chatRegistry.addMessageToChat(user, user2, message);

    Message foundMessage = chatRegistry.SearchMessage(user, "Find me!");
    ASSERT_EQ(foundMessage.getContent(), "Find me!");
}

TEST_F(ChatRegistryTest, SearchMessage_InvalidUser) {
    User user("Alice");
    User user2("Bob");
    Message message(user, "Hello, Bob!");

    chatRegistry.addMessageToChat(user, user2, message);

    ASSERT_THROW(chatRegistry.SearchMessage(User("Charlie"), "Hello, Bob!"), std::invalid_argument);
}

TEST_F(ChatRegistryTest, AddMessageToChat_SameUsernames) {
    User user1("Alice");
    User user2("Alice");
    Message message(user1, "Hello, Alice!");

    ASSERT_THROW(chatRegistry.addMessageToChat(user1, user2, message), std::invalid_argument);
}

TEST_F(ChatRegistryTest, ReadNthMessage_NonExistentChat) {
    User user1("Alice");
    User user2("Bob");

    ASSERT_THROW(chatRegistry.readNthMessage(user1, user2, 0), std::invalid_argument);
}

TEST_F(ChatRegistryTest, ReadNthMessage_NonExistentMessage) {
    User user1("Alice");
    User user2("Bob");
    Message message(user1, "Hello, Bob!");

    chatRegistry.addMessageToChat(user1, user2, message);

    ASSERT_THROW(chatRegistry.readNthMessage(user1, user2, 1), std::out_of_range);
}



// Test di User
class UserTest : public ::testing::Test {
protected:
    User user{"Alice"};
};

TEST_F(UserTest, GetUsername) {
    ASSERT_EQ(user.getUsername(), "Alice");
}

// Test di Message
class MessageTest : public ::testing::Test {
protected:
    User user{"Alice"};
    Message message{user, "Hello, world!"};
};

TEST_F(MessageTest, GetSenderName) {
    ASSERT_EQ(message.getSenderName(), "Alice");
}

TEST_F(MessageTest, GetContent) {
    ASSERT_EQ(message.getContent(), "Hello, world!");
}

TEST_F(MessageTest, IsRead) {
    ASSERT_FALSE(message.isRead());
}

TEST_F(MessageTest, SetRead) {
    message.setRead(true);
    ASSERT_TRUE(message.isRead());
}

TEST_F(MessageTest, DisplayMessage) {
    ASSERT_EQ(message.displayMessage(), "Alice: Hello, world!");
}

// Test di Chat
class ChatTest : public ::testing::Test {
protected:
    User user1{"Alice"};
    User user2{"Bob"};
    Chat chat{user1, user2};
};

TEST_F(ChatTest, GetUser1) {
    ASSERT_EQ(chat.getUser1(), "Alice");
}

TEST_F(ChatTest, GetUser2) {
    ASSERT_EQ(chat.getUser2(), "Bob");
}

TEST_F(ChatTest, AddMessage) {
    Message message{user1, "Hello, Bob!"};
    chat.addMessage(message);
    ASSERT_EQ(chat.readMessage(0), "Alice: Hello, Bob!");
}

TEST_F(ChatTest, DisplayChat) {
    Message message{user1, "Hello, Bob!"};
    chat.addMessage(message);

    std::string expectedOutput = "Message from Alice to Bob:\nAlice: Hello, Bob!\n";

    // Redirect cout to a stringstream to capture the output
    std::stringstream buffer;
    std::streambuf* old = std::cout.rdbuf(buffer.rdbuf());

    std::cout << chat.displayChat();

    std::cout.rdbuf(old);
    ASSERT_EQ(buffer.str(), expectedOutput);
}

TEST_F(ChatTest, MessagesCounter) {
    Message message1{user1, "Hello, Bob!"};
    Message message2{user2, "Hi, Alice!"};
    chat.addMessage(message1);
    chat.addMessage(message2);
    ASSERT_EQ(chat.messagesCounter(user1), 1);
}

TEST_F(ChatTest, ReadMessage_NonExistent) {
    ASSERT_THROW(chat.readMessage(1), std::out_of_range);
}

TEST_F(ChatTest, FindMessage) {
    Message message{user1, "Hello, Bob!"};
    chat.addMessage(message);
    ASSERT_EQ(chat.FindMessage("Hello, Bob!").getContent(), "Hello, Bob!");
}

TEST_F(ChatTest, FindMessage_NonExistent) {
    ASSERT_THROW(chat.FindMessage("Non-existent message"), std::invalid_argument);
}

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}

