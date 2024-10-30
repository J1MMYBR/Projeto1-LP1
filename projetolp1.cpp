#include <iostream>
#include <string>
using namespace std;

class Cliente {
private:
    string nome;  
    string cpf;     // Variaveis da classe

public:
    // Construtor que inicializa nome e cpf
    Cliente(string nome, string cpf) : nome(nome), cpf(cpf) {}

    
    string getNome() const {    // Getter para obter o nome do cliente
        return nome;
    }

    string getCpf() const {     // Getter para obter o cpf
        return cpf;
    }
};

class ContaBancaria {
private:
    int numero;         
    double saldo;       
    Cliente titular;    // Variaveis da classe

public:
    // Construtor que inicializa o numero da conta, o cliente titular e o saldo inicial, padrao 0
    ContaBancaria(int numero, Cliente titular, double saldo = 0.0) 
        : numero(numero), titular(titular), saldo(saldo) {}

    // Metodo para depositar um valor na conta
    void depositar(double valor) {
        if (valor > 0) {     // Verifica se o valor a depositar é positivo
            saldo += valor;  // Adiciona o valor ao saldo da conta
            cout << "Depositado: R$ " << valor << " na conta " << numero << endl;
        } else {
            cout << "Valor de depósito inválido!" << endl;
        }
    }

    // Metodo para sacar um valor da conta
    void sacar(double valor) {
        if (valor > 0 && saldo >= valor) {  // Verifica se o valor eh positivo e se ha saldo suficiente para o saque
            saldo -= valor;  // Retira o valor do saldo
            cout << "Sacado: R$ " << valor << " da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente ou valor inválido!" << endl;
        }
    }

    // Sobrecarga do metodo transferir - Transfere um valor para uma única conta de destino
    void transferir(double valor, ContaBancaria &destino) {   
        if (valor > 0 && saldo >= valor) {  // Verifica se o valor eh positivo e se ha saldo suficiente para a transferencia
            saldo -= valor;         // Retira o valor do saldo da conta que vai transferir
            destino.depositar(valor); // Deposita o valor na conta de destino
            cout << "Transferido: R$ " << valor << " da conta " << numero << " para a conta " << destino.numero << endl;
        } else {
            cout << "Saldo insuficiente ou valor inválido para transferência!" << endl;
        }
    }

    // Sobrecarga do metodo transferir - Transfere um valor dividido entre duas contas de destino
    void transferir(double valor, ContaBancaria &destino1, ContaBancaria &destino2) {
        double metade = valor / 2;  // Divide o valor igualmente para as duas contas de destino
        if (valor > 0 && saldo >= valor) {  // Verifica se o valor eh positivo e se ha saldo suficiente para a transferencia
            saldo -= valor;            // Retira o valor total do saldo da conta que vai transferir
            destino1.depositar(metade); // Deposita metade do valor na primeira conta de destino
            destino2.depositar(metade); // Deposita metade do valor na segunda conta
            cout << "Transferido: R$ " << metade << " para cada conta (" << destino1.numero << " e " << destino2.numero << ") da conta " << numero << endl;
        } else {
            cout << "Saldo insuficiente ou valor inválido para transferência!" << endl;
        }
    }

    // Metodo para exibir o saldo da conta
    void exibirSaldo() const {
        cout << "Saldo atual da conta " << numero << ": R$ " << saldo << endl;
    }

    // Metodo para exibir informações do titular e da conta
    void exibirInformacoes() const {
        cout << "Titular: " << titular.getNome() << ", CPF: " << titular.getCpf() << endl;
        cout << "Número da Conta: " << numero << ", Saldo: R$ " << saldo << endl;
    }
};

int main() {
    // Criacao dos clientes
    Cliente cliente1("Ana", "111.111.111-11");
    Cliente cliente2("Bruno", "222.222.222-22");
    Cliente cliente3("Carla", "333.333.333-33");

    // Criacao das contas bancarias associadas a cada cliente, apenas um com saldo definido, o resto eh 0
    ContaBancaria conta1(1001, cliente1, 1000.0);  
    ContaBancaria conta2(1002, cliente2);          
    ContaBancaria conta3(1003, cliente3);       

    // Exibe o saldo inicial da conta de Ana
    conta1.exibirSaldo();

    // Realiza uma transferencia de 200 reais da conta de Ana para a conta de Bruno
    conta1.transferir(200.0, conta2);

    // Realiza uma transferencia de 300 reais da conta de Ana para as contas de Bruno e Carla, dividindo o valor
    conta1.transferir(300.0, conta2, conta3);

    // Exibe as informacoes e os saldos finais das 3 contas
    cout << endl;
    conta1.exibirInformacoes();
    conta2.exibirInformacoes();
    conta3.exibirInformacoes();

    return 0;
}
