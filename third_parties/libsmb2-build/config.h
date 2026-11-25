#ifndef SMB2_CONFIG_H
#define SMB2_CONFIG_H

/* Switch (devkitA64/newlib) 构建配置 */
#define PACKAGE "libsmb2"
#define PACKAGE_BUGREPORT "ronniesahlberg@gmail.com"
#define PACKAGE_NAME "libsmb2"
#define PACKAGE_STRING "libsmb2 6.1.0"
#define PACKAGE_TARNAME "libsmb2"
#define PACKAGE_URL "https://github.com/sahlberg/libsmb2"
#define PACKAGE_VERSION "6.1.0"
#define VERSION "6.1.0"

#define STDC_HEADERS 1
#define HAVE_ARPA_INET_H 1
#define HAVE_DLFCN_H 1
#define HAVE_ERRNO_H 1
#define HAVE_FCNTL_H 1
#define HAVE_SYS_FCNTL_H 1
#define HAVE_INTTYPES_H 1
#define HAVE_NETDB_H 1
#define HAVE_NETINET_IN_H 1
#define HAVE_NETINET_TCP_H 1
#define HAVE_POLL_H 1
#define HAVE_SOCKADDR_LEN 1
#define HAVE_SOCKADDR_STORAGE 1
#define HAVE_LINGER 1
#define HAVE_STDINT_H 1
#define HAVE_STDIO_H 1
#define HAVE_STDLIB_H 1
#define HAVE_STRINGS_H 1
#define HAVE_STRING_H 1
#define HAVE_SYS_IOCTL_H 1
#define HAVE_SYS_POLL_H 1
#define HAVE_SYS_SOCKET_H 1
#define HAVE_SYS_STAT_H 1
#define HAVE_SYS_TYPES_H 1
#define HAVE_SYS_UIO_H 1
#define HAVE_TIME_H 1
#define HAVE_SYS_TIME_H 1
#define HAVE_UNISTD_H 1
#define HAVE_SYS_UNISTD_H 1

/* Switch 构建通过 -D__SWITCH__ 走 libsmb2 官方 Nintendo compat 块；不用 krb5/gssapi */
#endif
