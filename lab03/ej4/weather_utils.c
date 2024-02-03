#include "weather_utils.h"
#include <limits.h>

int get_min_min_temp(WeatherTable a){
    int min_min_temp = INT_MAX;

    for (unsigned int year = 0; year < YEARS; year++){
        for (month_t month = january; month <= december; month++){
            for (unsigned int day = 0; day < DAYS; day++){
                if (min_min_temp > a[year][month][day]._min_temp){
                    min_min_temp = a[year][month][day]._min_temp;
                }
            }
        }
    }
    return min_min_temp;
}

void get_anual_max_max_temp(WeatherTable a, int out[YEARS]){
    for (unsigned int year = 0; year < YEARS; year++){
        int max_anual_temp = INT_MIN;
        for (month_t month = january; month <= december; month++){
            for (unsigned int day = 0; day < DAYS; day++){
                if (max_anual_temp < a[year][month][day]._max_temp){
                    max_anual_temp = a[year][month][day]._max_temp;
                }
            }
        }
        out[year] = max_anual_temp;
        printf("La mayor temperatura registrada del año %d fue %d\n", year+1980, out[year]);
    }
}

void get_max_monthly_rainfall(WeatherTable array, month_t output[YEARS]){
    for(unsigned int year = 0u; year < YEARS; ++year) {
        unsigned int max_rainfall;
        output[year] = january;
        for(month_t month=january; month <= december; ++month){
            unsigned int sum_rainfall = 0;
            for(unsigned int day=0u; day < DAYS; ++day){
                sum_rainfall += array[year][month][day]._rainfall;
            }
            if(month == january){
                max_rainfall = sum_rainfall;
            }else if(max_rainfall < sum_rainfall){
                max_rainfall = sum_rainfall;
                output[year] = month;
            }
        }
        printf("El mes con mayor precipitaciones de %d fue %d\n", year+1980, output[year] + 1);
    }
}
