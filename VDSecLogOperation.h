#ifndef VDSECLOGOPERATION_H
#define VDSECLOGOPERATION_H


//////////////////////////////////////////////////////
//						//
// Lectura y escritura de sectores lógicos	//
//						//
//////////////////////////////////////////////////////
int vdreadseclog(int unidad_logica_o_particion,int sectorlog,char *buffer);

int vdwriteseclog(int unidad_logica_o_particion,int sectorlog,char *buffer);

int currdatetimetoint();

#endif /* VDSECLOGOPERATION_H */
