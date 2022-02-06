#include <stdint.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdlib.h>

#define GET_ARRAY_LEN( arrayName )      (sizeof( arrayName ) / sizeof(( arrayName)[ 0 ] ))
#define SET_BYTE(x, y, which)           ((x) |= ((y) << (which * 8)))
#define CLEAR_BYTE(x, type, which)      ((x) &= ~((type)0xff << (which * 8)))
#define GET_BYTE(n, k)                  (((n) >> (k * 8)) & 0xFF)
#define BIT_SET(x,which)                ((x) |=  (1<<(which)))
#define BIT_CLEAR(x,which)              ((x) &= ~(1<<(which)))
#define BIT_FLIP(x,which)               ((x) ^=  (1<<(which)))
#define BIT_CHECK(x,which)              ((x) &   (1<<(which)))

#define MEMCPY(DESTARR, SRCARR, ARRSIZE, ELLTYPE) \
    { struct _tmparrwrap_ { ELLTYPE xx[ARRSIZE]; }; *((struct _tmparrwrap_ *) DESTARR) = *((struct _tmparrwrap_ *) SRCARR); }
    
#ifndef MIN
#define MIN( n1, n2 )   ((n1) > (n2) ? (n2) : (n1))
#endif

#ifndef MAX
#define MAX( n1, n2 )   ((n1) > (n2) ? (n1) : (n2))
#endif

/* Determine whether the given signed or unsigned integer is odd. */
#define IS_ODD( num )   ((num) & 1)

/* Determine whether the given signed or unsigned integer is even. */
#define IS_EVEN( num )  (!IS_ODD( (num) ))

/**
Determine whether the given number is between the other two numbers
(both inclusive).
*/
#define IS_BETWEEN( numToTest, numLow, numHigh ) \
        ((unsigned char)((numToTest) >= (numLow) && (numToTest) <= (numHigh)))

/* Aligns the supplied size to the specified PowerOfTwo */
#define ALIGN_SIZE( sizeToAlign, PowerOfTwo )       \
        (((sizeToAlign) + (PowerOfTwo) - 1) & ~((PowerOfTwo) - 1))

/* Checks whether the supplied size is aligned to the specified PowerOfTwo */
#define IS_SIZE_ALIGNED( sizeToTest, PowerOfTwo )  \
        (((sizeToTest) & ((PowerOfTwo) - 1)) == 0)

/* Obtain the offset of a field in a struct */
#define GET_FIELD_OFFSET( StructName, FieldName ) \
        ((short)(long)(&((StructName *)NULL)->FieldName))

/* 
* Obtain the struct element at the specified offset given the struct ptr 
* typecast the pointer to get the value of the element
*/
#define GET_FIELD_PTR( pStruct, nOffset ) \
        ((void *)(((char *)pStruct) + (nOffset)))

/**
Initializes the given structure to zeroes using memset().
@param pStruct the pointer to structure that has to be initialized
@see ALLOC_STRUCT
*/
#define INIT_STRUCT( pStruct ) (memset( pStruct, '\0', sizeof( *(pStruct) )))

/**
Use this macro for unused parameters right in the beginning of a function body
to suppress compiler warnings about unused parameters.

This is mainly meant for function parameters and not for unused local variables.
*/
#define UNUSED( ParamName ) \
    ((void)(0 ? ((ParamName) = (ParamName)) : (ParamName)))

/**
 *Allocates a structure given the structure name and returns a pointer to
that allocated structure.

The main benefit is there is no need to cast the returned pointer, to the
structure type.

@param StructName the name of the structure
@return pointer to allocated structure if successful, else NULL.
@see INIT_STRUCT
*/
#define ALLOC_STRUCT( StructName ) ((StructName *)malloc( sizeof( StructName )))

#define printBits(size, num) ({                 \
    int num_bits = size * 8 - 1;                \
    for(int bit = num_bits; bit >= 0; bit--) {  \
        printf("%u",(num >>bit) & 1);           \
    }                                           \
})

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

#define STRUCT_RES_SIZE(name)    sizeof(name)
#define STRUCT_REQ_SIZE(name)    sizeof(name)

typedef union udata 
{
    struct __attribute__((packed)) STRUCT_REQ(data)
    {
        /* Some Data */
    } req;
    
    struct __attribute__((packed)) STRUCT_RES(data)
    {
    	/* Some Data */
    } res;
} data;

/*
 * This macros initialize a pointer and return 
 * if buffer size is les then required
 */
#define DEFINE_OR_RETURN(src, type, des, len)           \
    type *des = (type *)src;                            \
    if (sizeof(struct STRUCT_REQ(type)) < (len)) {      \
        return;                                         \
    }                                                   

/*
 * Used to separate incoming floating point to the bytes of data
 * data.DDataIn
 * data.FDataIn  
 * data.LDDataIn
 * data.dataOut[] 
 */
typedef union {
	union {
		double      DDataIn;
		float   	FDataIn;
        long double LDDataIn;
	};
	uint8_t  dataOut[sizeof(long double)];
} ToFloatingPointTypes;

