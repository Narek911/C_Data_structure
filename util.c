#include "util.h"

uint8_t get_crc8_inv(const uint8_t *data, size_t data_len,
                     uint8_t polynom, uint8_t preset)
{
    uint8_t crc;

    crc = preset;

    if (data) {
        size_t i, j;

        for (i = 0U; i < data_len; i++) {
            crc ^= data[i];
            for (j = 0U; j < 8U; j++) {
                if ((crc & 0x80U) != 0U) {
                    crc = (crc << 1U) ^ polynom;
                } else {
                    crc = crc << 1U;
                }
            }
        }
    }

    return crc;
}

uint16_t get_crc16(const uint8_t *data, size_t data_len,
                   uint16_t polynom, uint16_t preset)
{
    uint16_t crc;

    crc = preset;

    if (data) {
        size_t i, j;

        for (i = 0U; i < data_len; i++) {
            crc ^= (uint16_t)data[i];
            for (j = 0U; j < 8U; j++) {
                if ((crc & 0x0001U) != 0) {
                    crc = (crc >> 1U) ^ polynom;
                } else {
                    crc = crc >> 1U;
                }
            }
        }
    }

    return crc;
}

size_t split_str(char *s, char separator, char **parts, size_t max_count)
{
    size_t i, j, p, len;

    if (!s || !parts || max_count == 0U) {
        return 0;
    }

    len = strlen(s);

    for (i = 0U; i < max_count; i++) {
        parts[i] = NULL;
    }

    for (i = 0U, j = 0U, p = 0U; i < len && p < max_count; i++) {
        if (s[i] == separator) {
            s[i] = '\0';
            parts[p++] = s + j;
            j = i + 1U;
        }
    }

    if (p < max_count) {
        parts[p++] = s + j;
    }

    return p;
}

bool is_ipv4_address(const char *s)
{
    size_t len = strlen(s);
    size_t i, points_n;

    if (len < 7U || len > 15U) {
        return false;
    }

    points_n = 0U;

    for (i = 0U; i < len; i++) {
        if (s[i] == '.') {
            if (i > 0 && s[i - 1U] != '.') {
                points_n++;
            } else {
                return false;
            }
        } else if (s[i] < '0' || s[i] > '9') {
            return false;
        }
    }

    if (points_n != 3U) {
        return false;
    }

    return true;
}

uint32_t ipv4_to_u32(const char *s)
{
    size_t n;
    size_t len;
    uint32_t ipv4_u32 = 0U;
    char *parts[4U];
    char ipv4[16U];

    if (!is_ipv4_address(s)) {
        return ipv4_u32;
    }

    len = strlen(s);
    if (len >= sizeof ipv4) {
        return ipv4_u32;
    }

    strncpy(ipv4, s, sizeof ipv4 - 1U);
    ipv4[sizeof ipv4 - 1U] = '\0';

    n = split_str(ipv4, '.', parts, sizeof parts / sizeof parts[0U]);
    if (n != 4U) {
        return ipv4_u32;
    }

    ipv4_u32 |= (uint32_t)strtol(parts[0U], NULL, 10);
    ipv4_u32 <<= 8U;
    ipv4_u32 |= (uint32_t)strtol(parts[1U], NULL, 10);
    ipv4_u32 <<= 8U;
    ipv4_u32 |= (uint32_t)strtol(parts[2U], NULL, 10);
    ipv4_u32 <<= 8U;
    ipv4_u32 |= (uint32_t)strtol(parts[3U], NULL, 10);

    return ipv4_u32;
}

bool isdigit_str(char *s)
{
    size_t i, len = strlen(s);

    if (len == 0U || len > 20U) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (isdigit((unsigned char)s[i]) == 0) {
            return false;
        }
    }

    return true;
}

bool isfloat_str(char *s)
{
    size_t i, len = strlen(s);
    bool dot_found = false;

    if (len == 0U || len > 20U) {
        return false;
    }

    for (i = 0U; i < len; i++) {
        if (isdigit((unsigned char)s[i]) == 0) {
            if (i > 0 && s[i] == '.' && !dot_found) {
                dot_found = true;
                continue;
            }
            return false;
        }
    }

    return true;
}

void memcpy_inram(void * __restrict__ dst, const void * __restrict__ src,
                  size_t cnt)
{
    uint8_t *dst_u8 = (uint8_t *)dst;
    const uint8_t *src_u8 = (const uint8_t *)src;
    size_t i;

    for (i = 0U; i < cnt; i++) {
        dst_u8[i] = src_u8[i];
    }
}

