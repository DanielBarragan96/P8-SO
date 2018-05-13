#include "VDSecLogOperation.h"

#include "DataTypeDefinitions.h"
#include "vdisk.h"

//////////////////////////////////////////////////////
//													//
// Lectura y escritura de sectores lógicos			//
//													//
//////////////////////////////////////////////////////
int vdreadseclog(int unidad_logica_o_particion,int sectorlog,char *buffer)
{
	int ncyl,nhead,nsec;
	ncyl=((sectorlog + SFIP - 1)/(sl_secfis*sl_heads)) + CIP;
	nhead=((sectorlog + SFIP - 1) + SIP)/sl_secfis%sl_heads;
	nsec=(sectorlog + SFIP - 1)%sl_secfis + 1;
	//printf("%d, %d, %d\n", ncyl, nhead, nsec);
	vdreadsector(unidad_logica_o_particion,nhead,ncyl,nsec,1,buffer);
	
	return 1;
}

int vdwriteseclog(int unidad_logica_o_particion,int sectorlog,char *buffer)
{
	int ncyl,nhead,nsec;
	ncyl=((sectorlog + SFIP - 1)/(sl_secfis*sl_heads)) + CIP;
	nhead=((sectorlog + SFIP - 1) + SIP)/sl_secfis%sl_heads;
	nsec=(sectorlog + SFIP - 1)%sl_secfis + 1;
	vdwritesector(unidad_logica_o_particion,nhead,ncyl,nsec,1,buffer);
	
	return 1;
}

