/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 4: URI 1056 - Fatores e Múltiplos
 * https://www.urionlinejudge.com.br/judge/pt/problems/view/1056
 *
 * Compile com C++ 11:
 *   g++ uri1056.cpp -o uri1056.exe -std=c++11
 *
 */

#include <iostream>
#include <vector>

//#define V true
#define V false

#define LIMITE 100 // N e M estarão no intervalo [1,100]
int nTestes;    // # de testes (1 <= t < 50)
int N;          // # de A
int A[LIMITE];  // conj A
int M;          // # de B
int B[LIMITE];  // conj B

std::vector<int> *GRAFO;
int *EMPARELHAMENTO;
bool *VISITADOS;

bool aumentador( int u ) {
    for ( int vizinho : GRAFO[ u ] ) {
        if ( VISITADOS[ vizinho ] )
            continue;
        VISITADOS[ vizinho ] = true;
        if ( EMPARELHAMENTO[ vizinho ] == -1 ||
             aumentador( EMPARELHAMENTO[ vizinho ] )) {
            EMPARELHAMENTO[ vizinho ] = u;
            EMPARELHAMENTO[ u ] = vizinho;
            return true;
        }
    }
    return false;
}

int main() {
    // Cada Caso de Teste
    std::cin >> nTestes;
    for ( int teste = 1; teste <= nTestes; ++teste ) {
        // Le a entrada de A
        std::cin >> N;
        for ( int n = 0; n < N; ++n )
            std::cin >> A[ n ];

        // Le a entrada de B
        std::cin >> M;
        for ( int m = 0; m < M; ++m )
            std::cin >> B[ m ];

        // Inicializa os vetores
        GRAFO = new std::vector<int>[N + M];
        EMPARELHAMENTO = new int[N + M];
        for ( int k = 0; k < ( N + M ); ++k )
            EMPARELHAMENTO[ k ] = -1;

        // Para cada elemento de A
        for ( int i = 0; i < N; ++i )
            // Para cada elemento de B
            for ( int j = 0; j < M; ++j )
                // Verifica se deve ligar os vertices
                if (( A[ i ] == 0 && B[ j ] == 0 ) || // Se Ai==0 e Bj==0
                    ( B[ j ] == 0 ) ||                // OU somente Bj==0
                    ( A[ i ] != 0 ) && ( B[ j ] % A[ i ] == 0 )) {       // OU Ai!=0 E Bj eh multiplo de Ai
                    // entao dupla ligacao no grafo de i <=> j+N
                    GRAFO[ i ].push_back( j + N );
                    GRAFO[ j + N ].push_back( i );
                }

        // DEBUG da montagem do Grafo
        if ( V ) {
            std::cout << "A: ";
            for ( int n = 0; n < N; ++n )
                std::cout << A[ n ] << " ";
            std::cout << std::endl;

            std::cout << "B: ";
            for ( int m = 0; m < M; ++m )
                std::cout << B[ m ] << " ";
            std::cout << std::endl;

            std::cout << "GRAFO:" << std::endl;
            for ( int u = 0; u < N + M; ++u ) {
                std::cout << " " << u
                          << " ["
                          << ( u < N ? A[ u ] : B[ u - N ] )
                          << "]: ";
                for ( int v : GRAFO[ u ] ) {
                    std::cout << v
                              << " ["
                              << ( v < N ? A[ v ] : B[ v - N ] )
                              << "] ";
                }
                std::cout << std::endl;
            }
        }

        // Encontrar o emparelhamento maximo
        int emp_max = 0;
        // Para cada elemento de A
        for ( int i = 0; i < N; ++i )
            // se ainda nao emparelhou
            if ( EMPARELHAMENTO[ i ] == -1 ) {
                // inicializa os Visitados
                VISITADOS = new bool[N + M];
                for ( int v = 0; v < ( N + M ); ++v )
                    VISITADOS[ v ] = false;

                // Ha caminha aumentador?
                if ( aumentador( i ))
                    emp_max++;
            }
        // Resultado
        std::cout << "Case " << teste << ": " << emp_max << std::endl;
    }

    return 0;
}
