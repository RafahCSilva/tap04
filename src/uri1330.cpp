/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 4: URI 1330 - A Terra Herdada por Tio Tom
 * https://www.urionlinejudge.com.br/judge/pt/problems/view/1330
 *
 * Compile com C++ 17:
 *   g++ uri1330.cpp -o uri1330.exe -std=c++17
 *
 */

#include <iostream>
#include <vector>
#include <stdlib.h>

//#define V true
#define V false


int N = 0;  // # Linha: 1 <= N <= 100
int M = 0;  // # Coluna: 1 <= M <= 100
int K = 0;  // # Lagos: ((N x M) - K <= 50)
int X;  // Linha do lago: 1 <= X <= N
int Y;  // Coluna do Lago: 1 <= Y <= M
int **TERRENO;

#define t_LAGO -1
#define t_VAZIO 0
#define TOTAL (100 * 100)

std::vector< int > *GRAFO;
int *EMPARELHAMENTO;
bool *VISITADOS;

int coord2to1( int x, int y ) {
    return x * M + y;
}

int coord1to2_c( int x ) {
    return x % M;
}

int coord1to2_l( int x ) {
    return x / M;
}

bool aumentador( int u ) {
    for ( auto vizinho : GRAFO[ u ] ) {
        if ( VISITADOS[ vizinho ] )
            continue;
        VISITADOS[ vizinho ] = true;
        if ( EMPARELHAMENTO[ vizinho ] == -1 || aumentador( EMPARELHAMENTO[ vizinho ] ) ) {
            EMPARELHAMENTO[ vizinho ] = u;
            EMPARELHAMENTO[ u ] = vizinho;
            return true;
        }
    }
    return false;
}

int main() {

    GRAFO = new std::vector< int >[TOTAL];
    EMPARELHAMENTO = new int[TOTAL];
    VISITADOS = new bool[TOTAL];

    while ( true ) {
        // # Linhas e # Colunas
        std::cin >> N >> M;
        if ( N == 0 && M == 0 )
            return 0;

        // Monta o Terreno
        TERRENO = new int *[N];
        for ( int l = 0; l < N; ++l ) {
            TERRENO[ l ] = new int[M];
            for ( int c = 0; c < M; ++c )
                TERRENO[ l ][ c ] = t_VAZIO;
        }

        // Monta o Grafo vazio de N+M vertices
        for ( int i = 0; i < TOTAL; ++i )
            GRAFO[ i ].clear();

        // Monta o Emparelhamento  i = i
        for ( int i = 0; i < TOTAL; ++i )
            EMPARELHAMENTO[ i ] = i;

        // # de lagos
        std::cin >> K;
        for ( int i = 0; i < K; ++i ) {
            std::cin >> X >> Y;
            // add lago no terreno
            TERRENO[ X - 1 ][ Y - 1 ] = t_LAGO;
        }

        if ( V ) {
            std::cerr << "===============" << std::endl;
            std::cerr << "N Linhas:  " << N << std::endl;
            std::cerr << "M Colunas: " << M << std::endl;
            std::cerr << "K Lagos:   " << K << std::endl;
            std::cerr << "t_LAGO:   " << std::endl;
            for ( int l = 0; l < N; ++l ) {
                std::cerr << "  ";
                for ( int c = 0; c < M; ++c )
                    std::cerr << TERRENO[ l ][ c ] << "  ";
                std::cerr << std::endl;
            }
        }

        std::vector< int > PAR, IMPAR;
        for ( int l = 0; l < N; ++l ) {
            for ( int c = 0; c < M; ++c )
                if ( TERRENO[ l ][ c ] != t_LAGO ) {
                    int key = coord2to1( l, c );
//                    GRAFO[ key ].empty();
                    EMPARELHAMENTO[ key ] = -1;
                    if ( ( c + l ) % 2 )
                        IMPAR.push_back( key );
                    else
                        PAR.push_back( key );
                }
        }

        for ( int impar : IMPAR ) {
            for ( int par : PAR ) {
                int a = coord1to2_l( impar );
                int b = coord1to2_c( impar );
                int c = coord1to2_l( par );
                int d = coord1to2_c( par );
                if ( ( abs( a - c ) == 1 && b == d ) ||
                     ( abs( b - d ) == 1 && a == c ) ) {
                    GRAFO[ impar ].push_back( par );
                    GRAFO[ par ].push_back( impar );
                }
            }
        }

        int emp_max = 0;

        for ( int i = 0; i < ( N * M ); ++i ) {
            if ( EMPARELHAMENTO[ i ] == t_LAGO ) {
                for ( int i = 0; i < M; ++i )
                    VISITADOS[ i ] = false;
                if ( aumentador( i ) )
                    emp_max++;
            }
        }
        std::cout << emp_max << std::endl;

    }

    return 0;
}
