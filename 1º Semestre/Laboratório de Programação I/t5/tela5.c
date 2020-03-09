//
// tela5.c
// =======
//
// implementação de acesso à tela gráfica (usando allegro)
//
// para uso na disciplina de Laboratório de Programação I, 2017a
//


#include "tela5.h"
#include <stdio.h>

// Os includes do allegro
#include <allegro5/allegro.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

// fila para receber os eventos do teclado
ALLEGRO_EVENT_QUEUE *tela_eventos_teclado;
void tela_inicializa_teclado(void)
{
  al_install_keyboard();
  // cria e inicializa a fila de eventos do teclado
  tela_eventos_teclado = al_create_event_queue();
  al_register_event_source(tela_eventos_teclado,
                           al_get_keyboard_event_source());
}

void tela_inicializa_janela(tamanho tam)
{
  // cria uma janela
  ALLEGRO_DISPLAY *janela;
  janela = al_create_display(tam.l, tam.h);
  // esconde o cursor do mouse
  al_hide_mouse_cursor(janela);
}

// vetor com as cores
#define MAX_CORES 57
int ncores = 0;
ALLEGRO_COLOR cores[MAX_CORES];

cor tela_cria_cor(float vm, float vd, float az)
{
  if (ncores >= MAX_CORES) ncores = MAX_CORES-1;
  cores[ncores] = al_map_rgb_f(vm, vd, az);
  return ncores++;
}

void tela_muda_cor(cor c, float vm, float vd, float az)
{
  if (c > 0 && c < ncores) {
    cores[c] = al_map_rgb_f(vm, vd, az);
  }
}

void tela_inicializa_cores(void)
{
  transparente = 0;
  cores[transparente] = al_map_rgba_f(0, 0, 0, 0);
  ncores = 1;
  azul = tela_cria_cor(0, 0, 1);
  vermelho = tela_cria_cor(1, 0, 0);
  verde = tela_cria_cor(0, 1, 0);
  amarelo = tela_cria_cor(1, 1, 0);
  preto = tela_cria_cor(0, 0, 0);
  laranja = tela_cria_cor(1, 0.65, 0);
  rosa = tela_cria_cor(1, 0, 0.5);
  branco = tela_cria_cor(1, 1, 1);
  marrom = tela_cria_cor(0.58, 0.29, 0);
}


void tela_inicio(tamanho tam)
{
  // inicializa os subsistemas do allegro
  al_init();
  al_install_mouse();
  al_init_primitives_addon();
  al_init_font_addon();
  al_init_ttf_addon();

  // inicializa a tela
  tela_inicializa_janela(tam);
  tela_inicializa_teclado();
  tela_inicializa_cores();
}


void tela_fim(void)
{
  al_uninstall_system();
}

void tela_atualiza(void)
{
  al_flip_display();
}

double tela_agora(void)
{
  return al_get_time();
}

void tela_limpa(void)
{
  al_clear_to_color(cores[preto]);
}

void tela_circulo(circulo c, float l, cor corl, cor corint)
{
  al_draw_filled_circle(c.centro.x, c.centro.y, c.raio, cores[corint]);
  al_draw_circle(c.centro.x, c.centro.y, c.raio, cores[corl], l);
}

void tela_linha(ponto p1, ponto p2, float l, cor corl)
{
  al_draw_line(p1.x, p1.y, p2.x, p2.y, cores[corl], l);
}

void tela_retangulo(retangulo r, float l, cor corl, cor corint)
{
  al_draw_filled_rectangle(r.origem.x, r.origem.y,
                           r.origem.x+r.tam.l, r.origem.y+r.tam.h,
                           cores[corint]);
  al_draw_rectangle(r.origem.x, r.origem.y,
                    r.origem.x+r.tam.l, r.origem.y+r.tam.h,
                    cores[corl], l);
}

// tem que ter uma fonte para poder escrever
ALLEGRO_FONT *fonte = NULL;
int tamanho_das_letras = 0;

void tela_prepara_fonte(int tam)
{
  // se se quer o mesmo tamanho que antes, usa a mesma
  if (tam == tamanho_das_letras) return;

  // se ja tinha uma fonte carregada, livra-se dela antes de carregar outra
  if (fonte != NULL) {
    al_destroy_font(fonte);
  }

  // carrega uma fonte, para poder escrever na tela
  fonte = al_load_font("DejaVuSans.ttf", tam, 0);
  if (fonte == NULL) {
    printf("FONTE NAO ENCONTRADO.\n"
           "MUDE O PROGRAMA PARA APONTAR PARA UM ARQUIVO QUE EXISTA.\n");
    al_uninstall_system();
    exit(1);
  }
  tamanho_das_letras = tam;
}

void tela_texto(ponto p, int tam, cor c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], p.x, p.y-tam/2, ALLEGRO_ALIGN_CENTRE, t);
}

void tela_texto_esq(ponto p, int tam, cor c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], p.x, p.y, ALLEGRO_ALIGN_RIGHT, t);
}

void tela_texto_dir(ponto p, int tam, cor c, char t[])
{
  tela_prepara_fonte(tam);
  al_draw_text(fonte, cores[c], p.x, p.y, ALLEGRO_ALIGN_LEFT, t);
}

ponto tela_pos_rato(void)
{
  ponto p;
  ALLEGRO_MOUSE_STATE rato;
  al_get_mouse_state(&rato);
  p.x = al_get_mouse_state_axis(&rato, 0);
  p.y = al_get_mouse_state_axis(&rato, 1);
  return p;
}

bool tela_rato_apertado(void)
{
  ALLEGRO_MOUSE_STATE rato;
  al_get_mouse_state(&rato);
  // só nos interessa o botão da esquerda
  return al_mouse_button_down(&rato, 1);
}

char tela_le_tecla(void)
{
  ALLEGRO_EVENT ev;

  while (al_get_next_event(tela_eventos_teclado, &ev)) {
    if (ev.type == ALLEGRO_EVENT_KEY_CHAR) {
      int c = ev.keyboard.unichar;
      if (c == '\r') c = '\n'; // corrige windowscentrismo
      // só retorna caracteres imprimíveis, backspace e enter
      if ((c >= ' ' && c <= '~') || c == '\b' || c == '\n') {
        return (char) c;
      }
    }
  }
  // nada foi pressionado (ou foi pressionado algo não imprimível)
  return '\0';
}
