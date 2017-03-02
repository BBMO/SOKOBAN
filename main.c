#include <allegro.h>

#define filas_1 15 //FILAS Y
#define colum_1 22  //COLUMNAS X
BITMAP *buffer;
BITMAP *bloque;
BITMAP *obrero_bmp;
BITMAP *obrero;
BITMAP *cajas;
BITMAP *puntos;
BITMAP *game_over; BITMAP *game_over2;
BITMAP *fondo;  BITMAP *fondo2;
BITMAP *fondo3; BITMAP *fondo4;
BITMAP *cursor;
BITMAP *instrucciones;
BITMAP *nivel_1; BITMAP *nivel_2; BITMAP *nivel_3;
BITMAP *estadistic;
MIDI *musica1;
MIDI *musica_juego;
MIDI *perdiste;
struct datos_finales
{
    int cont_resul;
    char nombre[20];
    int cont[3];
    int nivel;
};

int direccion=0;
int px=30.1*12, py=30.1*10;
char mapa[filas_1][colum_1];

void dibujar_mapa_1(){
    int i,j;
    for (i=0;i<filas_1 ;i++ )
    {
        for (j=0;j<colum_1 ; j++ )
        {
           if(mapa[i][j]=='X')
           {
               draw_sprite(buffer, bloque, j*30, i*30);
           }
           else if(mapa[i][j]=='c')
           {
               draw_sprite(buffer, cajas, j*30, i*30);
           }
           else if(mapa[i][j]=='o')
           {
               draw_sprite(buffer, puntos, j*30, i*30);
           }

        }

    }


}


void pantalla(){
    blit(buffer, screen, 0,0,0,0,700, 500);
}
void dibujar_obrero(){
    blit(obrero_bmp, obrero, direccion*29, 0, 0,0,29,28);
    draw_sprite(buffer, obrero, px, py );
}


