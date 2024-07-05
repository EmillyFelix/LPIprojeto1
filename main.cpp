#include <iostream>
#include <fstream>
#include "astronautas.h"

using namespace std;

void inicializarArquivos() {
    ifstream fileAstronautas("astronautas.txt");
    if (!fileAstronautas) {
        ofstream outfile("astronautas.txt");
        outfile.close();
    } else {
        fileAstronautas.close();
    }

    ifstream fileVoos("voos.txt");
    if (!fileVoos) {
        ofstream outfile("voos.txt");
        outfile.close();
    } else {
        fileVoos.close();
    }
}

void cadastrarAstronauta(vector<Astronauta>& astronautas) {
    string cpf, nome;
    int idade;
    cout << "CPF: ";
    cin >> cpf;
    cout << "Nome: ";
    cin.ignore();
    getline(cin, nome);
    cout << "Idade: ";
    cin >> idade;
    Astronauta a(cpf, nome, idade);
    astronautas.push_back(a);
    Astronauta::salvarTodos(astronautas);
}

void cadastrarVoo(vector<Voo>& voos) {
    int codigo;
    cout << "Código do voo: ";
    cin >> codigo;
    Voo v(codigo);
    voos.push_back(v);
    Voo::salvarTodos(voos);
}

void adicionarAstronautaEmVoo(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    string cpf;
    int codigo;
    cout << "CPF do astronauta: ";
    cin >> cpf;
    cout << "Código do voo: ";
    cin >> codigo;

    for (auto& voo : voos) {
        if (voo.codigo == codigo && !voo.emCurso) {
            for (auto& astronauta : astronautas) {
                if (astronauta.cpf == cpf && astronauta.disponivel) {
                    voo.adicionarPassageiro(astronauta);
                    Voo::salvarTodos(voos);
                    Astronauta::salvarTodos(astronautas);
                    return;
                }
            }
        }
    }
    cout << "Falha ao adicionar astronauta no voo.\n";
}

void removerAstronautaDeVoo(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    string cpf;
    int codigo;
    cout << "CPF do astronauta: ";
    cin >> cpf;
    cout << "Código do voo: ";
    cin >> codigo;

    for (auto& voo : voos) {
        if (voo.codigo == codigo && !voo.emCurso) {
            voo.removerPassageiro(cpf);
            Voo::salvarTodos(voos);
            Astronauta::salvarTodos(astronautas);
            return;
        }
    }
    cout << "Falha ao remover astronauta do voo.\n";
}

void lancarVoo(vector<Voo>& voos) {
    int codigo;
    cout << "Código do voo: ";
    cin >> codigo;

    for (auto& voo : voos) {
        if (voo.codigo == codigo && !voo.emCurso && voo.passageiros.size() > 0) {
            voo.lancar();
            Voo::salvarTodos(voos);
            return;
        }
    }
    cout << "Falha ao lançar voo.\n";
}

void explodirVoo(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    int codigo;
    cout << "Código do voo: ";
    cin >> codigo;

    for (auto& voo : voos) {
        if (voo.codigo == codigo && voo.emCurso) {
            voo.explodir();
            Voo::salvarTodos(voos);
            Astronauta::salvarTodos(astronautas);
            return;
        }
    }
    cout << "Falha ao explodir voo.\n";
}

void finalizarVoo(vector<Astronauta>& astronautas, vector<Voo>& voos) {
    int codigo;
    bool sucesso;
    cout << "Código do voo: ";
    cin >> codigo;
    cout << "Foi bem-sucedido? (1 para sim, 0 para não): ";
    cin >> sucesso;

    for (auto& voo : voos) {
        if (voo.codigo == codigo && voo.emCurso) {
            voo.finalizar(sucesso);
            Voo::salvarTodos(voos);
            Astronauta::salvarTodos(astronautas);
            return;
        }
    }
    cout << "Falha ao finalizar voo.\n";
}

void listarVoos(vector<Voo>& voos) {
    cout << "Voos planejados:\n";
    for (auto& voo : voos) {
        if (!voo.emCurso && !voo.finalizado) {
            cout << "Voo " << voo.codigo << " com passageiros:\n";
            for (auto& p : voo.passageiros) {
                cout << p.cpf << " " << p.nome << endl;
            }
        }
    }

    cout << "Voos em curso:\n";
    for (auto& voo : voos) {
        if (voo.emCurso) {
            cout << "Voo " << voo.codigo << " com passageiros:\n";
            for (auto& p : voo.passageiros) {
                cout << p.cpf << " " << p.nome << endl;
            }
        }
    }

    cout << "Voos finalizados:\n";
    for (auto& voo : voos) {
        if (voo.finalizado) {
            cout << "Voo " << voo.codigo << (voo.sucesso ? " foi bem-sucedido" : "não foi bem-sucedido") << " com passageiros:\n";
            for (auto& p : voo.passageiros) {
                cout << p.cpf << " " << p.nome << endl;
            }
        }
    }
}

void listarAstronautasMortos(vector<Astronauta>& astronautas) {
    cout << "Astronautas mortos:\n";
    for (auto& astronauta : astronautas) {
        if (astronauta.morto) {
            cout << astronauta.cpf << " " << astronauta.nome << " participou dos voos:\n";
            // Aqui deveríamos listar os voos em que o astronauta participou
        }
    }
}

int main() {
    inicializarArquivos();

    vector<Astronauta> astronautas = Astronauta::carregarTodos();
    vector<Voo> voos = Voo::carregarTodos();

    int opcao;
    do {
        cout << "1. Cadastrar Astronauta\n";
        cout << "2. Cadastrar Voo\n";
        cout << "3. Adicionar Astronauta em Voo\n";
        cout << "4. Remover Astronauta de Voo\n";
        cout << "5. Lançar Voo\n";
        cout << "6. Explodir Voo\n";
        cout << "7. Finalizar Voo\n";
        cout << "8. Listar Voos\n";
        cout << "9. Listar Astronautas Mortos\n";
        cout << "0. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        switch (opcao) {
        case 1:
            cadastrarAstronauta(astronautas);
            break;
        case 2:
            cadastrarVoo(voos);
            break;
        case 3:
            adicionarAstronautaEmVoo(astronautas, voos);
            break;
        case 4:
            removerAstronautaDeVoo(astronautas, voos);
            break;
        case 5:
            lancarVoo(voos);
            break;
        case 6:
            explodirVoo(astronautas, voos);
            break;
        case 7:
            finalizarVoo(astronautas, voos);
            break;
        case 8:
            listarVoos(voos);
            break;
        case 9:
            listarAstronautasMortos(astronautas);
            break;
        case 0:
            cout << "Saindo...\n";
            break;
        default:
            cout << "Opção inválida.\n";
        }
    } while (opcao != 0);

    return 0;
}
