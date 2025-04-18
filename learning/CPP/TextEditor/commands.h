#pragma once
#include <string>




class Command
{
public:
    virtual void perform(std::string &str) = 0;
    virtual void undo(std::string &str) = 0;
};

class InsertCommand : public Command
{
private:
    string data;
    int position;

public:
    InsertCommand(int position, const std::string &test);
    void perform(std::string &str);
    void undo(std::string &str)
};

class DeleteCommand : public Command
{

public:
    DeleteCommand(int pos, int len);
    void perform(std::string &str);
    void undo(std::string &str)
}

class DeleteCommand : public Command
{

public:
    DeleteCommand(int pos, int len);
    void perform(std::string &str);
    void undo(std::string &str)
};

class DeleteCommand : public Command
{
    public:
        DeleteCommand(int pos, int len);
        void perform(std::string &str);
        void undo(std::string &str)
};