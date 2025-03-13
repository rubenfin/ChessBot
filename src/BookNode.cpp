#include "BookNode.hpp"

BookNode::BookNode() {
    // std::cout << "BookNode constructed" << std::endl;
}

BookNode::~BookNode() {
    // std::cout << "BookNode destructed" << std::endl;
}

std::shared_ptr<BookNode> BookNode::addFollowUpMove(std::string move)
{
    _followUpMoves.emplace(move, std::make_shared<BookNode>());
    return _followUpMoves[move];
}
