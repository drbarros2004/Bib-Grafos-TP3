#include <iostream>
#include <fstream>
#include <bits/stdc++.h>
#include <chrono>
using namespace std;

vector<vector<int>> txt_to_adjacency_vector(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt") {

    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }

    int numVertices, numArestas, u, v, degreeSum;
    arquivo >> numVertices;
    numArestas = 0;
    degreeSum = 0;
    vector<int> degrees(numVertices + 1, 0);

    vector<vector<int>> graph(numVertices + 1);

    while (arquivo >> u >> v) {
        graph[u].push_back(v);
        graph[v].push_back(u);

        numArestas++;
        degrees[u]++;
        degrees[v]++;
        degreeSum += 2;
    }

    arquivo.close();

    // Ordenar os graus
    sort(degrees.begin() + 1, degrees.end());

    // Encontrar grau máximo, mínimo e calcular estatísticas
    int maxDegree = degrees[numVertices];
    int minDegree = degrees[1];
    double averageDegree = static_cast<double>(degreeSum) / numVertices;
    double medianDegree;

    // Calcular a mediana do grau
    if (numVertices % 2 == 0) {
        medianDegree = (degrees[numVertices / 2] + degrees[(numVertices / 2) + 1]) / 2.0;
    } else {
        medianDegree = degrees[(numVertices + 1) / 2];
    }

    // Função para calcular componentes conexas
    vector<vector<int>> componentes;
    vector<int> tamanhos;
    int quant_componentes = 0;
    vector<bool> visitados(graph.size(), false);
    queue<int> fila;
    int iterador = 0;

    for (int node = 1; node < graph.size(); node++) {
        if (!visitados[node]) {
            quant_componentes++;
            componentes.push_back(vector<int>()); 
            tamanhos.push_back(0); 
            fila.push(node);
            visitados[node] = true;
            componentes[iterador].push_back(node);
            tamanhos[iterador]++;

            while (!fila.empty()) {
                int atual = fila.front();
                fila.pop();

                for (int vizinho : graph[atual]) {
                    if (!visitados[vizinho]) {
                        fila.push(vizinho);
                        visitados[vizinho] = true;
                        componentes[iterador].push_back(vizinho);
                        tamanhos[iterador]++;
                    }
                }
            }
            iterador++;
        }
    }

    sort(componentes.begin(), componentes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() > b.size();
    });

    sort(tamanhos.begin(), tamanhos.end());
    reverse(tamanhos.begin(), tamanhos.end());

    // Gravar os resultados no arquivo de saída no modo append (adiciona ao final do arquivo)
    ofstream arquivo_de_saida(nome_do_arquivo_de_saida_principal, std::ios::app);

    if (arquivo_de_saida.is_open()) {
        arquivo_de_saida << "Número de vértices: " << numVertices << endl;
        arquivo_de_saida << "Número de arestas: " << numArestas << endl;
        arquivo_de_saida << "Grau mínimo: " << minDegree << endl;
        arquivo_de_saida << "Grau máximo: " << maxDegree << endl;
        arquivo_de_saida << "Grau médio: " << averageDegree << endl;
        arquivo_de_saida << "Mediana de grau: " << medianDegree << '\n' << endl;

        // Adicionar os resultados das componentes conexas
        arquivo_de_saida << "Número de componentes conexas: " << quant_componentes << endl << endl;
        for (int j = 0; j < tamanhos.size(); j++) {
            arquivo_de_saida << "Componente " << j + 1 << " tem " << tamanhos[j] << " vértices, e eles são: " << endl;
            for (int i = 0; i < componentes[j].size(); i++) {
                arquivo_de_saida << componentes[j][i] << " ";
            }
            arquivo_de_saida << endl << endl << endl;
        }

        arquivo_de_saida.close();
        cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida_principal << endl;
    } else {
        cout << "Erro ao abrir o arquivo de resultados!" << endl;
    }

        return graph;
}


void BFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }       
        }       
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < graph.size(); i++){
        arquivo_de_saida  << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}

double BFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    using namespace std::chrono; 
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;

    auto inicio = high_resolution_clock::now();

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);

    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }       
        }       
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < graph.size(); i++){
        if (nivel[i] != INF) {
            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
        }
    }

    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}


void DFS_tree_vector(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt") {
    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    stack<int> pilha;

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);

    while (!pilha.empty()) {
        int atual = pilha.top();
        pilha.pop();
        for (int vizinho : graph[atual]) {
            if (!visitados[vizinho]) {
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);

    for (int i = 1; i < graph.size(); i++) {

        arquivo_de_saida << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
        
    }

    arquivo_de_saida.close();
    
    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;

}

double DFS_tree_vector_with_execution_time(const vector<vector<int>>& graph, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt") {
    using namespace std::chrono; 

    int INF = 1e9;
    vector<int> nivel(graph.size(), INF);
    vector<int> pai(graph.size(), INF);
    vector<bool> visitados(graph.size(), false);
    stack<int> pilha;
    
    auto inicio = high_resolution_clock::now(); // início do algoritmo

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);

    while (!pilha.empty()) {
        int atual = pilha.top();
        pilha.pop();
        for (int vizinho : graph[atual]) {
            if (!visitados[vizinho]) {
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }
    }


    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);

    for (int i = 1; i < graph.size(); i++) {
        arquivo_de_saida << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

    }

    arquivo_de_saida.close();
    
   // cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    return tempo_execucao.count();

}

int Diametro_aproximado_vector(const vector<vector<int>>& graph){
    int max_distancia = 0;
    for(int i = 0; i < 9; i ++){
        vector<int> dist(graph.size(), -1);
        int origem = rand() % graph.size();
        dist[origem] = 0;
        queue <int> fila;
        fila.push(origem);
        while(!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            for(int vizinho : graph[atual]){
                if(dist[vizinho] == -1){
                    dist[vizinho] = dist[atual] + 1;
                    fila.push(vizinho);
                    if (dist[vizinho] > max_distancia) {
                        max_distancia = dist[vizinho];
                    }
                }       
            }       
        }  
    }
    cout << "Diametro do grafo aproximado: " << max_distancia << endl;
}


