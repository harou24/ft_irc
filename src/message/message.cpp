#include "message.hpp"

Message::Message(void) : data("default"), hasBeenRead(false), cmd(new CmdParser()) { }

Message::Message(const std::string &data) : data(data), hasBeenRead(false), cmd(new CmdParser(data)) { }

Message::Message(Client *cl, const std::string &time, const std::string &data)
    : sentBy(cl), time(time), data(data), hasBeenRead(false), cmd(new CmdParser(data)) { }

Message::Message(const Message &m) : data(m.data), hasBeenRead(m.hasBeenRead) { }

Message::~Message(void) { }

Client*  Message::getSender(void) const { return (this->sentBy); }

std::string Message::getTime(void) const { return (this->time); }

std::string Message::getData(void) const { return (this->data); }

CmdParser&  Message::getCmd(void) const { return (*(this->cmd)); }

bool        Message::hasItBeenRead(void) const { return (this->hasBeenRead); }

void        Message::setData(const std::string &data) { this->data = data; }

void        Message::setRead(const bool status) { this->hasBeenRead = status; }