/**********************************************************main*************************************************/
void mapa_3();
void mapa_2();
void mapa_1();
int ganar_1();
void juego_1(struct datos_finales *estadisticas, int i);
int perder(int cambiador_puntos);
void cambiador_de_puntos(int cambia_puntos);
void resultados_finales(struct datos_finales *estadisticas, int i);
int main()
{
    char nombre[20],tecla;
    int i,j, salida, aux;
    struct datos_finales estadisticas;

	allegro_init();
	install_keyboard();
	install_mouse();
	install_sound(DIGI_AUTODETECT, MIDI_AUTODETECT, NULL);
	set_color_depth(32);
	set_gfx_mode(GFX_AUTODETECT_WINDOWED, 700, 500, 0, 0);

	buffer = create_bitmap(700,500);
    bloque = load_bitmap("bloque2.bmp", NULL);
    obrero_bmp = load_bitmap("obrero.bmp", NULL);
    obrero = create_bitmap(29,28);
    cajas=load_bitmap("cajas.bmp", NULL);
    puntos=load_bitmap("puntos.bmp",NULL);
    game_over=load_bitmap("game.bmp",NULL);
    game_over2=load_bitmap("game2.bmp",NULL);
    fondo=load_bitmap("fondo.bmp",NULL);
    fondo2=load_bitmap("fondo2.bmp",NULL);
    fondo3=load_bitmap("fondo3.bmp",NULL);
    fondo4=load_bitmap("fondo4.bmp",NULL);
    cursor=load_bitmap("cursor.bmp", NULL);
    instrucciones=load_bitmap("instrucciones.bmp", NULL);
    nivel_1=load_bitmap("nivel1.bmp", NULL);
    nivel_2=load_bitmap("nivel2.bmp", NULL);
    nivel_3=load_bitmap("nivel3.bmp",NULL);
    estadistic=load_bitmap("estadisticas.bmp", NULL);
    musica1=load_midi("menu.mid");
    musica_juego=load_midi("juego.mid");
    perdiste=load_midi("perder.mid");

    do
    {
        clear_keybuf();
        midi_resume();
        play_midi(musica1,1);
            clear(buffer);
            salida=0;

                while(salida==0)                       /*SALIDA == 0*/
                {
                    if(mouse_x >380 && mouse_x < 613 && mouse_y > 188 && mouse_y < 230)  /*COORDENADAS DE INICIAR*/
                    {
                        draw_sprite(buffer, fondo2, 0, 0);
                        pantalla();

                            if( mouse_b & 1) /*DAR CLIC IZQUIERDO*/
                            {
                                salida=1;
                            }
                    }
                    else if(mouse_x >305 && mouse_x < 686 && mouse_y > 262 && mouse_y < 293)  /*COORDENADAS DE INSTRUCCIONES*/
                    {
                        draw_sprite(buffer, fondo3, 0, 0);
                        pantalla();

                            if( mouse_b & 1) /*DAR CLIC IZQUIERDO*/
                            {
                                salida=2;
                            }
                    }
                    else if(mouse_x > 409 && mouse_x < 584 && mouse_y > 335 && mouse_y < 373)  /*COORDENADAS DE SALIR*/
                    {
                        draw_sprite(buffer, fondo4, 0, 0);
                        pantalla();

                            if( mouse_b & 1) /*DAR CLIC IZQUIERDO*/
                            {
                                salida=3;
                            }
                    }
                    else
                    {
                        draw_sprite(buffer, fondo, 0, 0);
                        pantalla();
                    }

                    masked_blit(cursor, buffer, 0,0, mouse_x, mouse_y, 13, 22);  /*IMPRIMIR EL CURSOR DEL MOUSE*/
                    pantalla();
                }

                            /*JUEGO*/

                            if(salida==1)
                            {
                                i=0;
                                aux=22;
    /*NOMBRE DEL JUGADOR*/      clear(buffer);
                                textout(buffer, font, "INTRODUZCA SU NOMBRE Y PESIONE INTRO: ", 4*30, 3*30, -1);
                                pantalla();
                                do
                                {
                                    tecla=readkey();
                                    estadisticas.nombre[i]=tecla;
                                    if(key[KEY_BACKSPACE] && i>=0)
                                    {
                                       i--;
                                       aux--;
                                       estadisticas.nombre[i]=' ';
                                       textprintf(buffer, font, aux*20, 3*30, -1,"%c", estadisticas.nombre[i]);
                                        pantalla();
                                    }
                                    else
                                    {
                                        textprintf(buffer, font, aux*20, 3*30, -1,"%c", estadisticas.nombre[i]);
                                        pantalla();
                                        i++;
                                        aux++;
                                    }

                                }while(tecla != 13);
                                play_midi(musica_juego, 1);
                                estadisticas.cont_resul=0;
                                clear(buffer);
                                draw_sprite(buffer, nivel_1, 12*30, 1.3*30);
                                textprintf(buffer, font, 13*30, 4*30, -1, "NUMERO DE MOVIMIENTOS %d", 0+0);
                                textout(buffer, font,"JUGADOR: ", 13*30, 5*30, -1);
                                for (j=0;j<i-1;j++ )
                                {
                                    textprintf(buffer, font, (31+j)*15, 150, -1,"%c", estadisticas.nombre[j]);
                                }

                                mapa_1();
                                px=30.1*12, py=30.1*10;
                                dibujar_mapa_1();
                                dibujar_obrero();
                                pantalla();
                                juego_1(&estadisticas, i);
                                clear(buffer);


                            }

                            /*INSTRUCCIONES*/
                            if(salida==2)
                            {

                                draw_sprite(buffer, instrucciones, 0, 0);
                                pantalla();

                                    textout(buffer, font, "PRESIONA UNA TECLA PARA VOLVER_", 1.7*30, 15.7*30, -1);
                                    pantalla();

                                readkey();
                            }


    }while(salida != 3);

	return 0;
}
END_OF_MAIN()

