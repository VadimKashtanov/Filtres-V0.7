#include "mdl.h"

typedef struct  {
	//	Chance de muter
	float MUTP_cst;
	float MUTP_p;
	float MUTP_ema_int;

	//	Taux d'heritage paternel
	float COEF_G_cst;
	float COEF_G_p;
	float COEF_G_ema_int;
	
	//  u += u*f*levier*( prix[i+l]/prix[i]-1 )
	uint l; //=3;
} Env_t;

//  Fonctions de score
float              gain(Mdl_t * mdl, Env_t env);					//	le gain exacte sur tout le `prix`
float        prediction(Mdl_t * mdl, Env_t env);					//	% de prediction de tendance
float    investissement(Mdl_t * mdl, Env_t env);					//	% de bon placement (donc ignorance de f(x)=0)
float         placement(Mdl_t * mdl, Env_t env);					//	% de bon placement (donc ignorance de f(x)=0)
float         gain_168H(Mdl_t * mdl, Env_t env);					//	gain dernier semaine avex x25
float gain_JUSQUE_PRIXS(Mdl_t * mdl, Env_t env, float __LEVIER);
float   placements_168H(Mdl_t * mdl, Env_t env);					//	nb de placement sur les dernieres 168H

extern uint SESSIONS;		// = 10
extern uint TAILLE_SESSION;	// = 500 ~= 3 semaines
void gain_pred_invest(Mdl_t * mdl, Env_t env,
	float *       _gain,
	float *       _pred,
	float *     _invest,
	float *      _place,
	float *  _gain_168H,
	float * _place_168H);  //Moyenne sur qlq sessions

//  Fonctions de Mutation
void        muter_filtres(Mdl_t * G, Mdl_t * P, Env_t env);
void          muter_poids(Mdl_t * G, Mdl_t * P, Env_t env);
void muter_ema_intervalle(Mdl_t * G, Mdl_t * P, Env_t env);

/*	Principe de selection :
		Scores: _gain, _pred, _invest ...
		  pts[i] -> 1*coef points :=: Score au dessus d'un autre model
		cintu[i] -> #rang du i-eme mdl
*/

extern uint MODE_DE_SCORE;// = 5
/*Valeur du rang dans les points
	0 : 1*pred + 1*gain
	1 : 1*pred
	2 : 	     1*gain
	3 : 2*pred + 1*gain
	4 : 1*pred + 2*gain
	5 : 1*pred + 1*gain + 1*invest + 1*place * 1*gain_168H + 1*place_168H
*/

typedef struct {
	uint Gs; uint Ps; uint T;
} Sel_t;

Mdl_t * sel2_filtres(
	Mdl_t * depart, Env_t env,
	Sel_t sel_filtres);

Mdl_t *   sel2_poids(
	Mdl_t * depart, Env_t env,
	Sel_t sel_filtres,
	Sel_t   sel_poids);

Mdl_t *      sel2_ei(
	Mdl_t * depart, Env_t env,
	Sel_t sel_filtres,
	Sel_t   sel_poids,
	Sel_t      sel_ei);