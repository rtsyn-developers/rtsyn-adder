/**
 * @file rtsyn/internal/adder.h
 * @author Sergio Hidalgo (sergiohg.dev@gmail.com)
 * @brief Internal header file for the RTSyn Module Plugin Adder.
 *
 * SPDX-License-Identifier: GPL-3.0-or-later
 * @copyright Copyright (c) Sergio Hidalgo 2026
 */
#ifndef RTSYN_INTERNAL_ADDER_H
#define RTSYN_INTERNAL_ADDER_H
#include <stdint.h>

#ifdef __cplusplus
extern "C" {
#endif

typedef struct rtsyn_adder_instance_s {
    double left;
    double right;
    double sum;
    double left_multiplier;
    double right_multiplier;
} rtsyn_adder_instance_t;

typedef enum rtsyn_adder_instance_ports_e : uint32_t {
    RTSYN_ADDER_PORT_LEFT = 0,
    RTSYN_ADDER_PORT_RIGHT,
    RTSYN_ADDER_PORT_SUM,
    RTSYN_ADDER_PORT_COUNT,
} rtsyn_adder_instance_ports_t;

typedef enum rtsyn_adder_instance_params_e : uint32_t {
    RTSYN_ADDER_PARAM_LEFT_MULTIPLIER = 0,
    RTSYN_ADDER_PARAM_RIGHT_MULTIPLIER,
    RTSYN_ADDER_PARAM_COUNT,
} rtsyn_adder_instance_params_t;

typedef enum rtsyn_adder_instance_states_e : uint32_t {
    RTSYN_ADDER_STATE_RESULT = 0,
    RTSYN_ADDER_STATE_COUNT,
} rtsyn_adder_instance_states_t;

#ifdef __cplusplus
}
#endif

#endif /* RTSYN_INTERNAL_ADDER_H */
