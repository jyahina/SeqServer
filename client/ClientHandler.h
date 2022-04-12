#pragma once

#include "socket/Socket.h"

#include <memory>
#include <vector>
#include <string>
#include <regex>

namespace client
{
    class ClientHandler
    {
        public:
            ClientHandler(std::unique_ptr<net_socket::Socket> currentSocket);
            ~ClientHandler();

            void main();

        private:
            struct SequenceProperty
            {
                SequenceProperty(const std::smatch& parsedLine);

                bool IsValidProperty() const;

                bool available = false;
                uint64_t id = 0;
                uint64_t first = 0;
                uint64_t step = 0;
                
            private:
                bool IsValidSequenceIndex() const;
                bool IsValidStep() const;
            };
        
        private:
            const std::regex sequenceRegex;
            const std::regex exportRegex;

            std::unique_ptr<net_socket::Socket> socket;
            std::vector<SequenceProperty> sequenceProperties;
            
            bool ExecuteCommand(const std::string &line);
            bool UpdateSequence(const SequenceProperty &property);
            bool ExportSequence();
            bool IsAvailableSequenceProperty() const;
            void SendWaitToUser();
    };    
}