uint8_t get_checksum(unsigned char *buf, size_t len)
{
    uint8_t result;
    size_t i;
    size_t j;
    
    result = 0xffU;

    for (i = 0U; i < len; i++)
    {
        result ^= buf[i];
        for (j = 0U; j < 8U; j++)
        {
            if ((result & 0x80U) != 0U)
            {
                result = (result << 1U) ^ 0x31U;
            }
            else
            {
                result = result << 1U;
            }
        }
    }

    return result;
}

/* taken from libhydrogen */
int hex2bin(uint8_t *bin, size_t bin_maxlen, const char *hex, size_t hex_len,
    const char *ignore, const char **hex_end_p)
{
    size_t        bin_pos = (size_t) 0U;
    size_t        hex_pos = (size_t) 0U;
    int           ret     = 0;
    unsigned char c;
    unsigned char c_alpha0, c_alpha;
    unsigned char c_num0, c_num;
    uint8_t       c_acc = 0U;
    uint8_t       c_val;
    unsigned char state = 0U;

    while (hex_pos < hex_len) {
        c        = (unsigned char) hex[hex_pos];
        c_num    = c ^ 48U;
        c_num0   = (c_num - 10U) >> 8;
        c_alpha  = (c & ~32U) - 55U;
        c_alpha0 = ((c_alpha - 10U) ^ (c_alpha - 16U)) >> 8;
        if ((c_num0 | c_alpha0) == 0U) {
            if (ignore != NULL && state == 0U && strchr(ignore, c) != NULL) {
                hex_pos++;
                continue;
            }
            break;
        }
        c_val = (uint8_t)((c_num0 & c_num) | (c_alpha0 & c_alpha));
        if (bin_pos >= bin_maxlen) {
            ret   = -1;
            errno = ERANGE;
            break;
        }
        if (state == 0U) {
            c_acc = c_val * 16U;
        } else {
            bin[bin_pos++] = c_acc | c_val;
        }
        state = ~state;
        hex_pos++;
    }
    if (state != 0U) {
        hex_pos--;
        errno = EINVAL;
        ret   = -1;
    }
    if (ret != 0) {
        bin_pos = (size_t) 0U;
    }
    if (hex_end_p != NULL) {
        *hex_end_p = &hex[hex_pos];
    } else if (hex_pos != hex_len) {
        errno = EINVAL;
        ret   = -1;
    }
    if (ret != 0) {
        return ret;
    }
    return (int) bin_pos;
}

int sck_data_to_hex(int fd, const unsigned char *in, size_t len,
    char *out, size_t out_size, int mode)
{
    size_t i;
    int size;
    const size_t prefix_fd_max_size = 32U;
    const size_t prefix_all_max_size = 64U;
    unsigned char ch;

    if (!in || !out)
    {
        return 0;
    }

    if (len > ((size_t)INT_MAX / 2) - prefix_all_max_size)
    {
        return 0;
    }

    if (out_size < prefix_all_max_size + len * 2U)
    {
        if (out_size > 0U)
            out[0U] = '\0';

        return 0;
    }

    size = snprintf(out, prefix_fd_max_size, "[#%i] ", fd);
    if (size < 0 || (size_t)size >= prefix_fd_max_size)
        size = 0;

    out[size++] = (mode == HEX_SND) ? '>' : '<';
    out[size++] = ' ';

    for (i = 0U; i < len; i++)
    {
        ch = in[i] >> 4U;
        if (ch <= (unsigned char)0x09U)
            out[size++] = (char)ch + '0';
        else
            out[size++] = (char)ch - (char)10 + 'a';

        ch = in[i] & (unsigned char)0x0fU;
        if (ch <= (unsigned char)0x09U)
            out[size++] = (char)ch + '0';
        else
            out[size++] = (char)ch - (char)10 + 'a';
    }

    out[size] = '\0';

    return size;
}

/*
 * cryptographically secure comparision of two strings
 *
 * returns -1 on error, 0 if the strings are equal, 1 otherwise
 */
int secure_compare(const char *a, const char *b)
{
    unsigned int len_a, len_b, len, eq, i;

    if (!a || !b)
        return -1;

    len_a = (unsigned int)strlen(a);
    len_b = (unsigned int)strlen(b);
    len = (len_a < len_b) ? len_a : len_b;

    eq = len_a ^ len_b;

    for (i = 0U; i < len; i++)
    {
        eq += (unsigned int)a[i] ^ (unsigned int)b[i];
    }

    return (eq == 0U) ? 0 : 1;
}
