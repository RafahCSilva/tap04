/**
 * @author Rafael Cardoso da Silva 21048012
 * Tecnicas Avancadas de Programacao – 2018.Q1
 * Projeto 5: URI 1331 - Blocos
 * https://www.urionlinejudge.com.br/judge/pt/problems/view/1331
 *
 * Compile com C++ 11:
 *   g++ uri1331.cpp -o uri1331.exe -std=c++11
 *
 */

#include <iostream>
#include <cstdio>

//#define V true
#define V false

#define LIMITE 205

int nTestes;    // # de testes (1 <= t <= 15)
int nCaixas;  // # de caixa (1 <= n <= 200)

int BLOCOS[LIMITE];                     // Blocos do Jogo
int PD[LIMITE][LIMITE][LIMITE];         // Memorizacao da PD
bool VISITADOS[LIMITE][LIMITE][LIMITE]; // Visitados / ja memorizados

/**
 * Retorna a melhor solucao encontrada para a instancia passada nos parametros.
 *
 * @param inicio    inicio do bloco
 * @param fim       fim do bloco
 * @param pontos    acumulado dos pontos
 * @return
 */
int melhor_solucao( const int inicio, const int fim, const int pontos ) {
  if ( V )
    printf( ">> %d %d %d v%d p%d\n", inicio, fim, pontos,
            VISITADOS[ inicio ][ fim ][ pontos ],
            PD[ inicio ][ fim ][ pontos ] );

  // passou, entao nao ganha nada
  if ( inicio > fim )
    return 0;

  // ramo da arvore de recursao já foi calculado, entao retorna o memorizado
  if ( VISITADOS[ inicio ][ fim ][ pontos ] )
    return PD[ inicio ][ fim ][ pontos ];

  // pontuacao acumulada da primeira possibilidade de segmento
  int M = ( pontos * pontos ) + melhor_solucao( inicio + 1, fim, 1 );

  // para cada possibilidade de segmento a ser escolhido
  for ( int i = inicio + 1; i <= fim; ++i )
    // se eh o mesmo segmento
    if ( BLOCOS[ i ] == BLOCOS[ inicio ] )
      // maior pontuacao para os possiveis subsegmentos:
      M = std::max(
          // OU anterior
          M,
          // OU segmento [inicio+1 .. i-1] + segmento [i .. fim]
          ( melhor_solucao( inicio + 1, i - 1, 1 ) +
            melhor_solucao( i, fim, pontos + 1 )));

  // visitado e salva a melhor solucao
  VISITADOS[ inicio ][ fim ][ pontos ] = true;
  PD[ inicio ][ fim ][ pontos ] = M;

  return M;
}

int main() {

  // inicializa PD
  for ( int i = 0; i < LIMITE; ++i )
    for ( int j = 0; j < LIMITE; ++j )
      for ( int k = 0; k < LIMITE; ++k )
        PD[ i ][ j ][ k ] = 0;

  // Cada Caso de Teste
  std::cin >> nTestes;
  for ( int teste = 1; teste <= nTestes; ++teste ) {
    // Le a entrada de caixas
    std::cin >> nCaixas;
    for ( int bloco = 0; bloco < nCaixas; ++bloco )
      std::cin >> BLOCOS[ bloco ];

    // inicializa VISITADOS
    for ( int i = 0; i < LIMITE; ++i )
      for ( int j = 0; j < LIMITE; ++j )
        for ( int k = 0; k < LIMITE; ++k )
          VISITADOS[ i ][ j ][ k ] = false;

    // Resolvem para todas as caixas qual a melhor solucao
    int solucao = melhor_solucao( 0, nCaixas - 1, 1 );
    std::cout << "Case " << teste << ": " << solucao << std::endl;
  }

  return 0;
}
