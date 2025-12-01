#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <time.h>

#include "bankAccount.h"
#include "log.h"

unsigned long processCommandLine(int argc, char** argv) {
    if (argc == 2) {
        return strtoul(argv[1], 0, 10);
    } else if (argc == 1) {
        return 1;
    } else {
        fprintf(stderr, "\nUso: ./mutualExclusion [numThreads]\n");
        exit(1);
    }
}

void* child(void* buf) {
    int tid = (int)(unsigned long) buf;

    for (int i = 0; i < 1000; i++) {

        int op = rand() % 4;          // 0=dep,1=saque,2=consulta,3=transf
        int conta = rand() % NUM_CONTAS;

        switch (op) {
            case 0:  // depósito
                deposit(conta, 50);
                logOperacao(tid, "DEPÓSITO", conta, 50);
                break;

            case 1:  // saque
                if (withdraw(conta, 20))
                    logOperacao(tid, "SAQUE", conta, 20);
                else
                    logOperacao(tid, "SAQUE FALHOU", conta, 20);
                break;

            case 2: { // consulta
                double saldo = consulta(conta);
                logConsulta(tid, conta, saldo);
                break;
            }

            case 3: { // transferência
                int destino = rand() % NUM_CONTAS;
                double valor = 30;
                int ok = transferencia(conta, destino, valor);
                logTransfer(tid, conta, destino, valor, ok);
                break;
            }
        }
    }

    return NULL;
}

int main(int argc, char** argv) {
    unsigned long numThreads = processCommandLine(argc, argv);
    pthread_t* threads = malloc(numThreads * sizeof(pthread_t));

    srand(time(NULL));

    initContas();
    initLog();

    printf("Criando %lu threads...\n", numThreads);

    for (unsigned long i = 0; i < numThreads; i++) {
        pthread_create(&threads[i], NULL, child, (void*) i);
    }

    for (unsigned long i = 0; i < numThreads; i++) {
        pthread_join(threads[i], NULL);
    }

    printf("\n--- SALDOS FINAIS ---\n");
    for (int i = 0; i < NUM_CONTAS; i++) {
        printf("Conta %d: %.2f\n", i, saldos[i]);
    }

    closeLog();
    cleanupContas();

    free(threads);
    return 0;
}

