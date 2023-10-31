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

    void factor() {
        if (nextToken == TOKEN_TYPE::IDENT) {
            //TODO
            lexical();
        } else if (nextToken == TOKEN_TYPE::CONST) {
            lexical();
        } else if (nextToken == TOKEN_TYPE::LPAREN) {
            lexical();
            expression();
            if (nextToken == TOKEN_TYPE::RPAREN) lexical();
            else error("missing right parenthesis");
        } else {
            error("??? #2");
        }
    }

    void term() {
        factor();
        while (next_token == TOKEN_TYPE::OP_MULTIPLY || nextToken == TOKEN_TYPE::OP_DIVIDE) {
            lexical();
            factor();
        }
    }

    void expression() {
        if (nextToken == TOKEN_TYPE::OP_PLUS || nextToken == TOKEN_TYPE::OPMINUS) {
            lexical();
            term();
        }
    }

    void statement() {
        _ID = _CONST = _OP = 0;
        if (nextToken == TOKEN_TYPE::IDENT) {
            _ID = 1;
            lexical();
            if (nextToken == TOKEN_TYPE::OP_ASSIGN) lexical();
            else error("missing assignment");
            expression();
        } else {
            error("missing identifier");
        }

        cout << endl
              << "ID: " << _ID
              << "; CONST: " << _CONST
              << "; OP: " << _OP << endl
              << "(OK)" << endl;
    }

    void statements() {
        do {
            lexical();
            statement();
        } while (nextToken == TOKEN_TYPE::SEMICOLON);
    }

    void lexical() {
        tokenString.clear();
        if (isdigit(_ch)) {
            while (isdigit(_ch)) {
                tokenString.push_back(_ch);
                getChar();
            }
            nextToken = TOKEN_TYPE::CONST;
            _CONST++;
        } else if (isalpha(_ch)) {
            while (isalpha(_ch) || isdigit(_ch)) {
                tokenString.push_back(_ch);
                getChar();
            }
            nextToken = TOKEN_TYPE::IDENT;
            _symTable[tokenString] = "";
            _ID++;
        } else if (isOperator(_ch)) {
            char prev = _ch;
            tokenString.push_back(_ch);
            nextToken = (TOKEN_TYPE)_ch;
            getChar();
            _OP++;
        } else if (isSpecial(_ch)) {
            char prev = _ch;
            tokenString.push_back(_ch);
            nextToken = (TOKEN_TYPE)_ch;
            getChar();

            if (prev == ':' && ch == '=') {
                tokenString.push_back(_ch);
                nextToken = TOKEN_TYPE::OP_ASSIGN;
                getChar();
            }
        } else if (_ch == EOF) {
            nextToken = TOKEN_TYPE::NONE;
        } else {
            nextToken = TOKEN_TYPE::NONE;
            getChar();
        }
        while (isspace(_ch)) getChar();

        cout << tokenString << " ";
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<input.txt>\n";
    }

	return 0;
}
