#ifndef BOOKNODE_HPP
#define BOOKNODE_HPP

#include <string>
#include <unordered_map>
#include <iostream>
#include <memory>

class BookNode {
    public:
        BookNode();
        ~BookNode();

        std::unordered_map<std::string, std::shared_ptr<BookNode> > _followUpMoves;
        std::shared_ptr<BookNode> addFollowUpMove(std::string move); 
};

#endif // BOOKNODE_HPP
