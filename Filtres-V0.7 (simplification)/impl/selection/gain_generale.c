#include "selection.h"

//	Resultat Tres exacte : S=20, TS=500
//	Assez approximatif : S=15 TS=400

uint SESSIONS = 20;
uint TAILLE_SESSION = 500;	// = ~3 semaines
	//	total = 20*500/env.l = 10.000/2 = 5.000 heures 

void gain_pred_invest(Mdl_t * mdl, Env_t env,
	float *       _gain,
	float *       _pred,
	float *     _invest,
	float *      _place,
	float *  _gain_168H,
	float * _place_168H)
{
	float       gain;
	float       pred;
	float     invest;
	float      place;
	float  gain_168H = USDT;
	float place_168H = 0.0;

	      (*_gain) = 0;
	      (*_pred) = 0;
	    (*_invest) = 0;
	     (*_place) = 0;
	 (*_gain_168H) = USDT;
	(*_place_168H) = 0.0;

	float p1, p0, _f;
	uint t, t_invest;

	FOR(0, s, SESSIONS) {
		uint depart = DEPART + (rand() % (JUSQUE-DEPART-TAILLE_SESSION));
		  gain = USDT;
		  pred = 0.0; t = 0;
		invest = 0.0; t_invest=0;
		 place = 0.0;
		FOR(0, i, TAILLE_SESSION) {
			p1 = prixs[i+env.l];
			p0 = prixs[i];
			_f = f(mdl, depart+i);
			
			//	--pred
			if (signe(_f) == signe(p1/p0-1)) pred += 1.0;

			if (_f != 0) {
				//  --place
				place += 1.0;
				
				//  --invest
				if (signe(_f) == signe(p1/p0-1)) invest += 1.0;

				//  --gain
				if (gain > 0) gain += gain * LEVIER * _f * (p1/p0 - 1.0);
				else if (gain != 0) gain = 0;

				t_invest++;
			}

			t++;

			i+=env.l;
		};
		  (*_gain) += (gain-USDT);
		  (*_pred) += pred   / (float)t;
		(*_invest) += invest / (float)t_invest;
		 (*_place) += place  / (float)t;
	}

	 gain_168H = USDT;
	place_168H = 0.0;
	t = 0;
	FOR(JUSQUE, i, PRIXS-1-env.l) {
		p1 = prixs[i+env.l];
		p0 = prixs[i];
		_f = f(mdl, i);
		if (_f != 0) {
			//	--place_168H
			place_168H += 1.0;

			//  --gain_168H
			if (gain_168H > 0) gain_168H += gain_168H * LEVIER * _f * (p1/p0 - 1.0);
			else if (gain_168H != 0) gain_168H = 0;
		};
		t++;
		i += env.l;
	}

	     (*_gain) /= (float)SESSIONS;
	     (*_pred) /= (float)SESSIONS;
	   (*_invest) /= (float)SESSIONS;
	    (*_place) /= (float)SESSIONS;

	 (*_gain_168H) = gain_168H - USDT;
	(*_place_168H) = place_168H / (float)t;
};