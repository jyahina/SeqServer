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
            ClientHandler(std::unique_ptr<socket::Socket> currentSocket);
            
            void main();

        private:
            struct SequenceProperty
            {
                SequenceProperty(const std::smatch& parsedLine);
                
                bool IsValidProperty();

                uint64_t id = 0;
                uint64_t first = 0;
                uint64_t step = 0;
                
            private:
                bool IsValidSequenceIndex();
                bool IsValidStep();
            };
        
        private:
            const std::regex sequenceRegex;
            const std::regex exportRegex;

            std::unique_ptr<socket::Socket> socket;
            std::vector<SequenceProperty> sequenceProperties;
            
            bool ExecuteCommand(const std::string &line);
            bool GenerateSequence(const SequenceProperty &property);
            bool ExportSequence();

            std::string GenerateStringSequence(const SequenceProperty &property);

    };    
}