int Diametro_vector(const vector<vector<int>>& graph){

    if(graph.size() >= 50000){
        return Diametro_aproximado_vector(graph);
    }
    else{
        int max_distancia = 0;
        for(int i = 1; i < graph.size(); i ++){
            vector<int> dist(graph.size(), -1);
            int origem = i;
            dist[origem] = 0;
            queue <int> fila;
            fila.push(origem);
            while(!fila.empty()) {
                int atual = fila.front();
                fila.pop();
                for(int vizinho : graph[atual]){
                    if(dist[vizinho] == -1){
                        dist[vizinho] = dist[atual] + 1;
                        fila.push(vizinho);
                        if (dist[vizinho] > max_distancia) {
                            max_distancia = dist[vizinho];
                        }
                    }       
                }       
            }  
        }
        cout << "Diametro do grafo: " << max_distancia << endl;
    }
}



void Distancia_vector(const vector<vector<int>>& graph, int origem, int destino){
    vector<int> dist(graph.size(), -1);
    vector<bool> visitados(graph.size(), false);
    queue <int> fila;
    int distancia = -1;
    visitados[origem] = true;
    dist[origem] = 0;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho : graph[atual]){
            if(!visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                dist[vizinho] = dist[atual] + 1;
                if(vizinho == destino){    
                    distancia = dist[vizinho];
                    cout << "A distancia entre " << origem << " e " << destino << " igual a: " << distancia << endl;
                    return;
                }
            }       
        }       
    }
    cout << "Impossivel ligar os vertices "  << origem << " e " << destino << "." << endl;
} 


vector<vector<bool>> txt_to_adjacency_matrix(const string& nome_arquivo, string nome_do_arquivo_de_saida_principal = "resultados.txt") {
    
    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }

    int numVertices, numArestas, u, v, degreeSum;
    
    // Ler o número de vértices
    arquivo >> numVertices;
    numArestas = 0;
    degreeSum = 0;

    // Inicializar o vetor de graus e a matriz de adjacência com base no número de vértices
    vector<int> degrees(numVertices + 1, 0);
    vector<vector<bool>> matrix(numVertices + 1, vector<bool>(numVertices + 1, false));

    // Ler as arestas e preencher a matriz de adjacência
    while (arquivo >> u >> v) {
        matrix[u][v] = true;  
        matrix[v][u] = true; 

        numArestas++;
        degrees[u]++;
        degrees[v]++;
        degreeSum += 2;
    }

    arquivo.close();

    // Ordenar os graus
    sort(degrees.begin() + 1, degrees.end());

    // Encontrar grau máximo, mínimo e calcular estatísticas
    int maxDegree = degrees[numVertices];
    int minDegree = degrees[1];
    double averageDegree = static_cast<double>(degreeSum) / numVertices;
    double medianDegree;

    // Calcular a mediana do grau
    if (numVertices % 2 == 0) {
        medianDegree = (degrees[numVertices / 2] + degrees[(numVertices / 2) + 1]) / 2.0;
    } else {
        medianDegree = degrees[(numVertices + 1) / 2];
    }

    // Função para calcular componentes conexas
    vector<vector<int>> componentes;
    vector<int> tamanhos;
    int quant_componentes = 0;
    vector<bool> visitados(matrix.size(), false);
    queue<int> fila;
    int iterador = 0;

    for (int node = 1; node < matrix.size(); node++) {
        if (!visitados[node]) {
            quant_componentes++;
            componentes.push_back(vector<int>()); 
            tamanhos.push_back(0); 
            fila.push(node);
            visitados[node] = true;
            componentes[iterador].push_back(node);
            tamanhos[iterador]++;

            while (!fila.empty()) {
                int atual = fila.front();
                fila.pop();

                for (int vizinho = 1; vizinho < matrix.size(); vizinho++) {
                    if (matrix[atual][vizinho] && !visitados[vizinho]) {
                        fila.push(vizinho);
                        visitados[vizinho] = true;
                        componentes[iterador].push_back(vizinho);
                        tamanhos[iterador]++;
                    }
                }
            }
            iterador++;
        }
    }

    sort(componentes.begin(), componentes.end(), [](const vector<int>& a, const vector<int>& b) {
        return a.size() > b.size();
    });

    sort(tamanhos.begin(), tamanhos.end());
    reverse(tamanhos.begin(), tamanhos.end());

    // Gravar os resultados no arquivo de saída
    ofstream arquivo_de_saida(nome_do_arquivo_de_saida_principal, std::ios::app);

    if (arquivo_de_saida.is_open()) {
        arquivo_de_saida << "Número de vértices: " << numVertices << endl;
        arquivo_de_saida << "Número de arestas: " << numArestas << endl;
        arquivo_de_saida << "Grau mínimo: " << minDegree << endl;
        arquivo_de_saida << "Grau máximo: " << maxDegree << endl;
        arquivo_de_saida << "Grau médio: " << averageDegree << endl;
        arquivo_de_saida << "Mediana de grau: " << medianDegree << endl;

        // Adicionar os resultados das componentes conexas
        arquivo_de_saida << "Número de componentes conexas: " << quant_componentes << endl << endl;
        for (int j = 0; j < tamanhos.size(); j++) {
            arquivo_de_saida << "Componente " << j + 1 << " tem " << tamanhos[j] << " vértices, e eles são: " << endl;
            for (int i = 0; i < componentes[j].size(); i++) {
                arquivo_de_saida << componentes[j][i] << " ";
            }
            arquivo_de_saida << endl << endl << endl;

        }

        arquivo_de_saida.close(); 
        cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida_principal << endl;
    } else {
        cout << "Erro ao abrir o arquivo de resultados!" << endl;
    }

    return matrix;
}

void BFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        arquivo_de_saida  << "Vértice: " << i << endl;
        arquivo_de_saida << "Nível: " << nivel[i] << endl;
        arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}

double BFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreBFS.txt"){
    using namespace std::chrono;

    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;

    auto inicio = high_resolution_clock::now();

    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    fila.push(origem);
    while(!fila.empty()){
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        
            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';
    }


    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}

void DFS_tree_matrix(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt"){
    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    stack <int> pilha;
    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);
    while(!pilha.empty()){
        int atual = pilha.top();
        pilha.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] == 1 & !visitados[vizinho]){
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        if (nivel[i] != 1e9) {

            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

        }
    }

    cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

}

double DFS_tree_matrix_with_execution_time(const vector<vector<bool>>& matrix, int origem, string nome_do_arquivo_de_saida = "arvoreDFS.txt"){
    using namespace std::chrono;

    int INF = 1e9;
    vector<int> nivel(matrix.size(), INF);
    vector<int> pai(matrix.size(), INF);
    vector<bool> visitados(matrix.size(), false);
    stack <int> pilha;

    auto inicio = high_resolution_clock::now(); // início do algoritmo


    visitados[origem] = true;
    nivel[origem] = 0;
    pai[origem] = -1;
    pilha.push(origem);
    while(!pilha.empty()){
        int atual = pilha.top();
        pilha.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho ++){
            if(matrix[atual][vizinho] && !visitados[vizinho]){
                pilha.push(vizinho);
                visitados[vizinho] = true;
                nivel[vizinho] = nivel[atual] + 1;
                pai[vizinho] = atual;
            }
        }      
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    ofstream arquivo_de_saida(nome_do_arquivo_de_saida);
    
    for(int i = 1; i < matrix.size(); i++){
        if (nivel[i] != 1e9) {

            arquivo_de_saida  << "Vértice: " << i << endl;
            arquivo_de_saida << "Nível: " << nivel[i] << endl;
            arquivo_de_saida << "Pai: " << pai[i] << '\n' << '\n';

        }
    }

    //cout << "Resultados gravados no arquivo " << nome_do_arquivo_de_saida << endl;
    arquivo_de_saida.close();

    return tempo_execucao.count();

}

int Diametro_aproximado_matrix(const vector<vector<bool>>& matrix){
    int max_distancia = 0;
    for(int i = 0; i < 9; i ++){
        vector<int> dist(matrix.size(), -1);
        int origem = rand() % matrix.size();
        dist[origem] = 0;
        queue <int> fila;
        fila.push(origem);
        while(!fila.empty()) {
            int atual = fila.front();
            fila.pop();
            for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
                if(matrix[atual][vizinho] && dist[vizinho] == -1){
                    dist[vizinho] = dist[atual] + 1;
                    fila.push(vizinho);
                    if (dist[vizinho] > max_distancia) {
                        max_distancia = dist[vizinho];
                    }
                }       
            }       
        }  
    }
    cout << "Diametro do grafo aproximado: " << max_distancia << endl;
}
 

int Diametro_matrix(const vector<vector<bool>>& matrix){

    if(matrix.size() >= 50000){
        return Diametro_aproximado_matrix(matrix);
    }
    else{
        int max_distancia = 0;
        for(int i = 1; i < matrix.size(); i ++){
            vector<int> dist(matrix.size(), -1);
            int origem = i;
            dist[origem] = 0;
            queue <int> fila;
            fila.push(origem);
            while(!fila.empty()) {
                int atual = fila.front();
                fila.pop();
                for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
                    if(matrix[atual][vizinho] && dist[vizinho] == -1){
                        dist[vizinho] = dist[atual] + 1;
                        fila.push(vizinho);
                        if (dist[vizinho] > max_distancia) {
                            max_distancia = dist[vizinho];
                        }
                    }       
                }       
            }  
        }
        cout << "Diametro do grafo: " << max_distancia << endl;
    }
}


void Distancia_matrix(const vector<vector<bool>>& matrix, int origem, int destino){
    vector<int> dist(matrix.size(), -1);
    vector<bool> visitados(matrix.size(), false);
    queue <int> fila;
    int distancia = -1;
    visitados[origem] = true;
    dist[origem] = 0;
    fila.push(origem);
    while(!fila.empty()) {
        int atual = fila.front();
        fila.pop();
        for(int vizinho = 1; vizinho < matrix.size(); vizinho++){
            if(matrix[atual][vizinho] && !visitados[vizinho]){
                fila.push(vizinho);
                visitados[vizinho] = true;
                dist[vizinho] = dist[atual] + 1;
                if(vizinho == destino){   
                    distancia = dist[vizinho];
                    cout << "A distancia entre " << origem << " e " << destino << " igual a: " << distancia << endl; 
                    return;
                }
            }       
        }       
    }
    cout << "Impossivel ligar os vertices " << origem << " e " << destino << "." << endl;
} 



// TP2:

vector<vector<pair<int, float>>> txt_to_weight_adjacency_vector(const string& nome_arquivo) {

    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }
    
    int numVertices, u, v;
    float w;
    int INF = 1e9;
    
    // Ler o número de vértices
    arquivo >> numVertices;

    vector<vector<pair<int, float>>> graph(numVertices + 1);

    pair<int, float> flag;
    flag.first = 0;
    flag.second = 0;
    graph[0].push_back(flag);

    while (arquivo >> u >> v >> w) {
        
        pair<int,float> relacao;
        relacao.first = v; 
        relacao.second = w; 

        if(w < 0) {
            flag.first = -1;
            flag.second = -1;
            graph[0].clear();
            graph[0].push_back(flag);

            // Essa parte coloca uma "flag" dentro de uma parte do grafo que não é utilizada: o vetor relacionado ao 0. Logo,
            // se essa flag existir, o algoritmo de Dijkstra não será executada.
        }

        graph[u].push_back(relacao);
        relacao.first = u; 
        graph[v].push_back(relacao);

        }

        arquivo.close();

    return graph;
}