void juego_1(struct datos_finales *estadisticas , int i)
{
   int direccion=5, ganador, cambia_puntos;
    int perdedor,j, cont;


    ganador=0;
    cambia_puntos=0;
    estadisticas->cont[0]=0;
    estadisticas->cont[1]=0;
    estadisticas->cont[2]=0;

    do
    {
        readkey();           /*GETCH*/

                if(key[KEY_RIGHT]){direccion=1;} //DERECHA
                else if(key[KEY_LEFT]){direccion=0;} //IZQUIERDA
                else if(key[KEY_UP]){direccion=2;}  //ARRIBA
                else if(key[KEY_DOWN]){direccion=3;}//ABAJO



            if(direccion==0)                            /*IZQUIERDA*/
            {
                if(mapa[py/30][(px-30)/30] == 'X')
                {
                  direccion=5;
                }
                else if(mapa[py/30][(px-30)/30]=='c')
                {
                    if(mapa[py/30][(px-60)/30] == ' ' || mapa[py/30][(px-60)/30] == 'o' )
                    {
                        mapa[py/30][(px-30)/30]=' ';
                        mapa[py/30][(px-60)/30]='c';
                        px=px-30;
                        if(cambia_puntos==0)estadisticas->cont[0]++;
                        if(cambia_puntos==1)estadisticas->cont[1]++;
                        if(cambia_puntos==2)estadisticas->cont[2]++;
                    }

                }
                else
                {
                    if(cambia_puntos==0)estadisticas->cont[0]++;
                    if(cambia_puntos==1)estadisticas->cont[1]++;
                    if(cambia_puntos==2)estadisticas->cont[2]++;
                    px=px-30;
                }

            }
            if(direccion == 1)                                     /*DERECHA*/
            {
                if(mapa[py/30][(px+30)/30] == 'X')
                {
                  direccion=5;
                }
                else if(mapa[py/30][(px+30)/30]=='c')
                {
                    if(mapa[py/30][(px+60)/30] == ' ' || mapa[py/30][(px+60)/30] == 'o')
                    {
                            mapa[py/30][(px+30)/30]=' ';
                            mapa[py/30][(px+60)/30]='c';
                        px=px+30;
                       if(cambia_puntos==0)estadisticas->cont[0]++;
                        if(cambia_puntos==1)estadisticas->cont[1]++;
                        if(cambia_puntos==2)estadisticas->cont[2]++;
                    }


                }
                else
                {
                    px=px+30;
                        if(cambia_puntos==0)estadisticas->cont[0]++;
                        if(cambia_puntos==1)estadisticas->cont[1]++;
                        if(cambia_puntos==2)estadisticas->cont[2]++;
                }

            }
             if(direccion==2)                             /*ARRIBA*/
            {
                if(mapa[(py-30)/30][px/30] == 'X')
                {
                   direccion=5;
                }
                else if(mapa[(py-30)/30][px/30]=='c')
                {
                    if(mapa[(py-60)/30][px/30] == ' ' || mapa[(py-60)/30][px/30] == 'o')
                    {
                        mapa[(py-30)/30][px/30]=' ';
                        mapa[(py-60)/30][px/30]='c';
                        py=py-30;
                        if(cambia_puntos==0)estadisticas->cont[0]++;
                        if(cambia_puntos==1)estadisticas->cont[1]++;
                        if(cambia_puntos==2)estadisticas->cont[2]++;
                    }

                }
                else
                {
                    py=py-30;
                    if(cambia_puntos==0)estadisticas->cont[0]++;
                    if(cambia_puntos==1)estadisticas->cont[1]++;
                    if(cambia_puntos==2)estadisticas->cont[2]++;
                }

            }
            if(direccion == 3)                                      /*ABAJO*/
            {
                if(mapa[(py+30)/30][px/30] == 'X')
                {
                   direccion=5;
                }
                else if(mapa[(py+30)/30][px/30]=='c')
                {
                    if(mapa[(py+60)/30][px/30] == ' ' || mapa[(py+60)/30][px/30] == 'o')
                    {
                        mapa[(py+30)/30][px/30]=' ';
                        mapa[(py+60)/30][px/30]='c';
                        py=py+30;
                    if(cambia_puntos==0)estadisticas->cont[0]++;
                    if(cambia_puntos==1)estadisticas->cont[1]++;
                    if(cambia_puntos==2)estadisticas->cont[2]++;
                    }

                }
                else
                {
                    py=py+30;
                    if(cambia_puntos==0)estadisticas->cont[0]++;
                    if(cambia_puntos==1)estadisticas->cont[1]++;
                    if(cambia_puntos==2)estadisticas->cont[2]++;
                }

            }

            cambiador_de_puntos(cambia_puntos);
            clear(buffer);

            if(cambia_puntos==0)
            {
                draw_sprite(buffer, nivel_1, 12*30, 1.3*30);
                textprintf(buffer, font, 13*30, 4*30, -1, "NUMERO DE MOVIMIENTOS %d", estadisticas->cont[0]);
                textout(buffer, font,"JUGADOR: ", 13*30, 5*30, -1);
                for (j=0;j<i-1;j++ )
                {
                    textprintf(buffer, font, (31+j)*15, 150, -1,"%c", estadisticas->nombre[j]);
                }
                ganador=ganar_1(cambia_puntos);
                estadisticas->nivel=0;
                perdedor=perder(cambia_puntos);
            }
            if(cambia_puntos==1)
            {
                draw_sprite(buffer, nivel_2, 8*30, 12*30);
                textprintf(buffer, font, 9*30, 14*30, -1, "NUMERO DE MOVIMIENTOS %d", estadisticas->cont[1]);
                textout(buffer, font,"JUGADOR: ", 9*30, 15*30, -1);
                for (j=0;j<i-1;j++ )
                {
                    textprintf(buffer, font, (23+j)*15, 450, -1,"%c", estadisticas->nombre[j]);
                }
                ganador=ganar_1(cambia_puntos);
                perdedor=perder(cambia_puntos);
            }
            if(cambia_puntos==2)
            {
                   draw_sprite(buffer, nivel_3, 15.9*30, 7.3*30);
                    textprintf(buffer, font, 16.5*30, 10*30, -1, "NUMERO DE MOVIMIENTOS %d", estadisticas->cont[2]);
                    textout(buffer, font,"JUGADOR: ", 16.5*30, 11*30, -1);
                    for (j=0;j<i-1;j++ )
                    {
                            textprintf(buffer, font, (38+j)*15, 11*30, -1,"%c", estadisticas->nombre[j]);
                    }
                 ganador=ganar_1(cambia_puntos);
                 perdedor=perder(cambia_puntos);   /*PIERDE*/

            }

            dibujar_mapa_1();
            dibujar_obrero();
            pantalla();



                                if(ganador==1)
                                {
                                    allegro_message("        GANASTE!!!");
                                    mapa_2();                                                     /*GENERO NIVEL 2*/
                                    px=30.1*11; py=30.1*6;
                                    clear(buffer);
                                    draw_sprite(buffer, nivel_2, 8*30, 12*30);
                                    textprintf(buffer, font, 9*30, 14*30, -1, "NUMERO DE MOVIMIENTOS %d", estadisticas->cont[1]);
                                    textout(buffer, font,"JUGADOR: ", 9*30, 15*30, -1);
                                    for (j=0;j<i-1;j++ )
                                    {
                                        textprintf(buffer, font, (23+j)*15, 450, -1,"%c", estadisticas->nombre[j]);
                                    }
                                    dibujar_mapa_1();
                                    dibujar_obrero();
                                    pantalla();
                                    cambia_puntos=1;
                                    ganador=5;
                                    estadisticas->nivel=1;
                                }
                                if(ganador==2)
                                {
                                    allegro_message("        GANASTE!!!");
                                    mapa_3();                                                     /*GENERO NIVEL 3*/
                                    px=30.1*8; py=30.1*3;
                                    clear(buffer);
                                    draw_sprite(buffer, nivel_3, 15.9*30, 7.3*30);
                                    textprintf(buffer, font, 16.5*30, 10*30, -1, "NUMERO DE MOVIMIENTOS %d", estadisticas->cont[2]);
                                    textout(buffer, font,"JUGADOR: ", 16.5*30, 11*30, -1);
                                     for (j=0;j<i-1;j++ )
                                     {
                                         textprintf(buffer, font, (38+j)*15, 11*30, -1,"%c", estadisticas->nombre[j]);
                                     }
                                    dibujar_mapa_1();
                                    dibujar_obrero();
                                    pantalla();
                                    cambia_puntos=2;
                                    ganador=5;
                                    estadisticas->nivel=2;

                                }
                                if(ganador==3)
                                {
                                    estadisticas->nivel=3;
                                    allegro_message("  ¡¡GANASTE EL JUEGO!!");
                                    break;
                                }
                                if(perdedor==1)
                                {
                                    cont=0;
                                    allegro_message("PERDISTE");
                                    play_midi(perdiste, 1);
                                    clear(buffer);

                                    do
                                    {
                                        clear_keybuf();
                                        draw_sprite(buffer, game_over, 22, 0);
                                        pantalla();
                                        rest(400);  //SLEEP
                                        draw_sprite(buffer, game_over2, 22, 0);
                                        pantalla();
                                        rest(400);   //SLEEP
                                        cont++;
                                    }while(cont<=9);

                                    clear(buffer);
                                    pantalla();
                                    midi_pause();
                                    break;
                                }
            direccion=5;
            rest(50);

    }while(!key[KEY_ESC]);

          estadisticas->cont_resul=estadisticas->cont[0]+estadisticas->cont[1]+estadisticas->cont[2];

                                    clear(buffer);
                                    resultados_finales(estadisticas, i);




}

