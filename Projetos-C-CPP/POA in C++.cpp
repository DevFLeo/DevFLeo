// Adicionar o modulo de limpeza de chat, adicionar o case , uma simulação de banco de dados e separar o codigo por modulos.

#include <iostream>
#include <fstream> // Para arquivos
#include <string>
#include <vector>
#include <memory>

class Conta {
protected:
    std::string numeroConta;
    double saldo;

public:
    Conta(std::string numeroConta, double saldoInicial)
        : numeroConta(numeroConta), saldo(saldoInicial) {}

    virtual bool sacar(double valor) = 0; // Método abstrato

    double getSaldo() const { return saldo; }
    std::string getNumeroConta() const { return numeroConta; }

    virtual std::string getTipo() const = 0; // Para saber o tipo da conta ao salvar
    virtual void salvar(std::ofstream& arquivo) const = 0; // Salvar no arquivo

    virtual ~Conta() {}
};

// Conta Corrente
class ContaCorrente : public Conta {
public:
    ContaCorrente(std::string numeroConta, double saldoInicial)
        : Conta(numeroConta, saldoInicial) {}

    bool sacar(double valor) override {
        if (saldo >= valor) {
            saldo -= valor;
            std::cout << "Saque de " << valor << " realizado com sucesso na Conta Corrente.\n";
            return true;
        }
        return false;
    }

    std::string getTipo() const override { return "Corrente"; }
    void salvar(std::ofstream& arquivo) const override {
        arquivo << getTipo() << " " << numeroConta << " " << saldo << "\n";
    }
};

// Conta Poupança
class ContaPoupanca : public Conta {
public:
    ContaPoupanca(std::string numeroConta, double saldoInicial)
        : Conta(numeroConta, saldoInicial) {}

    bool sacar(double valor) override {
        if (saldo >= valor) {
            saldo -= valor;
            std::cout << "Saque de " << valor << " realizado com sucesso na Conta Poupança.\n";
            return true;
        }
        return false;
    }

    std::string getTipo() const override { return "Poupanca"; }
    void salvar(std::ofstream& arquivo) const override {
        arquivo << getTipo() << " " << numeroConta << " " << saldo << "\n";
    }
};

// Conta Investimento
class ContaInvestimento : public Conta {
private:
    double taxaSaque;

public:
    ContaInvestimento(std::string numeroConta, double saldoInicial, double taxa)
        : Conta(numeroConta, saldoInicial), taxaSaque(taxa) {}

    bool sacar(double valor) override {
        double valorTotal = valor + (valor * taxaSaque);
        if (saldo >= valorTotal) {
            saldo -= valorTotal;
            std::cout << "Saque de " << valor << " realizado na Conta Investimento.\n";
            std::cout << "Taxa aplicada: " << (valor * taxaSaque) << "\n";
            return true;
        }
        return false;
    }

    std::string getTipo() const override { return "Investimento"; }
    void salvar(std::ofstream& arquivo) const override {
        arquivo << getTipo() << " " << numeroConta << " " << saldo << " " << taxaSaque << "\n";
    }
};

// Proxy para interceptar operações
class ContaProxy {
private:
    std::shared_ptr<Conta> conta;

public:
    ContaProxy(std::shared_ptr<Conta> conta) : conta(conta) {}

    bool sacar(double valor) {
        std::cout << "[LOG] Tentando sacar " << valor << " da conta " << conta->getNumeroConta() << "\n";

        if (!conta->sacar(valor)) {
            std::cout << "[ERRO] Saldo insuficiente na conta " << conta->getNumeroConta() << "\n";
            return false;
        }
        return true;
    }

    std::shared_ptr<Conta> getConta() { return conta; }
};

// Função para salvar todas as contas em um arquivo
void salvarContas(const std::vector<std::shared_ptr<Conta>>& contas) {
    std::ofstream arquivo("contas.txt");
    if (!arquivo) {
        std::cerr << "[ERRO] Não foi possível abrir o arquivo para salvar!\n";
        return;
    }

    for (const auto& conta : contas) {
        conta->salvar(arquivo);
    }

    std::cout << "[INFO] Contas salvas com sucesso!\n";
}

// Função para carregar contas do arquivo
std::vector<std::shared_ptr<Conta>> carregarContas() {
    std::vector<std::shared_ptr<Conta>> contas;
    std::ifstream arquivo("contas.txt");

    if (!arquivo) {
        std::cout << "[INFO] Nenhum arquivo encontrado. Criando novo banco de contas.\n";
        return contas;
    }

    std::string tipo, numeroConta;
    double saldo, taxa;

    while (arquivo >> tipo >> numeroConta >> saldo) {
        if (tipo == "Corrente") {
            contas.push_back(std::make_shared<ContaCorrente>(numeroConta, saldo));
        } else if (tipo == "Poupanca") {
            contas.push_back(std::make_shared<ContaPoupanca>(numeroConta, saldo));
        } else if (tipo == "Investimento") {
            arquivo >> taxa;
            contas.push_back(std::make_shared<ContaInvestimento>(numeroConta, saldo, taxa));
        }
    }

    std::cout << "[INFO] Contas carregadas com sucesso!\n";
    return contas;
}

// Função para exibir todas as contas
void listarContas(const std::vector<std::shared_ptr<Conta>>& contas) {
    std::cout << "=== Contas no Sistema ===\n";
    for (const auto& conta : contas) {
        std::cout << "Tipo: " << conta->getTipo() << ", Número: " << conta->getNumeroConta()
                  << ", Saldo: " << conta->getSaldo() << "\n";
    }
}

int main() {
    std::vector<std::shared_ptr<Conta>> contas = carregarContas();

    // Criando contas dinamicamente
    contas.push_back(std::make_shared<ContaCorrente>("123", 500));
    contas.push_back(std::make_shared<ContaPoupanca>("456", 300));
    contas.push_back(std::make_shared<ContaInvestimento>("789", 1000, 0.02));

    // Criando proxies
    ContaProxy conta1(contas[0]);
    ContaProxy conta2(contas[1]);
    ContaProxy conta3(contas[2]);

    conta1.sacar(600);
    conta2.sacar(100);
    conta3.sacar(200);

    // Listando contas após operações
    listarContas(contas);

    // Salvando contas no arquivo
    salvarContas(contas);

    return 0;
}

