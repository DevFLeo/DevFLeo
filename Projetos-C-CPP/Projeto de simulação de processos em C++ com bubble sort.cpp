#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <iomanip>  
#include <algorithm>

using namespace std;

// Função para limpar a tela (compatível com Windows e Unix)
void limparTela() {
    #ifdef _WIN32
        system("cls");  // Limpa a tela no Windows
    #else
        system("clear");  // Limpa a tela no Unix (Linux/Mac)
    #endif
}

// Estrutura de um aluno
struct Aluno {
    int matricula;
    string nome;
    string curso;
};

// Exibe os detalhes de um aluno específico
void exibirAluno(const Aluno& a) {
    limparTela();
    cout << "Matrícula: " << a.matricula << endl;
    cout << "Nome: " << a.nome << endl;
    cout << "Curso: " << a.curso << endl;
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Busca um aluno pela matrícula e retorna o índice no vetor
int buscarAluno(const vector<Aluno>& alunos, int matriculaBusca) {
    for (int i = 0; i < alunos.size(); i++) {
        if (alunos[i].matricula == matriculaBusca) {
            return i;  // Retorna o índice do aluno encontrado
        }
    }
    return -1;  // Retorna -1 se o aluno não foi encontrado
}

// Adiciona um novo aluno ao vetor
void adicionarAluno(vector<Aluno>& alunos) {
    limparTela();
    Aluno novoAluno;
    cout << "Digite o número da matrícula: ";
    cin >> novoAluno.matricula;
    cout << "Digite o nome do aluno: ";
    cin.ignore();  // Limpa o buffer para evitar problemas no getline
    getline(cin, novoAluno.nome);
    cout << "Digite o curso: ";
    getline(cin, novoAluno.curso);
    alunos.push_back(novoAluno);  // Adiciona o novo aluno ao vetor
    cout << "Aluno adicionado com sucesso!" << endl;
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Remove um aluno pela matrícula
void removerAluno(vector<Aluno>& alunos, int matricula) {
    limparTela();
    int indice = buscarAluno(alunos, matricula);  // Busca o índice do aluno
    if (indice != -1) {
        alunos.erase(alunos.begin() + indice);  // Remove o aluno do vetor
        cout << "Aluno removido com sucesso!" << endl;
    } else {
        cout << "Aluno com matrícula " << matricula << " não encontrado." << endl;
    }
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Exibe todos os alunos em uma tabela formatada
void exibirTabelaAlunos(const vector<Aluno>& alunos) {
    limparTela();
    cout << left << setw(15) << "Matrícula" 
         << setw(25) << "Nome" 
         << setw(20) << "Curso" << endl;
    cout << string(60, '-') << endl;
    for (const auto& aluno : alunos) {
        cout << setw(15) << aluno.matricula 
             << setw(25) << aluno.nome 
             << setw(20) << aluno.curso << endl;
    }
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Ordena os alunos usando Bubble Sort pela matrícula
void bubbleSortAlunos(vector<Aluno>& alunos) {
    for (int i = 0; i < alunos.size() - 1; i++) {
        bool swapped = false;  // Variável para verificar se houve troca
        for (int j = 0; j < alunos.size() - i - 1; j++) {
            if (alunos[j].matricula > alunos[j + 1].matricula) {
                swap(alunos[j], alunos[j + 1]);  // Troca se a matrícula for maior
                swapped = true;  // Marca que houve troca
            }
        }
        if (!swapped) break;  // Sai do loop se não houver trocas (vetor já ordenado)
    }
    cout << "Alunos ordenados com sucesso usando Bubble Sort!" << endl;
    cout << "\nPressione Enter para continuar...";
    cin.ignore();
    cin.get();
}

// Salva dados dos alunos em um arquivo de texto
void salvarAlunos(const vector<Aluno>& alunos) {
    ofstream arquivo("alunos.txt");
    if (arquivo.is_open()) {
        for (const auto& aluno : alunos) {
            arquivo << aluno.matricula << endl;
            arquivo << aluno.nome << endl;
            arquivo << aluno.curso << endl;
        }
        arquivo.close();
        cout << "Dados salvos com sucesso!" << endl;
    } else {
        cout << "Erro ao abrir o arquivo para salvar os dados!" << endl;
    }
}

// Função auxiliar para particionar o vetor no Quick Select de acordo com a prioridade
int partition(vector<Aluno>& alunos, int low, int high, const string& prioridade) {
    Aluno pivot = alunos[high];
    int i = low - 1;

    for (int j = low; j < high; j++) {
        bool condition;
        if (prioridade == "nome") {
            condition = alunos[j].nome < pivot.nome;
        } else if (prioridade == "curso") {
            condition = alunos[j].curso < pivot.curso;
        } else {  // "matricula" como padrão
            condition = alunos[j].matricula < pivot.matricula;
        }

        if (condition) {
            i++;
            swap(alunos[i], alunos[j]);
        }
    }
    swap(alunos[i + 1], alunos[high]);
    return i + 1;  // Retorna a posição final do pivô
}

// Função Quick Select customizada para ordenar de acordo com a prioridade
void quickSelect(vector<Aluno>& alunos, int low, int high, const string& prioridade) {
    if (low < high) {
        int pi = partition(alunos, low, high, prioridade);

        // Ordena recursivamente à esquerda e à direita do pivô
        quickSelect(alunos, low, pi - 1, prioridade);
        quickSelect(alunos, pi + 1, high, prioridade);
    }
}

// Função para ordenar e exibir alunos de acordo com a prioridade escolhida
void ordenarEExibirAlunos(vector<Aluno>& alunos) {
    limparTela();  
    int opcao;
    string prioridade;

    // Menu de seleção de prioridade de ordenação
    cout << "Escolha a prioridade de ordenação:\n";
    cout << "1. Matrícula\n";
    cout << "2. Nome\n";
    cout << "3. Curso\n";
    cout << "Digite a opção desejada: ";
    cin >> opcao;

    // Define a prioridade com base na escolha
    switch(opcao) {
        case 1:
            prioridade = "matricula";
            break;
        case 2:
            prioridade = "nome";
            break;
        case 3:
            prioridade = "curso";
            break;
        default:
            cout << "Opção inválida. Ordenando por matrícula." << endl;
            prioridade = "matricula";
    }

    // Ordena e exibe os alunos
    quickSelect(alunos, 0, alunos.size() - 1, prioridade);
    exibirTabelaAlunos(alunos);
}

// Carrega os alunos de um arquivo para o vetor
void carregarAlunos(vector<Aluno>& alunos) {
    ifstream arquivo("alunos.txt");
    if (arquivo.is_open()) {
        Aluno aluno;
        while (arquivo >> aluno.matricula) {
            arquivo.ignore();  // Ignora o newline após a matrícula
            getline(arquivo, aluno.nome);
            getline(arquivo, aluno.curso);
            alunos.push_back(aluno);  // Adiciona o aluno ao vetor
        }
        arquivo.close();
        cout << "Dados carregados com sucesso!" << endl;
    } else {
        cout << "Nenhum dado encontrado para carregar." << endl;
    }
}

// Função principal para o menu do sistema
int main() {
    vector<Aluno> alunos;
    carregarAlunos(alunos);  // Carrega alunos do arquivo no início

    int opcao;
    do {
        limparTela();  // Limpa a tela antes de exibir o menu
        cout << "\nMenu de Gerenciamento Acadêmico:\n";
        cout << "1. Adicionar Aluno\n";
        cout << "2. Buscar Aluno\n";
        cout << "3. Remover Aluno\n";
        cout << "4. Exibir Todos os Alunos\n";
        cout << "5. Ordenar e Exibir Alunos por Quick Select\n";
        cout << "6. Ordenar Alunos pelo Bubble Sort\n";
        cout << "7. Sair\n";
        cout << "Escolha uma opção: ";
        cin >> opcao;

        // Executa a opção escolhida pelo usuário
        switch(opcao) {
            case 1:
                adicionarAluno(alunos);
                break;
            case 2: {
                int matriculaBusca;
                cout << "Digite a matrícula do aluno que deseja buscar: ";
                cin >> matriculaBusca;
                int indice = buscarAluno(alunos, matriculaBusca);
                if (indice != -1) {
                    exibirAluno(alunos[indice]);
                } else {
                    cout << "Aluno com matrícula " << matriculaBusca << " não encontrado." << endl;
                    cout << "\nPressione Enter para continuar...";
                    cin.ignore();
                    cin.get();
                }
                break;
            }
            case 3: {
                int matriculaRemove;
                cout << "Digite a matrícula do aluno que deseja remover: ";
                cin >> matriculaRemove;
                removerAluno(alunos, matriculaRemove);
                break;
            }
            case 4:
                exibirTabelaAlunos(alunos);
                break;
            case 5:
                ordenarEExibirAlunos(alunos);
                break;
            case 6:
                bubbleSortAlunos(alunos);
                exibirTabelaAlunos(alunos);
                break;
            case 7:
                salvarAlunos(alunos);
                cout << "Saindo do sistema..." << endl;
                break;
            default:
                cout << "Opção inválida. Tente novamente." << endl;
                cout << "\nPressione Enter para continuar...";
                cin.ignore();
                cin.get();
        }
    } while (opcao != 7);

    return 0;
}
