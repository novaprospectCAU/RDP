#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <stdio.h>

//###: debugging tool sentence

using namespace std;

class RDP { //recursive descent parsing
    typedef enum {
        END = -1,
        NONE = 0,

        IDENT, //any names conforming to C identifier rules
        CONST, //any decimal numbers

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
            statements();
            printSymbolTable();
        }
    }

private:
    TOKEN_TYPE next_token = TOKEN_TYPE::NONE;
    string token_string;

    FILE *_fp = 0;  //input file
    char _ch = 0;   //current character
    int _ID, _CONST, _OP;
    string _result;
    vector<string> _tokens;
    map<string, string> _symTable;

    void addToken() {
        _tokens.push_back(token_string);
    }

    void getChar() {
        _ch = fgetc(_fp);
    }

    bool isSpace(char c) {
        return c <= 32;
    }

    bool isOperator(char c) {
        return c == '+' || c == '-' || c == '*' || c == '/';
    }

    bool isOperator(string s) {
        return s == "+" || s == "-" || s == "*" || s == "/";
    }

    bool isSpecial(char c) {
        return c == ':' || c == ';' || c == '(' || c == ')';
    }

    void msgError(string msg) {
        _result = "(Error) " + msg;
    }

    void msgWarning(string msg) {
        _result = "(Warning) " + msg;
    }

    void printStatement() {
        if (_tokens.size() == 0) return;
        for (int i = 0; i < (int)_tokens.size()-1; i++) {
            cout << _tokens[i];
            if (_tokens[i] != "(" && _tokens[i+1] != ")") cout << " ";
        }
        cout << _tokens.back() << ";\n";
        cout << "ID: " << _ID << "; CONST: " << _CONST << "; OP: " << _OP << endl;
        cout << _result << endl;
    }

    void printSymbolTable() {
        cout << "Result ==> ";
        for (auto p = _symTable.begin(); p != _symTable.end(); ++p) {
            cout << p->first << ": " <<  (p->second != "" ? p->second : "Unknown") << "; ";
        }
        cout << endl;
    }

    string factor() {
cout << "   #FACTOR: " << token_string << endl; //###
        string ret;
        if (next_token == TOKEN_TYPE::IDENT) {
            addToken();
            if (_symTable.find(token_string) == _symTable.end()) {
                _symTable[token_string] = ""; //add variable
                msgError("undefined variable (" + token_string + ") referenced");
            }
            ret = _symTable[token_string];
cout << "--- " << token_string << "(" << ret << ")\n"; //###
            lexical();
        } else if (next_token == TOKEN_TYPE::CONST) {
            addToken();
            ret = token_string;
            lexical();
        } else if (next_token == TOKEN_TYPE::LPAREN) {
            addToken();
            lexical();
            ret = expression();
            if (next_token == TOKEN_TYPE::RPAREN) {
                addToken();
                lexical();
            } else msgError("missing right parenthesis");
        } else { //try error correction
            if (isOperator(token_string)) msgWarning("remove duplicated operator(" + token_string + ")");
            else msgWarning("ignore incomplete syntax");
        }
        return ret;
    }

    string term() {
cout << "   #TERM: " << token_string << endl; //###
        string ret = factor();
cout << "   #FACTOR_TAIL: " << token_string << endl; //###
        while (next_token == TOKEN_TYPE::OP_MULTIPLY || next_token == TOKEN_TYPE::OP_DIVIDE) {
            addToken();
            TOKEN_TYPE op = next_token;
            lexical();
            string val = factor();
            if (ret.empty() || val.empty());
            else if (op == TOKEN_TYPE::OP_MULTIPLY) {
                ret = to_string(stoi(ret) * stoi(val));
            } else {
                ret = to_string(stoi(ret) / stoi(val));
            }
        }
        return ret;
    }

    string expression() {
cout << "   #EXPRESSION: " << token_string << endl; //###
        string ret = term();
cout << "   #TERM_TAIL: " << token_string << endl; //###
        while (next_token == TOKEN_TYPE::OP_PLUS || next_token == TOKEN_TYPE::OP_MINUS) {
            addToken();
            TOKEN_TYPE op = next_token;
            lexical();
            string val = term();
            if (ret.empty() || val.empty());
            else if (op == TOKEN_TYPE::OP_PLUS) {
                ret = to_string(stoi(ret) + stoi(val));
            } else {
                ret = to_string(stoi(ret) - stoi(val));
            }
        }
        return ret;
    }

    void statement() {
        _result = "(OK)";
        _tokens.clear();
        _ID = _CONST = _OP = 0;
cout << "\n#STATEMENT: " << token_string << endl; //###
        if (next_token == TOKEN_TYPE::END) {
            return;
        } else if (next_token == TOKEN_TYPE::IDENT) {
            addToken();
            string id = token_string;
            _ID = 1;
            _symTable[id] = ""; //new variable

            lexical();
            if (next_token == TOKEN_TYPE::OP_ASSIGN) {
                addToken();
                lexical();
            } else {
                msgError("missing assignment");
            }
            _symTable[id] = expression();
cout << "--- " << id << "(" << _symTable[id] << ")\n"; //###
        } else {
            msgError("missing identifier");
        }

        printStatement();
    }

    void statements() {
        while (isspace(_ch = fgetc(_fp)));
        do {
            lexical();
            statement();
        } while (next_token == TOKEN_TYPE::SEMICOLON);
    }

    void lexical() {
        token_string.clear();
        if (isdigit(_ch)) {
            while (isdigit(_ch)) {
                token_string.push_back(_ch);
                getChar();
            }
            next_token = TOKEN_TYPE::CONST;
            _CONST++;
        } else if (isalpha(_ch)) {
            while (isalpha(_ch) || isdigit(_ch)) {
                token_string.push_back(_ch);
                getChar();
            }
            next_token = TOKEN_TYPE::IDENT;
            _ID++;
        } else if (isOperator(_ch)) {
            token_string.push_back(_ch);
            next_token = (TOKEN_TYPE)_ch;
            getChar();
            _OP++;
        } else if (isSpecial(_ch)) {
            char prev = _ch;
            token_string.push_back(_ch);
            next_token = (TOKEN_TYPE)_ch;
            getChar();

            if (prev == ':' && _ch == '=') {
                token_string.push_back(_ch);
                next_token = TOKEN_TYPE::OP_ASSIGN;
                getChar();
            }
        } else if (_ch == EOF) {
            next_token = TOKEN_TYPE::END;
        } else {
printf("WARNING: CH %d(%c)\n", _ch, _ch); //###
            next_token = TOKEN_TYPE::NONE;
            getChar();
        }
        while (isspace(_ch)) getChar(); //remove tailing space
    }
};

int main(int argc, char *argv[])
{
    if (argc != 2) {
        cout << "usage: " << argv[0] << "<input.txt>\n";
        return -1;
    }

    RDP rdp(argv[1]);
    rdp.parse();

	return 0;
}

/**
TODO
    operand 시작 시 연산자가 오는 경우
    operand := 3; -> operand :+ 3
                  -> operand := + 3 + 3

**/
