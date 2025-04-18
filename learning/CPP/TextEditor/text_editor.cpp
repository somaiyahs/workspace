#include "text_editor.h"
#include <queue>
#include <stack>

class TextEditor{
    private:
    std::string text; 
    std::queue<Command*> commandBuffer;
    std::stack<Command*> undoStack; 
    std::stack<Command*> redoStack;

    public: 
    void insert(int pos, const std::string& str){
        commandBuffer.push(new InsertCommand(pos, str));
    }

    void erase(int pos, int len){
        commandBuffer.push(new DeleteCommand(pos, len));
    }

    void reverse(int pos, int len){
        commandBuffer.push(new ReverseCommand(pos, len));
    }

    void commit(){
        while(!commandBuffer.empty()){
            Command* cmd = commandBuffer.front();
            commandBuffer.pop();
            cmd->perform(text);
            undoStack.push(cmd);
            /****** to be explained later */
            while (!redoStack.empty()){
                delete redoStack.top();
                redoStack.pop();
            }
        }
        getText();
    }

    void undo(){
        if (!undoStack.empty()){
            Command* cmd = undoStack.top();
            undoStack.pop();
            cmd->undo(text);
            redoStack.push(cmd);
        }
        gethText();
    }

    void redo(){
        if (!redoStack.empty()){
            Command* cmd = redoStack.top();
            redoStack.pop();
            cmd->perform(text);
            udoStack.push(cmd);
        }

        getText();
    }

    void getText(){
        std::cout << text << std::endl;
    }
};