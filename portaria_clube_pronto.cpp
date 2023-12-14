#include <iostream>
#include <fstream>
#include <string>
#include <locale>

using namespace std;

// Estrutura para socios
struct Socio
{
    int numeroTitulo;
    string nomeTitular;
    string nomeDependente1;
    string nomeDependente2;
    bool mensalidadeEmDia;
    Socio *proximo;
};

// Lista de socios
Socio *listaSocios = NULL;

// Lista de registros de portaria
struct RegistroPortaria
{
    int numeroTitulo;
    string nomeSocio;
    bool operacaoEntrada = false;
    bool operacaoSaida = false; // 'E' para entrada, 'S' para saida
    RegistroPortaria *proximo;
};
// Lista de registro
RegistroPortaria *registrosPortaria = NULL;

// Protótipos das funcoes
void inserirSocio();
void listarSocios();
void removerSocio();
void carregarSocios();
void registrarEntradaSaida();
void gerarRelatorioVisitas();
void gerarRelatorioVisitasArquivo();
void liberarMemoria();

int main()
{
    setlocale(LC_ALL, "Portuguese");
    int escolha;

    do
    {
        cout << "-----------Menu---------" << endl;
        cout << "1. Carregar socios" << endl;
        cout << "2. Inserir socios" << endl;
        cout << "3. Listar socios" << endl;
        cout << "4. Remover socio" << endl;
        cout << "5. Registro de Entrada/saida" << endl;
        cout << "6. Gerar relatório de visitas" << endl;
        cout << "7. Gerar relatório de visitas em arquivo" << endl;
        cout << "0. Sair" << endl;
        cout << "Escolha uma opcao: ";
        cin >> escolha;

        switch (escolha)
        {
        case 1:
            carregarSocios();
            break;
        case 2:
            inserirSocio();
            break;
        case 3:
            listarSocios();
            break;
        case 4:
            removerSocio();
            break;
        case 5:
            registrarEntradaSaida();
            break;
        case 6:
            gerarRelatorioVisitas();
            break;
        case 7:
            gerarRelatorioVisitasArquivo();
            break;
        case 0:
            cout << "Saindo do programa. Ate mais!" << endl;
            break;
        default:
            cout << "Opcao inválida. Tente novamente." << endl;
        }
    } while (escolha != 0);

    liberarMemoria();

    return 0;
}

void inserirSocio()
{
    // Cria um novo objeto Socio
    Socio *novoSocio = new Socio;
    cout << "----- Inserindo sócio -----" << endl;
    cout << "Número do título: ";
    cin >> novoSocio->numeroTitulo;
    cout << "Nome do titular: ";
    cin >> novoSocio->nomeTitular;
    cout << "Nome do dependente 1: ";
    cin >> novoSocio->nomeDependente1;
    cout << "Nome do dependente 2: ";
    cin >> novoSocio->nomeDependente2;
    cout << "Mensalidade em dia (1 para sim, 0 para não): ";
    cin >> novoSocio->mensalidadeEmDia;
    // Adiciona o novo sócio no início da lista
    novoSocio->proximo = listaSocios;
    listaSocios = novoSocio;
}

void listarSocios()
{
    cout << "------ Lista de sócios ------" << endl;
    Socio *atualSocio = listaSocios;
    while (atualSocio != NULL)
    {
        // Imprime os detalhes do sócio
        cout << "Número do título: " << atualSocio->numeroTitulo << endl;
        cout << "Nome do titular: " << atualSocio->nomeTitular << endl;
        cout << "Nome do dependente 1: " << atualSocio->nomeDependente1 << endl;
        cout << "Nome do dependente 2: " << atualSocio->nomeDependente2 << endl;
        cout << "Mensalidade em dia: " << (atualSocio->mensalidadeEmDia ? "Sim" : "Não") << endl;
        cout << "--------------------------" << endl;
        atualSocio = atualSocio->proximo;
    }
}

