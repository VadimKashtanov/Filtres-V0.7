#include "selection.h"

//  Fonctions de score
float gain(Mdl_t * mdl, Env_t env) {
	float u = USDT;
	float p0, p1;
	//UNE_COURBE(s)
	FOR(DEPART, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		u += u*LEVIER*f(mdl, i)*(p1/p0-1.0);
		i += env.l;
	//	SUIVIE_COURBE(s, u)
	};
	//PLUMER_LA_COURBE(s)
	return u - USDT;
};

float prediction(Mdl_t * mdl, Env_t env) {
	float p = 0.0;
	float p0, p1;
	uint t = 0;
	FOR(DEPART, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		if (signe(p1/p0-1.0) == signe(-f(mdl, i))) p += 1.0;
		i += env.l;
		//
		t++;
	};
	return p / (float)t;
};

float investissement(Mdl_t * mdl, Env_t env) {
	float p = 1.0;
	float p0, p1, _f;
	uint t = 0;
	FOR(DEPART, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		_f = f(mdl, i);
		if (_f != 0) {
			t++;
			if (signe(p1/p0-1) == signe(_f)) p += 1.0;
		}
		i += env.l;
	};
	return p / (float)t;
};

float placement(Mdl_t * mdl, Env_t env) {
	float p = 0.0;
	uint t = 0;
	FOR(DEPART, i, PRIXS-1-env.l) {
		if (f(mdl, i) != 0.0) {p += 1.0;};
		i += env.l;
		t++;
	};
	return p / (float)t;
};

float gain_168H(Mdl_t * mdl, Env_t env) {
	float u = USDT;
	float p0, p1;
	FOR(JUSQUE, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		u += u*LEVIER*f(mdl, i)*(p1/p0-1.0);
		i += env.l;
	};
	return u - USDT;
};

float gain_JUSQUE_PRIXS(Mdl_t * mdl, Env_t env, float __LEVIER) {
	float u = USDT;
	float p0, p1;
	FOR(JUSQUE, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		u += u*__LEVIER*f(mdl, i)*(p1/p0-1.0);
		i += env.l;
	};
	return u - USDT;
};

float placements_168H(Mdl_t * mdl, Env_t env) {
	float p = 0.0;
	uint t = 0;
	FOR(JUSQUE, i, PRIXS-1-env.l) {
		if (f(mdl, i) != 0.0) {p += 1.0;};
		i += env.l;
		t++;
	};
	return p / (float)t;
};