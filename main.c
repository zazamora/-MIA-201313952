#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <edd.h>
#include <particiones.h>
#include <reportes.h>


//comentario
#define MAX_DIC_SZ 256



//DECLARANDO LOS METODOS
void inicio();
void leecad(char *cad, int n);
void SplitDosPuntos(char* igual);
void SplitEspacio(char* blanco);
void SplitSlash(char* slash);
void getAnalizador(char* token);

//-----------------------------------------------------------------------------------------------------------
//VARIABLES GLOBALES
char entrada[400];
char compara[4];
char path[200];
char in[1024];
char *lista[8];
char *listaError[4] = {"", "", "", ""};
char *sublista[2];
int KB = 1024;
int otro = 0;
int bandera = 1;
int f1, f2;
int id = 0;
char *abecedario[26] = {"a", "b", "c", "d", "e", "f", "g", "h", "i", "j", "k", "l", "m",
    "n", "o", "p", "q", "r", "s", "t", "u", "v", "w", "x", "y", "z",};

char *subListaN[2];
char *subListaC[2];

void ImprimeEnca() {
    system("clear");
    printf("UNIVERSIDAD DE SAN CARLOS DE GUATEMALA\n");
    printf("FACULTAD DE INGENIERIA\n");
    printf("ESCUELA DE CIENCIAS Y SISTEMAS\n");
    printf("MANEJO E IMPLEMENTACION DE ARCHIVOS\n");
    printf("SECCION A+\n");
    printf("ERWIN SAUL PALACIOS MORALES 201313952\n\n");
    printf("PROYECTO_1\n\n");
}

//-----------------------------------------------------------------------------------------------------------
void limpiar() {
    printf("\033[2J\033[1;1H");
}
//-----------------------------------------------------------------------------------------------------------
//METODO QUE SE UTILIZARA PARA LEER LA CADENA SIN IMPORTAR ESPACIOS E INDICANDO EL TAMAÑO

void leecad(char *cad, int n) {
    int i, c;
    i = -1;
    c = getchar();
    if (c == EOF) {
        cad[i] = '\0';
        return;
    } else {
        cad[0] = c;
        i = 1;
    }
    for (; i < n - 1 && (c = getchar()) != EOF && c != '\n'; i++)
        cad[i] = c;
    cad[i] = '\0';
    if (c != '\n' && c != EOF)
        while ((c = getchar()) != '\n' && c != EOF);
    return;
}
//-----------------------------------------------------------------------------------------------------------
//METODO QUE INICIA EL PROCESO

void inicio() {
    printf("\nMIA-SAUL$ ");
    leecad(entrada, 300);
    printf("\n");
    //printf("ENTRADA: %s\n",entrada);
    SplitEspacio(entrada);
    strcpy(entrada, "");
    inicio();
}

//-----------------------------------------------------------------------------------------------------------
//METODO QUE VERIFICA LOS TOKENS CON IF

