// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <stdio.h>

// Include the trusted [[project-name]] header that is generated
// during the build. This file is generated by calling the
// sdk tool oeedger8r against the [[project-name]].edl file.
#include "[[project-name]]_t.h"

// This is the function that the host calls. It wraps
// a message from the host before calling back out to
// the host to print a message from there.
int ecall_handle_message(
    char* input_msg,
    char* enclave_msg,
    unsigned int enclave_msg_size)
{
    if (snprintf(
            enclave_msg,
            enclave_msg_size,
            "{ \"enclave\": %s, \"signature\": \"<TODO>\" }",
            input_msg) < 0)
    {
        fprintf(stderr, "message handling failed\n");
        return 1;
    }

    // Call back into the host
    int retval = 0;
    oe_result_t result = ocall_log(&retval, enclave_msg);
    if (result != OE_OK)
    {
        fprintf(
            stderr,
            "Call to ecall_handle_message failed: result=%u (%s)\n",
            result,
            oe_result_str(result));
        return 1;
    }

    return retval;
}

#define TA_UUID                                            \
    { /* [[generated-uuid]] */           \
        [[generated-uuid-part-1]], [[generated-uuid-part-2]], [[generated-uuid-part-3]],                        \
        {                                                  \
            [[generated-uuid-part-4-a]], [[generated-uuid-part-4-b]], [[generated-uuid-part-5-a]], [[generated-uuid-part-5-b]], [[generated-uuid-part-5-c]], [[generated-uuid-part-5-d]], [[generated-uuid-part-5-e]], [[generated-uuid-part-5-f]] \
        }                                                  \
    }

OE_SET_ENCLAVE_OPTEE(
    TA_UUID,
    1 * 1024 * 1024,
    12 * 1024,
    TA_FLAG_EXEC_DDR,
    "1.0.0",
    "[[project-name]]")
