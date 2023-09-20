#pragma once

#include "etc.h"

#define USDT 100.0
#define LEVIER 10.0

#define PRIXS 53170//100000 		//100.000 * NB_DIFF_EMA * 32-flotant = NB_DIFF_EMA/10 * 1Mo = 0.1Mo * NB_DIFF_EMA
#define JUSQUE (PRIXS-24*7*4)	// 4 semaines
//#define MAX_GAIN 2001520.0

#define MAX_N_PREMIERE_COUCHE 10
#define MAX_INTERVALLE 1000
#define MAX_GLISSADE 10
#define DEPART 20000//((MAX_N_PREMIERE_COUCHE+MAX_GLISSADE)*MAX_INTERVALLE)

#define INTERVALLES 20
extern uint intervalles[INTERVALLES]; // = {1 -> 1000}


extern float prixs[PRIXS];

//0, 3, 5, 10, 25, 50, 100, 250, 500, 1000
#define NB_DIFF_EMA 10
#define MAX_EMA NB_DIFF_EMA

extern float ema[NB_DIFF_EMA][PRIXS];
extern float probas_choix_ema[NB_DIFF_EMA];

void charger_les_prixs();