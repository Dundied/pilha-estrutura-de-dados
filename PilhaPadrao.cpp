#include <iostream>
#include <stack> //biblioteca de Pilha
#include <string>
#include "Pilha.h"

using namespace std;

// Função para verificar se é um operador
bool éoperador(char c) {
    return (c == '+' or c == '-' or c == '*' or c == '/');
}

// Função para retornar o significado do operador em inteiro
int significado(char op) {
    if (op == '+' or op == '-')
        return 1;
    if (op == '*' or op == '/')
        return 2;
    return 0;
}

// Função para converter expressão para NPR
string conversao_NPR(string exp) {
    string postfix = "";
    stack<char> s;
    for (char& c : exp) { //ponteiro para a variável da função "éoperador"
        if (c == ' ')
            continue;
        else if (isdigit(c)) {// verifica se é valor numério
            postfix += c;
            postfix += ' '; 
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                postfix += ' '; 
                s.pop();
            }
            if (!s.empty() && s.top() == '(')
                s.pop();
        } else {
            while (!s.empty() && significado(s.top()) >= significado(c)) {
                postfix += s.top();
                postfix += ' '; 
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        postfix += ' '; 
        s.pop();
    }
    return postfix;
}

// Função que calcula a expressão
float calculo_NPR(string exp) {
    Pilha* p = criarPilha(); // cria a pilha
    for (char& c : exp) {
        if (c == ' ')
            continue;
        else if (isdigit(c)) { // verifica se é valor numério
            push(p, c - '0'); // adiciona o valor na pilha
        } else if (éoperador(c)) { // verifica se a pilha é válida
            if (p->n < 2) {
                cout << "Expressao estava errada" << endl;
                liberarPilha(p);
                return 0;
            }
            float op2 = pop(p);
            float op1 = pop(p);
            switch (c) {
                case '+':
                    push(p, op1 + op2);
                    break;
                case '-':
                    push(p, op1 - op2);
                    break;
                case '*':
                    push(p, op1 * op2);
                    break;
                case '/':
                    push(p, op1 / op2);
                    break;
            }
        }
    }
    if (p->n != 1) {
        cout << "Expressao estava errada" << endl;
        liberarPilha(p);
        return 0;
    }
    float result = pop(p);
    liberarPilha(p);
    return result;
}

//main
int main() {
    string exp;
    cout << "Digite a expressao matematica: ";
    getline(cin, exp);

    string postfixExp = conversao_NPR(exp);
    cout << "NPR: " << postfixExp << endl;

    float result = calculo_NPR(postfixExp);
    if (result != 0)
        cout << "Resultado: " << result << endl;

    return 0;
}
