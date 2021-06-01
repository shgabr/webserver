#include "HTTPService.h"

long HTTPService::getTimeStamp (string date_string)//gets the time and returns it
{
    const char * months[] = { "Jan", "Feb",
                             "Mar", "Apr",
                             "May", "Jun", "Jul",
                            "Aug","Sep","Oct","Nov","Dec"};
    struct tm timeinfo;
    char sec[3];
    char min[3];
    char hour[3];
    char day[3];
    char mon[3];
    char year[5];

    char month[4];
    char week_day[4];
    char utc[4];
    memset (sec,0,3);
    memset (min,0,3);
    memset (hour,0,3);
    memset (day,0,3);
    memset (mon,0,3);
    memset (year,0,5);
    memset (month,0,4);
    date_string[19]= ' ';
    date_string[22]= ' ';

    sscanf (date_string.c_str(),"%s %s %s %s %s %s %s %s", week_day,day, month, year,
           hour, min, sec,utc);
    for ( int i = 0 ; i < 12 ; i++)
    {
        if ( strcmp (months[i],month) == 0)
        {
            sprintf (mon,"%01d",i+1);
            break;
        }
    }
    string return_date_string = year;
    return_date_string += mon;
    return_date_string += day;
    return_date_string += hour;
    return_date_string += min;
    return_date_string += sec;

    return atol(return_date_string.c_str());
}

HTTPService::HTTPService(FileCache * p_fileCache,bool p_clean_cache)//constructor
{
    fileCache = p_fileCache;
    clean_cache=p_clean_cache;
}
HTTPService::~HTTPService()//destructor
{
    if (clean_cache && fileCache != NULL) delete (fileCache);
}
