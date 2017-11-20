#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <allegro5/allegro.h>
#include <allegro5/allegro_native_dialog.h>
#include <allegro5/allegro_ttf.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_primitives.h>
#define TAMANHO_MAX 100
// Funções
void GerarAleatorio(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam);
void ExibirMatriz (int matriz[TAMANHO_MAX][TAMANHO_MAX], int tam, int color);
void RodarGeracoesImprimir(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int nvezes, int tam);
void AbrirArquivoGeracao(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam);
void SalvarArquivo(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam);
void LimparCampos(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int matriz3[TAMANHO_MAX][TAMANHO_MAX], int matriz4[TAMANHO_MAX][TAMANHO_MAX], int tam);

int main(){
    int screen=0, exit=0, draw=1, tinit=1;
    int speed=2, color=0;
    int i, j, k=0, tamanho=TAMANHO_MAX, n_geracoes=7, nsalvar=0;
    int red, blue, green;
    char r, g, b;
    int m1[TAMANHO_MAX][TAMANHO_MAX], m2[TAMANHO_MAX][TAMANHO_MAX], m3[TAMANHO_MAX][TAMANHO_MAX], m4[TAMANHO_MAX][TAMANHO_MAX];
    int x, y;
    ALLEGRO_DISPLAY *display;
    if (!al_init()){
        al_show_native_message_box(NULL,NULL,NULL,"Nao foi possivel inicializar",NULL,NULL);
    }
    display=al_create_display(500, 575);
    if(!display){
        al_show_native_message_box(display,NULL,"Erro","Display nao foi criado",NULL,NULL);
    }
    al_set_window_title(display,"Game of Life");
    al_init_font_addon();
    al_init_ttf_addon();
    al_init_primitives_addon();
    al_install_mouse();
    ALLEGRO_FONT *font1=al_load_font("verdana.ttf", 130, NULL);
    ALLEGRO_FONT *font2=al_load_font("verdana.ttf", 30, NULL);
    ALLEGRO_EVENT_QUEUE *event_queue = al_create_event_queue();
    al_register_event_source(event_queue, al_get_mouse_event_source());
    ALLEGRO_TIMER *timer;
    ALLEGRO_EVENT events;
    LimparCampos(m1,m2,m3,m4,tamanho);
    GerarAleatorio(m1,m2,tamanho);
    do{
        al_wait_for_event(event_queue, &events);
        if(events.type==ALLEGRO_EVENT_MOUSE_AXES){
            x=events.mouse.x;
            y=events.mouse.y;
            /*MENU:*/
            if(screen==0){
                if(x>0&&x<165&&y>475&&y<525){
                    al_draw_filled_rectangle(50,475,165,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),107, 481, 1, "START");
                }
                else if (x>192&&x<307&&y>475&&y<525){
                    al_draw_filled_rectangle(192,475,307,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 481, 1, "MENU");
                }
                else if (x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "EXIT");
                }
                else{
                    al_draw_filled_rectangle(40,470,460,530,al_map_rgb(0,0,0));
                    al_draw_rectangle(50,475,165,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),107, 481, 1, "START");
                    al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "MENU");
                    al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "EXIT");
                    }}
            /*OPCOES DE JOGO:*/
            else if (screen==1){
                if (x>192&&x<307&&y>150&&y<200){
                    al_draw_filled_rectangle(192,150,307,200,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 156, 1, "PLAY");
                }
                else if (x>192&&x<307&&y>225&&y<275){
                    al_draw_filled_rectangle(192,225,307,275,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 231, 1, "EDIT");
                }
                else if (x>192&&x<307&&y>300&&y<350){
                    al_draw_filled_rectangle(192,300,307,350,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 306, 1, "LOAD");
                }
                else if (x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "BACK");
                }
                else{
                    al_draw_filled_rectangle(190,140,310,350,al_map_rgb(0,0,0));
                    al_draw_rectangle(192,150,307,200,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 156, 1, "PLAY");
                    al_draw_rectangle(192,225,307,275,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 231, 1, "EDIT");
                    al_draw_rectangle(192,300,307,350,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 306, 1, "LOAD");
                    al_draw_filled_rectangle(330,470,460,530,al_map_rgb(0,0,0));
                    al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                }
            }
            /*CONFIGURACOES DO MAPA:*/
            else if (screen==2){
                if (x>320&&x<440&&y>83&&y<103){
                    al_draw_filled_rectangle((tamanho-50)*2+321,84,(tamanho-50)*2+339,102,al_map_rgb(0,0,0));
                    al_draw_rectangle((tamanho-50)*2+321,84,(tamanho-50)*2+339,102,al_map_rgb(255,255,255),2);
                }
                else if (x>420&&x<430&&y>133&&y<153){
                    al_draw_filled_rectangle(420,133,430,153,al_map_rgb(255,255,255));
                }
                else if (x>405&&x<415&&y>138&&y<153){
                    al_draw_filled_rectangle(405,138,415,153,al_map_rgb(255,255,255));
                }
                else if (x>390&&x<400&&y>143&&y<153){
                    al_draw_filled_rectangle(390,143,400,153,al_map_rgb(255,255,255));
                }
                else if (x>375&&x<385&&y>148&&y<153){
                    al_draw_filled_rectangle(375,148,385,153,al_map_rgb(255,255,255));
                }
                else if (x>320&&x<340&&y>185&&y<205){
                    al_draw_filled_rectangle(319,184,341,206,al_map_rgb(255,255,255));
                    al_draw_line(323,195,337,195,al_map_rgb(0,0,0),2);
                }
                else if (x>410&&x<430&&y>185&&y<205){
                    al_draw_filled_rectangle(409,184,431,206,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),420,175,1,"+");
                }
                else if (x>275&&x<295&&y>235&&y<255){
                    al_draw_filled_rectangle(274,234,296,256,al_map_rgb(255,115,70));
                }
                else if (x>320&&x<340&&y>235&&y<255){
                    al_draw_filled_rectangle(319,234,341,256,al_map_rgb(40,125,250));
                }
                else if (x>365&&x<385&&y>235&&y<255){
                    al_draw_filled_rectangle(364,234,386,256,al_map_rgb(130,20,165));
                }
                else if (x>410&&x<430&&y>235&&y<255){
                    al_draw_filled_rectangle(409,234,431,256,al_map_rgb(255,255,255));
                }
                else if (x>75&&x<190&&y>375&&y<425){
                    al_draw_filled_rectangle(75,375,190,425,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),132, 381, 1, "RESET");
                }
                else if (x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "BACK");
                }
                else {
                    al_clear_to_color(al_map_rgb(0,0,0));
                    draw=1;
                }
            }
            /*JOGO:*/
            else if (screen==3){
                if (x>192&&x<307&&y>475&&y<525){
                    al_draw_filled_rectangle(192,475,307.5,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 481, 1, "SAVE");
                }
                else if (x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "BACK");
                }
                else {
                    al_draw_filled_rectangle(190,470,460,530,al_map_rgb(0,0,0));
                    al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "SAVE");
                    al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                }
            }
            /*EDITAR MAPA:*/
            else if (screen==4){
                if (x>192&&x<307&&y>475&&y<525){
                    al_draw_filled_rectangle(192,475,307.5,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 481, 1, "CLEAR");
                }
                else if(x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "BACK");
                }
                else {
                    al_draw_filled_rectangle(190,470,460,530,al_map_rgb(0,0,0));
                    al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "CLEAR");
                    al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                }
            }
            /*SALVAR MAPA:*/
            else {
                if(x>195&&x<215&&y>185&&y<205){
                    al_draw_filled_rectangle(194,184,216,206,al_map_rgb(255,255,255));
                    al_draw_line(198,195,212,195,al_map_rgb(0,0,0),2);
                }
                else if (x>285&&x<305&&y>185&&y<205){
                    al_draw_filled_rectangle(284,184,306,206,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),295,175,1,"+");
                }
                else if (x>192&&x<307&&y>225&&y<275){
                    al_draw_filled_rectangle(192,225,307,275,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),250, 231, 1, "SAVE");
                }
                else if(x>335&&x<450&&y>475&&y<525){
                    al_draw_filled_rectangle(335,475,450,525,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),392, 481, 1, "BACK");
                }
                else{
                    al_draw_filled_rectangle(190,180,310,280,al_map_rgb(0,0,0));
                    al_draw_filled_rectangle(195,185,215,205,al_map_rgb(255,255,255));
                    al_draw_line(198,195,212,195,al_map_rgb(0,0,0),2);
                    al_draw_textf(font2,al_map_rgb(255,255,255),250,175,1,"%d",nsalvar+1);
                    al_draw_filled_rectangle(285,185,305,205,al_map_rgb(255,255,255));
                    al_draw_text(font2,al_map_rgb(0,0,0),295,175,1,"+");
                    al_draw_rectangle(192,225,307,275,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),250, 231, 1, "SAVE");
                    al_draw_filled_rectangle(330,470,460,530,al_map_rgb(0,0,0));
                    al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                    al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                }
            }
        }
        else if (events.type==ALLEGRO_EVENT_MOUSE_BUTTON_DOWN){
            if(events.mouse.button & 1){
                /*MENU:*/
                if (screen==0){
                    if(x>0&&x<165&&y>475&&y<525){
                        screen=1;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>192&&x<307&&y>475&&y<525){
                        screen=2;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>335&&x<475&&y>450&&y<525){
                        exit=1;
                        timer=al_create_timer(1);
                        /*devido a funcao destroy_timer, o programa nao fecha corretamente se o timer nao for incializado.
                        para garantir que o jogo feche em qualquer ocasiao, atruibui-se um valor qualquer a timer antes de sair.*/
                    }
                }
                /*OPCOES DE JOGO:*/
                else if (screen==1){
                    if (x>192&&x<307&&y>150&&y<200){
                        screen=3;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>192&&x<307&&y>225&&y<275){
                        screen=4;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>192&&x<307&&y>300&&y<350){
                        LimparCampos(m1, m2, m3, m4, tamanho);
                        AbrirArquivoGeracao(m1, m2, tamanho);
                        screen=3;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>335&&x<450&&y>475&&y<525){
                        screen=0;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                }
                /*CONFIGURACOES DO MAPA:*/
                else if (screen==2){
                    if (x>320&&x<440&&y>83&&y<103){
                        tamanho=(x-330)/2 +50;
                        if (tamanho>100){
                            tamanho=100;
                        }
                        else if (tamanho<50){
                            tamanho=50;
                        }
                        al_draw_filled_rectangle(225,74,440,122,al_map_rgb(0,0,0));
                        al_draw_line(330,93,430,93,al_map_rgb(255,255,255),2);
                        al_draw_filled_rectangle((tamanho-50)*2+321,84,(tamanho-50)*2+339,102,al_map_rgb(0,0,0));
                        al_draw_rectangle((tamanho-50)*2+321,84,(tamanho-50)*2+339,102,al_map_rgb(255,255,255),2);
                        al_draw_textf(font2,al_map_rgb(255,255,255),285,75,1,"%d",tamanho);
                    }
                    else if (x>420&&x<430&&y>133&&y<153){
                        speed=0;
                        tinit=1;
                    }
                    else if (x>405&&x<415&&y>138&&y<153){
                        speed=1;
                        tinit=1;
                    }
                    else if (x>390&&x<400&&y>143&&y<153){
                        speed=2;
                        tinit=1;
                    }
                    else if (x>375&&x<385&&y>148&&y<153){
                        speed=3;
                        tinit=1;
                    }
                    else if (x>320&&x<340&&y>185&&y<205){
                        n_geracoes--;
                        if (n_geracoes<0){
                            n_geracoes=0;
                        }
                        else{
                            al_draw_filled_rectangle(350,175,400,215,al_map_rgb(0,0,0));
                            al_draw_textf(font2,al_map_rgb(255,255,255),375,175,1,"%d",n_geracoes);
                        }
                    }
                    else if (x>410&&x<430&&y>185&&y<205){
                        n_geracoes++;
                        al_draw_filled_rectangle(350,175,400,215,al_map_rgb(0,0,0));
                        al_draw_textf(font2,al_map_rgb(255,255,255),375,175,1,"%d",n_geracoes);
                    }
                    else if (x>275&&x<295&&y>235&&y<255){
                        color=3;
                    }
                    else if (x>320&&x<340&&y>235&&y<255){
                        color=2;
                    }
                    else if (x>365&&x<385&&y>235&&y<255){
                        color=1;
                    }
                    else if (x>410&&x<430&&y>235&&y<255){
                        color=0;
                    }
                    else if (x>75&&x<190&&y>375&&y<425){
                        /*volta para as configuracoes default do mapa*/
                        tamanho=100;
                        speed=2;
                        tinit=1;
                        n_geracoes=7;
                        color=0;
                        al_draw_filled_rectangle(225,74,440,122,al_map_rgb(0,0,0));
                        al_draw_line(330,93,430,93,al_map_rgb(255,255,255),2);
                        al_draw_filled_rectangle(420,83,440,103,al_map_rgb(255,255,255));
                        al_draw_textf(font2,al_map_rgb(255,255,255),285,75,1,"%d",tamanho);
                        al_draw_filled_rectangle(320,185,340,205,al_map_rgb(255,255,255));
                        al_draw_line(323,195,337,195,al_map_rgb(0,0,0),2);
                        al_draw_filled_rectangle(345,180,405,210,al_map_rgb(0,0,0));
                        al_draw_textf(font2,al_map_rgb(255,255,255),375,175,1,"%d",n_geracoes);
                        al_draw_filled_rectangle(410,185,430,205,al_map_rgb(255,255,255));
                        al_draw_text(font2,al_map_rgb(0,0,0),420,175,1,"+");
                    }
                    else if (x>335&&x<450&&y>475&&y<525){
                        screen=0;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                }
                /*JOGO:*/
                else if (screen==3){
                    if (x>192&&x<307&&y>475&&y<525){
                        screen=5;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>335&&x<450&&y>475&&y<525){
                        screen=1;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                        k=0;
                    }
                }
                /*EDITAR MAPA:*/
                else if (screen==4){
                    if (x>(250-2*tamanho)&&x<(250+2*tamanho)&&y>(250-2*tamanho)&&y<(250+2*tamanho)){
                        i=(x-250+2*tamanho)/4;
                        j=(y-250+2*tamanho)/4;
                        if (m1[i][j]==0){
                            m1[i][j]=m2[i][j]=1;
                            if (color==0){
                                red=255;
                                green=255;
                                blue=255;
                            }
                            else if (color==1){
                                red=150-2*(i/5);
                                green=0+7*(i/5);
                                blue=155+i;
                            }
                            else if (color==2){
                                    red=60+3*(i/5);
                                    green=250-5*(i/2);
                                    blue=245+i/10;
                            }
                            else{
                                red=255;
                                green=105+5*(i/4);
                                blue=140-7*(i/5);
                            }
                            r= (char) red;
                            g= (char) green;
                            b= (char) blue;
                            al_draw_filled_rectangle(250-tamanho*2+4*i,250-tamanho*2+4*j,250-tamanho*2+4*i+4,250-tamanho*2+4*j+4,al_map_rgb(r,g,b));
                            }
                        else {
                            m1[i][j]=m2[i][j]=0;
                            al_draw_filled_rectangle(250-tamanho*2+4*i,250-tamanho*2+4*j,250-tamanho*2+4*i+4,250-tamanho*2+4*j+4,al_map_rgb(0,0,0));
                        }
                    }
                    else if(x>335&&x<450&&y>475&&x<525){
                        screen=1;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                    }
                    else if (x>192&&x<307&&y>475&&y<525){
                        LimparCampos(m1,m2,m3,m4,tamanho);
                        ExibirMatriz(m1,tamanho,color);
                    }
                }
                /*SALVAR MAPA:*/
                else{
                    if(x>195&&x<215&&y>185&&y<205){
                        nsalvar--;
                        if (nsalvar<0){
                            nsalvar=0;
                        }
                        else{
                            al_draw_filled_rectangle(230,155,270,205,al_map_rgb(0,0,0));
                            al_draw_textf(font2,al_map_rgb(255,255,255),250,175,1,"%d",nsalvar+1);
                        }
                    }
                    else if (x>285&&x<305&&y>185&&y<205){
                        nsalvar++;
                        if (nsalvar>n_geracoes-1){
                            nsalvar=n_geracoes-1;
                        }
                        else{
                            al_draw_filled_rectangle(230,155,270,205,al_map_rgb(0,0,0));
                            al_draw_textf(font2,al_map_rgb(255,255,255),250,175,1,"%d",nsalvar+1);
                        }
                    }
                    else if (x>192&&x<307&&y>225&&y<275){
                        RodarGeracoesImprimir(m3, m4, nsalvar, tamanho);
                        SalvarArquivo(m3, m4, tamanho);
                        al_show_native_message_box(display, NULL, "OK!", "Gravacao concluida com sucesso", NULL, NULL);
                    }
                    else if(x>335&&x<450&&y>475&&y<525){
                        screen=3;
                        al_clear_to_color(al_map_rgb(0,0,0));
                        draw=1;
                        k=0;
                    }
                }
            }
        }
        else if (screen==3){
            if (events.type==ALLEGRO_EVENT_TIMER && k<n_geracoes){
                draw=1;
            }
        }
        if(draw==1){
            /*MENU:*/
            if (screen==0){
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_text(font1, al_map_rgb(255,255,255), 250, 37, 1, "GAME");
                al_draw_text(font1, al_map_rgb(255,255,255), 250, 162, 1, "OF");
                al_draw_text(font1, al_map_rgb(255,255,255), 250, 287, 1, "LIFE");
                al_draw_rectangle(50,475,165,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),107.5, 481, 1, "START");
                al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "MENU");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "EXIT");
                draw=0;
            }
            /*OPCOES DE JOGO:*/
            else if (screen==1){
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_rectangle(192,150,307,200,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 156, 1, "PLAY");
                al_draw_rectangle(192.5,225,307,275,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 231, 1, "EDIT");
                al_draw_rectangle(192,300,307,350,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 306, 1, "LOAD");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                draw=0;
            }
            /*CONFIGURACOES DO MAPA:*/
            else if (screen==2){
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),75, 75, 0, "MAP SIZE");
                al_draw_line(330,93,430,93,al_map_rgb(255,255,255),2);
                al_draw_filled_rectangle((tamanho-50)*2+320,83,(tamanho-50)*2+340,103,al_map_rgb(255,255,255));
                al_draw_textf(font2,al_map_rgb(255,255,255),285,75,1,"%d",tamanho);
                al_draw_text(font2,al_map_rgb(255,255,255),75, 125, 0, "SPEED");
                if (speed==0){
                    al_draw_filled_rectangle(419,132,431,154,al_map_rgb(255,255,255));
                    al_draw_rectangle(405,138,415,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(390,143,400,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(375,148,385,153,al_map_rgb(255,255,255),2);
                }
                else if (speed==1){
                    al_draw_rectangle(420,133,430,153,al_map_rgb(255,255,255),2);
                    al_draw_filled_rectangle(404,137,416,154,al_map_rgb(255,255,255));
                    al_draw_rectangle(390,143,400,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(375,148,385,153,al_map_rgb(255,255,255),2);
                }
                else if (speed==2){
                    al_draw_rectangle(420,133,430,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(405,138,415,153,al_map_rgb(255,255,255),2);
                    al_draw_filled_rectangle(389,142,401,154,al_map_rgb(255,255,255));
                    al_draw_rectangle(375,148,385,153,al_map_rgb(255,255,255),2);
                }
                else{
                    al_draw_rectangle(420,133,430,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(405,138,415,153,al_map_rgb(255,255,255),2);
                    al_draw_rectangle(390,143,400,153,al_map_rgb(255,255,255),2);
                    al_draw_filled_rectangle(374,147,386,154,al_map_rgb(255,255,255));
                }
                al_draw_text(font2,al_map_rgb(255,255,255),75, 175, 0, "GENS");
                al_draw_filled_rectangle(320,185,340,205,al_map_rgb(255,255,255));
                al_draw_line(323,195,337,195,al_map_rgb(0,0,0),2);
                al_draw_textf(font2,al_map_rgb(255,255,255),375,175,1,"%d",n_geracoes);
                al_draw_filled_rectangle(410,185,430,205,al_map_rgb(255,255,255));
                al_draw_text(font2,al_map_rgb(0,0,0),420,175,1,"+");
                al_draw_text(font2,al_map_rgb(255,255,255),75, 225, 0, "COLOR");
                if (color==0){
                    al_draw_filled_rectangle(409,234,431,256,al_map_rgb(255,255,255));
                    al_draw_filled_rectangle(365,235,385,255,al_map_rgb(130,20,165));
                    al_draw_filled_rectangle(320,235,340,255,al_map_rgb(40,125,250));
                    al_draw_filled_rectangle(275,235,295,255,al_map_rgb(255,115,70));
                }
                else if (color==1){
                    al_draw_filled_rectangle(410,235,430,255,al_map_rgb(255,255,255));
                    al_draw_filled_rectangle(364,234,386,256,al_map_rgb(130,20,165));
                    al_draw_filled_rectangle(320,235,340,255,al_map_rgb(40,125,250));
                    al_draw_filled_rectangle(275,235,295,255,al_map_rgb(255,115,70));
                }
                else if (color==2){
                    al_draw_filled_rectangle(410,235,430,255,al_map_rgb(255,255,255));
                    al_draw_filled_rectangle(365,235,385,255,al_map_rgb(130,20,165));
                    al_draw_filled_rectangle(319,234,341,256,al_map_rgb(40,125,250));
                    al_draw_filled_rectangle(275,235,295,255,al_map_rgb(255,115,70));
                }
                else{
                    al_draw_filled_rectangle(410,235,430,255,al_map_rgb(255,255,255));
                    al_draw_filled_rectangle(365,235,385,255,al_map_rgb(130,20,165));
                    al_draw_filled_rectangle(320,235,340,255,al_map_rgb(40,125,250));
                    al_draw_filled_rectangle(274,234,296,256,al_map_rgb(255,115,70));
                }
                al_draw_rectangle(75,375,190,425,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),132, 381, 1, "RESET");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                draw=0;
            }
            /*JOGO:*/
            else if (screen==3){
                if (tinit==1){
                    if (speed==0){
                        timer=al_create_timer(0.1);
                        al_register_event_source(event_queue, al_get_timer_event_source(timer));
                        al_start_timer(timer);
                    }
                    else if (speed==1){
                        timer=al_create_timer(0.5);
                        al_register_event_source(event_queue, al_get_timer_event_source(timer));
                        al_start_timer(timer);
                    }
                    else if (speed==2){
                        timer=al_create_timer(1);
                        al_register_event_source(event_queue, al_get_timer_event_source(timer));
                        al_start_timer(timer);
                    }
                    else if (speed==3){
                        timer=al_create_timer(5);
                        al_register_event_source(event_queue, al_get_timer_event_source(timer));
                        al_start_timer(timer);
                    }
                    tinit=0;
                }
                ExibirMatriz(m1, tamanho, color);
                if (k<n_geracoes-1)
                    RodarGeracoesImprimir(m1,m2,n_geracoes,tamanho);
                k++;
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "SAVE");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                draw=0;
            }
            /*EDITAR JOGO:*/
            else if (screen==4){
                ExibirMatriz(m1,tamanho,color);
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_rectangle(192,475,307,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 481, 1, "CLEAR");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                draw=0;
            }
            /*SALVAR MAPA:*/
            else {
                for(i=0;i<tamanho;i++){
                    for(j=0;j<tamanho;j++){
                        m3[i][j] = m1[i][j];
                    }
                }
                al_draw_rectangle(50,50,450,450,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250,75,1,"WHICH GENERATION?");
                al_draw_filled_rectangle(195,185,215,205,al_map_rgb(255,255,255));
                al_draw_line(198,195,212,195,al_map_rgb(0,0,0),2);
                al_draw_textf(font2,al_map_rgb(255,255,255),250,175,1,"%d",nsalvar+1);
                al_draw_filled_rectangle(285,185,305,205,al_map_rgb(255,255,255));
                al_draw_text(font2,al_map_rgb(0,0,0),295,175,1,"+");
                al_draw_rectangle(192,225,307,275,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),250, 231, 1, "SAVE");
                al_draw_rectangle(335,475,450,525,al_map_rgb(255,255,255),2);
                al_draw_text(font2,al_map_rgb(255,255,255),392, 481, 1, "BACK");
                draw=0;
            }
        }
        al_flip_display();
    }while(exit!=1);
    al_destroy_event_queue(event_queue);
    al_destroy_font(font1);
    al_destroy_font(font2);
    al_destroy_timer(timer);
    al_destroy_display(display);
    printf("Obrigado por jogar!");
    return 0;
}

