#include "commands.h"

#include <memory> 
#include <string> 

class TextEditor{
    public:
    const std::string& getText() const; 
    void prepare(const std::shared_ptr<Command>& command);

    void commit 
    undo 
    redo 
}


v reverse 
i insert 
d delete 
c commit 
r redo 
u undo
