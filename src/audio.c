/**
* @file SDL_affichage.c
* @brief affichage avec SDL
* @author Alexandre COMBEAU
* @date 13-05-2015
*/


/*SDL et la gestion de l'audio ... trop bas niveau, je n'y comprends rien !*/

#include <stdlib.h>
#include <stdio.h>
#include <SDL/SDL.h>
#include <string.h>

#include "SDL_affichage.h"
#include "audio.h"


SDL_AudioSpec audioSortie;
Uint8 *audio_chunk;
Uint32 audio_len;
Uint8 *audio_pos;

//SDL_OpenAudio(SDL_AudioSpec *desired, SDL_AudioSpec *obtained);



void audioCallback(void *udata, Uint8 *stream, int len)
{
	if ( audio_len == 0 )
		return;

	len = ( len > audio_len ? audio_len : len );
	SDL_MixAudio(stream, audio_pos, len, SDL_MIX_MAXVOLUME);
	audio_pos += len;
	audio_len -= len;
}

void audioInit(void)
{
    // Définition des propriétés audio
    audioSortie.freq = 44100;
    audioSortie.format = AUDIO_S16;
    audioSortie.channels = 1;
    audioSortie.samples = 2048;
    audioSortie.callback = audioCallback;
    audioSortie.userdata = NULL;

    if (SDL_OpenAudio(&audioSortie, NULL) < 0)
    {
    	printf("ErreurAudioInit : Ca marche pas :( ...\n");
    	exit(EXIT_FAILURE);
    }
}

void audioLoad(char* path)
{
	SDL_LoadWAV("ressources/audio/swag.wav", &audio)
}


void audioQuit (void) {SDL_CloseAudio();}