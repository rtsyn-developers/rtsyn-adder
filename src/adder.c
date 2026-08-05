#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#include "rtsyn/adder.h"
#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/create.h"
#include "rtsyn/internal/adder/destroy.h"
#include "rtsyn/internal/adder/process.h"
#include "rtsyn/internal/adder/read_state.h"
#include "rtsyn/internal/adder/set_param.h"
#include "rtsyn/internal/adder/start.h"
#include "rtsyn/internal/adder/stop.h"

static const rtsyn_abi_port_descriptor_t rtsyn_adder_ports[RTSYN_ADDER_PORT_COUNT] = {
    [RTSYN_ADDER_PORT_LEFT] =
        {
            .name = "left",
            .value_type = RTSYN_ABI_VALUE_F64,
            .direction = RTSYN_ABI_PORT_DIRECTION_IN,
        },
    [RTSYN_ADDER_PORT_RIGHT] =
        {
            .name = "right",
            .value_type = RTSYN_ABI_VALUE_F64,
            .direction = RTSYN_ABI_PORT_DIRECTION_IN,
        },
    [RTSYN_ADDER_PORT_SUM] =
        {
            .name = "sum",
            .value_type = RTSYN_ABI_VALUE_F64,
            .direction = RTSYN_ABI_PORT_DIRECTION_OUT,
        },
};

static const rtsyn_abi_param_descriptor_t rtsyn_adder_params[RTSYN_ADDER_PARAM_COUNT] = {
    [RTSYN_ADDER_PARAM_LEFT_MULTIPLIER] =
        {
            .name = "left_multiplier",
            .description = "Constant multiplier applied to the left operand",
            .value_type = RTSYN_ABI_VALUE_F64,
        },
    [RTSYN_ADDER_PARAM_RIGHT_MULTIPLIER] =
        {
            .name = "right_multiplier",
            .description = "Constant multiplier applied to the right operand",
            .value_type = RTSYN_ABI_VALUE_F64,
        },
};

static const rtsyn_abi_state_descriptor_t rtsyn_adder_states[RTSYN_ADDER_STATE_COUNT] = {
    [RTSYN_ADDER_STATE_RESULT] =
        {
            .name = "result",
            .description = "Most recently computed result",
            .value_type = RTSYN_ABI_VALUE_F64,
        },
};

static const rtsyn_abi_node_descriptor_t rtsyn_adder_descriptor = {
    .name = "adder",
    .node_type = RTSYN_ABI_NODE_PLUGIN,
    .port_count = RTSYN_ADDER_PORT_COUNT,
    .ports = rtsyn_adder_ports,
    .param_count = RTSYN_ADDER_PARAM_COUNT,
    .params = rtsyn_adder_params,
    .state_count = RTSYN_ADDER_STATE_COUNT,
    .states = rtsyn_adder_states,
    .callbacks =
        {
            .create = rtsyn_adder_create,
            .set_param = rtsyn_adder_set_param,
            .read_state = rtsyn_adder_read_state,
            .start = rtsyn_adder_start,
            .process = rtsyn_adder_process,
            .stop = rtsyn_adder_stop,
            .destroy = rtsyn_adder_destroy,
        },
};

const rtsyn_abi_node_descriptor_t *RTSYN_ABI_CALL
rtsyn_adder_get_descriptor(void)
{
    return &rtsyn_adder_descriptor;
}

const rtsyn_abi_node_descriptor_t *RTSYN_ABI_CALL
rtsyn_module_get_descriptor(void)
{
    return rtsyn_adder_get_descriptor();
}
