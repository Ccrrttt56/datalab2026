/* WARNING: Do not include any other libraries here,
 * otherwise you will get an error while running test.py
 * You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 *
 * Using printf will interfere with our script capturing the execution results.
 * At this point, you can only test correctness with ./btest.
 * After confirming everything is correct in ./btest, remove the printf
 * and run the complete tests with test.py.
 */

 /*
 * bitAnd - x & y using only ~ and |
 * Example: bitAnd(4, 5) = 4
 * Legal ops: ~ |
 * Max ops: 7
 * Difficulty: 1
 */
int bitAnd(int x, int y) {
    return ~(~x|~y);
}

/*
 * bitXor - x ^ y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 7
 *   Difficulty: 1
 */
int bitXor(int x, int y) {
    return ~(~x&~y)&~(x&y);
}

/*
 * samesign - Determines if two integers have the same sign.
 *   0 is not positive, nor negative
 *   Example: samesign(0, 1) = 0, samesign(0, 0) = 1
 *            samesign(-4, -5) = 1, samesign(-4, 5) = 0
 *   Legal ops: >> << ! ^ && if else &
 *   Max ops: 12
 *   Difficulty: 2
 *
 * Parameters:
 *   x - The first integer.
 *   y - The second integer.
 *
 * Returns:
 *   1 if x and y have the same sign , 0 otherwise.
 */
int samesign(int x, int y) {
    if(!x&&!y){
        return 1;
    }
    else if(!x&&y){
        return 0;
    }
    else if(x&&!y){
        return 0;
    }
    else{
        if((x&0x80000000)^(y&0x80000000)){
            return 0;
        }
        else{
            return 1;
        }
    }
}

/*
 * logtwo - Calculate the base-2 logarithm of a positive integer using bit
 *   shifting. (Think about bitCount)
 *   Note: You may assume that v > 0
 *   Example: logtwo(32) = 5
 *   Legal ops: > < >> << |
 *   Max ops: 25
 *   Difficulty: 4
 */
int logtwo(int v) {
    int m= v>0x0000FFFF;
    int res=0;
    v=v>>(m<<4);
    res=res|(m<<4);

    m=v>0x000000FF;
    v=v>>(m<<3);
    res=res|(m<<3);

    m=v>0x0000000F;
    v=v>>(m<<2);
    res=res|(m<<2);

    m=v>0x00000003;
    v=v>>(m<<1);
    res=res|(m<<1);

    m=v>0x00000001;
    res=res|m;

    return res;

}

/*
 *  byteSwap - swaps the nth byte and the mth byte
 *    Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *              byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *    Note: You may assume that 0 <= n <= 3, 0 <= m <= 3
 *    Legal ops: ! ~ & ^ | + << >>
 *    Max ops: 17
 *    Difficulty: 2
 */
int byteSwap(int x, int n, int m) {
    int sn=n<<3,sm=m<<3;
    int mask_n=(x&(0xFFu<<sn))>>sn,mask_m=(x&(0xFFu<<sm))>>sm;
    int diff=mask_m^mask_n;
    return x^((diff&0xFFu)<<sm)^((diff&0xFFu)<<sn);


} 

/*
 * reverse - Reverse the bit order of a 32-bit unsigned integer.
 *   Example: reverse(0xFFFF0000) = 0x0000FFFF reverse(0x80000000)=0x1 reverse(0xA0000000)=0x5
 *   Note: You may assume that an unsigned integer is 32 bits long.
 *   Legal ops: << | & - + >> for while ! ~ (You can define unsigned in this function)
 *   Max ops: 30
 *   Difficulty: 3
 */
unsigned reverse(unsigned v) {
    unsigned v1=v>>16,v2=v<<16;
    v=v1|v2;

    v1=(v&0xFF00FF00)>>8;
    v2=(v&0x00FF00FF)<<8;
    v=v1|v2;

    v1=(v&0xF0F0F0F0)>>4;
    v2=(v&0x0F0F0F0F)<<4;
    v=v1|v2;

    v1=(v&0xCCCCCCCC)>>2;
    v2=(v&0x33333333)<<2;
    v=v1|v2;

    v1=(v&0xAAAAAAAA)>>1;
    v2=(v&0x55555555)<<1;
    v=v1|v2;

    return v;
}

/*
 * logicalShift - shift x to the right by n, using a logical shift
 *   Examples: logicalShift(0x87654321,4) = 0x08765432
 *   Note: You can assume that 0 <= n <= 31
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Difficulty: 3
 */
int logicalShift(int x, int n) {
    int temp=(x&~0x80000000)>>n;
    int mask=(x>>31)&(0x80000000>>n);    
    return temp|mask;
}

