#ifndef COMMAND_HANDLER_HPP
#define COMMAND_HANDLER_HPP

#include "graph_state.hpp"
#include <string>
#include <sstream>

class CommandHandler {
private:
    GraphState& graphState;
    
public:
    CommandHandler(GraphState& state);

    std::string processCommand(const std::string& command);

    std::string handleNewGraph(std::istringstream& iss);

    std::string handleNewPoint(std::istringstream& iss);

    std::string handleRemovePoint(std::istringstream& iss);

    std::string handleConvexHull();
};

#endif
