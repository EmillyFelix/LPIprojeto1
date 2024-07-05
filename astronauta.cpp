#include "astronautas.h"

// Constructor for Astronauta
Astronauta::Astronauta(std::string cpf, std::string nome, int idade)
    : cpf(cpf), nome(nome), idade(idade), disponivel(true), morto(false) {}

// Save astronaut to file
void Astronauta::salvar(std::ofstream& file) {
    file << cpf << " " << nome << " " << idade << " " << disponivel << " " << morto << std::endl;
}

// Load astronaut from file
void Astronauta::carregar(std::ifstream& file) {
    file >> cpf >> nome >> idade >> disponivel >> morto;
}

// Save all astronauts to file
void Astronauta::salvarTodos(std::vector<Astronauta>& astronautas) {
    std::ofstream file("astronautas.txt");
    for (auto& astronauta : astronautas) {
        astronauta.salvar(file);
    }
    file.close();
}

// Load all astronauts from file
std::vector<Astronauta> Astronauta::carregarTodos() {
    std::vector<Astronauta> astronautas;
    std::ifstream file("astronautas.txt");
    while (!file.eof()) {
        Astronauta a("", "", 0);
        a.carregar(file);
        if (a.cpf != "")
            astronautas.push_back(a);
    }
    file.close();
    return astronautas;
}

// Constructor for Voo
Voo::Voo(int codigo) : codigo(codigo), emCurso(false), finalizado(false), sucesso(false) {}

// Add passenger to flight
void Voo::adicionarPassageiro(Astronauta& astronauta) {
    if (astronauta.disponivel) {
        passageiros.push_back(astronauta);
        astronauta.disponivel = false;
    }
}

// Remove passenger from flight
void Voo::removerPassageiro(std::string cpf) {
    for (auto it = passageiros.begin(); it != passageiros.end(); ++it) {
        if (it->cpf == cpf) {
            it->disponivel = true;
            passageiros.erase(it);
            break;
        }
    }
}

// Launch flight
void Voo::lancar() {
    if (passageiros.size() > 0) {
        emCurso = true;
        for (auto& p : passageiros) {
            p.disponivel = false;
        }
    }
}

// Explode flight
void Voo::explodir() {
    finalizado = true;
    sucesso = false;
    for (auto& p : passageiros) {
        p.morto = true;
    }
}

// Finalize flight
void Voo::finalizar(bool sucesso) {
    finalizado = true;
    emCurso = false;
    this->sucesso = sucesso;
    for (auto& p : passageiros) {
        p.disponivel = true;
    }
}

// Save flight to file
void Voo::salvar(std::ofstream& file) {
    file << codigo << " " << emCurso << " " << finalizado << " " << sucesso << std::endl;
    for (auto& p : passageiros) {
        file << p.cpf << std::endl;
    }
    file << "END" << std::endl;
}

// Load flight from file
void Voo::carregar(std::ifstream& file) {
    file >> codigo >> emCurso >> finalizado >> sucesso;
    std::string cpf;
    while (file >> cpf && cpf != "END") {
        Astronauta a("", "", 0);
        a.cpf = cpf;
        passageiros.push_back(a);
    }
}

// Save all flights to file
void Voo::salvarTodos(std::vector<Voo>& voos) {
    std::ofstream file("voos.txt");
    for (auto& voo : voos) {
        voo.salvar(file);
    }
    file.close();
}

// Load all flights from file
std::vector<Voo> Voo::carregarTodos() {
    std::vector<Voo> voos;
    std::ifstream file("voos.txt");
    while (!file.eof()) {
        Voo v(0);
        v.carregar(file);
        if (v.codigo != 0)
            voos.push_back(v);
    }
    file.close();
    return voos;
}
