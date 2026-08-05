#include <stdlib.h>

#include "rtsyn/internal/adder.h"
#include "rtsyn/internal/adder/destroy.h"

void RTSYN_ABI_CALL
rtsyn_adder_destroy(void *instance)
{
    rtsyn_adder_instance_t *adder = (rtsyn_adder_instance_t *)instance;
    free(adder);
}