vector<float> Dijkstra_Vector_Vector(const vector<vector<pair<int,float>>>& graph, int origem) {

    if (graph[0][0].first == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    int INF = 1e9;
    int n = graph.size();
    vector<float> dist(n, INF); // Distâncias parciais
    vector<bool> visitado(n, false); 

    dist[origem] = 0; // Distância da origem é zero

    for (int i = 0; i < n; ++i) {
        // Encontrar o vértice não visitado com a menor distância
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos
        for (const auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }
    
    return dist;
}

vector<float> Dijkstra_Vector_Heap(const vector<vector<pair<int,float>>>& graph, int origem) {

    if (graph[0][0].first == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    float INF = 1e9;
    int n = graph.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false); 

    dist[origem] = 0;

    priority_queue<pair<int, float>, vector<pair<int, float>>, greater<pair<int, float>>> fila;
    
    fila.push({origem, 0});

    while (!fila.empty()) {
        int u = fila.top().first;
        float dist_u = fila.top().second;
        fila.pop();

        // Se já visitamos este vértice, continuamos
        if (visitado[u]) continue;
        visitado[u] = true;

        // Para cada vizinho v de u
        for (auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({v, dist[v] });
            }
        }
    }

    return dist;

}


double Dijkstra_Vector_Vector_With_Execution_Time(const vector<vector<pair<int,float>>>& graph, int origem) {

    if (graph[0][0].first == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();

    int INF = 1e9;
    int n = graph.size();
    vector<float> dist(n, INF); // Distâncias parciais
    vector<bool> visitado(n, false); 

    dist[origem] = 0; 

    for (int i = 0; i < n; ++i) {
        // Encontrar o vértice não visitado com a menor distância
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        if (dist[u] == INF) break;

        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos
        for (const auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;
    
    return tempo_execucao.count();

}



double Dijkstra_Vector_Heap_With_Execution_Time(const vector<vector<pair<int,float>>>& graph, int origem) {

    if (graph[0][0].first == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();

    int INF = 1e9;
    int n = graph.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false); 

    dist[origem] = 0;

    priority_queue<pair<int, float>, vector<pair<int, float>>, greater<pair<int, float>>> fila;
    
    fila.push({origem, 0});

    while (!fila.empty()) {
        int u = fila.top().first;
        float dist_u = fila.top().second;
        fila.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        // Para cada vizinho v de u
        for (auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({v, dist[v] });
            }
        }
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    return tempo_execucao.count();

}


void Caminho_Minimo_Vector(const vector<vector<pair<int, float>>>& graph, int origem, int destino)  {

        if (graph[0][0].first == -1) {
            cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
            return;
        }

    float INF = 1e9; 
    int n = graph.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false);
    vector<int> pai(n, -1); // O valor inicial do pai deve ser -1 para indicar que não tem pai

    dist[origem] = 0;

    // Fila de prioridade (min-heap) para armazenar {distância, vértice}

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> fila;

    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        float dist_u = fila.top().first;
        fila.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        for (auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({dist[v], v}); 
                pai[v] = u;
            }
        }
    }

    vector<int> caminho;
    for (int i = destino; i != -1; i = pai[i]) {
        caminho.push_back(i);
    }
    reverse(caminho.begin(), caminho.end());

    for (int i = 0; i < caminho.size(); i++) {
        cout << caminho[i];
        if (i != caminho.size() - 1) cout << " -> ";
    }
    cout << endl;

    cout << "Custo do caminho: " << dist[destino] << "\n" << endl;
}


vector<vector<float>> txt_to_weight_adjacency_matrix(const string& nome_arquivo) {

    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }

    int numVertices, u, v;
    float w;
    int INF = 1e9;
    bool Dijkstra = true;

    // Ler o número de vértices
    arquivo >> numVertices;

    
    vector<vector<float>> matrix(numVertices + 1, vector<float>(numVertices + 1, INF)); 

    while (arquivo >> u >> v >> w) {

        if(w < 0) {
            matrix[0][0] = -1;
            // Essa parte coloca uma "flag" dentro de uma parte do grafo que não é utilizada: o vetor relacionado ao 0. Logo,
            // se essa flag existir, o algoritmo de Dijkstra não será executada.
        }
        matrix[u][v] = w;  
        matrix[v][u] = w; 

    }

    arquivo.close();

    return matrix;
}

