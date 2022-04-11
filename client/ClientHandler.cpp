#include "ClientHandler.h"
#include "socket/Socket.h"
#include "socket/SocketException.h"

#include <thread>
#include <iostream>

//----------
const size_t SEQUENCE_COUNT = 3;
const size_t MAX_LENGTH_LINE = 60;
const int SLEEP_TIME_MILLISECONDS = 100;
const std::string SEQUENCE_REGEX_STRING = "^seq(\\d) (\\d+) (\\d+)";
const std::string EXPORT_REGEX_STRING = "^export seq";
const std::string WAIT_COMMAND = "-> ";
//----------

namespace client
{
    ClientHandler::SequenceProperty::SequenceProperty(const std::smatch& parsedLine)
    {
        this->id = static_cast<uint64_t>(std::stoi(parsedLine[1]));
        this->first = static_cast<uint64_t>(std::stoi(parsedLine[2]));
        this->step = static_cast<uint64_t>(std::stoi(parsedLine[3]));
        this->available = true;
    }
    bool ClientHandler::SequenceProperty::IsValidProperty() const
    {
        return this->available && IsValidSequenceIndex() && IsValidStep();
    }
    bool ClientHandler::SequenceProperty::IsValidSequenceIndex() const
    {
        return this->id >= 1 && this->id <= SEQUENCE_COUNT;
    }
    bool ClientHandler::SequenceProperty::IsValidStep() const
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

    ClientHandler::~ClientHandler()
    {
        this->socket->Close();
    }

    void ClientHandler::main()
    {
        std::string buffer = "";
        char input[MAX_LENGTH_LINE + 1];

        try
        {
            SendWaitToUser();

            while (true)
            {
                memset(input, 0, sizeof(input)); // set cmd data

                this->socket->Recv(input, MAX_LENGTH_LINE);

                buffer.append(input);

                const auto endLine = buffer.find("\n");
                if (endLine != std::string::npos)
                {
                    const auto command = buffer.substr(0, endLine);
                    buffer = buffer.substr(endLine + 1, buffer.size());

                    ExecuteCommand(command);
                    SendWaitToUser();
                }

                std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_TIME_MILLISECONDS));
            }
        }
        catch (socket::SocketException& e)
        {
            std::cout << e.what() << std::endl;
            return;
        }
    }

    bool ClientHandler::ExecuteCommand(const std::string &line)
    {
        std::smatch result;

        if (std::regex_search(line, result, sequenceRegex))
        {
            SequenceProperty sequenceProperty(result);            

            return UpdateSequence(sequenceProperty);
        } 
        else if (std::regex_search(line, result, exportRegex))
        {
            return ExportSequence();
        }

        return false;
    }

    bool ClientHandler::UpdateSequence(const SequenceProperty& property)
    {
        if (!property.IsValidProperty())
        {
            return false;
        }

        sequenceProperties[property.id] = property;

        return true;
    }

    bool ClientHandler::ExportSequence()
    {
        if (!IsAvailableSequenceProperty())
        {
            return false;
        }

        std::vector<uint64_t> currentValueOfSequence(SEQUENCE_COUNT, 0);

        while (true)
        {
            std::string sequences = "";

            for (size_t id = 0; id < SEQUENCE_COUNT; ++id)
            {
                if (!this->sequenceProperties[id].IsValidProperty())
                {
                    continue;
                }

                currentValueOfSequence[id] = (UINT64_MAX - currentValueOfSequence[id] < this->sequenceProperties[id].step)
                    ? this->sequenceProperties[id].first
                    : currentValueOfSequence[id] + this->sequenceProperties[id].step;

                sequences.append(std::to_string(currentValueOfSequence[id]) + "\t");

            }

            sequences.append("\r\n");

            this->socket->Send(sequences);

            std::this_thread::sleep_for(std::chrono::microseconds(SLEEP_TIME_MILLISECONDS));
        }

        return true;
    }

    bool ClientHandler::IsAvailableSequenceProperty() const
    {
        bool isAvailable = false;

        for (const auto& property : sequenceProperties)
        {
            isAvailable = isAvailable || property.available;
        }

        return isAvailable;
    }

    void ClientHandler::SendWaitToUser()
    {
        this->socket->Send(WAIT_COMMAND);
    }
}