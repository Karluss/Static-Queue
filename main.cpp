// Carlos Manoel Pedrosa de Oliveira - TIA: 32068549

#include <iostream>
#include "StaticQueue.h"
#include <ctime>
#include <climits>

using namespace std;

propriedadesAgua CreateAgua()
{
    propriedadesAgua agua =
    {
        ' ',
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0
    };

    return agua;
}

propriedadesAgua recebeDados(propriedadesAgua& agua, time_t t){
    t = time(0);
    tm *current = localtime(&t);
    cout << "\nInsira as informações para armazenar a água: \n" << endl;
    cout << "Marca: ";
    cin >> agua.marca;
    cout << "Estante: ";
    cin >> agua.estante;
    cout << "Prateleira: ";
    cin >> agua.prateleira;
    cout << "Gaveta: ";
    cin >> agua.gaveta;

    //Para imprimir a data e hora de uma maneira que o usuário consiga entender, me baseei no código do link abaixo:
    //https://stackoverflow.com/questions/5494166/c-timestamps-updating-output
    agua.dia = current->tm_mday;
    agua.mes = current->tm_mon+1;
    agua.ano = current->tm_year+1900;
    agua.hora = current->tm_hour;
    agua.minuto = current->tm_min;
    agua.segundos = current->tm_sec;

    return agua;
}


void EnqueueA(StaticQueue& queue ,propriedadesAgua& agua){
    Enqueue(queue, agua);
    cout << "Data: " << agua.dia << '/' << agua.mes << '/' << agua.ano << endl;
    cout << "Hora: " << agua.hora << ':' << agua.minuto << ':' << agua.segundos << endl;
}

void EnqueueB(StaticQueue& queue ,propriedadesAgua& agua){
    Enqueue(queue, agua);
    cout << "Data: " << agua.dia << '/' << agua.mes << '/' << agua.ano << endl;
    cout << "Hora: " << agua.hora << ':' << agua.minuto << ':' << agua.segundos << endl;
}

void DequeueA(StaticQueue& queue, propriedadesAgua& agua){
    if (IsEmpty(queue)){
        cout << "Estoque da marca A vazio. Não há nenhuma água para retirar." << endl;
    }
    else{
        cout << "\nA seguinte água está sendo retirada: \n" << endl;
        cout << "Marca: " << Front(queue).marca << endl;
        cout << "Estante: " << Front(queue).estante << endl;
        cout << "Prateleira: " << Front(queue).prateleira << endl;
        cout << "Gaveta: " << Front(queue).gaveta << endl;
        cout << "Data em que foi armazenada: " << Front(queue).dia << '/' << Front(queue).mes << '/' << Front(queue).ano << endl;
        cout << "Hora em que foi armazenada: " << Front(queue).hora << ':' << Front(queue).minuto << ':' << Front(queue).segundos << endl;
        Dequeue(queue);
    }
}

void DequeueB(StaticQueue& queue, propriedadesAgua& agua){
    if (IsEmpty(queue)){
        cout << "Estoque da marca B vazio. Não há nenhuma água para retirar." << endl;
    }
    else{
        cout << "\nA seguinte água está sendo retirada: \n" << endl;
        cout << "Marca: " << Front(queue).marca << endl;
        cout << "Estante: " << Front(queue).estante << endl;
        cout << "Prateleira: " << Front(queue).prateleira << endl;
        cout << "Gaveta: " << Front(queue).gaveta << endl;
        cout << "Data em que foi armazenada: " << Front(queue).dia << '/' << Front(queue).mes << '/' << Front(queue).ano << endl;
        cout << "Hora em que foi armazenada: " << Front(queue).hora << ':' << Front(queue).minuto << ':' << Front(queue).segundos << endl;
        Dequeue(queue);
    }
}

