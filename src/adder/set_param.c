#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/set_param.h"

rtsyn_abi_status_t RTSYN_ABI_CALL
rtsyn_adder_set_param(void *instance, uint32_t param_index, const void *value)
{
    rtsyn_adder_instance_t *adder = (rtsyn_adder_instance_t *)instance;

    if (!adder || !value)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }

    switch (param_index)
    {
    case RTSYN_ADDER_PARAM_LEFT_MULTIPLIER:
        adder->left_multiplier = *(const double *)value;
        return RTSYN_ABI_STATUS_OK;
    case RTSYN_ADDER_PARAM_RIGHT_MULTIPLIER:
        adder->right_multiplier = *(const double *)value;
        return RTSYN_ABI_STATUS_OK;
    default:
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }
}
