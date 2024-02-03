#ifndef _WEATHER_UTILS_H
#define _WEATHER_UTILS_H

#include <stdbool.h>
#include "weather.h"
#include "array_helpers.h"

// @brief Obtiene la minima temperatura histórica registrada
// @param[in] a arreglo de tipo estructura Tabla de Clima
int get_min_min_temp(WeatherTable a);

// @brief Obtiene la máxima temperatura registrada por año entre 1980 y 2016
// @param[in] a arreglo de tipo estructura Tabla de Clima
// @param[in] out arreglo de años
void get_anual_max_max_temp(WeatherTable a, int out[YEARS]);

// @brief Obtiene la máxima cant de precipitaciones registrada por mes
// @param[in] a arreglo de tipo estructura Tabla de Clima
// @param[in] out arreglo de meses
void get_max_monthly_rainfall(WeatherTable a, month_t out[YEARS]);

#endif