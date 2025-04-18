#include "commands.h"


class InsertCommand : public Command {
    private:
    std::string text;
    int position; 

    public:
    InsertCommand(int pos, const std::string& t) : position(pos), text(t) {}
    
    void perform(std::string& str) override {
        if (position > str.size()){
            position = str.size();
        }
        str.insert(position, text);
    }

    void undo(std::string& str) override{
        str.erase(position, text.size());
    }
};

class DeleteCommand : public Command {
    private: 
    std::string removedData; 
    int position;
    int length;
    public:
    DeleteCommand(int pos, int len) : position(pos), length(len) {}
    
    void perform(std::string& str) override{
        if(position +length > str.size()) {
            length = str.size() - position;
        }

        removedData = str.substr(position, length);
        str.erase(position, length);
    }
    
    void undo(std::string& str) override{
        str.insert(position, removedData);
    }
};

class ReverseCommand: Command {
    private: 
    int position; 
    int length;

    public: 
    ReverseCommand(int pos, int len): position(pos). length(len){}

    void perform(std::string& str) override{
        if (position+length > str.size()){
            length = str.size() - position
        }
        std::reverse(str.begin() +  position, str.begin()+ length);
    }

    void undo(std::string& str) override {
        perform(str);
    }
};