/*
 * leftBitCount - returns count of number of consective 1's in left-hand (most) end of word.
 *   Examples: leftBitCount(-1) = 32, leftBitCount(0xFFF0F0F0) = 12,
 *             leftBitCount(0xFE00FF0F) = 7
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 50
 *   Difficulty: 4
 */
int leftBitCount(int x) {
    int v=~x;
    
    int m= !!(v&0xFFFF0000);
    int res=0;
    v=v>>(m<<4);
    res=res|(m<<4);

    m=!!(v&0x0000FF00);
    v=v>>(m<<3);
    res=res|(m<<3);

    m=!!(v&0x000000F0);
    v=v>>(m<<2);
    res=res|(m<<2);

    m=!!(v&0x0000000C);
    v=v>>(m<<1);
    res=res|(m<<1);

    m=!!(v&0x00000002);
    res=res|m;

    res=~res+1;
    return 31+res+!v;
}

/*
 * float_i2f - Return bit-level equivalent of expression (float) x
 *   Result is returned as unsigned int, but it is to be interpreted as
 *   the bit-level representation of a single-precision floating point values.
 *   Legal ops: if else while for & | ~ + - >> << < > ! ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned float_i2f(int x) {
    unsigned sign = x & 0x80000000u;
    unsigned mag, tmp, exp, frac, rem, half;
    int k = 0, shift;

    if (x == 0) return 0;

    if (x < 0) mag = ~x + 1u;
    else mag = x;

    tmp = mag;
    while (tmp > 1) {
        tmp = tmp >> 1;
        k = k + 1;
    }

    exp = k + 127;

    if (k < 24) {
        frac = mag << (23 - k);
    } else {
        shift = k - 23;
        frac = mag >> shift;
        rem = mag & ((1u << shift) - 1u);
        half = 1u << (shift - 1);

        if (rem > half) frac = frac + 1;
        else if (rem == half) {
            if (frac & 1u) frac = frac + 1;
        }

        if (frac >> 24) exp = exp + 1;
    }

    return sign | (exp << 23) | (frac & 0x7fffffu);
}

/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: & >> << | if > < >= <= ! ~ else + ==
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatScale2(unsigned uf) {
    unsigned sign = uf & 0x80000000u;
    unsigned exp = uf & 0x7f800000u;
    unsigned frac = uf & 0x007fffffu;

    if (exp == 0x7f800000u) return uf;

    if (exp == 0) return sign | (frac << 1);

    exp = exp + 0x00800000u;
    if (exp == 0x7f800000u) frac = 0;

    return sign | exp | frac;
}

/*
 * float64_f2i - Convert a 64-bit IEEE 754 floating-point number to a 32-bit signed integer.
 *   The conversion rounds towards zero.
 *   Note: Assumes IEEE 754 representation and standard two's complement integer format.
 *   Parameters:
 *     uf1 - The lower 32 bits of the 64-bit floating-point number.
 *     uf2 - The higher 32 bits of the 64-bit floating-point number.
 *   Returns:
 *     The converted integer value, or 0x80000000 on overflow, or 0 on underflow.
 *   Legal ops: >> << | & ~ ! + - > < >= <= if else
 *   Max ops: 60
 *   Difficulty: 3
 */
int float64_f2i(unsigned uf1, unsigned uf2) {
    int exp = (uf2 >> 20) & 0x7ff;
    int e = exp - 1023;
    int sig = (1 << 20) | (uf2 & 0xfffff);
    int mag;

    if (e < 0) return 0;
    if (e > 30) return ~0x7fffffff;

    if (e <= 20) {
        mag = sig >> (20 - e);
    } else {
        mag = (sig << (e - 20)) | (uf1 >> (52 - e));
    }

    if (uf2 >> 31) return -mag;
    return mag;
}

/*
 * floatPower2 - Return bit-level equivalent of the expression 2.0^x
 *   (2.0 raised to the power x) for any 32-bit integer x.
 *
 *   The unsigned value that is returned should have the identical bit
 *   representation as the single-precision floating-point number 2.0^x.
 *   If the result is too small to be represented as a denorm, return
 *   0. If too large, return +INF.
 *
 *   Legal ops: < > <= >= << >> + - & | ~ ! if else &&
 *   Max ops: 30
 *   Difficulty: 4
 */
unsigned floatPower2(int x) {
    if (x < -149) return 0;
    if (x > 127) return 0x7f800000u;
    if (x < -126) return 1u << (x + 149);
    return (x + 127) << 23;
    
}
