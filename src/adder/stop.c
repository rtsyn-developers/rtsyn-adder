#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/stop.h"

rtsyn_abi_status_t RTSYN_ABI_CALL
rtsyn_adder_stop(void *instance)
{
    rtsyn_adder_instance_t *adder = (rtsyn_adder_instance_t *)instance;
    if (!adder)
    {
        return RTSYN_ABI_STATUS_INVALID_ARGUMENT;
    }
    adder->left = 0.0;
    adder->right = 0.0;
    adder->sum = 0.0;

    return RTSYN_ABI_STATUS_OK;
}
