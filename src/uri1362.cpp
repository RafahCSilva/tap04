/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 4: URI 1362 - Minha Camiseta Me Serve
 * https://www.urionlinejudge.com.br/judge/pt/problems/view/1362
 *
 * Compile com C++ 17:
 *   g++ uri1362.cpp -o uri1362.exe -std=c++17
 *
 */

#include <iostream>
#include <vector>

//#define V true
#define V false

std::vector< int > *GRAFO;
int *EMPARELHAMENTO;

#define TAM 6
std::string TAMANHOS[TAM] = { "XXL", "XL", "L", "M", "S", "XS" };

int T = 0;  // # Casos de Testes
int N = 0;  // # Camisetas: Multiplo de 6, 1 <= N <= 36 : mesmo # de camiseta pra cada tamanho
int M = 0;  // # Voluntarios: 1 <= M <= 30 e N >= M
int N6 = 0; // # de Repeticoes das Camisetas: N6 = N / 6
std::string serve[2]; // Possiveis tamanhos q lhe serve

bool *VISITADOS;

bool DFS( int u ) {
    for ( auto vizinho : GRAFO[ u ] ) {
        if ( VISITADOS[ vizinho ] )
            continue;
        VISITADOS[ vizinho ] = true;
        if ( EMPARELHAMENTO[ vizinho ] == vizinho || DFS( EMPARELHAMENTO[ vizinho ] ) ) {
            EMPARELHAMENTO[ vizinho ] = u;
            return true;
        }
    }
    return false;
}

bool emparelhamento_max() {
    VISITADOS = new bool[M];
    for ( int pessoa = 0; pessoa < M; ++pessoa ) {
        for ( int i = 0; i < M; ++i )
            VISITADOS[ i ] = false;
        if ( !DFS( pessoa ) )
            return false;
    }

    return true;
}

int main() {

    std::cin >> T;
    for ( int caso = 0; caso < T; ++caso ) {
        std::cin >> N >> M;
        N6 = N / 6;

        if ( V ) {
            std::cerr << "Caso " << ( caso + 1 ) << "/" << T << ": " << std::endl;
            std::cerr << "  N Camisetas: " << N << std::endl;
            std::cerr << "  M Voluntarios: " << M << std::endl;
            std::cerr << "  N6 repeticoes: " << N6 << std::endl;
        }

        // Monta o grafo vazio de N+M vertices
        GRAFO = new std::vector< int >[M];
//        std::vector< int > GRAFO[M];
//        GRAFO = GRAFO;

        // Emparelhamento  i = i
        EMPARELHAMENTO = new int[N + M];
//        int EMPARELHAMENTO[N + M];
//        EMPARELHAMENTO = EMPARELHAMENTO;
        for ( int i = 0; i < ( N + M ); ++i )
            EMPARELHAMENTO[ i ] = i;

        // Conectar pessoas com as camisetas
        // Para cada Pessoa
        for ( int m = 0; m < M; ++m ) {
            // Suas possiveis camisetas

            std::cin >> serve[ 0 ] >> serve[ 1 ];
            if ( V ) std::cout << m << ": " << serve[ 0 ] << " " << serve[ 1 ] << std::endl;

            for ( int s = 0; s < 2; ++s )

                // Verificar todos os matchs
                for ( int t = 0; t < TAM; ++t ) {
                    if ( !serve[ s ].compare( TAMANHOS[ t ] ) )

                        // liga as pessoas com todas as possiveis camisetas
                        for ( int possib = 0; possib < N6; ++possib )
                            GRAFO[ m ].push_back( t + M + ( possib * 6 ) );
                }
        }

        if ( V ) {
            std::cerr << "  Grafo: " << std::endl;
            for ( int g = 0; g < M; ++g ) {
                std::cerr << "    " << g << ": ";
                for ( auto i : GRAFO[ g ] )
                    std::cerr << i << "[" << TAMANHOS[ ( i - M ) % 6 ] << "], ";
                std::cerr << std::endl;
            }
        }

        if ( emparelhamento_max() )
            std::cout << "YES" << std::endl;
        else
            std::cout << "NO" << std::endl;

//        delete[] GRAFO;
//        delete EMPARELHAMENTO;
    }

    return 0;
}