vector<float> Dijkstra_Matrix_Vector(const vector<vector<float>>& matrix, int origem) {

    if (matrix[0][0] == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }
    
    int INF = 1e9;
    int n = matrix.size();
    vector<float> dist(n, INF); // Distâncias parciais
    vector<bool> visitado(n, false); 

    dist[origem] = 0; 

    for (int i = 0; i < n; ++i) {
        // Encontrar o vértice não visitado com a menor distância
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        // Se não há mais vértices alcançáveis, termina
        if (dist[u] == INF) break;

        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos de u
        for (int v = 0; v < n; ++v) {
            float peso = matrix[u][v];
            if (peso > 0 && !visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    return dist;
}


vector<float> Dijkstra_Matrix_Heap(const vector<vector<float>>& matrix, int origem) {

    if (matrix[0][0] == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    float INF = 1e9;
    int n = matrix.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false);

    dist[origem] = 0;

    // Fila de prioridade (min-heap) para armazenar {distância, vértice}
    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> fila;
    
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        float dist_u = fila.top().first;
        fila.pop();

        // Se já visitamos este vértice, continuamos
        if (visitado[u]) continue;
        visitado[u] = true;

        // Percorrendo todos os vizinhos de u
        for (int v = 0; v < n; ++v) {
            float peso = matrix[u][v];
            
            // Ignorar se não houver aresta
            if (peso == INF || u == v) continue;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({dist[v], v});
            }
        }
    }

    return dist;
}

double Dijkstra_Matrix_Vector_With_Execution_Time(const vector<vector<float>>& matrix, int origem) {

    if (matrix[0][0] == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();
    
    int INF = 1e9;
    int n = matrix.size();
    vector<float> dist(n, INF); // Distâncias parciais
    vector<bool> visitado(n, false); 

    dist[origem] = 0; 

    for (int i = 0; i < n; ++i) {
        // Encontrar o vértice não visitado com a menor distância
        int u = -1;
        for (int j = 0; j < n; ++j) {
            if (!visitado[j] && (u == -1 || dist[j] < dist[u])) {
                u = j;
            }
        }

        // Se não há mais vértices alcançáveis, termina
        if (dist[u] == INF) break;

        visitado[u] = true;

        // Atualiza as distâncias dos vizinhos de u
        for (int v = 0; v < n; ++v) {
            float peso = matrix[u][v];
            if (peso > 0 && !visitado[v] && dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
            }
        }
    }

    auto fim = high_resolution_clock::now(); // fim do algoritmo

    duration<double> tempo_execucao = fim - inicio;

    return tempo_execucao.count();
}


double Dijkstra_Matrix_Heap_With_Execution_Time(const vector<vector<float>>& matrix, int origem) {

    if (matrix[0][0] == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return {};
    }

    using namespace std::chrono;
    auto inicio = high_resolution_clock::now();

    float INF = 1e9;
    int n = matrix.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false);

    dist[origem] = 0;

    // Fila de prioridade (min-heap) para armazenar {distância, vértice}

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> fila;
    
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        float dist_u = fila.top().first;
        fila.pop();

        // Se já visitamos este vértice, continuamos
        if (visitado[u]) continue;
        visitado[u] = true;

        // Percorrendo todos os vizinhos de u
        for (int v = 0; v < n; ++v) {
            float peso = matrix[u][v];
            
            // Ignorar se não houver aresta 
            if (peso == INF || u == v) continue;


            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({dist[v], v});
            }
        }
    }

    auto fim = high_resolution_clock::now(); 

    duration<double> tempo_execucao = fim - inicio;

    return tempo_execucao.count();
}

void Caminho_Minimo_Matrix(const vector<vector<float>>& matrix, int origem, int destino) {

    if (matrix[0][0] == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return;
    }

    float INF = 1e9; 
    int n = matrix.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false);
    vector<int> pai(n, -1); // O valor inicial do pai deve ser -1 para indicar que não tem pai

    dist[origem] = 0;

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> fila;

    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        float dist_u = fila.top().first;
        fila.pop();

        // Se já visitamos este vértice, continuamos
        if (visitado[u]) continue;
        visitado[u] = true;

        // Percorrendo todos os vizinhos de u
        for (int v = 0; v < n; ++v) {
            float peso = matrix[u][v];

            // Ignorar se não houver aresta 
            if (peso == INF || u == v) continue;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({dist[v], v});
                pai[v] = u;
            }
        }
    }

    vector<int> caminho;
    for (int i = destino; i != -1; i = pai[i]) {
        caminho.push_back(i);
    }
    reverse(caminho.begin(), caminho.end());

    for (int i = 0; i < caminho.size(); i++) {
        cout << caminho[i];
        if (i != caminho.size() - 1) cout << " -> ";
    }
    cout << endl;

    cout << "Custo do caminho: " << dist[destino] << "\n" << endl;

}

vector<pair<int, string>> txt_to_dictionary(const string& nome_arquivo_grafo, const string& nome_arquivo_dicionario) {

    ifstream arquivo1(nome_arquivo_grafo);
    if (!arquivo1.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada (grafo)!");
    }
    
    int numVertices;
    
    arquivo1 >> numVertices;

    arquivo1.close();

    ifstream arquivo2(nome_arquivo_dicionario);
    if (!arquivo2.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada (dicionário)!");
    }

    vector<pair<int, string>> dict(numVertices + 1); 

    int id;
    string nome;
    string linha;

    while (getline(arquivo2, linha)) {
        size_t virgula_pos = linha.find(','); 
        if (virgula_pos != string::npos) {
            id = stoi(linha.substr(0, virgula_pos)); 
            nome = linha.substr(virgula_pos + 1);    
            if (id <= numVertices) {
                dict[id] = make_pair(id, nome); 
            }
        }
    }

    arquivo2.close();

    return dict;
}

void Caminho_Minimo_Rede(const vector<vector<pair<int, float>>>& graph, string nome_origem, string nome_destino, const vector<pair<int,string>>& dict)  {

     if (graph[0][0].first == -1) {
        cout << "O grafo possui pesos negativos! O algoritmo de Dijkstra nao garante caminho minimo nesse caso.";
        return;
    }

    float INF = 1e9;
    int n = graph.size();
    vector<float> dist(n, INF);
    vector<bool> visitado(n, false);
    vector<int> pai(n, -1);

    int origem = -1, destino = -1;
    for (const auto& entry : dict) {
        if (entry.second == nome_origem) {
            origem = entry.first;
        }
        if (entry.second == nome_destino) {
            destino = entry.first;
        }
    }

    if (origem == -1 || destino == -1) {
        cout << "Origem ou destino não encontrado no dicionário!" << endl;
        return;
    }

    dist[origem] = 0;

    priority_queue<pair<float, int>, vector<pair<float, int>>, greater<pair<float, int>>> fila;
    fila.push({0, origem});

    while (!fila.empty()) {
        int u = fila.top().second;
        fila.pop();

        if (visitado[u]) continue;
        visitado[u] = true;

        for (auto& vizinho : graph[u]) {
            int v = vizinho.first;
            float peso = vizinho.second;

            if (dist[u] + peso < dist[v]) {
                dist[v] = dist[u] + peso;
                fila.push({dist[v], v});
                pai[v] = u;
            }
        }
    }

    if (pai[destino] == -1) {
        cout << "Sem caminho possivel de " << nome_origem << " para " << nome_destino << endl;
        return;
    }

    vector<int> caminho;
    vector<string> caminho_nomes;
    for (int i = destino; i != -1; i = pai[i]) {
        caminho.push_back(i);
    }
    reverse(caminho.begin(), caminho.end());

    // Convertendo IDs para nomes
    for (int id : caminho) {
        for (const auto& entry : dict) {
            if (entry.first == id) {
                caminho_nomes.push_back(entry.second);
                break;
            }
        }
    }

    for (int i = 0; i < caminho_nomes.size(); i++) {
        cout << caminho_nomes[i];
        if (i != caminho_nomes.size() - 1) cout << " -> ";
    }
    cout << endl;

    cout << "Custo do caminho: " << dist[destino] << "\n" << endl;
    
}


