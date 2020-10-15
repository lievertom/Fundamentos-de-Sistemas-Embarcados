#include <data.h>


void date_hour (char * date, char * hour)
{
    time_t rawtime;
    struct tm * timeinfo;

    time(&rawtime);
    timeinfo = localtime(&rawtime);
    strftime(date, DATE_SIZE, "%F", timeinfo);
    strftime(hour, HOUR_SIZE, "%X", timeinfo);
}

void *save_data (void *args)
{
    Data *data = (Data *) args;
    char date[DATE_SIZE];
    char hour[HOUR_SIZE];

    date_hour (date, hour);
    FILE *file = fopen(PATH_DATA,"a+");

    /* If file is not defined, return */
    if(file == NULL)
    {
        printf("Error: File is not defined!\n");
        exit(3);
    }

    fseek (file, 0, SEEK_END);

    /* Add header if file is empty */
    if(ftell(file) == 0)
    {
        fprintf(file, "Date, Hour, Internal Temperature, External Temperature, Reference Tempearature\n");
    }

    /* Store data mean rounded with one decimal place */
    fprintf(file, "%s, %s, %0.2f, %0.2f, %0.2f,\n", date, hour, data->internal_temperature, data->external_temperature, data->reference_temperature);

    fclose(file);
    return NULL;
}
