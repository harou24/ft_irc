#include "message.hpp"

Message::Message(void) : data("default"), hasBeenRead(false) { }

Message::Message(const std::string &data) : data(data), hasBeenRead(false) { }

Message::Message(const Message &m) : data(m.data), hasBeenRead(m.hasBeenRead) { }

Message::~Message(void) { }

std::string Message::getData(void) const { return (this->data); }

bool        Message::hasItBeenRead(void) const { return (this->hasBeenRead); }

void        Message::setData(const std::string &data) { this->data = data; }

void        Message::setRead(const bool status) { this->hasBeenRead = status; }
