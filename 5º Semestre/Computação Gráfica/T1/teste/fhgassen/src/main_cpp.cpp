/*********************************************************************
// Trabalho 1 da disciplina de Computação Gráfica
//  Autor: Frederico Hansel dos Santos Gassen
//         18/04/2019
//
//  Esse arquivo é a main executável do trabalho 1
// *********************************************************************/


#include <GL/glut.h>
#include <GL/freeglut_ext.h> //callback da wheel do mouse.

#include <time.h>
#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#include <vector>
#include <cmath>
#include <iostream>
#include <string>

#include "gl_canvas2d.h"
#include "Graph.hpp"
#include "Button.hpp"
#include "Structs.hpp"

using namespace std;

#define NUMERO_AMOSTRAS 64 // número de amostras a ser criado no arquivo de criação
#define CRIAR_ARQUIVO FALSE // bool pra saber se é pra criar um arquivo novo ou não
#define DIM_X 1280 // largura da tela
#define DIM_Y 640 // altura da tela

vector<int> amostras; // amostras lidas
vector<float> amostrasFloat; // amostras convertidas pra float
vector<float> vetorDCT;
vector<float> vetorIDCT;
vector<float> vetorDiff;
vector<int> vetorQuantizacoes; // vetor de quantizações

vector<Button*> buttonsScreen; // botões da tela

bool quantized = false;
bool showIDCT = false;
bool showDiff = false;

//as 4 instâncias dos gráficos da tela
Graph* gInput = nullptr;
Graph* gDCT = nullptr;
Graph* gIDCT = nullptr;
Graph* gDiff = nullptr;

void calculaDCT(); // função que calcula DCT
void calculaIDCT(); // função que calcula a inversa da DCT
void calculaDiff(); // função que calcula a diferença entre a IDCT e o input
float calculaCoeficiente(int k, int num_amostras); // função que calcula o coeficiente usado nos cálculos da DCT e IDCT
void plotGraph(Graph* g); // função que plota um gráfico passado por parâmetro
void plotButtons(); // função que plota os botões
int valueInVerticalMark(int i, Graph* g); // função que calcula o valor nas marcas do eixo y do gráfico
void plotGraphs(); // função que plota todos os gráficos que não são nullptr
int criaArquivo(bool input, bool output); // função que cria o arquivo, com parâmetros indicando se é arquivo de entrada ou saída
void detectClickButton(int x, int y); // função que detecta se houve clique de botões
void buttonClicked(int i); // função que ativa a função de clique do botão com índice i
void addButtons(); // função que cria os botões na tela
void configuracoesIniciais(); // função que configura as coisas iniciais
void instanciaVetorQuantizacoes();
void leArquivo(); // função que lê o arquivo

void calculaDCT()
{
    vetorDCT.clear();
    for (int k=0; k<amostras.size(); k++)
    {
        float produtoTmp = calculaCoeficiente(k, amostras.size());
        float somaTmp = 0;
        for (int n=0; n<amostras.size(); n++)
        {
            somaTmp += (amostras[n] * cos((PI*k*(2*n+1))/(2*amostras.size())));
        }
        produtoTmp *= somaTmp;
        if (quantized){
            vetorDCT.push_back(produtoTmp/vetorQuantizacoes[k]);
        } else {
            vetorDCT.push_back(produtoTmp);
            printf("\nDCT[%d] %f", k, vetorDCT[k]);
        }
    }
}

void calculaIDCT()
{
    vetorIDCT.clear();
    if (quantized){
        for (int k=0;k<vetorDCT.size();k++){
            vetorDCT[k] = vetorDCT[k] * vetorQuantizacoes[k];
        }
    }
    for (int k=0; k<vetorDCT.size(); k++)
    {
        float somaTmp = 0;
        for (int n=0; n<vetorDCT.size(); n++)
        {
            somaTmp += (calculaCoeficiente(n, vetorDCT.size()) * vetorDCT[n] * cos((PI*n*(2*k+1))/(2*vetorDCT.size())));
        }
        vetorIDCT.push_back(somaTmp);
        printf("\nIDCT[%d] %f", k, vetorIDCT[k]);
    }
}

void calculaDiff()
{
    vetorDiff.clear();
    for (int k=0; k<amostrasFloat.size(); k++)
    {
        vetorDiff.push_back(amostrasFloat[k]-vetorIDCT[k]);
    }
}