// TP3: Representando redes de fluxo e Algoritmo de Ford-Fulkerson:

vector<vector<pair<int, float>>> txt_to_weight_adjacency_targeted_vector(const string& nome_arquivo, bool direcionado) {

    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }
    
    int numVertices, u, v;
    float w;
    int INF = 1e9;
    
    arquivo >> numVertices;

    vector<vector<pair<int, float>>> graph(numVertices + 1);

    pair<int, float> flag;
    flag.first = 0;
    flag.second = 0;
    graph[0].push_back(flag);

    while (arquivo >> u >> v >> w) {
        
        pair<int,float> relacao;
        relacao.first = v; 
        relacao.second = w; 

        if(w < 0) {
            flag.first = -1;
            flag.second = -1;
            graph[0].clear();
            graph[0].push_back(flag);

            // Essa parte coloca uma "flag" dentro de uma parte do grafo que não é utilizada: o vetor relacionado ao 0. Logo,
            // se essa flag existir, o algoritmo de Dijkstra não será executada.

        }

        graph[u].push_back(relacao);

        // Só entramos nesse loop se o grafo não for direcionado.

        if (direcionado = false) {

            relacao.first = u; 
            graph[v].push_back(relacao);

        }

    }

        arquivo.close();

    return graph;
}


vector<vector<pair<int, pair<int, int>>>> txt_to_flow_network_vector(const string& nome_arquivo, bool direcionado) {

    ifstream arquivo(nome_arquivo);
    if (!arquivo.is_open()) {
        throw runtime_error("Erro ao abrir o arquivo de entrada!");
    }

    int numVertices, u, v, capacidade;
    int fluxo = 0; // Fluxo inicial.
    
    arquivo >> numVertices;

    vector<vector<pair<int, pair<int, int>>>> graph(numVertices + 1);

    while (arquivo >> u >> v >> capacidade) {
        pair<int, pair<int, int>> relacao;
        relacao.first = v; 
        relacao.second.first = capacidade;
        relacao.second.second = fluxo; 

        graph[u].push_back(relacao);

        // Para grafos não direcionados, adiciona a aresta reversa.
        if (!direcionado) {
            relacao.first = u; 
            graph[v].push_back(relacao);
        }
    }

    cout << nome_arquivo << " foi carregado com sucesso!" << endl;

    return graph;
}


//COLOCAR UM BOOLEANO AQUI TAMBEM REPRESENTANDO ORIGINAL E REVERSA PARA CASO DE 4 ARESTAS EM 2 VERTICES



vector<vector<pair<int, pair<int, bool>>>> create_residual_graph_vector(const vector<vector<pair<int, pair<int, int>>>>& graph) {

    int numVertices = graph.size();
    vector<vector<pair<int, pair<int, bool>>>> residual_vector(numVertices);

    for (int u = 0; u < numVertices; ++u) {

        for (const auto& edge : graph[u]) {
            int v = edge.first;                 // Vértice de destino
            int capacidade = edge.second.first; // Capacidade da aresta original
            int fluxo = edge.second.second;

            if (capacidade > 0) {

            // Adiciona aresta original ao grafo residual
            residual_vector[u].push_back({v, {capacidade - fluxo, true}}); 

            // Adiciona aresta reversa ao grafo residual com capacidade zero
            residual_vector[v].push_back({u, {fluxo, false}});

            }

        }
    }

    //cout << "O grafo residual foi criado com sucesso!" << endl;

    return residual_vector;
}

int Find_Bottleneck_Vector(const vector<vector<pair<int, pair<int, bool>>>>& residual_vector, int s, int t, vector<int>& pai) {

    int INF = 1e9;
    vector<bool> visitados(residual_vector.size(), false);

    queue<int> fila;
    visitados[s] = true;
    pai.assign(residual_vector.size(), -1); // Reseta o vetor pai
    fila.push(s);

    // Realiza a BFS para encontrar o caminho de s até t
    while (!fila.empty()) {
        int atual = fila.front();
        fila.pop();

        for (const auto& edge : residual_vector[atual]) {
            int vizinho = edge.first;
            int capacidade = edge.second.first;

            // Se o vizinho não foi visitado e a capacidade é maior que 0
            if (!visitados[vizinho] && capacidade > 0) {
                pai[vizinho] = atual;
                visitados[vizinho] = true;
                fila.push(vizinho);

                // Para se chegar no destino
                if (vizinho == t) break;
            }
        }
    }

    // Se não encontramos um caminho até t
    if (!visitados[t]) {
        return 0; // Não há caminho com capacidade positiva entre s e t
    }

    // Caminho encontrado: calcula o bottleneck (menor capacidade no caminho)
    int bottleneck = INF;
    int atual = t;

    while (atual != s) {
        int anterior = pai[atual];

        // Encontra a aresta correspondente no grafo residual
        for (const auto& edge : residual_vector[anterior]) {
            if (edge.first == atual) {
                bottleneck = min(bottleneck, edge.second.first);
                break;
            }
        }

        atual = anterior;
    }

    //cout << "Um gargalo de " << bottleneck << " foi criado com sucesso!" << endl;

    return bottleneck;
}

