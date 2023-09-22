#include "mdl.h"

float COND5_f(float * x, float * poid, uint n) {
	float x0=x[0], x1=x[1];
	uint ix0;
	uint ix1;
	if (x0 > -0.6) {
		if (x0 > -0.2) {
			if (x0 > 0.2) {
				if (x0 > 0.6) {
					ix0 = 4;
				} else {
					ix0 = 3;
				}
			} else {
				ix0 = 2;
			}
		} else {
			ix0 = 1;
		}
	} else {
		ix0 = 0;
	}
	if (x1 > -0.6) {
		if (x1 > -0.2) {
			if (x1 > 0.2) {
				if (x1 > 0.6) {
					ix1 = 4;
				} else {
					ix1 = 3;
				}
			} else {
				ix1 = 2;
			}
		} else {
			ix1 = 1;
		}
	} else {
		ix1 = 0;
	}
	return poid[ix0*5+ix1];
};

#define __ROUGE_ROUGE "\033[41m_\033[0m"
#define __VERT_VERT  "\033[42m_\033[0m"
#define __ROUGE "\033[101m_\033[0m"
#define __VERT  "\033[102m_\033[0m"
#define __NEUTRE "\033[47m_\033[0m"

#define __ROUGE_ROUGE_zone "\033[41m-1.;-.6\033[0m"
#define __VERT_VERT_zone  "\033[42m+.6;+1.\033[0m"
#define __ROUGE_zone "\033[101m-.6;-.2\033[0m"
#define __VERT_zone  "\033[102m+.2;+.6\033[0m"
#define __NEUTRE_zone "\033[47m-.2;+.2\033[0m"

static char * couleurs[] = {__ROUGE_ROUGE, __ROUGE, __NEUTRE, __VERT, __VERT_VERT};
static char * couleurs_zone[] = {__ROUGE_ROUGE_zone, __ROUGE_zone, __NEUTRE_zone, __VERT_zone, __VERT_VERT_zone};

void COND5_plume_poids(Mdl_t * mdl, uint c) {
	ptr("COND5 #%i\n", c);
	FOR(0, y, mdl->y[c]) {
		uint depart = mdl->poid_depart[c] + y*25;
		printf("           ");
		FOR(0, i, 5) printf("%s ", couleurs_zone[i]);
		printf("\n");
		FOR(0, i, 5) {
			printf("%.3i-%.3i|%s%s|", depart + i*5, depart + (i+1)*5-1, couleurs[i], couleurs[i]);
			FOR(0, j, 5) {
				if (mdl->poid[depart + i*5 + j] < 0)
					printf("\033[4;41m %+1.2f \033[0m|", mdl->poid[depart + i*5 + j]);
				else if (mdl->poid[depart + i*5 + j] == 0)
					printf("\033[4;47m %+1.2f \033[0m|", mdl->poid[depart + i*5 + j]);
				else if (mdl->poid[depart + i*5 + j] >= 0)
					printf("\033[4;42m %+1.2f \033[0m|", mdl->poid[depart + i*5 + j]);
			}
			printf("\n");
		}
	}
};

void COND5_plume_config(Mdl_t * mdl, uint c) {
	printf("#%2.i COND5 n=%i:\n", c, mdl->n[c]);
	FOR(0, j, mdl->y[c])
		ptr("%3.i|\ty[%i] : cond5(%i,%i)\n", (mdl->y_depart[c]+j), j, j*2, j*2+1);
};