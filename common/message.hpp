#ifndef MESSAGE_HPP
#define MESSAGE_HPP

enum MessageType {
    echo, disconnect, yourturn, opponentturn
};

class Message {
public:
    const char * getBuffer() const; // Get the message buffer

    MessageType getType() const; // Get the message type
    void setType(MessageType type); // Set the type of the message

    const char * getContent() const; // Get the message content
    void setContent(const char * content); // Set the content of the message (must be null terminated)

    int send(int socket); // Send a message to the socket
    int receive(int socket); // Receive a message from the socket
private:
    char m_buffer[256]; // The buffer send to the socket
};

#endif // MESSAGE_HPP