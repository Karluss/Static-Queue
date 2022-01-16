// Carlos Manoel Pedrosa de Oliveira - TIA: 32068549

#ifndef STATICQUEUE_H_INCLUDED
#define STATICQUEUE_H_INCLUDED

const int STATIC_QUEUE_CAPACITY = 100;

struct propriedadesAgua
{
    char marca;
    int dia;
    int mes;
    int ano;
    int hora;
    int minuto;
    int segundos;
    int estante;
    int prateleira;
    int gaveta;
};

struct StaticQueue
{
	int front;
	int rear;
	int count;

	propriedadesAgua values[STATIC_QUEUE_CAPACITY];
};


StaticQueue Create();


bool Enqueue(StaticQueue &queue, propriedadesAgua elem);


propriedadesAgua Dequeue(StaticQueue &queue);

propriedadesAgua Front(const StaticQueue &queue);


int Size(const StaticQueue &queue);


int Count(const StaticQueue &queue);

bool IsEmpty(const StaticQueue &queue);


bool Clear(StaticQueue &queue);


#endif // STATICQUEUE_H_INCLUDED