float calculaCoeficiente(int k, int num_amostras)
{
    return ( k==0 ? sqrt((float)1/num_amostras) : sqrt((float)2/num_amostras) );
}

void plotGraph(Graph* g)
{
    color(0, 0, 0);
    rect(g->border.p1.x, g->border.p1.y, g->border.p2.x, g->border.p2.y);
    line(g->axis_x.p1.x, g->axis_x.p1.y, g->axis_x.p2.x, g->axis_x.p2.y);
    line(g->axis_y.p1.x, g->axis_y.p1.y, g->axis_y.p2.x, g->axis_y.p2.y);
    text(g->title_locate.x, g->title_locate.y, g->m_title.c_str());
    for (int i=0; i<g->m_input.size(); i++)
    {
        line(g->marks[i].p1.x, g->marks[i].p1.y, g->marks[i].p2.x, g->marks[i].p2.y);
        if (i%5==0)
        {
            text(g->marks[i].p2.x-5, g->marks[i].p2.y-15, to_string(i).c_str());
        }
    }

    for (int i=0; i<g->marks_vertical.size(); i++)
    {
        line(g->marks_vertical[i].p1.x, g->marks_vertical[i].p1.y, g->marks_vertical[i].p2.x, g->marks_vertical[i].p2.y);
        text(g->marks_vertical[i].p1.x-35, g->marks_vertical[i].p2.y-5, to_string(valueInVerticalMark(i, g)).c_str());
    }

    color(1, 0, 0);
    for (int i=0; i<g->m_input.size(); i++)
    {
        circleFill(g->input_points[i].x, g->input_points[i].y, 3, 30);
        if (i>0)
        {
            line(g->input_points[i].x, g->input_points[i].y, g->input_points[i-1].x, g->input_points[i-1].y);
        }
    }
}

void plotButtons()
{
    color(0, 0, 1);
    for (int i=0; i<buttonsScreen.size(); i++)
    {
        rectFill(buttonsScreen[i]->m_design.p1.x, buttonsScreen[i]->m_design.p1.y, buttonsScreen[i]->m_design.p2.x, buttonsScreen[i]->m_design.p2.y);
    }
    color(1, 1, 1);
    for (int i=0; i<buttonsScreen.size(); i++)
    {
        text(buttonsScreen[i]->m_design.p1.x+5, buttonsScreen[i]->m_design.p1.y+5, buttonsScreen[i]->m_text.c_str());
    }
}

int valueInVerticalMark(int i, Graph* g)
{
    return ((int)((g->maiorInputInModule - i*(g->maiorInputInModule/(g->marks_vertical.size()/2)))/-1));
}

void plotGraphs()
{
    if (gInput != nullptr)
    {
        plotGraph(gInput);
    }
    if (gDCT != nullptr)
    {
        plotGraph(gDCT);
    }
    if (gIDCT != nullptr && showIDCT)
    {
        plotGraph(gIDCT);
    }
    if (gDiff != nullptr && showDiff)
    {
        plotGraph(gDiff);
    }
}

void render()
{
    plotGraphs();
    plotButtons();
}

void keyboard(int key)
{
    if (key==27)
    {
        exit(0);
    }
}

void keyboardUp(int key)
{

}

void mouse(int button, int state, int wheel, int direction, int x, int y)
{
    if (button == 0 && state == 0)
    {
        detectClickButton(x, altura-y);
    }
}

int criaArquivo(bool input, bool output)
{
    if (input)
    {
        FILE* arq = fopen("input.dct", "wb");
        if(arq == NULL)
        {
            printf("Erro na abertura do arquivo!");
            return 1;
        }
        int num_amostras = NUMERO_AMOSTRAS;

        fwrite(&num_amostras, sizeof(int), 1, arq);

        for (int i=0; i<num_amostras; i++)
        {
            char c = (char) (rand()%256)-128;
            fwrite(&c, sizeof(char), 1, arq);
        }

        fclose(arq);
    }
    else if (output)
    {
        FILE* arq = fopen("output.dct", "wb");
        if(arq == NULL)
        {
            printf("Erro na abertura do arquivo!");
            return 1;
        }
        int num_amostras = vetorIDCT.size();

        fwrite(&num_amostras, sizeof(int), 1, arq);

        for (int i=0; i<num_amostras; i++)
        {
            char c = (char) (round(vetorIDCT[i]));
            fwrite(&c, sizeof(char), 1, arq);
        }

        fclose(arq);
    }
    return 0;
}