void Update_Flow_Vector (
    vector<vector<pair<int, pair<int, int>>>>& graph,
    vector<vector<pair<int, pair<int, bool>>>>& residual_vector,
    const vector<int>& pai,
    int bottleneck,
    int s, // Origem do fluxo
    int t, // Destino do fluxo
    bool direcionado
) {

    int atual = t;

    // Atualiza os fluxos no caminho do destino até a origem
    while (atual != s) {
        int anterior = pai[atual];

        // Atualiza o fluxo no grafo original
        for (auto& edge : graph[anterior]) {
            if (edge.first == atual) {
                edge.second.second += bottleneck; // Incrementa o fluxo direto
                break;
            }
        }

        // Atualiza o fluxo reverso no grafo original, se não for direcionado
        if (!direcionado) {
            for (auto& edge : graph[atual]) {
                if (edge.first == anterior) {
                    edge.second.second -= bottleneck; // Decrementa fluxo reverso
                    break;
                }
            }
        }

        // Atualiza o grafo residual na aresta direta
        for (auto& edge : residual_vector[anterior]) {
            if (edge.first == atual) {
                edge.second.first -= bottleneck; // Diminui a capacidade residual
                break;
            }
        }

        // Atualiza o grafo residual na aresta reversa
        for (auto& edge : residual_vector[atual]) {
            if (edge.first == anterior) {
                edge.second.first += bottleneck; // Aumenta a capacidade residual reversa
                break;
            }
        }

        atual = anterior; // Avança para o próximo vértice
    }
}


void create_edges_flow_allocation_txt_Vector(vector<vector<pair<int, pair<int, int>>>> graph, string txt_file_name) {

    ofstream arquivo_de_saida(txt_file_name);
    int numVertices = graph.size();

    for (int v = 0; v < numVertices; v++) {

        for (auto& edge : graph[v]) {

            int u = edge.first;
            int capacidade = edge.second.first;
            int fluxo = edge.second.second;

            arquivo_de_saida << v << " -> " << u << ". Capacidade = " << capacidade << ". Fluxo = " << fluxo << endl;

        }

    }

    arquivo_de_saida.close();

}

int FordFulkerson_Vector(vector<vector<pair<int, pair<int, int>>>> graph, int s, int t, bool create_txt_file = false, string txt_file_name = "flow_network_results.txt") {

    vector<vector<pair<int, pair<int, bool>>>> residual = create_residual_graph_vector(graph);
    int numVertices = graph.size();
    vector<int> pai(numVertices);
    int max_flow = 0;

    int bottleneck;
    while ((bottleneck = Find_Bottleneck_Vector(residual, s, t, pai)) != 0) {

        max_flow += bottleneck;
        Update_Flow_Vector(graph, residual, pai, bottleneck, s, t, true);

        //cout << "Grafo atualizado com o gargalo." << endl;
        
    }

    if (create_txt_file) {

        create_edges_flow_allocation_txt_Vector(graph, txt_file_name);
            
        cout << "Alocacao de fluxo para todas as arestas gravada em " << txt_file_name << endl;

    }

    return max_flow;

}





// //MATRIZ


// vector<vector<float>> txt_to_weight_adjacency_matrix(const string& nome_arquivo, bool direcionado) {

//     ifstream arquivo(nome_arquivo);
//     if (!arquivo.is_open()) {
//         throw runtime_error("Erro ao abrir o arquivo de entrada!");
//     }

//     int numVertices, u, v;
//     float w;
//     int INF = 1e9;

//     // Ler o número de vértices
//     arquivo >> numVertices;

    
//     vector<vector<float>> matrix(numVertices + 1, vector<float>(numVertices + 1, INF)); 

//     while (arquivo >> u >> v >> w) {

//         if(w < 0) {
//             matrix[0][0] = -1;
//             // Essa parte coloca uma "flag" dentro de uma parte do grafo que não é utilizada: o vetor relacionado ao 0. Logo,
//             // se essa flag existir, o algoritmo de Dijkstra não será executada.


//             // tirar essa parte da flag provavelmente
//         }
//         matrix[u][v] = w;  

//         if(direcionado == false){
//             matrix[v][u] = w; 
//         }

//     }

//     arquivo.close();

//     return matrix;
// }

// //VER SE ESSA MATRIX É INT OU FLOAT(CONSIDERANDO DIJKSTRA C PESO FLOAT, CASO FAÇA COM QUE INTERLIGUE OS TRABALHOS)



// vector<vector<pair<int, int>>> txt_to_flow_network_matrix(const string& nome_arquivo, bool direcionado) {

//     ifstream arquivo(nome_arquivo);
//     if (!arquivo.is_open()) {
//         throw runtime_error("Erro ao abrir o arquivo de entrada!");
//     }

//     int numVertices, u, v, capacidade;
//     int fluxo = 0; // Fluxo inicial das arestas

//     // Lê o número de vértices
//     arquivo >> numVertices;

//     // Inicializa a matriz de adjacência com pares (capacidade, fluxo) zerados
//     vector<vector<pair<int, int>>> matrix(numVertices + 1, vector<pair<int, int>>(numVertices + 1, {0, 0}));

//     // Lê as arestas do arquivo
//     while (arquivo >> u >> v >> capacidade) {
//         // Define a capacidade da aresta e o fluxo inicial (0)
//         matrix[u][v] = {capacidade, fluxo};

//         // Se o grafo não for direcionado, adiciona a aresta inversa
//         if (direcionado == false) {
//             matrix[v][u] = {capacidade, fluxo};
//         }
//     }

//     arquivo.close();

//     return matrix;
// }

// //COLOCAR UM BOOLEANO AQUI TAMBEM REPRESENTANDO ORIGINAL E REVERSA PARA CASO DE 4 ARESTAS EM 2 VERTICES



