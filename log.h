/* logging.h
 * Controle de log para operações bancárias.
 */

#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <pthread.h>

FILE *logFile;
pthread_mutex_t logLock;

// inicializa o log
void initLog() {
    logFile = fopen("log.txt", "w");
    pthread_mutex_init(&logLock, NULL);
}

// encerra log
void closeLog() {
    fclose(logFile);
    pthread_mutex_destroy(&logLock);
}

// funções de log
void logOperacao(int tid, const char* tipo, int conta, double valor) {
    pthread_mutex_lock(&logLock);
    fprintf(logFile, "Thread %d: %s | Conta %d | Valor: %.2f\n",
            tid, tipo, conta, valor);
    pthread_mutex_unlock(&logLock);
}

void logConsulta(int tid, int conta, double saldo) {
    pthread_mutex_lock(&logLock);
    fprintf(logFile, "Thread %d: CONSULTA | Conta %d | Saldo: %.2f\n",
            tid, conta, saldo);
    pthread_mutex_unlock(&logLock);
}

void logTransfer(int tid, int origem, int destino, double valor, int sucesso) {
    pthread_mutex_lock(&logLock);
    if (sucesso)
        fprintf(logFile, "Thread %d: TRANSF OK | %d → %d | Valor: %.2f\n",
                tid, origem, destino, valor);
    else
        fprintf(logFile, "Thread %d: TRANSF FALHOU | %d → %d | Valor: %.2f\n",
                tid, origem, destino, valor);
    pthread_mutex_unlock(&logLock);
}

#endif
