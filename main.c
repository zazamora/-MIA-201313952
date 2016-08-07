#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>

#include <estructuras.h>
#include <particiones.h>
#include <reportes.h>
#include <acciones.h>

//comentario
#define MAX_DIC_SZ 256



//DECLARANDO LOS METODOS
void inicio();
void leecad(char *cad, int n);
void SplitIgual(char* igual);
void SplitBlanco(char* blanco);
void SplitSlash(char* slash);
void getTokensIF(char* token);

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

void ImprimeEnca() {
    system("clear");
    printf("UNIVERSIDAD DE SAN CARLOS DE GUATEMALA\n");
    printf("FACULTAD DE INGENIERIA\n");
    printf("ESCUELA DE CIENCIAS Y SISTEMAS\n");
    printf("MANEJO E IMPLEMENTACION DE ARCHIVOS\n");
    printf("SECCION A+\n");
    printf("ERWIN SAUL PALACIOS MORALES 201313952\n\n");
    printf("PROYECTO_1\n\n");
    //printf("ESCRIBA EL DIRECTORIO DONDE SE GUARDARAN LOS ARHIVOS:\n");
}

//-----------------------------------------------------------------------------------------------------------
//LIMPIA PANTALLA PORQUE NO ME FUNCIONA EL SYSTEM("CLEAR")

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
    SplitBlanco(entrada);
    strcpy(entrada, "");
    inicio();
}

//-----------------------------------------------------------------------------------------------------------
//METODO QUE VERIFICA LOS TOKENS CON IF

