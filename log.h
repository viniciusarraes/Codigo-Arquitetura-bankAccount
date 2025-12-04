#ifndef LOGGING_H
#define LOGGING_H

#include <stdio.h>
#include <pthread.h>

FILE *logFile0;
FILE *logFile1;
FILE *logFile2;
FILE *logFile3;
FILE *logFile4;
pthread_mutex_t logLock;

// inicializa o log
void initLog() {
    logFile0 = fopen("log0.txt", "w");
    logFile1 = fopen("log1.txt", "w");
    logFile2 = fopen("log2.txt", "w");
    logFile3 = fopen("log3.txt", "w");
    logFile4 = fopen("log4.txt", "w");
    pthread_mutex_init(&logLock, NULL);
}

// encerra log
void closeLog() {
    fclose(logFile0);
    fclose(logFile1);
    fclose(logFile2);
    fclose(logFile3);
    fclose(logFile4);
    pthread_mutex_destroy(&logLock);
}

// funções de log
void logOperacao(int tid, const char* tipo, int conta, double valor) {
    pthread_mutex_lock(&logLock);

    FILE *temp;

    if (conta == 0) {
        temp = logFile0;
    }
    else if (conta == 1) {
        temp = logFile1;
    }
    else if (conta == 2) {
        temp = logFile2;
    }
    else if (conta == 3) {
        temp = logFile3;
    }
    else {
        temp = logFile4;
    }

    fprintf(temp, "Thread %d: %s | Conta %d | Valor: %.2f\n",
            tid, tipo, conta, valor);
    pthread_mutex_unlock(&logLock);
}

void logConsulta(int tid, int conta, double saldo) {
    pthread_mutex_lock(&logLock);

    FILE *temp;

    if (conta == 0) {
        temp = logFile0;
    }
    else if (conta == 1) {
        temp = logFile1;
    }
    else if (conta == 2) {
        temp = logFile2;
    }
    else if (conta == 3) {
        temp = logFile3;
    }
    else {
        temp = logFile4;
    }

    fprintf(temp, "Thread %d: CONSULTA | Conta %d | Saldo: %.2f\n",
            tid, conta, saldo);
    pthread_mutex_unlock(&logLock);
}

void logTransfer(int tid, int origem, int destino, double valor, int sucesso) {
    pthread_mutex_lock(&logLock);

    FILE *temp1;
    FILE *temp2;

    if (origem == 0) {
        temp1 = logFile0;
    }
    else if (origem == 1) {
        temp1 = logFile1;
    }
    else if (origem == 2) {
        temp1 = logFile2;
    }
    else if (origem == 3) {
        temp1 = logFile3;
    }
    else if (origem == 4) {
        temp1 = logFile4;
    }

    if (destino == 0) {
        temp2 = logFile0;
    }
    else if (destino == 1) {
        temp2 = logFile1;
    }
    else if (destino == 2) {
        temp2 = logFile2;
    }
    else if (destino == 3) {
        temp2 = logFile3;
    }
    else if (destino == 4) {
        temp2 = logFile4;
    }

    if (sucesso) {
        fprintf(temp1, "Thread %d: TRANSF OK | %d → %d | Valor: %.2f\n",
                tid, origem, destino, valor);

        fprintf(temp2, "Thread %d: RECEBEU OK | %d → %d | Valor: %2.f\n",
                tid, origem, destino, valor);}
    else
        fprintf(temp1, "Thread %d: TRANSF FALHOU | %d → %d | Valor: %.2f\n",
                tid, origem, destino, valor);
    pthread_mutex_unlock(&logLock);
}

#endif