void DequeueAny(StaticQueue& queue1, StaticQueue& queue2, propriedadesAgua& agua){
    if (IsEmpty(queue1) && IsEmpty(queue2)){
        cout << "Estoque de ambas as marcas está vazio. Não há água para retirar." << endl;
    }
    else if (IsEmpty(queue1)){
        DequeueB(queue2,agua);
    }
    else if (IsEmpty(queue2)){
        DequeueA(queue1,agua);
    }
    else{
        if (Front(queue1).dia == Front(queue2).dia && Front(queue1).mes == Front(queue2).mes && Front(queue1).ano == Front(queue2).ano){
            if (Front(queue1).hora < Front(queue2).hora){
                DequeueA(queue1, agua);
            }
            else if (Front(queue1).hora < Front(queue2).hora){
                DequeueB(queue2, agua);
            }
            else{
                if (Front(queue1).minuto < Front(queue2).minuto){
                    DequeueA(queue1, agua);
                }
                else if (Front(queue1).minuto > Front(queue2).minuto){
                    DequeueB(queue2, agua);
                }
                else{
                    if (Front(queue1).segundos < Front(queue2).segundos){
                        DequeueA(queue1, agua);
                    }
                    else if (Front(queue1).segundos > Front(queue2).segundos){
                        DequeueB(queue2, agua);
                    }
                }
            }
        }
        else if (Front(queue1).dia < Front(queue2).dia){
            DequeueA(queue1, agua);
        }
        else if (Front(queue1).dia > Front(queue2).dia){
            DequeueB(queue2,agua);
        }
        else if (Front(queue1).mes < Front(queue2).mes){
            DequeueA(queue1,agua);
        }
        else if (Front(queue1).mes > Front(queue2).mes){
            DequeueB(queue2,agua);
        }
        else if (Front(queue1).ano < Front(queue2).ano){
            DequeueA(queue1,agua);
        }
        else if (Front(queue1).ano > Front(queue2).ano){
            DequeueB(queue2,agua);
        }
    }
}

int main()
{
    setlocale(LC_ALL, "Portuguese");
    StaticQueue queueA = Create();
    StaticQueue queueB = Create();
    propriedadesAgua agua = CreateAgua();
    int opcao;
    int retirar;
    time_t t;

    cout << "Bem vindo ao sistema!" << endl;
    cout << "---------------------------------------------" << endl;
    cout << "Insira o número de uma das opções abaixo: \n" << endl;
    cout << "1. Inserir água no estoque." << endl;
    cout << "2. Retirar uma água do estoque." << endl;
    cout << "3. Sair do sistema." << endl;
    cout << "\nOpção: ";
    cin >> opcao;
    while (opcao != 3){
        while (cin.fail()){
            //Neste trecho de código, para conseguir impedir o usuário de inserir um valor do tipo char, utilizei o algoritmo que está no seguinte link:
            //https://stackoverflow.com/questions/11523569/how-can-i-avoid-char-input-for-an-int-variable
            cin.clear();
            cin.ignore(INT_MAX, '\n');
            cout << "Opção inválida. Insira uma opção válida!\n";
            cout << "\nOpção: ";
            cin >> opcao;
        }
        while (opcao != 1 && opcao != 2 && opcao != 3){
            cout << "Opção inválida. Tente novamente: ";
            cin >> opcao;
        }

        if (opcao == 1){
            agua = recebeDados(agua,t);
            if (agua.marca == 'a' || agua.marca == 'A'){
                EnqueueA(queueA, agua);
            }
            else if (agua.marca == 'b' || agua.marca == 'B'){
                EnqueueB(queueB,agua);
            }
            else{
                cout << "Não foi possível cadastrar o produto. Marca inválida!" << endl;
            }

        }
        if (opcao == 2){
            cout << "\nEscolha uma das opções abaixo: " << endl;
            cout << "\n1.Retirar água da marca A." << endl;
            cout << "2.Retirar água da marca B." << endl;
            cout << "3.Retirar água de qualquer marca." << endl;
            cout << "\nOpção: ";
            cin >> retirar;

            if (retirar == 1){
                DequeueA(queueA,agua);
            }
            else if (retirar == 2){
                DequeueB(queueB, agua);
            }
            else if (retirar == 3){
                DequeueAny(queueA,queueB,agua);
            }
            else{
                cout << "Não foi possível realizar a operação. Opção inválida!" << endl;
            }
        }

        cout << endl << "---------------------------------------------" << endl;
        cout << "Insira o número de uma das opções abaixo: \n" << endl;
        cout << "1. Inserir água no estoque." << endl;
        cout << "2. Retirar uma água do estoque." << endl;
        cout << "3. Sair do sistema." << endl;
        cout << "\nOpção: ";
        cin >> opcao;
    }

}
