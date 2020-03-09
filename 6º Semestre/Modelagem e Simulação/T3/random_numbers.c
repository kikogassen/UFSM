#include <stdio.h>
#include <stdlib.h>
#include <time.h>

FILE* cria_arquivo (char* nome_arq){  // Função que cria o arquivo.
  FILE* arq = fopen(nome_arq, "a");
  return arq;
}

float* gera_cheg (float max, int* tam_main, int var_min, int var_max){ // Função que gera a diferença entre
  int tam = 1;                                                         // as chegadas dos clientes.
  float soma = 0, num_at = 0;
  float* vetor = (float*) malloc (sizeof(float));
  while (soma <= max){ // Limite de clientes, definido pelo horário.
    realloc(vetor, sizeof(float) * tam); // Como não há certeza da quantidade de clientes, usa-se realloc.
    num_at = (float)rand()/RAND_MAX*var_max + var_min; // Inicialmente, é gerado um valor entre 0.0 e 1.0 e depois
                                                       // multiplica-se pelo valor máximo e adiciona o mínimo.
                                                       // A variável contém o número aleatório gerado.
    vetor[tam-1] = num_at;
    tam++;
    soma = soma + num_at;  // Adiciona ao limite
  }
  *tam_main = tam - 1; // Atribui o tamanho do vetor à variável tamanho
  return vetor;
}

float* gera_trans (int tam, int var_min, int var_max){ // Função que gera a quantidade de tempo de atendimento
  int i;
  float* vetor = (float*) malloc (sizeof(float) * tam);
  for (i = 0; i < tam; i++){
    vetor[i] = (float)rand()/RAND_MAX*var_max + var_min;
  }
  return vetor;
}

void preenche_num(FILE* arq, float* num, int tam){ // Preenche o arquivo com os números gerados
  int i = 0, j = 0;
  for (j = 0; j < tam; j++){
    fprintf (arq, "%.3f ", num[i]);
    if (i % 5 == 4){  // Quebra de linha ao colocar 5 números.
      fprintf (arq, "\n");
    }
    i++;
  }
}

void main(){            // Na main, os valores são atribuidos e os arquivos criados.
  srand(time(NULL));
  int tam;
  FILE* arq = cria_arquivo("caixas_cheg.txt");
  float* num = gera_cheg(11*60, &tam, 0, 7); // Também são definidas as limitações, mínimas e máximas, de cada arquivo.
  preenche_num(arq, num, tam);              // Entende-se por limitações o valor min/max que os números gerados terão.

  arq = cria_arquivo("caixas_trans.txt");
  num = gera_trans(tam + 1, 1, 6);
  preenche_num(arq, num, tam + 1);

  arq = cria_arquivo("maq_cheg.txt");
  num = gera_cheg(24*60, &tam, 0, 10);
  preenche_num(arq, num, tam);

  arq = cria_arquivo("maq_trans.txt");
  num = gera_trans(tam + 1, 1, 5);
  preenche_num(arq, num, tam + 1);

  arq = cria_arquivo("drive_cheg.txt");
  num = gera_cheg(11*60, &tam, 0, 12);
  preenche_num(arq, num, tam);

  arq = cria_arquivo("drive_trans.txt");
  num = gera_trans(tam + 1, 1, 7);
  preenche_num(arq, num, tam + 1);

  return;
}