void getAnalizador(char* token) {

    //IF DEL COMANDO MKDISK---------------------------------------------------------------------------------------
    if (strcasecmp(token, "mkdisk") == 0) {
        printf("\n********************** MKDISK *************************\n");
        int size;
        char unit[1];
        int tam;
        if (lista[1] != NULL) {
            SplitDosPuntos(lista[1]);
            if (strcasecmp(sublista[0], "-size") == 0) {
                if (atoi(sublista[1]) >= 0) {
                    size = atoi(sublista[1]);
                    printf("<!> INFO: Tamano del disco = %d\n", size);
                } else {
                    printf("<E> ERROR: El tamaño que ingreso es invalido.\n");
                    bandera = 0;
                }
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -SIZE\n");
                bandera = 0;
            }
        }
        if (lista[2] != NULL) {
            SplitDosPuntos(lista[2]);
            if (strcasecmp(sublista[0], "+unit") == 0) {
                otro = size;
                strcpy(unit, sublista[1]);
                printf("<!> INFO: Tipo de unidad = %s\n", unit);
                if (strcasecmp(unit, "K") == 0) {
                    tam = otro*KB;
                }else if (strcasecmp(unit, "M") == 0) {
                    tam = otro * KB*KB;
                }else {
                    printf("<E> ERROR: DEBE DE ASIGNARLE UN PARAMETRO PERMITIDO A -UNIT\n");
                    bandera = 0;

                }
            } else if (strcasecmp(sublista[0], "-path") == 0) {
                SplitComillas(sublista[1]);
                strcpy(sublista[1], subListaC[0]);
                strcpy(path, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", path);
                tam = size * KB*KB;

            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        if (lista[3] != NULL) {
            SplitDosPuntos(lista[3]);
            if (strcasecmp(sublista[0], "-path") == 0) {
                SplitComillas(sublista[1]);
                strcpy(sublista[1], subListaC[0]);
                strcpy(path, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", path);
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        if (lista[4] != NULL) {
            SplitDosPuntos(lista[4]);
            if (strcasecmp(sublista[0], "-name") == 0) {
                SplitComillas(sublista[1]);
                strcpy(sublista[1], subListaC[0]);
                SplitPunto(sublista[1]);
                if (strcasecmp(subListaN[1], "dsk") == 0) {
                    strcat(sublista[1], ".dsk");
                    printf("<!> INFO: Nombre del archivo = %s\n", sublista[1]);
                }else{
                    printf("<E> ERROR: EXTENSION DE ARCHIVO INVALIDO.\n");
                    bandera = 0;
                }
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -NAME\n");
                bandera = 0;
            }
        }
        printf("<!> INFO: Esto hay en PATH = %s\n", path);
        if (bandera == 1) {
            CrearDisco(path, tam);
        }
    }
        //IF DEL COMANDO RMDISK---------------------------------------------------------------------------------------
    else if (strcasecmp(token, "rmdisk") == 0) {
        printf("\n********************** RMDISK *************************\n");
        char *ruta;
        ruta = malloc(sizeof (200));
        if (lista[1] != NULL) {
            SplitDosPuntos(lista[1]);
            if (strcasecmp(sublista[0], "-path") == 0) {
                SplitComillas(sublista[1]);
                strcpy(sublista[1], subListaC[0]);
                strcpy(ruta, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", ruta);
                bandera = 1;
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        if (bandera == 1) {
            printf("<!> Desea eliminar el archivo: %s(S/N)\n", ruta);
            leecad(compara, 2);
            if (strcasecmp(compara, "N") == 0 || strcasecmp(compara, "n") == 0) {
                printf("<E> ERROR: El archivo no fue eliminado.\n");
            } else if (strcasecmp(compara, "S") == 0 || strcasecmp(compara, "s") == 0) {
                EliminarDisco(ruta);
            } else {
                printf("<E> ERROR: La opcion que ingreso es incorrecta\n");

            }
        }
    }

//IF DEL COMANDO FDISK---------------------------------------------------------------------------------------

        else if (strcasecmp(token, "fdisk") == 0) {
            printf("Entro fdisk");
            bandera = 1;
            int aux;
            aux = 0;
            f1 = 0;
            f2 = 0;
            int size = 0;
            char *unit;
            char *fit;
            char *del;
            int tam = 0;
            char *ruta;
            char *name;
            int add;
            char *type;
            if (lista[1] != NULL) {
                SplitDosPuntos(lista[1]);
                if (strcasecmp(sublista[0], "-size") == 0) {
                    printf("Viene -size");
                    if (atoi(sublista[1]) >= 0) {
                        size = atoi(sublista[1]);
                        tam = size*KB;
                        printf("ESTO HAY EN TAMAÑO %d\n", size);
                    } else {
                        printf("El tamaño que ingreso es invalido");
                        bandera = 0;
                    }
                } else {
                    printf("SE ESPERABA -SIZE");
                    bandera = 0;
                }
            }
            if (lista[2] != NULL) {
                SplitDosPuntos(lista[2]);
                if (strcasecmp(sublista[0], "+unit") == 0 && f1 == 0 && f2 == 0) {
                    otro = size;
                    unit = malloc(1);
                    strcpy(unit, sublista[1]);
                    printf("ESTO HAY EN UNIT: %s\n", unit);
                    printf("ESTO HAY EN SUBLISTA: %s\n", sublista[0]);
                    if (strcasecmp(unit, "K") == 0) {
                        printf("VIENE K");
                        tam = otro*KB;
                        printf("Esto tiene otro %d\n", otro);
                        printf("Esto tiene K %d\n", tam);

                    } else if (strcasecmp(unit, "M") == 0) {
                        printf("VIENE M");
                        tam = otro * KB*KB;
                        printf("Esto tiene size %d\n", otro);
                        printf("Esto tiene M %d\n", tam);
                    } else if (strcasecmp(unit, "B") == 0) {
                        printf("VIENE B");
                        tam = otro;
                        printf("Esto tiene size %d\n", otro);
                        printf("Esto tiene B %d\n", tam);
                    } else {
                        printf("DEBE DE ASIGNARLE UN PARAMETRO PERMITIDO A +UNIT");
                        bandera = 0;
                    }
                }
            }
            if (lista[3] != NULL) {
                SplitDosPuntos(lista[3]);
                if (strcasecmp(sublista[0], "-path") == 0 && f1 == 0 && f2 == 0) {
                    ruta = malloc(200);
                    strcpy(ruta, sublista[1]);
                    printf("ESTO HAY EN PATH: %s\n", ruta);
                } else {
                    printf("SE ESPERABA PATH");

                }
            }

            if (lista[4] != NULL) {
                SplitDosPuntos(lista[4]);
                if (strcasecmp(sublista[0], "+type") == 0 && f1 == 0 && f2 == 0) {
                    printf("Entro +type");
                    printf("VIENE +Type\n");
                    if (strcasecmp(sublista[1], "P") == 0) {
                        type = malloc(1);
                        strcpy(type, sublista[1]);

                    } else if (strcasecmp(sublista[1], "E") == 0) {
                        type = malloc(1);
                        strcpy(type, sublista[1]);

                    } else if (strcasecmp(sublista[1], "L") == 0) {
                        type = malloc(1);
                        strcpy(type, sublista[1]);
                    } else {
                        printf("Debe asignarle un valor permitido a +type\n");
                        bandera = 0;
                    }

                } else {
                    printf("INGRESE UN COMANDO VALIDO");
                    bandera = 0;
                }
            }
            if (lista[5] != NULL) {
                SplitDosPuntos(lista[5]);
                if (strcasecmp(sublista[0], "+fit") == 0 && f1 == 0 && f2 == 0) {
                    printf("Entro +fit");
                    if (strcasecmp(sublista[1], "BF") == 0) {
                        fit = malloc(2);
                        strcpy(fit, sublista[1]);

                    } else if (strcasecmp(sublista[1], "FF") == 0) {
                        fit = malloc(2);
                        strcpy(fit, sublista[1]);


                    } else if (strcasecmp(sublista[1], "WF") == 0) {
                        fit = malloc(2);
                        strcpy(fit, sublista[1]);

                    } else {
                        printf("Asignele un valor correcto a +fit\n");
                    }

                } else {
                    bandera = 0;
                }
            }
            if (lista[6] != NULL) {
                SplitDosPuntos(lista[6]);
                if (strcasecmp(sublista[0], "-name") == 0 && f1 == 0 && f2 == 0) {
                    printf("Entro -name");
                    name = malloc(50);
                    strcpy(name, sublista[1]);

                } else {
                    bandera = 0;
                }
            }
            printf("ESTO TRAEN LAS F'S: %d, %d", f1, f2);
            //printf("size%d\n",tam);
            //printf("unit%s\n",unit);
            //printf("path%s\n",ruta);
            //printf("type%s\n",type);
            //printf("fit%s\n",fit);
            //printf("name%s\n",name);
            //printf("del%s\n",del);
            //printf("add%d\n",add);
            if (bandera == 1) {
                if (f1 == 0 && f2 == 0) {
                    CrearParticion(tam, ruta, fit, type, name);
                }
                if (f1 == 1) {
                    EliminarParticion(ruta, del, name);
                }
                if (f2 == 1) {
                    AgregarEspacio(ruta, tam, add, name);

                }
            }

        }



//IF DEL COMANDO EXIT---------------------------------------------------------------------------------------
    else if (strcasecmp(token, "exit") == 0) {
        exit(0);

    }
//IF DEL COMANDO CLEAR---------------------------------------------------------------------------------------
    else if (strcasecmp(token, "clear") == 0) {
        limpiar();
    }
    bandera = 1;
}


//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT ESPACIO EN BLANCO

void SplitEspacio(char* blanco) {
    const char s[2] = " ";
    char *token;
    token = malloc(sizeof (char));
    token = strtok(blanco, s);
    int contador = 0;
    while (token != NULL) {
        lista[contador] = malloc(200);
        //printf("%s\n", token);
        strcpy(lista[contador], token);
        printf("LISTA POSICION %d: %s\n", contador, lista[contador]);
        contador = contador + 1;
        token = strtok(NULL, s);
    }

    if (strncmp(lista[0], "#", 1) == 0) {
        printf("Entro a comentario\n");
    } else {
        //printf("ANTES DEL TOKEN");
        getAnalizador(lista[0]);
        //printf("DESPUES DEL TOKEN\n");
    }
}
//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT =

void SplitDosPuntos(char* igual) {
    const char s[2] = "::";
    char *token;
    token = malloc(200);
    token = strtok(igual, s);
    int contador = 0;
    while (token != NULL) {
        sublista[contador] = malloc(200);
        strcpy(sublista[contador], token);
        contador = contador + 1;
        token = strtok(NULL, s);
    }
}

//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT /

void SplitSlash(char* slash) {
    const char s[2] = "/";
    char *token;
    token = malloc(200);
    token = strtok(slash, s);
    while (token != NULL) {
        //printf("%s\n", token);
        token = strtok(NULL, s);
    }
}
//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT .

void SplitPunto(char* punto) {
    const char p[2] = ".";
    char *token;
    token = malloc(200);
    token = strtok(punto, p);
    int contador = 0;
    while (token != NULL) {
        subListaN[contador] = malloc(200);
        strcpy(subListaN[contador], token);
        contador = contador + 1;
        token = strtok(NULL, p);
    }
}

void SplitComillas(char* comilla){
    const char c[2] = "\"";
    char *token;
    token = malloc(200);
    token = strtok(comilla, c);
    int contador = 0;
    while(token != NULL){
        subListaC[contador] = malloc(200);
        strcpy(subListaC[contador], token);
        contador = contador + 1;
        token = strtok(NULL, c);
    }
}

//-----------------------------------------------------------------------------------------------------------
//METODO PARA CREAR DISCO

void CrearDisco(char* dir, int tam) {
    if (id < 26) {
        disco tempDisco;
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char fecha[15];
        char *idDisc;

        char *rutaManejador;
        strftime(fecha, 128, "%d/%m/%y %H:%M", tlocal);
        tempDisco.direccion = malloc(200);
        rutaManejador = (char*) malloc(200);
        idDisc = (char*) malloc(10);
        strcpy(rutaManejador, "/home/saul/Desktop/manejador.dsk");
        switch(id){
            case 0:strcpy(tempDisco.llave,"vda");break;
            case 1:strcpy(tempDisco.llave,"vdb");break;
            case 2:strcpy(tempDisco.llave,"vdc");break;
            case 3:strcpy(tempDisco.llave,"vdd");break;
            case 4:strcpy(tempDisco.llave,"vde");break;
            case 5:strcpy(tempDisco.llave,"vdf");break;
            case 6:strcpy(tempDisco.llave,"vdg");break;
            case 7:strcpy(tempDisco.llave,"vdh");break;
            case 8:strcpy(tempDisco.llave,"vdi");break;
            case 9:strcpy(tempDisco.llave,"vdj");break;
            case 10:strcpy(tempDisco.llave,"vdk");break;
            case 11:strcpy(tempDisco.llave,"vdl");break;
            case 12:strcpy(tempDisco.llave,"vdm");break;
            case 13:strcpy(tempDisco.llave,"vdn");break;
            case 14:strcpy(tempDisco.llave,"vdo");break;
            case 15:strcpy(tempDisco.llave,"vdp");break;
            case 16:strcpy(tempDisco.llave,"vdq");break;
            case 17:strcpy(tempDisco.llave,"vdr");break;
            case 18:strcpy(tempDisco.llave,"vds");break;
            case 19:strcpy(tempDisco.llave,"vdt");break;
            case 20:strcpy(tempDisco.llave,"vdu");break;
            case 21:strcpy(tempDisco.llave,"vdv");break;
            case 22:strcpy(tempDisco.llave,"vdw");break;
            case 23:strcpy(tempDisco.llave,"vdx");break;
            case 24:strcpy(tempDisco.llave,"vdy");break;
            case 25:strcpy(tempDisco.llave,"vdz");break;
        }
        printf("<!> INFO: Identificador de diso = %s \n", tempDisco.llave);

        if(mkdir(dir, 0777) == 0){
            printf("<!> INFO: Se ha creado la carpeta.");
        }

        strcat(dir, sublista[1]);
        tempDisco.direccion = dir;
        tempDisco.estado = 1;
        FILE *indx = fopen(rutaManejador, "ab");
        fseek(indx, 0, SEEK_END);
        fwrite(&tempDisco, sizeof (disco), 1, indx);
        printf("%s | %s | %d\n\n", tempDisco.llave, tempDisco.direccion, tempDisco.estado);
        fclose(indx);

        //ESCRITURA DEL DISCO
        int contador;
        contador = 1;
        MBR tempMBR;
        basura tempBasura;
        int i;
        FILE *disc = fopen(dir, "ab");
        tempMBR.mbr_tamanio = tam;
        tempMBR.mbr_disk_signature = contador;
        strcpy(tempMBR.mbr_fecha_creacion, fecha);
        int j;
        for (j = 0; j < 4; j++) {
            strcpy(tempMBR.mbr_particion[j].part_status, "0");
            tempMBR.mbr_particion[j].part_type = malloc(1);
            strcpy(tempMBR.mbr_particion[j].part_type, "");
            strcpy(tempMBR.mbr_particion[j].part_fit, "");
            tempMBR.mbr_particion[j].part_start = 0;
            tempMBR.mbr_particion[j].part_size = 0;
            strcpy(tempMBR.mbr_particion[j].part_name, "");
            tempMBR.mbr_particion[j].part_id = j + 1;
            /*printf("<$> PART_STATUS=%s      <$> PART_TYPE=%s\n", tempMBR.mbr_particion[j].part_status, tempMBR.mbr_particion[j].part_type);
            printf("<$> PART_FIT=%s     <$> PART_START=%d\n", tempMBR.mbr_particion[j].part_fit, tempMBR.mbr_particion[j].part_start);
            printf("<$> PART_SIZE=%d    <$> PART_NAME=%s\n", tempMBR.mbr_particion[j].part_size, tempMBR.mbr_particion[j].part_name);
            printf("<$> PART_ID=%d\n\n", tempMBR.mbr_particion[j].part_id);*/
        }
        fseek(disc, 0, SEEK_SET);
        fwrite(&tempMBR, sizeof (MBR), 1, disc);
        tam = (tam - sizeof (MBR)) / sizeof (basura);
        for (i = 0; i < tam; i++) {
            fseek(disc, 0, SEEK_END);
            strcpy(tempBasura.espacio, "");
            fwrite(&tempBasura, sizeof (basura), 1, disc);
            fflush(disc);
        }
        fclose(disc);
        contador = contador + 1;
        id++;
    }
}

//-----------------------------------------------------------------------------------------------------------
//METODO PARA ELIMINAR DISCO

void EliminarDisco(char *dir) {
    if (remove(dir) == 0) {
        printf("<!> INFO: El archivo fue eliminado satisfactoriamente.\n");
        FILE *eliminar = fopen("/home/saul/Desktop/manejador.dsk", "rb+");
        fseek(eliminar, 0L, SEEK_SET);
        disco temp;
        while (fread(&temp, sizeof (disco), 1, eliminar)) {
            if (feof(eliminar))
                break;
            if (strcmp(dir, temp.direccion) == 0) {
                temp.estado = 0;
            }
        }
        fclose(eliminar);
    } else {
        printf("<E> ERROR: No se pudo eliminar el archivo.\n");
    }

}

int main(void) {
    system("clear");
    ImprimeEnca();
    inicio();
    return EXIT_SUCCESS;
}