void GerarAleatorio(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam){
    /*Gerando a matriz default*/
    matriz1[2][4] = matriz2[2][4] = 1;
    matriz1[2][5] = matriz2[2][5] = 1;
    matriz1[2][6] = matriz2[2][6] = 1;
    matriz1[2][10] = matriz2[2][10] = 1;
    matriz1[2][11] = matriz2[2][11] = 1;
    matriz1[2][12] = matriz2[2][12] = 1;
    matriz1[4][2]=matriz2[4][2]=1;
    matriz1[4][7]=matriz2[4][7]=1;
    matriz1[4][9]=matriz2[4][9]=1;
    matriz1[4][14]=matriz2[4][14]=1;
    matriz1[5][2]=matriz2[5][2]=1;
    matriz1[5][7]=matriz2[5][7]=1;
    matriz1[5][9]=matriz2[5][9]=1;
    matriz1[5][14]=matriz2[5][14]=1;
    matriz1[6][2]=matriz2[6][2]=1;
    matriz1[6][7]=matriz2[6][7]=1;
    matriz1[6][9]=matriz2[6][9]=1;
    matriz1[6][14]=matriz2[6][14]=1;
    matriz1[7][4] = matriz2[7][4] = 1;
    matriz1[7][5] = matriz2[7][5] = 1;
    matriz1[7][6] = matriz2[7][6] = 1;
    matriz1[7][10] = matriz2[7][10] = 1;
    matriz1[7][11] = matriz2[7][11] = 1;
    matriz1[7][12] = matriz2[7][12] = 1;
    matriz1[9][4] = matriz2[9][4] = 1;
    matriz1[9][5] = matriz2[9][5] = 1;
    matriz1[9][6] = matriz2[9][6] = 1;
    matriz1[9][10] = matriz2[9][10] = 1;
    matriz1[9][11] = matriz2[9][11] = 1;
    matriz1[9][12] = matriz2[9][12] = 1;
    matriz1[10][2]=matriz2[10][2]=1;
    matriz1[10][7]=matriz2[10][7]=1;
    matriz1[10][9]=matriz2[10][9]=1;
    matriz1[10][14]=matriz2[10][14]=1;
    matriz1[11][2]=matriz2[11][2]=1;
    matriz1[11][7]=matriz2[11][7]=1;
    matriz1[11][9]=matriz2[11][9]=1;
    matriz1[11][14]=matriz2[11][14]=1;
    matriz1[12][2]=matriz2[12][2]=1;
    matriz1[12][7]=matriz2[12][7]=1;
    matriz1[12][9]=matriz2[12][9]=1;
    matriz1[12][14]=matriz2[12][14]=1;
    matriz1[14][4] = matriz2[14][4] = 1;
    matriz1[14][5] = matriz2[14][5] = 1;
    matriz1[14][6] = matriz2[14][6] = 1;
    matriz1[14][10] = matriz2[14][10] = 1;
    matriz1[14][11] = matriz2[14][11] = 1;
    matriz1[14][12] = matriz2[14][12] = 1;
}

