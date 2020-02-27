// Copyright (c) Open Enclave SDK contributors.
// Licensed under the MIT License.

#include <unistd.h>
#include "tlscli.h"

int main()
{
    int r;
    tlscli_t* cli = NULL;
    tlscli_err_t err;
    const char CRT_PATH[] = "/tmp/oe_attested_cert.der";
    const char PK_PATH[] = "/tmp/oe_private_key.pem";

    if ((r = tlscli_startup(&err)) != 0)
    {
        tlscli_put_err(&err);
        exit(1);
    }

    if ((r = tlscli_connect(
             true, "127.0.0.1", "12345", CRT_PATH, PK_PATH, &cli, &err)) != 0)
    {
        tlscli_put_err(&err);
        exit(1);
    }

    const char message[] = "abcdefghijklmnopqrstuvwxyz";

    for (size_t i = 0; i < 10; i++)
    {
        if ((r = tlscli_write(cli, message, sizeof(message), &err)) < 0)
        {
            tlscli_put_err(&err);
            exit(1);
        }

        char buf[1024];

        if ((r = tlscli_read(cli, buf, sizeof(buf), &err)) < 0)
        {
            tlscli_put_err(&err);
            exit(1);
        }

        printf("buf{%s}\n", buf);
    }

    tlscli_destroy(cli, &err);

    tlscli_shutdown(&err);

    return 0;
}
