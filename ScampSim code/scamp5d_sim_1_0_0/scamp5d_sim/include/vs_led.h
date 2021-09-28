/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/

/*!

\file

\ingroup VS_COMMON_MODULE

\author Jianing Chen

*/

#ifndef VS_LED_H
#define VS_LED_H

#include <vs_common.h>


#define VS_LED_0   0
#define VS_LED_1   1
#define VS_LED_2   2


/*!
    \brief turn on an LED
*/
void vs_led_on(int idx);


/*!
    \brief turn off an LED
*/
void vs_led_off(int idx);


/*!
    \brief toggle on/off an LED
*/
void vs_led_toggle(int idx);


#endif
