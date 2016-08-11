#ifndef ESTRUCTURAS
#define ESTRUCTURAS
#include <time.h>

//ESTRUCTURA DE BASURA
typedef struct Basura{
    char espacio[1024];
}basura;

//ESTRUCTURA DE DISCO
typedef struct Disk{
    int estado;
    char llave[3];
    char *direccion;
}disco;

//ESTRUCTURA DE PARTICIONES
typedef struct Particiones{
    char part_status[1];
    char *part_type;
    char part_fit[2];
    int part_start;
    int part_size;
    char part_name[16];
    int part_id;

}Particion;

//ESTRUCTURA DEL MASTER BOOT RECORD
typedef struct MasterBootRecord{
    int mbr_tamanio;
    char mbr_fecha_creacion[15];
    int mbr_disk_signature;
    Particion mbr_particion[4];
}MBR;

//ESTRUCTURA DEL EXTENDED BOOT RECORD

typedef struct ExtendedBootRecord{
    char part_status;
    char part_fit;
    int part_start;
    int part_size;
    int part_next;
    char part_name[16];

}EBR;

//ESTRUCTURA DEL SUPER BLOQUE

typedef struct SuperBloque{
    int s_inodes_count;
    int s_blocks_count;
    int s_free_blocks_count;
    int s_free_inodes_count;
    char s_mtime[17];
    char s_umtime[17];
    int s_mnt_count;
    char s_magic[6];
    int s_inode_size;
    int s_block_size;
    int s_first_ino;
    int s_first_blo;
    int s_bm_inode_start;
    int s_bm_block_start;
    int s_inode_start;
    int s_block_start;
}SB;



#endif // ESTRUCTURAS

