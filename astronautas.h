#ifndef ASTRONAUTAS_H
#define ASTRONAUTAS_H

#include <string>
#include <vector>
#include <iostream>
#include <fstream>

class Astronauta {
public:
    std::string cpf;
    std::string nome;
    int idade;
    bool disponivel;
    bool morto;

    Astronauta(std::string cpf, std::string nome, int idade);

    void salvar(std::ofstream& file);
    void carregar(std::ifstream& file);

    static void salvarTodos(std::vector<Astronauta>& astronautas);
    static std::vector<Astronauta> carregarTodos();
};

class Voo {
public:
    int codigo;
    std::vector<Astronauta> passageiros;
    bool emCurso;
    bool finalizado;
    bool sucesso;

    Voo(int codigo);

    void adicionarPassageiro(Astronauta& astronauta);
    void removerPassageiro(std::string cpf);
    void lancar();
    void explodir();
    void finalizar(bool sucesso);

    void salvar(std::ofstream& file);
    void carregar(std::ifstream& file);

    static void salvarTodos(std::vector<Voo>& voos);
    static std::vector<Voo> carregarTodos();
};

#endif // ASTRONAUTAS_H
