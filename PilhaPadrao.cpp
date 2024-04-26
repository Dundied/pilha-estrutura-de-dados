#include <iostream>
#include <string>
#include "Pilha.h"

using namespace std;

// Função para verificar se é um operador
bool e_operador(char c) {
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
    Pilha* s = criarPilha(); // Pilha usando a lógica definida em Pilha.h
    for (char& c : exp) {
        if (c == ' ')
            continue;
        else if (isdigit(c)) { // verifica se é valor numérico
            postfix += c;
            postfix += ' '; 
        } else if (c == '(') {
            push(s, c);
        } else if (c == ')') {
            while (!estaVazia(s) && verTopo(s) != '(') {
                postfix += pop(s);
                postfix += ' '; 
            }
            if (!estaVazia(s) && verTopo(s) == '(')
                pop(s);
        } else {
            while (!estaVazia(s) && significado(verTopo(s)) >= significado(c)) {
                postfix += pop(s);
                postfix += ' '; 
            }
            push(s, c);
        }
    }
    while (!estaVazia(s)) {
        postfix += pop(s);
        postfix += ' '; 
    }
    liberarPilha(s); // Liberar a pilha alocada
    return postfix;
}

// Função que calcula a expressão
float calculo_NPR(string exp) {
    Pilha* p = criarPilha(); // cria a pilha
    for (char& c : exp) {
        if (c == ' ')
            continue;
        else if (isdigit(c)) { // verifica se é valor numérico
            push(p, c - '0'); // adiciona o valor na pilha
        } else if (e_operador(c)) { // verifica se é operador
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
    cout << "expressao em NPR: " << postfixExp << endl;

    float result = calculo_NPR(postfixExp);
    if (result != 0)
        cout << "Resultado: " << result << endl;

    return 0;
}
