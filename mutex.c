#include <stdio.h>
#include <pthread.h>
#include <string.h>
#include <stdbool.h>
char buffer[100];
bool mutex = true;
bool empty = true;
bool full = false;
void wait(bool *available)
{
    while (!(*available))
        ;
    *available = false;
}
void signal(bool *available)
{
    *available = true;
}
void *produce(void *param)
{
    char data[] = "10100010101001000110";
    wait(&empty);
    wait(&mutex);
    for (int i = 0; i < strlen(data); i++)
    {
        buffer[i] = data[i];
    }
    printf("produced\n");
    signal(&mutex);
    signal(&full);
}
void *consume(void *param)
{
    wait(&full);
    wait(&mutex);
    for (int i = 0; i < strlen(buffer); i++)
    {
        printf("%c", buffer[i]);
    }
    printf("\nconsumed\n");
    signal(&mutex);
    signal(&empty);
}
int main()
{
    pthread_t threads[2];
    pthread_attr_t attributes;
    pthread_attr_init(&attributes);
    pthread_create(&threads[1], &attributes, produce, NULL);
    pthread_create(&threads[0], &attributes, consume, NULL);
    for (int i = 0; i < 2; i++)
    {
        pthread_join(threads[i], NULL);
    }
    // consume(NULL);
    // produce(NULL);
    return 0;
}