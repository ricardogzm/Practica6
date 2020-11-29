#include "semaforos.h"


int iniciarSemaforo(key_t semkey){
    int status = 0, semid;

    if((semid = semget(semkey, 3, SEMPERM|IPC_CREAT|IPC_EXCL)) == -1){
        if(errno == EEXIST){
            semid = semget(semkey, 3, 0); //obtiene id de los semáforos si ya existen
        }
    }

    semctl(semid, 0, SETVAL, 0);
    semctl(semid, 1, SETVAL, 0);
    status = semctl(semid, 2, SETVAL, 1);

    if (semid  == -1 || status == -1) {
        perror("Error al iniciar semáforos.\n");
        return -1;
    } else {
        return semid; //exito
    }
}

int manejarSemaforo(int semid, int numsem, int op){  //manejo de semaforo con op
    struct sembuf buf;
    buf.sem_num = numsem;
    buf.sem_op = op;
    buf.sem_flg = SEM_UNDO;

    if (semop(semid, &buf, 1) == -1){
        perror("Error\n");//error al modificar semaforo
        exit(1);
    } else {
        return 0;
    }
}