int ganar_1(int cambia_puntos)
{
    if(cambia_puntos==0)
    {
        if(mapa[8][18]=='c' && mapa[9][18]=='c' && mapa[10][18]=='c')
        {
            if(mapa[8][17]=='c'&&mapa[9][17]=='c'&&mapa[10][17]=='c')
            {
                return 1;
            }

        }
    }
    if(cambia_puntos==1)
    {
        if(mapa[3][3]=='c' && mapa[4][3]=='c' && mapa[5][3]=='c'&& mapa[6][3]=='c' && mapa[7][3]=='c')
        {
            if(mapa[3][4]=='c' && mapa[4][4]=='c' && mapa[5][4]=='c'&& mapa[6][4]=='c' && mapa[7][4]=='c')
            {
                return 2;
            }

        }
    }
     if(cambia_puntos==2)
    {
        if(mapa[7][12]=='c' && mapa[8][12]=='c' && mapa[9][12]=='c'&& mapa[10][12]=='c')
        {
            if(mapa[8][11]=='c' && mapa[9][11]=='c' && mapa[10][11]=='c')
            {
                 if(mapa[7][13]=='c' && mapa[8][13]=='c' && mapa[9][13]=='c' &&mapa[10][13]=='c')
                {
                    return 3;
                }

            }

        }
    }


    return 0;
}
void mapa_1()
{
   int i,j;
    char nivel_1[filas_1][colum_1]={"                    ",
                                "                    ",
                                "     XXXXX          ",
                                "     X   X          ",
                                "     Xc  X          ",
                                "   XXX  cXX         ",
                                "   X  c c X         ",
                                " XXX X XX X   XXXXXX",
                                " X   X XX XXXXX  ooX",
                                " X c  c          ooX",
                                " XXXXX XXX X XX  ooX",
                                "     X     XXXXXXXXX",
                                "     XXXXXXX        ",};

    for(i=0;i<filas_1;i++)
    {
        for(j=0;j<colum_1;j++)
        {
            mapa[i][j]=nivel_1[i][j];
        }
    }

}
void mapa_2()
{
    int i,j;
    char nivel_2[filas_1][colum_1]={"                     ",
                                   "                     ",
                                   "  XXXXXXXXXXXXXX     ",
                                   "  Xoo    X     XXX   ",
                                   "  Xoo    X c  c  X   ",
                                   "  Xoo    XcXXXX  X   ",
                                   "  Xoo        XX  X   ",
                                   "  Xoo    X X  c XX   ",
                                   "  XXXXXXXX XXc c X   ",
                                   "    X c    c c c X   ",
                                   "    X      X     X   ",
                                   "    XXXXXXXXXXXXXX   ",
                                   "                     ",};


     for(i=0;i<filas_1;i++)
      {
         for(j=0;j<colum_1;j++)
             {
                   mapa[i][j]=nivel_2[i][j];
               }
      }


}