// vector<vector<pair<int, pair<int, bool>>>> create_residual_graph_matrix(const vector<vector<pair<int, int>>>& matrix) {
//     int numVertices = matrix.size();

//     // Inicializa a matriz residual
//     vector<vector<pair<int, pair<int, bool>>>> residual_matrix(numVertices, vector<pair<int, pair<int, bool>>>(numVertices, {0, {0, false}}));

//     // Percorre toda a matriz de adjacência
//     for (int u = 0; u < numVertices; ++u) {
//         for (int v = 0; v < numVertices; ++v) {
//             int capacidade = matrix[u][v].first; // Capacidade da aresta original
//             int fluxo = matrix[u][v].second;     // Fluxo na aresta original

//             if (capacidade > 0) {
//                 // Atualiza aresta direta
//                 residual_matrix[u][v].first = capacidade - fluxo;  // Capacidade residual
//                 residual_matrix[u][v].second.first = true;         // Direção direta

//                 // Atualiza aresta reversa
//                 residual_matrix[v][u].first = fluxo;               // Capacidade residual reversa
//                 residual_matrix[v][u].second.first = false;        // Direção reversa
//             }
//         }
//     }

//     return residual_matrix;
// }

// // fazer um txt de resposta!

// int FordFulkerson_Matrix(vector<vector<pair<int, int>>> matrix, int s, int t) {

//     vector<vector<pair<int, pair<int, bool>>>> residual = create_residual_graph_matrix(matrix);
//     int numVertices = matrix.size();
//     vector<int> pai(numVertices);

//     int bottleneck;
//     while (bottleneck = Find_Bottleneck_Matrix(residual, s, t, pai) != 0) {

        







        

//     }







// }

// int Find_Bottleneck_Matrix(const vector<vector<pair<int, pair<int, bool>>>>& residual_matrix, int s, int t, vector<int>& pai) {
    
//     int INF = 1e9;
//     int numVertices = residual_matrix.size();
//     vector<bool> visitados(numVertices, false);

//     queue<int> fila;
//     visitados[s] = true;
//     pai.assign(numVertices, -1); // Reseta o vetor pai
//     fila.push(s);

//     // Realiza a BFS para encontrar o caminho de s até t
//     while (!fila.empty()) {
//         int atual = fila.front();
//         fila.pop();

//         for (int vizinho = 1; vizinho < numVertices; vizinho++) {
//             int capacidade = residual_matrix[atual][vizinho].first;

//             // Se o vizinho não foi visitado e a capacidade é maior que 0
//             if (!visitados[vizinho] && capacidade > 0) {
//                 pai[vizinho] = atual;
//                 visitados[vizinho] = true;
//                 fila.push(vizinho);

//                 // Para se alcançar o destino
//                 if (vizinho == t) break;
//             }
//         }
//     }

//     // Se não encontramos um caminho até t
//     if (!visitados[t]) {
//         return 0; // Não há caminho com capacidade positiva entre s e t
//     }

//     // Caminho encontrado: calcula o bottleneck (menor capacidade no caminho)
//     int bottleneck = INF;
//     int atual = t;

//     while (atual != s) {
//         int anterior = pai[atual];
//         bottleneck = min(bottleneck, residual_matrix[anterior][atual].first);
//         atual = anterior;
//     }

//     return bottleneck;
// }



// //VER SE VAI SER PARAMETRO OU A PROPRIA FUNCAO VAI CHAMAR AS OUTRAS

// void Update_Flow_Matrix(
//     vector<vector<pair<int, int>>>& matrix,           // Grafo original (matriz de adjacência com capacidades)
//     vector<vector<pair<int, pair<int, bool>>>>& residual_matrix, // Grafo residual (com capacidade e direção)
//     const vector<int>& pai,              // Caminho encontrado (vetor de pais)
//     int bottleneck,                      // Gargalo do caminho
//     bool direcionado                    // Se o grafo é direcionado ou não
// ) {
//     int atual = pai.back();  // Começa do destino
//     int s = pai.front();     // Origem do caminho

//     while (atual != s) {
//         int anterior = pai[atual];

//         // Atualiza o fluxo no grafo original (matriz de adjacência)
//         matrix[anterior][atual].second += bottleneck;  // Incrementa fluxo na aresta direta (segundo valor da pair)

//         // Atualiza o fluxo reverso no grafo original, se não for direcionado
//         if (!direcionado) {
//             matrix[atual][anterior].second -= bottleneck;  // Decrementa fluxo na aresta reversa
//         }

//         // Atualiza o grafo residual na aresta direta (matriz residual)
//         if (residual_matrix[anterior][atual].second.second == true) {  // Se a aresta é original (bool true)
//             residual_matrix[anterior][atual].first -= bottleneck;  // Diminui a capacidade residual
//         }

//         // Atualiza o grafo residual na aresta reversa
//         if (residual_matrix[atual][anterior].second.second == false) {  // Se a aresta é reversa (bool false)
//             residual_matrix[atual][anterior].first += bottleneck;  // Aumenta a capacidade residual reversa
//         }

//         // Move para o próximo vértice no caminho
//         atual = anterior;
//     }
// }



// void BFS(const vector<vector<int>>& graph, int origem){

//     int INF = 1e9;

//     vector<int> nivel(graph.size(), INF);
//     vector<int> pai(graph.size(), INF);
//     vector<bool> visitados(graph.size(), false);
//     queue <int> fila;

//     visitados[origem] = true;
//     nivel[origem] = 0;
//     pai[origem] = -1;
//     fila.push(origem);
//     while(!fila.empty()) {
//         int atual = fila.front();
//         fila.pop();
//         for(int vizinho : graph[atual]){

//             if(!visitados[vizinho]){
//                 fila.push(vizinho);
//                 visitados[vizinho] = true;
//                 nivel[vizinho] = nivel[atual] + 1;
//                 pai[vizinho] = atual;

//             }       
//         }       
//     }

// } 