void ExibirMatriz (int matriz[TAMANHO_MAX][TAMANHO_MAX], int tam, int color){
    int i, j;
    int red, green, blue;
    char r,g,b;
    /* Exibindo a matriz*/
    for(i = 0;i < tam; i++){
        for(j = 0;j < tam; j++){
            if (matriz[i][j]==1){
                if (color==0){
                    red=255;
                    green=255;
                    blue=255;
                }
                else if (color==1){
                    red=150-2*(i/5);
                    green=0+7*(i/5);
                    blue=155+i;
                }
                else if (color==2){
                    red=60+3*(i/5);
                    green=250-5*(i/2);
                    blue=245+i/10;
                }
                else{
                    red=255;
                    green=105+5*(i/4);
                    blue=140-7*(i/5);
                }
                r= (char) red;
                g= (char) green;
                b= (char) blue;
                al_draw_filled_rectangle(250-tam*2+4*i,250-tam*2+4*j,250-tam*2+4*i+4,250-tam*2+4*j+4,al_map_rgb(r,g,b));
            }
            else{
                al_draw_filled_rectangle(250-tam*2+4*i,250-tam*2+4*j,250-tam*2+4*i+4,250-tam*2+4*j+4,al_map_rgb(0,0,0));
            }
        }
    }
}