void removerSocio()
{
    // Variável para armazenar o número do título do sócio a ser removido
    int numeroTitulo;
    cout << "----- Remover sócio -----" << endl;
    cout << "Digite o número do título do sócio a ser removido: ";
    cin >> numeroTitulo;
    // Ponteiros para navegar na lista de sócios
    Socio *anterior = NULL;
    Socio *atualSocio = listaSocios;
    // Percorre a lista de sócios
    while (atualSocio != NULL)
    {
        // Verifica se o sócio atual tem o número do título desejado
        if (atualSocio->numeroTitulo == numeroTitulo)
        {
            // Remove o sócio da lista
            if (anterior == NULL)
            {
                // O sócio a ser removido é o primeiro da lista
                listaSocios = atualSocio->proximo;
            }
            else
            {
                // O sócio a ser removido não é o primeiro, ajusta o ponteiro do anterior
                anterior->proximo = atualSocio->proximo;
            }

            // Libera a memória alocada para o sócio removido
            delete atualSocio;
            cout << "Sócio removido com sucesso." << endl;
            return;
        }

        // Atualiza os ponteiros para continuar percorrendo a lista
        anterior = atualSocio;            // apontar para o nó atual da lista
        atualSocio = atualSocio->proximo; // move o ponteiro para o próximo nó na lista, preparando-o para a próxima iteração do loop ou finalizando o loop se atingir o final da lista.
    }

    // Se o número do título não foi encontrado na lista
    cout << "Sócio não encontrado." << endl;
}

void carregarSocios()
{
    ifstream arquivo("socios.txt"); // ler o arquivo

    if (!arquivo)
    {
        // Exibe mensagem de erro se não conseguir abrir o arquivo
        cout << "Erro ao abrir o arquivo de sócios." << endl;
        return;
    }
    Socio socio;

    while (arquivo >> socio.numeroTitulo >> socio.nomeTitular >> socio.nomeDependente1 >> socio.nomeDependente2 >> socio.mensalidadeEmDia)
    {
        // Cria um novo objeto Socio e carrega os dados do arquivo
        Socio *novoSocio = new Socio;
        *novoSocio = socio;
        novoSocio->proximo = NULL;

        // Verifica se a lista está vazia
        if (listaSocios == NULL)
        {
            listaSocios = novoSocio; // esta linha atribui o ponteiro novoSocio à variável listaSocios. Isso significa que o primeiro nó da lista agora aponta para o novo sócio.
        }
        else
        {
            // Adiciona o novo sócio no final da lista
            Socio *ultimoSocio = listaSocios;    // inicializa com o ponteiro para o primeiro nó da lista
            while (ultimoSocio->proximo != NULL) //  ultimoSocio não for nulo. Isso significa que o loop percorrerá a lista até encontrar o último nó
            {
                ultimoSocio = ultimoSocio->proximo; // atualiza o ponteiro ultimoSocio para apontar para o próximo nó na lista
            }
            ultimoSocio->proximo = novoSocio; // adiciona o novo sócio como o último nó da lista.
        }
    }

    arquivo.close();

    cout << "Sócios carregados com sucesso." << endl;
}

void registrarEntradaSaida()
{
    int numeroTitulo;
    char operacao;
    
    cout << "Digite o numero da carteirinha: ";
    cin >> numeroTitulo;

    Socio *socioAtual = listaSocios;

    // Encontrar o sócio na lista de socios
    while (socioAtual != NULL && socioAtual->numeroTitulo != numeroTitulo)
    {
        socioAtual = socioAtual->proximo;
    }

    if (socioAtual == NULL)
    {
        cout << "Socio nao encontrado." << endl;
        return;
    }

    if (!socioAtual->mensalidadeEmDia)
    {
        cout << "Socio inadimplente. Entrada/saida nao permitida." << endl;
        return;
    }

    cout << "Digite 'E' para entrada ou 'S' para saida: ";
    cin >> operacao;

    // Verificar se a operacao é válida
    if (operacao != 'E' && operacao != 'S')
    {
        cout << "Operacao inválida. Digite 'E' para entrada ou 'S' para saida." << endl;
        return;
    }

    // Registrar entrada/saida na lista de registrosPortaria
    RegistroPortaria *novoRegistro = new RegistroPortaria;
    novoRegistro->numeroTitulo = numeroTitulo;
    novoRegistro->nomeSocio = socioAtual->nomeTitular;
    
    if (operacao == 'E')
    {
        novoRegistro->operacaoEntrada = true;
    }
    else if (operacao == 'S')
    {
        novoRegistro->operacaoSaida = true;
    }

    // Adicionar o novo registro à lista
    novoRegistro->proximo = registrosPortaria;
    registrosPortaria = novoRegistro;

    cout << "Operacao registrada com sucesso." << endl;
}

