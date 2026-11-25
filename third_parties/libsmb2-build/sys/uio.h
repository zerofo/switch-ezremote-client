#ifndef _SYS_UIO_COMPAT_H
/* newlib 没有 sys/uio.h；提供 struct iovec 与 readv/writev 原型 */
#pragma once

#include <stddef.h>
#include <sys/types.h> /* ssize_t */

struct iovec
{
    void *iov_base;
    size_t iov_len;
};

#ifdef __cplusplus
extern "C" {
#endif

ssize_t readv(int fd, const struct iovec *iov, int iovcnt);
ssize_t writev(int fd, const struct iovec *iov, int iovcnt);

#ifdef __cplusplus
}
#endif

#define IOV_MAX 1024
#endif
