#include "mdl.h"

#define N 4
uint params[N] = {C_max, Y_max, FLTR_max, N_max};

void ecrire_mdl(Mdl_t * mdl, char * file) {
	FILE * fp = fopen(file, "wb");
	if (fp == 0) ERR("Fichier %s existse pas", file);
	//
	(void)fwrite(params, sizeof(uint), N, fp);
	(void)fwrite(mdl, sizeof(Mdl_t), 1, fp);
	fclose(fp);
}

Mdl_t * lire_mdl(char * file) {
	FILE * fp = fopen(file, "rb");
	if (fp == 0) ERR("Fichier %s existse pas", file);

	uint autres[N];
	(void)!fread(autres, sizeof(uint), N, fp);
	FOR(0, i, N) assert(params[i] == autres[i]);
	Mdl_t * ret = malloc(sizeof(Mdl_t));
	(void)!fread(ret, sizeof(Mdl_t), 1, fp);
	return ret;
};
