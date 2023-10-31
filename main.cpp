#include <iostream>
#include <string>
#include <stdio.h>

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

    void parse() {
        if (_fp) {
            while (isspace(_ch = fgetc(_fp)));
            do {
                lexical();
                statement();
            } while (nextToken != TOKEN_TYPE::NONE);
            printSymbolTable();
        }
    }

private:
    TOKEN_TYPE nextToken = TOKEN_TYPE::NONE;
    string tokenString;

    File *_fp = 0;  //input file
    char _ch = 0;   //current character
    int _ID, _CONST, _OP;
    map<string, string> _symTable;

    void getChar() {
        _ch = fgetc(_fp);
    }

    bool isSpace(char c)
        return c <= 32;
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isSpecial(char c) {
        return c == ':' || c == ';' || c == '(' || c == ')';
    }

    void msgError(const char *msg) {
        cerr << "(Error) " << msg << endl;
    }

    void msgWarning(const char *msg) {
        cerr << "(Warning) " << msg << endl;
    }

    void printSymbolTable() {
        cout << "Result ==> ";
        for (auto p = _symTable.begin(); p != _symTable.end(); p++) {
            cout << p->first << ": " <<  (p->second != "" ? p->second : "Unknown") << "; ";
        }
        cout << endl;
    }

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
