#include <curl/curl.h>
#include <cjson/cJSON.h>
#include "utils.h"

int main(int argc, char *argv[])
{
    CURL *curl;
    CURLcode res;

    struct Memory chunk;
    chunk.data = malloc(1);  // initial buffer
    chunk.size = 0;

    curl = curl_easy_init();

    char urlreq[256];
    char tokenweather[] = "f3786404d317540398ce534959c0104b";

    sprintf(urlreq, "https://api.openweathermap.org/data/2.5/weather?q=%s&appid=%s", argv[1], tokenweather);
    if (curl) {
        curl_easy_setopt(curl, CURLOPT_URL, urlreq);

        curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, write_callback);
        curl_easy_setopt(curl, CURLOPT_WRITEDATA, (void *)&chunk);

        curl_easy_setopt(curl, CURLOPT_USERAGENT, "libcurl-agent/1.0");

        res = curl_easy_perform(curl);
        if (res != CURLE_OK) {
            fprintf(stderr, "curl error: %s\n", curl_easy_strerror(res));
        }

        // json data
        cJSON *json = cJSON_Parse(chunk.data);
        const cJSON *name         = cJSON_GetObjectItem(json, "name");
        const cJSON *main         = cJSON_GetObjectItem(json, "main");
        const cJSON *temp         = cJSON_GetObjectItem(main, "temp");
        const cJSON *weatherArray = cJSON_GetObjectItem(json, "weather");
        const cJSON *weather      = cJSON_GetArrayItem(weatherArray, 0);
        const cJSON *description  = cJSON_GetObjectItem(weather, "description");
        const cJSON *weatherMain  = cJSON_GetObjectItem(weather, "main");
        const cJSON *country      = cJSON_GetObjectItem(cJSON_GetObjectItem(json, "sys"), "country");

        if(json && name && main && temp && weatherArray && weather && description &&
           cJSON_IsString(name) && cJSON_IsNumber(temp) && cJSON_IsString(description)
        ) {
            printf("⠀          ⣀⠴⠢⠤⣀            ⠀& WeatherWave &\n");
            printf("       ⡔⣝⢏⠁⠀⠀⠀⢀⣉⣀⣀⡀          ---------------\n");
            printf("⠀⠀⢀⠤⢉⡩⠟⣓⡿⠁⠀⠀⡖⠁⠀⠀⠀⠀⠀⠉⠳⣄⠀⠀⠀⠀⠀⠀⠀location . : %s / %s\n", name->valuestring, country->valuestring);
            printf("⡠⣒⢯⢕⣫⡯⠗⠉⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡗⡆⠀⠀⠀⠀temperature: %1.f°C\n", temp->valuedouble - 273.15);
            printf("⠉⡜⢛⣿⡇⡏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⡄⠀⠀status . . : %s\n", weatherMain->valuestring);
            printf("⠀⠈⠉⠉⠁⠉⠛⠛⠉⠉⠉⠉⠁⠉⠁⠁⠁⠉⠉⠉⠒⠉⠁⠉⠀⠀⠀⠀⠀description: %s\n", description->valuestring);
            printf("                            ⠀last_uptade: %s\n", gettime());
        } else printf("Unable to retrieve data\n");

        cJSON_Delete(json);
        free(chunk.data);
        curl_easy_cleanup(curl);
    }

    return 0;
}
