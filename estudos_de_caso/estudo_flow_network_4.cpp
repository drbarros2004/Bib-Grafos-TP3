#include <bits/stdc++.h>
#include "graph_lib.h"
#include <chrono>
typedef long long ll;
using namespace std;

int main () {

    string nome_arquivo = "grafo_rf_4.txt";
    string txt_file_results_name = "flow_network_4_results.txt";

    vector<vector<pair<int, pair<int, int>>>> flow_network_4 = txt_to_flow_network_vector(nome_arquivo, true);

    int max_flow = FordFulkerson_Vector(flow_network_4, 1, 2, true, txt_file_results_name);
    cout << "Fluxo maximo: " << max_flow << endl;

    // Teste de tempo do Ford-Fulkerson

    double tempo_total_ford_fulkerson = 0;
    
    srand(time(0));  

    for (int i = 0; i < 10; i++) {
        tempo_total_ford_fulkerson += FordFulkerson_Vector_With_Execution_Time(flow_network_4, 1, 2);
    }

    double tempo_medio_ford_fulkerson = tempo_total_ford_fulkerson / 10;
    cout << "Tempo medio das 10 execucoes de Ford-Fulkerson: " << tempo_medio_ford_fulkerson << endl;

    return 0;

}