#ifndef PARTICIONES
#define PARTICIONES

#include "edd.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <time.h>
#include <math.h>

//AQUI ESTAN TODOS LOS METODOS:


//--------------------------------------------------------------------------------------------------------------------

void CrearParticion(int tam, char *rutaA, char *fitN, char *tipo, char *nombre) {
    printf("Entro a CrearParticion\n");
    MBR tempMBR;
    EBR tempEBR;
    EBR newEBR;
    int i = 0;
    int bandera;
    bandera = 1;
    FILE *archivoDisc = fopen(rutaA, "rb+");
    int inicio;
    inicio = sizeof (MBR);
    int estadoLogica = 0;
    int extendidas = 0;
    int tamTotal = 0;
    if (archivoDisc) {
        fseek(archivoDisc, 0, SEEK_SET);
        fread(&tempMBR, sizeof (MBR), 1, archivoDisc);
        int w;
        for(w = 0; w < 4; w++){
            tamTotal += tempMBR.mbr_particion[i].part_size;
            if(strcasecmp(tempMBR.mbr_particion[i].part_type, "E") == 0){
                fseek(archivoDisc, inicio + tamTotal, SEEK_SET);
                tempEBR.part_start = -1;
                fread(&tempEBR, sizeof(EBR), 1, archivoDisc);
                if(tempEBR.part_start != -1){
                    printf("<@> INFO: ENTRO A PARTICIONES LOGICAS");
                    while(tempEBR.part_start != -1){
                        extendidas += tempEBR.part_size;
                        fread(&tempEBR, sizeof(EBR), 1, archivoDisc);
                    }
                }
            }
        }
        fseek(archivoDisc, 0, SEEK_SET);
        fread(&tempMBR, sizeof (MBR), 1, archivoDisc);
        printf("********** Tam MBR: %d TamTotal: ", tempMBR.mbr_tamanio);
        if((tempMBR.mbr_tamanio - tamTotal) < tam){
            printf("<E> ERROR: ESPACIO INSUFICIENTE PARA NUEVA PARTICION");
        }else{
            for (i = 0; i < 4; i++) {
                inicio = inicio + tempMBR.mbr_particion[i].part_size;
                if(strcasecmp(tipo, "L") == 0  && bandera == 1){
                    if(strcasecmp(tempMBR.mbr_particion[i].part_type, "E") == 0){
                        int iniE = 0;
                        iniE = tempMBR.mbr_particion[i].part_start;
                        fseek(archivoDisc, inicio, SEEK_SET);
                        //if(extendidas < 1){
                            strcpy(newEBR.part_fit, fitN);
                            strcpy(newEBR.part_name, nombre);
                            newEBR.part_next = inicio + tam;
                            newEBR.part_size = tam;
                            newEBR.part_start = tempMBR.mbr_particion[i].part_start;
                            strcpy(newEBR.part_status, "0");
                            printf("<!> INFO: PARTICION LOGICA CREADA");
                            bandera = 0;
                        /*}else{
                            printf("<E> ERROR: NO HAY ESPACIO SUFICIENTE PARA PARTICION LOGICA ");
                            bandera = 0;
                        }*/
                    }
                }
                if (strcasecmp(tempMBR.mbr_particion[i].part_name, "") == 0 && bandera == 1) {
                    strcpy(tempMBR.mbr_particion[i].part_status, "0");
                    strcpy(tempMBR.mbr_particion[i].part_fit, fitN);
                    strcpy(tempMBR.mbr_particion[i].part_name, nombre);
                    tempMBR.mbr_particion[i].part_size = tam;
                    tempMBR.mbr_particion[i].part_type = malloc(1);
                    tempMBR.mbr_particion[i].part_type = tipo;
                    tempMBR.mbr_particion[i].part_start = inicio;
                    bandera = 0;
                }
                fseek(archivoDisc, 0, SEEK_SET);
                fwrite(&tempMBR, sizeof (MBR), 1, archivoDisc);
            }
        }
        fclose(archivoDisc);
    }
}


#endif // PARTICIONES