void mapa_3()
{
    int i,j;
    char nivel_3[filas_1][colum_1]={"                     ",
                                   "         XXXXXX      ",
                                   "    XXXXXXX   XX     ",
                                   "   XX X  XX cc X     ",
                                   "   X    c      X     ",
                                   "   X  c  XXX   X     ",
                                   "   XXX XXXXXcXXX     ",
                                   "   X c  XXX ooX      ",
                                   "   X c c c oooX      ",
                                   "   X    XXXoooX      ",
                                   "   X cc X XoooX      ",
                                   "   X  XXX XXXXX      ",
                                   "   XXXX              ",};


     for(i=0;i<filas_1;i++)
      {
         for(j=0;j<colum_1;j++)
             {
                   mapa[i][j]=nivel_3[i][j];
               }
      }


}

void cambiador_de_puntos(int cambia_puntos)
{


        if (cambia_puntos==0)                                          /*PUNTOS NIVEL 1*/
            {
                    if(mapa[8][17]==' ')
                    {
                        mapa[8][17]='o';
                    }
                    if(mapa[9][17]==' ')
                    {
                        mapa[9][17]='o';
                    }
                    if(mapa[10][17]==' ')
                    {
                        mapa[10][17]='o';
                    }
                    if(mapa[9][18]==' ')
                    {
                        mapa[9][18]='o';
                    }

            }

             if (cambia_puntos==1)                                             /*PUNTOS NIVEL 2*/
            {
                    if(mapa[3][4]==' ')
                    {
                        mapa[3][4]='o';
                    }
                    if(mapa[4][4]==' ')
                    {
                        mapa[4][4]='o';
                    }
                    if(mapa[5][4]==' ')
                    {
                        mapa[5][4]='o';
                    }
                    if(mapa[6][4]==' ')
                    {
                        mapa[6][4]='o';
                    }
                    if(mapa[7][4]==' ')
                    {
                        mapa[7][4]='o';
                    }
                    if(mapa[4][3]==' ')
                    {
                        mapa[4][3]='o';
                    }
                    if(mapa[5][3]==' ')
                    {
                        mapa[5][3]='o';
                    }
                    if(mapa[6][3]==' ')
                    {
                        mapa[6][3]='o';
                    }

            }

            if(cambia_puntos==2)                                             /*PUNTOS NIVEL 3*/
            {
                     if(mapa[7][12]==' ')
                    {
                        mapa[7][12]='o';
                    }
                    if(mapa[8][12]==' ')
                    {
                        mapa[8][12]='o';
                    }
                    if(mapa[9][12]==' ')
                    {
                        mapa[9][12]='o';
                    }
                    if(mapa[10][12]==' ')
                    {
                        mapa[10][12]='o';
                    }
                    if(mapa[8][11]==' ')
                    {
                        mapa[8][11]='o';
                    }
                    if(mapa[9][11]==' ')
                    {
                        mapa[9][11]='o';
                    }
                    if(mapa[8][13]==' ')
                    {
                        mapa[8][13]='o';
                    }
                    if(mapa[9][13]==' ')
                    {
                        mapa[9][13]='o';
                    }
            }

}

