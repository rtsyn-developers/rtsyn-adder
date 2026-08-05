
#include <stdlib.h>

#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/create.h"

rtsyn_abi_status_t RTSYN_ABI_CALL
rtsyn_adder_create(void **out_instance)
{

    if (!out_instance)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }

    rtsyn_adder_instance_t *adder =
        (rtsyn_adder_instance_t *)malloc(sizeof(rtsyn_adder_instance_t));

    if (!adder)
    {
        return RTSYN_ABI_STATUS_ERROR;
    }

    adder->left = 0.0;
    adder->right = 0.0;
    adder->sum = 0.0;
    adder->left_multiplier = 1.0;
    adder->right_multiplier = 1.0;
    *out_instance = adder;

    return RTSYN_ABI_STATUS_OK;
}