void detectClickButton(int x, int y)
{
    for (int i=0; i<buttonsScreen.size(); i++)
    {
        if (x>=buttonsScreen[i]->m_design.p1.x && x<=buttonsScreen[i]->m_design.p2.x && y>=buttonsScreen[i]->m_design.p1.y && y<=buttonsScreen[i]->m_design.p2.y)
        {
            buttonClicked(i);
        }
    }
}

void buttonClicked(int i)
{
    switch (i)
    {
        case 0:
        leArquivo();
        gInput = new Graph("Input", {10.0, 40.0}, amostrasFloat);
        break;

        case 1:
        if (gInput != nullptr)
        {
            quantized = false;
            calculaDCT();
            gDCT = new Graph("DCT", {10.0, gInput->m_source.y+gInput->dimension_y + 50}, vetorDCT);
            calculaIDCT();
            gIDCT = new Graph("IDCT", {10.0 + gDCT->dimension_x + 50, gDCT->m_source.y}, vetorIDCT);
            calculaDiff();
            gDiff = new Graph("Diff", {10.0 + gInput->dimension_x + 50, gInput->m_source.y}, vetorDiff);
        }
        break;

        case 2:
        if (gInput != nullptr)
        {
            quantized = true;
            calculaDCT();
            gDCT = new Graph("DCT quantized", {10.0, gInput->m_source.y+gInput->dimension_y + 50}, vetorDCT);
            calculaIDCT();
            gIDCT = new Graph("IDCT desquantized", {10.0 + gDCT->dimension_x + 50, gDCT->m_source.y}, vetorIDCT);
            calculaDiff();
            gDiff = new Graph("Diff", {10.0 + gInput->dimension_x + 50, gInput->m_source.y}, vetorDiff);
        }
        break;

        case 3:
        if (gDCT != nullptr)
        {
            showIDCT = true;
        }
        break;

        case 4:
        if (gIDCT != nullptr)
        {
            showDiff = true;
        }
        break;

        case 5:
        if (gIDCT != nullptr)
        {
            criaArquivo(false, true);
        }
        break;
    }
}

void addButtons()
{
    buttonsScreen.push_back(new Button("Load input", {10, 10}));
    buttonsScreen.push_back(new Button("Calculate DCT", {buttonsScreen.back()->m_design.p2.x+10, 10}));
    buttonsScreen.push_back(new Button("Calculate DCT quantized", {buttonsScreen.back()->m_design.p2.x+10, 10}));
    buttonsScreen.push_back(new Button("Calculate IDCT", {buttonsScreen.back()->m_design.p2.x+10, 10}));
    buttonsScreen.push_back(new Button("Calculate Diff", {buttonsScreen.back()->m_design.p2.x+10, 10}));
    buttonsScreen.push_back(new Button("Save output.dct", {buttonsScreen.back()->m_design.p2.x+10, 10}));
}

void configuracoesIniciais()
{
    srand(time(NULL));

    if (CRIAR_ARQUIVO)
    {
        if (criaArquivo(true, false))
        {
            exit(0);
        }
    }

    addButtons();

    instanciaVetorQuantizacoes();
}

void instanciaVetorQuantizacoes()
{
    vector<int> vect{3, 5, 7, 9, 11, 13, 15, 17, 5, 7, 9,
        11, 13, 15, 17, 19, 7, 9, 11, 13, 15, 17, 19, 21,
        9, 11, 13, 15, 17, 19, 21, 23, 11, 13, 15, 17, 19,
        21, 23, 25, 13, 15, 17, 19, 21, 23, 25, 27, 15, 17,
        19, 21, 23, 25, 27, 29, 17, 19, 21, 23, 25, 27, 29, 31};
        vetorQuantizacoes = vect;
    }

    void leArquivo()
    {
        amostras.clear();
        amostrasFloat.clear();
        FILE* arq = fopen("input.dct", "rb");
        if(arq == NULL)
        {
            printf("Erro na abertura do arquivo!");
            exit(0);
        }

        int num_amostras = -1;
        fread(&num_amostras, sizeof(int), 1, arq);
        for (int i=0; i<num_amostras; i++)
        {
            char amostra;
            fread(&amostra, sizeof(char), 1, arq);
            amostras.push_back((int)amostra);
            amostrasFloat.push_back((float)((int)amostra));
        }
    }

    int main(void)
    {
        initCanvas(DIM_X, DIM_Y, "Trabalho 1 - Frederico H. dos S. Gassen");

        configuracoesIniciais();

        runCanvas();
    }
