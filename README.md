Descrição
Sistema em C++ para gestão de astronautas e voos espaciais, permitindo cadastro, lançamento, explosão e finalização de voos, além de listar voos e astronautas mortos.

Funcionalidades
- Cadastrar astronauta e voo
- Adicionar/remover astronauta de um voo
- Lançar, explodir e finalizar voos
- Listar voos (planejados, em curso, finalizados)
- Listar astronautas mortos

Estrutura do Projeto
- astronautas.h: Declaração das classes Astronauta e Voo
- astronauta.cpp: Implementação das funções das classes
- main.cpp: Interface do usuário e lógica principal

Foi utilizado o: vsCode, é necessário configurar tasks.json no VS Code

Criar .vscode/tasks.json com o seguinte conteúdo:
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "build",
            "type": "shell",
            "command": "g++",
            "args": [
                "-Wall",
                "-Wextra",
                "-g3",
                "main.cpp",
                "astronauta.cpp",
                "-o",
                "output/main.exe"
            ],
            "group": {
                "kind": "build",
                "isDefault": true
            },
            "problemMatcher": ["$gcc"]
        }
    ]
}

Compilação e execução:
Compilar: Ctrl + Shift + B no VS Code
executar: cd output
          ./main.exe