void RodarGeracoesImprimir(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int nvezes, int tam){
    int i, j;
    int t;
    for(i=0;i<tam;i++){
        for (j=0;j<tam;j++){
            t=0;
            /* Série de testes sobre os 6 vizinhos possivéis*/
            if (matriz1[(i-1+tam)%tam][(j-1+tam)%tam]==1)
                t++;
            if (matriz1[(i-1+tam)%tam][j]==1)
                t++;
            if (matriz1[(i-1+tam)%tam][(j+1)%tam]==1)
                t++;
            if (matriz1[i][(j-1+tam)%tam]==1)
                t++;
            if (matriz1[i][(j+1)%tam]==1)
                t++;
            if (matriz1[(i+1)%tam][(j-1+tam)%tam]==1)
                t++;
            if (matriz1[(i+1)%tam][j]==1)
                t++;
            if (matriz1[(i+1)%tam][(j+1)%tam]==1)
                t++;
            /* Atribuir o valores atualizadoos*/
            if ((t==0)||(t==1)||(t>=4)){
                matriz2[i][j]=0;
            }
            else if(t==3){
                matriz2[i][j]=1;
            }
            else{
                matriz2[i][j]=matriz1[i][j];
            }
        }
    }
    /* Atribuindo a matriz real(matriz2) na matriz de teste(matriz1)*/
    for(i=0;i<tam;i++){
        for(j=0;j<tam;j++){
            matriz1[i][j] = matriz2[i][j];
        }
    }
}

