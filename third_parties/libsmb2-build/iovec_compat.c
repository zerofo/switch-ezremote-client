/* newlib 没有 readv/writev/getlogin_r，这里提供简单实现（合并缓冲区读写） */
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>

struct iovec {
    void *iov_base;
    size_t iov_len;
};

ssize_t writev(int fd, const struct iovec *vector, int count)
{
    size_t total = 0;
    int i;
    char *buffer;

    for (i = 0; i < count; ++i) {
        if (((ssize_t)-1) - (ssize_t)total < (ssize_t)vector[i].iov_len) {
            errno = EINVAL;
            return -1;
        }
        total += vector[i].iov_len;
    }

    buffer = malloc(total);
    if (!buffer)
        return -1;

    size_t offset = 0;
    for (i = 0; i < count; ++i) {
        memcpy(buffer + offset, vector[i].iov_base, vector[i].iov_len);
        offset += vector[i].iov_len;
    }

    ssize_t written = write(fd, buffer, total);
    free(buffer);
    return written;
}

ssize_t readv(int fd, const struct iovec *vector, int count)
{
    size_t total = 0;
    int i;
    char *buffer;

    for (i = 0; i < count; ++i) {
        if (((ssize_t)-1) - (ssize_t)total < (ssize_t)vector[i].iov_len) {
            errno = EINVAL;
            return -1;
        }
        total += vector[i].iov_len;
    }

    buffer = malloc(total);
    if (!buffer)
        return -1;

    ssize_t read_bytes = read(fd, buffer, total);
    if (read_bytes < 0) {
        free(buffer);
        return -1;
    }

    size_t offset = 0;
    for (i = 0; i < count && offset < (size_t)read_bytes; ++i) {
        size_t copy = vector[i].iov_len < (size_t)(read_bytes - offset)
                       ? vector[i].iov_len
                       : (size_t)(read_bytes - offset);
        memcpy(vector[i].iov_base, buffer + offset, copy);
        offset += copy;
    }

    free(buffer);
    return read_bytes;
}

int getlogin_r(char *buf, size_t size)
{
    if (size > 5) {
        const char *user = "ezremote";
        size_t len = 0;
        while (user[len] && len + 1 < size)
            buf[len++] = user[len];
        buf[len] = '\0';
        return 0;
    }
    errno = ENOSPC;
    return -1;
}
