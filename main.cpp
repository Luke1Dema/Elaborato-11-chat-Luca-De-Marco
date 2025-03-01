//ELABORATO N.11


#include "User.h"
#include "Chat.h"
#include "Message.h"
#include "ChatRegistry.h"


int main() {
    User user1("Alice");
    User user2("Barbara");
    User user3("Carlo");

    ChatRegistry registry;


    registry.addMessageToChat(user1, user2, Message(user1, "Ciao Barbara!"));
    registry.addMessageToChat(user2, user1, Message(user2, "Ciao Alice! Come stai?"));
    registry.addMessageToChat(user1, user2, Message(user1, "Bene, grazie! E tu?"));


    registry.addMessageToChat(user1, user3, Message(user1, "Ciao Carlo!"));
    registry.addMessageToChat(user3, user1, Message(user3, "Ehi Alice!"));


    registry.displayAllChats();

    return 0;
}