void getTokensIF(char* token) {

    //IF DEL COMANDO MKDISK---------------------------------------------------------------------------------------
    if (strcasecmp(token, "mkdisk") == 0) {
        printf("\n********************** MKDISK *************************\n");
        int size;
        char unit[1];
        int tam;
        int cont;

        if (lista[1] != NULL) {
            SplitIgual(lista[1]);
            if (strcasecmp(sublista[0], "-size") == 0) {
                //printf("Viene -size");
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
            SplitIgual(lista[2]);
            if (strcasecmp(sublista[0], "+unit") == 0) {
                otro = size;
                strcpy(unit, sublista[1]);
                printf("<!> INFO: Tipo de unidad = %s\n", unit);
                //printf("ESTO HAY EN SUBLISTA: %s\n",sublista[0]);
                if (strcasecmp(unit, "K") == 0) {
                    //printf("VIENE K");
                    tam = otro*KB;
                    //printf("Esto tiene otro %d\n",otro);
                    //printf("Esto tiene K %d\n",tam);

                } else if (strcasecmp(unit, "M") == 0) {
                    //printf("VIENE M");
                    tam = otro * KB*KB;
                    //printf("Esto tiene size %d\n",otro);
                    //printf("Esto tiene M %d\n",tam);
                } else {
                    printf("<E> ERROR: DEBE DE ASIGNARLE UN PARAMETRO PERMITIDO A -UNIT\n");
                    bandera = 0;

                }
            } else if (strcasecmp(sublista[0], "-path") == 0) {
                strcpy(path, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", path);
                tam = size * KB*KB;

            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        if (lista[3] != NULL) {
            SplitIgual(lista[3]);
            if (strcasecmp(sublista[0], "-path") == 0) {
                strcpy(path, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", path);
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        if (lista[4] != NULL) {
            SplitIgual(lista[4]);
            if (strcasecmp(sublista[0], "-name") == 0) {
                SplitPunto(sublista[1]);
                if (strcasecmp(subListaN[1], "dsk") == 0) {
                    /*strcat(path, "/");
                    strcat(path, sublista[1]);*/
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
        //printf("Esto tiene tam %d\n",tam);
        printf("<!> INFO: Esto hay en PATH = %s\n", path);
        //printf("<!> INFO: Esto tiene bandera %d\n",bandera);
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
            SplitIgual(lista[1]);
            if (strcasecmp(sublista[0], "-path") == 0) {
                strcpy(ruta, sublista[1]);
                printf("<!> INFO: Ruta del disco = %s\n", ruta);
                bandera = 1;
            } else {
                printf("<E> ERROR: SE ESPERABA EL PARAMETRO OBLIGATORIO -PATH\n");
                bandera = 0;
            }
        }
        //printf("BANDERA: %d\n",bandera);
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

        //IF DEL COMANDO EXIT---------------------------------------------------------------------------------------
    else if (strcasecmp(token, "exit") == 0) {
        exit(0);

    }        //IF DEL COMANDO CLEAR---------------------------------------------------------------------------------------
    else if (strcasecmp(token, "clear") == 0) {
        limpiar();
    }
    bandera = 1;
}


//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT ESPACIO EN BLANCO

void SplitBlanco(char* blanco) {
    const char s[2] = " ";
    char *token;
    token = malloc(sizeof (char));
    token = strtok(blanco, s);
    int contador = 0;
    while (token != NULL) {
        lista[contador] = malloc(200);
        printf("%s\n", token);
        strcpy(lista[contador], token);
        printf("LISTA POSICION %d: %s\n", contador, lista[contador]);
        contador = contador + 1;
        token = strtok(NULL, s);
    }

    if (strncmp(lista[0], "#", 1) == 0) {
        printf("Entro a comentario\n");
    } else {
        //printf("ANTES DEL TOKEN");
        getTokensIF(lista[0]);
        //printf("DESPUES DEL TOKEN\n");
    }
}
//-----------------------------------------------------------------------------------------------------------
//METODO PARA SPLIT =

void SplitIgual(char* igual) {
    const char s[2] = "::";
    char *token;
    token = malloc(200);
    token = strtok(igual, s);
    int contador = 0;
    while (token != NULL) {
        sublista[contador] = malloc(200);
        //printf( "%s\n", token );
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
        printf("%s\n", token);
        //system("gnome mkdir /home/kris/Hola/Kristhal -p &");
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

//-----------------------------------------------------------------------------------------------------------
//METODO PARA CREAR DISCO

void CrearDisco(char* dir, int tam) {
    printf("ENTRO A CREAR DISCO\n");
    if (id < 26) {
        disco tempDisco;
        time_t tiempo = time(0);
        struct tm *tlocal = localtime(&tiempo);
        char fecha[15];
        char *idDisc;
        char identificador[1];
        char *rutaManejador;
        strftime(fecha, 128, "%d/%m/%y %H:%M", tlocal);
        tempDisco.direccion = malloc(200);
        rutaManejador = (char*) malloc(200);
        idDisc = (char*) malloc(10);
        strcpy(rutaManejador, "/home/saul/Desktop/manejador.dsk");
        strcpy(identificador, abecedario[id]);
        strcpy(idDisc, "vd");
        strcat(idDisc, identificador);
        printf("<!> INFO: Identificador de diso = %s \n", idDisc);
        strcpy(tempDisco.llave, idDisc);
        tempDisco.direccion = dir;
        tempDisco.estado = 1;
        FILE *indx = fopen(rutaManejador, "ab");
        fseek(indx, 0, SEEK_END);
        fwrite(&tempDisco, sizeof (disco), 1, indx);
        printf("%s | %s | %d\n\n", tempDisco.llave, tempDisco.direccion, tempDisco.estado);
        fclose(indx);
        //AQUI ESCRIBO EL DISCO
        int contador;
        contador = 1;
        MBR tempMBR;
        basura tempBasura;
        int i;

        if(mkdir(dir, 0777) == 0){
            printf("Se creo la carpeta.");
        }
        strcat(dir, "/");
        strcat(dir, sublista[1]);

        FILE *disc = fopen(dir, "ab");


        tempMBR.mbr_tamanio = tam;
        //printf("TAM=%d\n",tempMBR.mbr_tamanio);
        tempMBR.mbr_disk_signature = contador;
        //printf("CORRELATIVO=%d",tempMBR.mbr_disk_signature);
        strcpy(tempMBR.mbr_fecha_creacion, fecha);
        //printf("FECHA=%s",tempMBR.mbr_fecha_creacion);
        int j;
        for (j = 0; j < 4; j++) {
            strcpy(tempMBR.mbr_particion[j].part_status, "0");
            printf("<$> PART_STATUS=%s\n", tempMBR.mbr_particion[j].part_status);
            tempMBR.mbr_particion[j].part_type = malloc(1);
            strcpy(tempMBR.mbr_particion[j].part_type, "");
            printf("<$> PART_TYPE=%s\n", tempMBR.mbr_particion[j].part_type);
            strcpy(tempMBR.mbr_particion[j].part_fit, "");
            printf("<$> PART_FIT=%s\n", tempMBR.mbr_particion[j].part_fit);
            tempMBR.mbr_particion[j].part_start = 0;
            printf("<$> PART_START=%d\n", tempMBR.mbr_particion[j].part_start);
            tempMBR.mbr_particion[j].part_size = 0;
            printf("<$> PART_SIZE=%d\n", tempMBR.mbr_particion[j].part_size);
            strcpy(tempMBR.mbr_particion[j].part_name, "");
            printf("<$> PART_NAME=%s\n", tempMBR.mbr_particion[j].part_name);
            tempMBR.mbr_particion[j].part_id = j + 1;
            printf("<$> PART_ID=%d\n\n", tempMBR.mbr_particion[j].part_id);
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
    //printf("ENTRO A ELIMINAR\n");
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
    //char *directorio = malloc (MAX_DIC_SZ);
    system("clear");
    ImprimeEnca();

    /*fgets (directorio, MAX_DIC_SZ, stdin);
    if ((strlen(directorio)>0) && (directorio[strlen (directorio) - 1] == '\n'))
            directorio[strlen (directorio) - 1] = '\0';*/
    inicio();
    return EXIT_SUCCESS;
}