void AbrirArquivoGeracao(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam){
    int linha, coluna;
    FILE *arq;
    char url[] = "recSuperElisa.txt";
    arq = fopen(url, "r");
    if(arq == NULL)
        al_show_native_message_box(NULL, NULL, NULL, "Erro, nao foi possivel abrir o arquivo", NULL, NULL);
    else
        fscanf(arq,"Tamanho: %d\n", &tam);
    while((fscanf(arq,"%d - %d\n", &linha, &coluna)) != EOF){
        matriz1[linha][coluna] = matriz2[linha][coluna] = 1;
    }
    fclose(arq);
}

void SalvarArquivo(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int tam){
    int i, j;
    /* Variaveis para auxiliar na criação e gravação do arquivo*/
    char rec[100];
    FILE *arq;
    int result, contador = 0;
    char url[] = "recSuperElisa.txt";
    arq = fopen(url, "wt");
    if(arq == NULL){
        al_show_native_message_box(NULL, NULL, NULL, "Problemas na criacao do arquivo", NULL, NULL);
    }
    sprintf(rec, "Tamanho: %d\n", tam);
    result = fputs(rec, arq);
    for(i=0; i < tam;i++){
        for(j=0; j< tam; j++){;
            if(matriz2[i][j]==1){
                sprintf(rec, "%d - %d\n", i,j);
                result = fputs(rec,arq);
                contador++;
            }
        }
    }
    fclose(arq);
}


void LimparCampos(int matriz1[TAMANHO_MAX][TAMANHO_MAX], int matriz2[TAMANHO_MAX][TAMANHO_MAX], int matriz3[TAMANHO_MAX][TAMANHO_MAX], int matriz4[TAMANHO_MAX][TAMANHO_MAX], int tam){
    int i, j;
    for (i=0;i<tam;i++){
        for (j=0;j<tam;j++){
            matriz1[i][j] = matriz2[i][j] = matriz3[i][j] = matriz4[i][j] = 0;
        }
    }
}