void gerarRelatorioVisitas()
{
    // Variável para armazenar a data atual
    string dataAtual;
    cout << "------ Relatório de Visitas ------" << endl;

    // Obtenha a data atual (assumindo que você tenha essa informação disponível)
    cout << "Data do Arquivo: ";
    cin >> dataAtual;

    // Imprime a data no estilo "dd-mm-yyyy"
    cout << dataAtual << endl;
    cout << "========" << endl;

    // Exibir relatório na tela
    RegistroPortaria *atual = registrosPortaria;

    // Percorre a lista de registros de portaria
    while (atual != NULL)
    {
        // Imprime o número do título formatado na tela
        cout << (atual->numeroTitulo < 10 ? "0000" : (atual->numeroTitulo < 100 ? "000" : (atual->numeroTitulo < 1000 ? "00" : (atual->numeroTitulo < 10000 ? "0" : ""))));
        cout << atual->numeroTitulo << " " << atual->nomeSocio << " ";

        // Verifica se houve operação de entrada e/ou saída e imprime na tela
        if (atual->operacaoEntrada && atual->operacaoSaida)
        {
            cout << "E S";
        }
        else if (atual->operacaoEntrada)
        {
            cout << "E";
        }
        else if (atual->operacaoSaida)
        {
            cout << "S";
        }

        // Adiciona uma quebra de linha para o próximo registro
        cout << endl;

        // Move para o próximo nó na lista de registros de portaria
        atual = atual->proximo;
    }
}

void gerarRelatorioVisitasArquivo()
{
    // Gerar relatório em arquivo texto
    ofstream arquivo("relatorio_visitas.txt");
    // Verificar se o arquivo foi aberto com sucesso
    if (!arquivo.is_open())
    {
        cout << "Erro ao abrir o arquivo." << endl;
        return;
    }

    // Variável para armazenar a data atual
    string dataAtual;
    cout << "------ Relatório de Visitas ------" << endl;
    // Obtenha a data atual (assumindo que você tenha essa informação disponível)
    cout << "Data do Arquivo: ";
    cin >> dataAtual;
    // Imprime a data no estilo "dd-mm-yyyy" no arquivo
    arquivo << dataAtual << endl;
    arquivo << "========" << endl;
    // Exibir relatório no arquivo
    RegistroPortaria *atual = registrosPortaria;

    // Percorre a lista de registros de portaria
    while (atual != NULL)
    {
        // Imprime o número do título formatado no arquivo
        arquivo << (atual->numeroTitulo < 10 ? "0000" : (atual->numeroTitulo < 100 ? "000" : (atual->numeroTitulo < 1000 ? "00" : (atual->numeroTitulo < 10000 ? "0" : ""))));
        arquivo << atual->numeroTitulo << " " << atual->nomeSocio << " ";

        // Verifica se houve operação de entrada e/ou saída e escreve no arquivo
        if (atual->operacaoEntrada && atual->operacaoSaida)
        {
            arquivo << "E S";
        }
        else if (atual->operacaoEntrada)
        {
            arquivo << "E";
        }
        else if (atual->operacaoSaida)
        {
            arquivo << "S";
        }

        // Adiciona uma quebra de linha para o próximo registro
        arquivo << endl;

        // Move para o próximo nó na lista de registros de portaria
        atual = atual->proximo;
    }
    // Fecha o arquivo após concluir a escrita
    arquivo.close();
    // Exibe uma mensagem indicando o sucesso da geração do relatório no arquivo
    cout << "Relatorio de visitas gerado no arquivo 'relatorio_visitas.txt'." << endl;
}

void liberarMemoria()
{
    // Libera a memória alocada para a lista de sócios
    Socio *atualSocio = listaSocios;
    while (atualSocio != NULL)
    {
        // Armazena o próximo sócio antes de liberar a memória do atual
        Socio *proximoSocio = atualSocio->proximo;
        delete atualSocio;         // Libera a memória do sócio atual
        atualSocio = proximoSocio; // Move para o próximo sócio na lista
    }

    // Libera a memória alocada para a lista de registros de portaria
    RegistroPortaria *atualRegistro = registrosPortaria;
    while (atualRegistro != NULL)
    {
        // Armazena o próximo registro antes de liberar a memória do atual
        RegistroPortaria *proximoRegistro = atualRegistro->proximo;
        delete atualRegistro;            // Libera a memória do registro atual
        atualRegistro = proximoRegistro; // Move para o próximo registro na lista
    }
}