/**
Determines whether the memory architecture of current processor is LittleEndian.

Optimizing compiler should be able to reduce this macro to a boolean constant
TRUE or FALSE.

@return 1 if LittleEndian, else 0
*/
#define IS_LITTLE_ENDIAN()  (((*(short *)"21") & 0xFF) == '2')

/**
Determines whether the memory architecture of current processor is BigEndian.

Optimizing compiler should be able to reduce this macro to a boolean constant
TRUE or FALSE.

@return 1 if BigEndian, else 0
*/
#define IS_BIG_ENDIAN()     (((*(short *)"21") & 0xFF) == '1')

/**
Change this macro to change the default endian format. In this example,
the default endian format is Little Endian.

Optimizing compiler should be able to reduce this macro to a boolean constant
TRUE or FALSE.

@return 1 if the curren endian format is the default format, else 0
*/
#define IS_DEFAULT_ENDIAN() IS_LITTLE_ENDIAN()

/**
Reverses the bytes of the supplied byte array.
*/
#define REVERSE_BYTE_ARRAY( ByteArray, Size, force )                        \
        if (!IS_DEFAULT_ENDIAN() || force)                                  \
        {                                                                   \
            int     _i, _j;                                                 \
            char    _cTmp;                                                  \
            for (_i = 0, _j = (Size) - 1; _i < _j; _i++, _j--)              \
            {                                                               \
                _cTmp = ((char *)(ByteArray))[ _i ];                        \
                ((char *)(ByteArray))[ _i ] = ((char *)(ByteArray))[ _j ];  \
                ((char *)(ByteArray))[ _j ] = _cTmp;                        \
            }                                                               \
        }

/**
If the current machine is not default endian, re-arranges the bytes of the
given number. Does nothing if the current machine is default endian.

Use this for number variable whose size is greater than 32 bits.

For 16 and 32 bit numbers CONVERT_NUM16() and CONVERT_NUM32() are recommended.
*/
#define CONVERT_NUM( n )    REVERSE_BYTE_ARRAY( (&(n)), sizeof( n ))

/**
If the current machine is not default endian, re-arranges the bytes of the
given 16-bit number. Does nothing if the current machine is default endian.
*/
#define CONVERT_NUM16( n )  ((void)(IS_DEFAULT_ENDIAN() ? (n)       \
        : ((n) = ((((n) & 0x00FF) << 8) | (((n) & 0xFF00) >> 8)))))

/**
If the current machine is not default endian, re-arranges the bytes of the
given 32-bit number. Does nothing if the current machine is default endian.
*/
#define CONVERT_NUM32( n )  ((void)(IS_DEFAULT_ENDIAN() ? (n)               \
        : ((n) = ((((n) & 0x000000FF) << 24) | (((n) & 0x0000FF00) << 8)    \
        | (((n) & 0xFF0000) >> 8) | (((n) & 0xFF000000) >> 24)))))

/**
If the current machine is not default endian, re-arranges the bytes of the
given 32-bit floating point number. Does nothing if the current machine is
default endian.
*/
#define CONVERT_FLOAT( f )  CONVERT_NUM32( (*(long *)&(f) ))

/**
If the current machine is not default endian, re-arranges the bytes of the
given 64-bit floating point number. Does nothing if the current machine is
default endian.
*/
#define CONVERT_DOUBLE( d ) CONVERT_NUM( d )

/**
If the current machine is not default endian, re-arranges the bytes of the
given 64-bit point number. Does nothing if the current machine is
default endian.
*/
#define CONVERT_NUM64( n )  CONVERT_NUM( n )

/* It is used to get structure poiner using the members address of that data structure */
#define container_of(ptr, type, member) ({                  \
const typeof( ((type *)0)->member ) *__mptr = (ptr);    \
    (type *)( (char *)__mptr - offsetof(type,member) ); })

#define LSB(x) ((x) ^ ((x) - 1) & (x))   // least significant bit


/*
int
main (int argc, char **argv)
{
  int (*max) (int, int) = 
    lambda (int, (int x, int y) { return x > y ? x : y; });
  return max (1, 2);
}
*/
#define lambda(ret_type, ...)               \
        __extension__                       \
        ({                                  \
                ret_type __fn__ __VA_ARGS__ \
                __fn__;                     \
        })

/*
int main() {
    float a[] = { 1.1, 2.2, 3.3, 4.4, 54., 6.2, 7.5 };
    for_each(float const* c, a) {
        printf("sum = %f\n", *c);
    }  
}
*/
#define FOREACH(item, array)                        \
    for(int keep=1, count=0,                        \
            size=sizeof (array)/sizeof *(array);    \
        keep && count != size;                      \
        keep = !keep, count++)                      \
        for(item = (array)+count; keep; keep = !keep)


#define NEW(type, n) ( (type *) malloc(1 + (n) * sizeof(type)) )

#define SEARCH(arr, size, target)           \
  ({                                        \
        __label__ found;                    \
        int i = 0;                          \
        int value = -1;                     \
        for (i = 0; i < size; i++) {        \
                if (arr[i] == target) {     \
                        value = i;          \
                        goto found;         \
                }                           \
        }                                   \
        value = -1;                         \
        found:                              \
        value;                              \
   })
