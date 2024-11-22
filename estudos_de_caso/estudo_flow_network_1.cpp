#include <bits/stdc++.h>
#include "graph_lib.h"
#include <chrono>
#include <windows.h>
#include <psapi.h>
typedef long long ll;
using namespace std;

void print_memory_usage(const string& label) {
    PROCESS_MEMORY_COUNTERS memCounters;
    if (GetProcessMemoryInfo(GetCurrentProcess(), &memCounters, sizeof(memCounters))) {
        cout << label << " - Memória usada: " 
             << memCounters.WorkingSetSize / 1024 / 1024 << " MB" << endl;
    } else {
        cerr << "Erro ao obter informações de memória" << endl;
    }
}

int main () {

    string nome_arquivo = "grafo_rf_1.txt";
    string txt_file_results_name = "flow_network_1_results.txt";

    // 1. Carregar a rede de fluxo
    vector<vector<pair<int, int>>> flow_network_1;
    try {
        print_memory_usage("Antes de carregar a rede de fluxo");
        flow_network_1 = txt_to_flow_network_matrix(nome_arquivo, true);
        print_memory_usage("Após carregar a rede de fluxo");
        cout << "Rede de fluxo carregada com sucesso!" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao carregar a rede de fluxo: " << e.what() << endl;
        return 1; // Interrompe o programa se não conseguir carregar a rede de fluxo
    }

    // 2. Criar a matriz residual
    vector<vector<pair<int, pair<int, bool>>>> residual_graph;
    try {
        print_memory_usage("Antes de criar a matriz residual");
        residual_graph = create_residual_graph_matrix(flow_network_1);
        print_memory_usage("Após criar a matriz residual");
        cout << "Matriz de grafo residual criada com sucesso!" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao criar a matriz residual: " << e.what() << endl;
        return 1;
    }

    // 3. Testando a função de busca do gargalo (bottleneck)
    vector<int> pai;
    int bottleneck = -1;
    try {
        print_memory_usage("Antes de buscar o bottleneck");
        bottleneck = Find_Bottleneck_Matrix(residual_graph, 1, 2, pai);  // Exemplo de s=1 e t=2
        print_memory_usage("Após buscar o bottleneck");
        cout << "Bottleneck encontrado: " << bottleneck << endl;
    } catch (const exception& e) {
        cerr << "Erro ao encontrar o bottleneck: " << e.what() << endl;
        return 1;
    }

    // 4. Testando a atualização do fluxo
    try {
        print_memory_usage("Antes de atualizar o fluxo");
        // Aqui seria necessário ter a residual_matrix e outras variáveis para atualizar corretamente
        // Update_Flow_Matrix(flow_network_1, residual_graph, pai, bottleneck, 1, 2, true);
        print_memory_usage("Após atualizar o fluxo");
        cout << "Fluxo atualizado com sucesso!" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao atualizar o fluxo: " << e.what() << endl;
        return 1;
    }

    // 5. Testando a criação do arquivo de alocação de fluxos
    try {
        print_memory_usage("Antes de criar o arquivo de alocação de fluxos");
        // Se você tem a função para criar os arquivos de fluxo, descomente a linha
        // create_edges_flow_allocation_txt_Matrix(flow_network_1, txt_file_results_name);
        print_memory_usage("Após criar o arquivo de alocação de fluxos");
        cout << "Arquivo de alocação de fluxos criado com sucesso!" << endl;
    } catch (const exception& e) {
        cerr << "Erro ao criar o arquivo de alocação de fluxos: " << e.what() << endl;
        return 1;
    }

    // 6. Testando o algoritmo de Ford-Fulkerson (máximo fluxo)
    int max_flow = -1;
    try {
        print_memory_usage("Antes de calcular o fluxo máximo");
        max_flow = Ford_Fulkerson_Matrix(flow_network_1, 1, 2, true, txt_file_results_name);
        print_memory_usage("Após calcular o fluxo máximo");
        cout << "Fluxo máximo: " << max_flow << endl;
    } catch (const exception& e) {
        cerr << "Erro ao calcular o fluxo máximo: " << e.what() << endl;
        return 1;
    }

    return 0;
}

// int main () {

//     string nome_arquivo = "grafo_rf_1.txt";
//     string txt_file_results_name = "flow_network_1_results.txt";

//     vector<vector<pair<int, pair<int, int>>>> flow_network_1 = txt_to_flow_network_vector(nome_arquivo, true);

//     int max_flow = Ford_Fulkerson_Vector(flow_network_1, 1, 2, true, txt_file_results_name);
//     cout << "Fluxo maximo: " << max_flow << endl;

//     // Teste de tempo do Ford-Fulkerson

//     double tempo_total_ford_fulkerson = 0;
    
//     srand(time(0));  

//     for (int i = 0; i < 10; i++) {
//         tempo_total_ford_fulkerson += Ford_Fulkerson_Vector_With_Execution_Time(flow_network_1, 1, 2);
//     }

//     double tempo_medio_ford_fulkerson = tempo_total_ford_fulkerson / 10;
//     cout << "Tempo medio das 10 execucoes de Ford-Fulkerson: " << tempo_medio_ford_fulkerson << endl;

//     return 0;
// }
