#ifndef BANKACCOUNT_H
#define BANKACCOUNT_H

#include <pthread.h>

#define NUM_CONTAS 5

double saldos[NUM_CONTAS];
pthread_mutex_t locks[NUM_CONTAS];

// inicializa saldos e mutexes
void initContas() {
    for (int i = 0; i < NUM_CONTAS; i++) {
        saldos[i] = 0.0;
        pthread_mutex_init(&locks[i], NULL);
    }
}

// deposita
void deposit(int conta, double valor) {
    pthread_mutex_lock(&locks[conta]);
    saldos[conta] += valor;
    pthread_mutex_unlock(&locks[conta]);
}

// saque
int withdraw(int conta, double valor) {
    pthread_mutex_lock(&locks[conta]);
    if (saldos[conta] >= valor) {
        saldos[conta] -= valor;
        pthread_mutex_unlock(&locks[conta]);
        return 1;
    }
    pthread_mutex_unlock(&locks[conta]);
    return 0;
}

// consulta
double consulta(int conta) {
    pthread_mutex_lock(&locks[conta]);
    double r = saldos[conta];
    pthread_mutex_unlock(&locks[conta]);
    return r;
}

// transferência entre contas
int transferencia(int origem, int destino, double valor) {
    if (origem == destino) return 0;

    // evitar deadlock
    int primeiro = origem < destino ? origem : destino;
    int segundo  = origem < destino ? destino : origem;

    pthread_mutex_lock(&locks[primeiro]);
    pthread_mutex_lock(&locks[segundo]);

    if (saldos[origem] >= valor) {
        saldos[origem] -= valor;
        saldos[destino] += valor;
        pthread_mutex_unlock(&locks[segundo]);
        pthread_mutex_unlock(&locks[primeiro]);
        return 1;
    }

    pthread_mutex_unlock(&locks[segundo]);
    pthread_mutex_unlock(&locks[primeiro]);
    return 0;
}

// libera mutexes
void cleanupContas() {
    for (int i = 0; i < NUM_CONTAS; i++) {
        pthread_mutex_destroy(&locks[i]);
    }
}

#endif
