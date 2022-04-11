#include "ClientHandler.h"
#include "socket/Socket.h"

//----------
const int SEQUENCE_COUNT = 3;
const std::string SEQUENCE_REGEX_STRING = "^seq(\\d) (\\d+) (\\d+)";
const std::string EXPORT_REGEX_STRING = "^export seq";
//----------

namespace client
{
    ClientHandler::SequenceProperty::SequenceProperty(const std::smatch& parsedLine)
    {
        this->id = static_cast<uint64_t>(std::stoi(parsedLine[1]));
        this->first = static_cast<uint64_t>(std::stoi(parsedLine[2]));
        this->step = static_cast<uint64_t>(std::stoi(parsedLine[3]));
    }
    bool ClientHandler::SequenceProperty::IsValidProperty()
    {
        return IsValidSequenceIndex() && IsValidStep();
    }
    bool ClientHandler::SequenceProperty::IsValidSequenceIndex()
    {
        return this->id >= 1 && this->id <= SEQUENCE_COUNT;
    }
    bool ClientHandler::SequenceProperty::IsValidStep()
    {
        return this->step > 0;
    }
}

namespace client
{
    ClientHandler::ClientHandler(std::unique_ptr<socket::Socket> currentSocket)
    : socket(std::move(currentSocket))
    , sequenceRegex(SEQUENCE_REGEX_STRING)
    , exportRegex(EXPORT_REGEX_STRING)
    {
        sequenceProperties.resize(SEQUENCE_COUNT);
    }

    void ClientHandler::main()
    {

    }

    bool ClientHandler::ExecuteCommand(const std::string &line)
    {
        std::smatch result;

        if (std::regex_search(line, result, sequenceRegex))
        {
            SequenceProperty sequenceProperty(result);            

            return GenerateSequence(sequenceProperty);
        } 
        else if (std::regex_search(line, result, exportRegex))
        {
            return ExportSequence();
        }

        return false;
    }

    bool ClientHandler::GenerateSequence(const SequenceProperty& property)
    {
        return false;
    }

    bool ClientHandler::ExportSequence()
    {
        return false;
    }

    std::string ClientHandler::GenerateStringSequence(const SequenceProperty& property)
    {

    }
}