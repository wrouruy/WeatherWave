#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <curl/curl.h>
#include <time.h>

struct Memory {
    char *data;
    size_t size;
};

// a function that adds the received bytes to the buffer
size_t write_callback(void *contents, size_t size, size_t nmemb, void *userp)
{
    size_t totalSize = size * nmemb;
    struct Memory *mem = (struct Memory *)userp;

    char *ptr = realloc(mem->data, mem->size + totalSize + 1);
    if (!ptr) return 0; // error of memory

    mem->data = ptr;
    memcpy(&(mem->data[mem->size]), contents, totalSize);
    mem->size += totalSize;
    mem->data[mem->size] = '\0'; // end of line

    return totalSize;
}

char *gettime(void)
{
    char *result = malloc(16);
    if (!result) return NULL;

    time_t now = time(NULL);
    struct tm *splitTime = localtime(&now);

    snprintf(result, 32, "%d.%d.%d", splitTime->tm_mday, splitTime->tm_mon + 1, splitTime->tm_year + 1900);
    return result;
}
