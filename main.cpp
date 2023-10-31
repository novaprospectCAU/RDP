#include <iostream>
#include <string>

using namespace std;

class RDP { //recursive descent parsing
    typedef enum {
        NONE = 0,

        IDENT, // any names conforming to C identifier rules
        CONST, // any decimal numbers

        OP_ASSIGN, // :=
        OP_PLUS = '+',
        OP_MINUS = '-',
        OP_MULTIPLY = '*',
        OP_DIVIDE = '/',

        SEMICOLON = ';',
        LPAREN = '(',
        RPAREN = ')'
    } TOKEN_TYPE;
public:
    RDP(const char *filepath) {
        _fp = fopen(filepath, "r");
    }

    ~RDP() {
        if (_fp) fclose(_fp);
    }
private:
    void getChar() {}
    bool isSpace(char c) {}
    bool isOperator(char c) {}
    bool isSpecial(char c) {}

    void msgError(const char *msg) {}
    void msgWarning(const char *msg) {}
    void printSymbolTable() {}

    void factor() {}
    void term() {}
    void expression() {}
    void statement() {}
    void statements() {}
    void lexical() {}
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<input.txt>\n";
    }

	return 0;
}
