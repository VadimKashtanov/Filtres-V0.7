#pragma once

#include "macros.h"

float rnd();

//  =========== Factorielles ==============

extern const uint factoriel[13]; //il a 12 facto en i32 et 20 facto en i64, meme i128 en a que 34. Il est donc plus rentable de les ecrires toutes en liste.
//FACT(n) est dans macros.h

//  =========== Calcule Optimisee =========
float ___exp(register float x);

float ___gauss(register float x);
float ___d_gauss(register float x);

float ___logistique(register float x);    //  2*(tanh(x))+0.5
float ___d_logistique(register float x);

float ___tanh(register float x);			//  x/( 0.5 + fabs(x) )
float ___d_tanh(register float x);

//	====

float signe(register float x);

//  ========= Utilitaire =============

void gnuplot(float * arr, uint len, char * titre);

uint* cpyuint(uint * arr, uint len);
float* allouer_flotants(uint nb);

//	==== Maximum =====
uint u_max(uint * x, uint len);
