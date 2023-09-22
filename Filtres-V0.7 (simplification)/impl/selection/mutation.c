#include "selection.h"

void muter_filtres(Mdl_t * G, Mdl_t * P, Env_t env) {
	float COEF_G = env.COEF_G_cst;
	//
	float s[G->n[0]];
	float d[G->n[0]];
	//
	float r[G->n[0]];
	float _max, _max1, _min, _min1;
	float avant, apres;
	uint pos;
	FOR(0, i, G->y[0]) {
		if (rnd() <= env.MUTP_cst) {
#define SUR 2
			s[0] =  2*(rnd()-.5);
			d[0] =  2*(rnd()-.5);
			r[0] = s[0]/SUR+d[0];
			_max = r[0];
			_min = r[0];
			FOR(1, k, G->n[0]) {
				if (k % 1 == 0) s[k] = s[k-1] + (rnd()-.5);
				if (k % 2 == 0) d[k] = d[k-1] + (rnd()-.5)/2;
				r[k] = s[k]/SUR + d[k];
				//
				if (_max < r[k]) _max = r[k];
				if (_min > r[k]) _min = r[k];
			}
			//
			_max1 = 0;
			_min1 = 1;
			FOR(0, k, G->n[0]) {
				pos = i*G->n[0] + k;
				//
				avant = (k > 0 ? r[k-1] : r[0]);
				apres = (k < (G->n[0]-1) ? r[k+1] : r[G->n[0]-1]);
				//
				P->conste[pos] = COEF_G*G->conste[pos] + (1-COEF_G)*((avant+4*r[k]+apres)/6 - _min)/(_max-_min);
				if (P->conste[pos] > _max1) _max1 = P->conste[pos];
				if (P->conste[pos] < _min1) _min1 = P->conste[pos];
			};
			FOR(0, k, G->n[0]) {
				pos = i*G->n[0] + k;
				P->conste[pos] = (P->conste[pos]-_min1)/(_max1-_min1);
			}
		} else {
			memcpy(P->conste + i*G->n[0], P->conste + i*G->n[0], sizeof(float)*G->n[0]);
		}
	}
};

void muter_poids(Mdl_t * G, Mdl_t * P, Env_t env) {
	memcpy(P->poid, G->poid, sizeof(float)*G->poids);
	//
	uint pos;
	FOR(0, i, (uint)roundf((float)G->poids * proba)) {
		pos = rand() % G->poids;
		P->poid[pos] = poid_cond_le_plus_proche(
			COEF_G*G->poid[pos] + (1-COEF_G)*poid_cond_rnd());
	}
};

void muter_ema_intervalle(Mdl_t * G, Mdl_t * P, Env_t env) {
	memcpy(P->intervalles, G->intervalles, sizeof(uint)*G->y[0]);
	memcpy(P->ema, G->ema, sizeof(uint)*G->y[0]);
	//
	float proba = env.MUTP_ema_int;
	float COEF_G = env.COEF_G_ema_int;
	uint pos;
	FOR(0, i, (uint)roundf(0.5+(float)G->y[0]*proba)) {
		pos = rand() % G->y[0];
		//
		P->intervalles[pos] = (uint)roundf(
			COEF_G*G->intervalles[pos] + (1-COEF_G)*(rand()%INTERVALLES));
		P->ema[pos] = (uint)roundf(
			COEF_G*G->ema[pos] + (1-COEF_G)*(rand()%NB_DIFF_EMA));
	}
};