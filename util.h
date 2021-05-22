#define ARRAY_SIZE(a)                   ((sizeof(a) / sizeof(*(a))))
#define SET_BYTE(x, y, which)           ((x) |= ((y) << (which * 8)))
#define CLEAR_BYTE(x, type, which)      ((x) &= ~((type)0xff << (which * 8)))
#define GET_BYTE(n, k)                  (((n) >> (k * 8)) & 0xFF)
#define BIT_SET(x,which)                ((x) |=  (1<<(which)))
#define BIT_CLEAR(x,which)              ((x) &= ~(1<<(which)))
#define BIT_FLIP(x,which)               ((x) ^=  (1<<(which)))
#define BIT_CHECK(x,which)              ((x) &   (1<<(which)))

#define MIN(a, b) ((a) < (b) ? (a) : (b))
#define MAX(a, b) ((a) > (b) ? (a) : (b))


#define MOOG_E         2.71828182845904523536028747135266250
#define MOOG_LOG2E     1.44269504088896340735992468100189214
#define MOOG_LOG10E    0.434294481903251827651128918916605082
#define MOOG_LN2       0.693147180559945309417232121458176568
#define MOOG_LN10      2.30258509299404568401799145468436421
#define MOOG_PI        3.14159265358979323846264338327950288
#define MOOG_PI_2      1.57079632679489661923132169163975144
#define MOOG_PI_4      0.785398163397448309615660845819875721
#define MOOG_1_PI      0.318309886183790671537767526745028724
#define MOOG_2_PI      0.636619772367581343075535053490057448
#define MOOG_2_SQRTPI  1.12837916709551257389615890312154517
#define MOOG_SQRT2     1.41421356237309504880168872420969808
#define MOOG_SQRT1_2   0.707106781186547524400844362104849039
#define MOOG_INV_PI_2  0.159154943091895


#define STRUCT_RES(name)    name##__res
#define STRUCT_REQ(name)    name##__req

typedef union udata 
{
    struct __attribute__((packed)) STRUCT_REQ(data)
    {
       	/* some data */
    } req;
    
    struct __attribute__((packed)) STRUCT_RES(data)
    {
        /* some data */
    } res;
} data;