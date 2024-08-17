/*******************************************************************************
 *  Copyright (c) 2002-2024 Christian Nowak <chnowak@web.de>                   *
 *   This file is part of chn's modplay.                                       *
 *                                                                             *
 *  modplay is free software: you can redistribute it and/or modify it         *
 *  under the terms of the GNU General Public License as published by the Free *
 *  Software Foundation, either version 3 of the License, or (at your option)  *
 *  any later version.                                                         *
 *                                                                             *          
 *  modplay is distributed in the hope that it will be useful, but             * 
 *  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY *
 *  or FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License    *
 *  for more details.                                                          *
 *                                                                             *
 *  You should have received a copy of the GNU General Public License along    *
 *  with modplay. If not, see <https://www.gnu.org/licenses/>.                 *
 *******************************************************************************/


#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "modplay/modplay.h"
#include <SDL.h>

void audio_callback(void *userdata, Uint8 *stream, int len) {

  MODFILE *mod = userdata;

  mod->mixingbuf = (void*)stream;
  mod->mixingbuflen = len;
  MODFILE_Player(mod);
}

int main(int argc, char * argv[]) {

  MODFILE mod;
  SDL_AudioSpec spec;
  memset( &spec, 0, sizeof( SDL_AudioSpec ) );
  SDL_AudioSpec obtained;

  printf("Sigma Player v0.10b (SDL)\n");
  printf("Copyright (c)2002, 2003, 2004, 2005, 2007 by Christian Nowak <chnowak@web.de>\n\n");

  if (argc != 2) {

    fprintf(stderr, "Usage: %s modfile\n", argv[0]);
    return -1;
  }

  if (SDL_Init(SDL_INIT_AUDIO) < 0) {

    fprintf(stderr,"Couldn't initialize SDL\n");
    return 1;
  }
  
  atexit(SDL_Quit);

  MODFILE_Init(&mod);

  if (MODFILE_Load(argv[1], &mod) < 0) {

    fprintf(stderr, "Couldn't load file\n");
    return -1;
  }

  spec.freq = 44100;
  spec.format = AUDIO_S16;
  spec.channels = 2;
  spec.samples = 4096;
  spec.callback = audio_callback;
  spec.userdata = &mod;

  SDL_AudioDeviceID audioDeviceID = SDL_OpenAudioDevice( NULL, 0, &spec, &obtained, 0 );
  if (audioDeviceID == 0) {

    fprintf(stderr, "Couldn't start audio: %s\n", SDL_GetError());
    MODFILE_Free(&mod);
    return -1;
  }

  mod.musicvolume = 64;
  mod.sfxvolume = 64;
  MODFILE_Start(&mod);

  MODFILE_SetFormat(&mod, obtained.freq, obtained.channels,
                    obtained.format == AUDIO_S16 || obtained.format == AUDIO_U16 ? 16 : 8,
                    obtained.format == AUDIO_S16 || obtained.format == AUDIO_S8);

  SDL_PauseAudioDevice(audioDeviceID, 0);

  scanf("\n");

  SDL_PauseAudioDevice(audioDeviceID, 1);
  MODFILE_Stop(&mod);
  SDL_CloseAudioDevice(audioDeviceID);
  MODFILE_Free(&mod);

  return 0;
}
