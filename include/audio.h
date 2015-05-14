/**
* @file SDL_affichage.c
* @brief affichage avec SDL
* @author Alexandre COMBEAU
* @date 13-05-2015
*/
#ifndef __AUDIO_H_
#define __AUDIO_H_


#include <SDL/SDL.h>

SDL_AudioSpec audioSortie;
Uint8 *audio_chunk;
Uint32 audio_len;
Uint8 *audio_pos;

void audioCallback(void *udata, Uint8 *stream, int len);
void audioInit(void);
void audioQuit (void);
#endif