int perder(int cambia_puntos)
{
    if(cambia_puntos==0) /*POSICIONES CRITICAS DE MAPA 1*/
    {
        if(mapa[3][6]=='c')return 1;
        if(mapa[3][8]=='c')return 1;
        if(mapa[6][4]=='c')return 1;
        if(mapa[6][9]=='c')return 1;
        if(mapa[8][2]=='c')return 1;
        if(mapa[8][15]=='c')return 1;
        if(mapa[9][2]=='c')return 1;
        if(mapa[9][3]=='c' && mapa[9][4]=='c' )return 1;
        if(mapa[10][15]=='c')return 1;
        if(mapa[11][6]=='c')return 1;
        if(mapa[4][6]=='c' && mapa[5][6]=='c' )return 1;
        if(mapa[10][16]=='c' && mapa[10][17]=='c' )return 1;
        if(mapa[8][16]=='c' && mapa[8][17]=='c' )return 1;


    }
    if(cambia_puntos==1)
    {
        if(mapa[3][8]=='c')return 1;
        if(mapa[3][10]=='c')return 1;
        if(mapa[3][14]=='c')return 1;
        if(mapa[4][16]=='c')return 1;
        if(mapa[6][12]=='c')return 1;
        if(mapa[6][16]=='c')return 1;
        if(mapa[7][8]=='c')return 1;
        if(mapa[7][12]=='c')return 1;
        if(mapa[8][16]=='c')return 1;
        if(mapa[9][5]=='c')return 1;
        if(mapa[10][5]=='c')return 1;
        if(mapa[10][10]=='c')return 1;
        if(mapa[10][12]=='c')return 1;
        if(mapa[10][16]=='c')return 1;
        if(mapa[9][6]=='c' &&  mapa[9][7]=='c')return 1;
        if(mapa[4][11]=='c' &&  mapa[4][12]=='c')return 1;
        if(mapa[4][12]=='c' &&  mapa[4][13]=='c')return 1;
        if(mapa[4][13]=='c' &&  mapa[4][14]=='c')return 1;
        if(mapa[9][7]=='c' &&  mapa[9][8]=='c')return 1;
        if(mapa[9][8]=='c' &&  mapa[9][9]=='c')return 1;
        if(mapa[9][16]=='c' &&  mapa[8][15]=='c')return 1;
        if(mapa[6][15]=='c' &&  mapa[7][15]=='c')return 1;
        if(mapa[8][13]=='c' &&  mapa[8][14]=='c' && mapa[9][13]=='c' &&  mapa[9][14]=='c')return 1;
        if(mapa[6][15]=='c' &&  mapa[7][15]=='c')return 1;
        if(mapa[9][12]=='c' &&  mapa[9][11]=='c')return 1;
        if(mapa[9][12]=='c' &&  mapa[9][13]=='c')return 1;
        if(mapa[10][15]=='c')return 1;
        if(mapa[10][14]=='c')return 1;
        if(mapa[10][13]=='c')return 1;
        if(mapa[6][15]=='c' &&  mapa[7][15]=='c')return 1;
        if(mapa[9][12]=='c' &&  mapa[9][11]=='c')return 1;
        if(mapa[3][4]=='c' && mapa[3][5]=='c')return 1;
        if(mapa[3][5]=='c' && mapa[3][6]=='c')return 1;
        if(mapa[3][6]=='c' && mapa[3][7]=='c')return 1;
        if(mapa[7][4]=='c' && mapa[7][5]=='c')return 1;
        if(mapa[7][5]=='c' && mapa[7][6]=='c')return 1;
        if(mapa[7][6]=='c' && mapa[7][7]=='c')return 1;

    }

    if(cambia_puntos==2)
    {
        if(mapa[2][11]=='c')return 1;
        if(mapa[2][12]=='c')return 1;
        if(mapa[2][13]=='c')return 1;
        if(mapa[3][14]=='c')return 1;
        if(mapa[3][5]=='c')return 1;
        if(mapa[3][7]=='c')return 1;
        if(mapa[3][8]=='c')return 1;
        if(mapa[4][4]=='c')return 1;
        if(mapa[5][4]=='c')return 1;
        if(mapa[5][8]=='c')return 1;
        if(mapa[5][14]=='c')return 1;
        if(mapa[7][4]=='c')return 1;
        if(mapa[7][7]=='c')return 1;
        if(mapa[7][11]=='c')return 1;
        if(mapa[10][7]=='c')return 1;
        if(mapa[11][4]=='c')return 1;
        if(mapa[11][5]=='c')return 1;
        if(mapa[5][12]=='c' &&  mapa[6][12]=='c')return 1;
        if(mapa[4][14]=='c')return 1;
        if(mapa[8][4]=='c')return 1;
        if(mapa[9][4]=='c')return 1;
        if(mapa[10][4]=='c')return 1;
        if(mapa[9][7]=='c' &&  mapa[10][6]=='c')return 1;
        if(mapa[4][12]=='c' &&  mapa[5][12]=='c' && mapa[4][13]=='c' &&  mapa[8][7]=='c' &&  mapa[8][8]=='c')return 1;
        if(mapa[4][12]=='c' &&  mapa[5][12]=='c' && mapa[4][13]=='c' &&  mapa[8][7]=='c' &&  mapa[8][9]=='c')return 1;
        if(mapa[4][12]=='c' &&  mapa[5][12]=='c' && mapa[4][13]=='c' &&  mapa[8][7]=='c' &&  mapa[8][10]=='c')return 1;
        if(mapa[8][8]=='c' &&  mapa[8][9]=='c')return 1;


    }

    return 0;
}

void resultados_finales(struct datos_finales *estadisticas, int i)
{
    int j;

    clear(buffer);
    draw_sprite(buffer, estadistic, 0, 0);

    for (j=0;j<i-1;j++ )
    {
        textprintf(buffer, font, (28+j)*15, 5.4*30, -1,"%c", estadisticas->nombre[j]);
    }
    textprintf(buffer, font, 11.7*30, 7.4*30, -1, "%d", estadisticas->nivel);
    textprintf(buffer, font, 11.7*30, 11*30, -1, "%d", estadisticas->cont[0]);
    textprintf(buffer, font, 11.7*30, 12.4*30, -1, "%d", estadisticas->cont[1]);
    textprintf(buffer, font, 11.7*30, 13.6*30, -1, "%d", estadisticas->cont[2]);
    textprintf(buffer, font, 11.7*30, 15.1*30, -1, "%d", estadisticas->cont_resul);
    pantalla();
rest(5000);

}


