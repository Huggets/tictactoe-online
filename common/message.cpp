#include "message.hpp"
#include <cstring>
#include <unistd.h>

const char * Message::getBuffer() const {
    return m_buffer;
}

MessageType Message::getType() const {
    return static_cast<MessageType>(m_buffer[0]);
}

void Message::setType(MessageType type) {
    m_buffer[0] = type;
}

const char * Message::getContent() const {
    return m_buffer + 1;
}

void Message::setContent(const char * content) {
    strcpy(m_buffer + 1, content);
}

int Message::send(int socket) {
    return write(socket, m_buffer, 256);
}

int Message::receive(int socket) {
    return read(socket, m_buffer, 256);
}