/*************************************************************************
 * SCAMP Vision Chip Development System Library
 *------------------------------------------------------------------------
 * Copyright (c) 2020 The University of Manchester. All Rights Reserved.
 *
 *************************************************************************/

/*!

\file

\ingroup VS_SCAMP5_MODULE

\author Jianing Chen

*/

#ifndef SCAMP5_HPP
#define SCAMP5_HPP

#include <vs_m0.hpp>
#include <vs_scamp5.hpp>

#include <scamp5_output.hpp>
#include <scamp5_api_analog.hpp>
#include <scamp5_api_digital.hpp>

#ifdef __LPC43XX__
#include <scamp5_kernel_api.hpp>
#include <scamp5_kernel_api_macro_analog.hpp>
#include <scamp5_kernel_api_macro_digital.hpp>
#else
#include <sim_kernel_api.hpp>
#include <sim_kernel_api_macro_analog.hpp>
#include <sim_kernel_api_macro_digital.hpp>
#endif

#include <scamp5_sim.hpp>


#endif
