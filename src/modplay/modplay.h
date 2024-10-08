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


#ifndef __MODPLAY_H__
#define __MODPLAY_H__

#include "modplay_core.h"


#ifdef __cplusplus
extern "C" {
#endif

#define MODULE_MOD   1
#define MODULE_S3M   2
#define MODULE_XM    3


typedef struct MODFORMAT {

  int   (*set)(u8 *, int, MODFILE *);
  BOOL  (*is) (u8 *, int);
  int   (*getFormatID)(void);
  char *(*getDescription)(void);
  char *(*getAuthor)(void);
  char *(*getVersion)(void);
  char *(*getCopyright)(void);
} MODFORMAT;

extern const MODFORMAT mod_formats[];



int MODFILE_Load(const char *fname, MODFILE *mod);

void MODFILE_Start(MODFILE *s3m);
void MODFILE_Stop(MODFILE *s3m);
void MODFILE_Player(MODFILE *s3m);
void MODFILE_Free(MODFILE *mod);
void MODFILE_Init(MODFILE *mod);
void MODFILE_SetFormat(MODFILE *mod, int freq, int channels, int bits, BOOL mixsigned);
int MODFILE_Set(u8 *modfile, int modlength, MODFILE *mod);
BOOL MODFILE_Is(u8 *, int);

MOD_Instrument *MODFILE_MakeInstrument(void *rawData, int nBytes, int nBits);
int MODFILE_AllocSFXChannels(MODFILE *mod, int nChannels);
void MODFILE_TriggerSFX(MODFILE *mod, MOD_Instrument *instr, int channel, u8 note);

#ifdef __cplusplus
}
#endif

#endif
