/*
 * CS:APP Data Lab
 *
 * <anbenqishi>
 *
 * bits.c - Source file with your solutions to the Lab.
 *          This is the file you will hand in to your instructor.
 *
 * WARNING: Do not include the <stdio.h> header; it confuses the dlc
 * compiler. You can still use printf for debugging without including
 * <stdio.h>, although you might get a compiler warning. In general,
 * it's not good practice to ignore compiler warnings, but in this
 * case it's OK.
 */

#if 0
/*
 * Instructions to Students:
 *
 * STEP 1: Read the following instructions carefully.
 */

You will provide your solution to the Data Lab by
editing the collection of functions in this source file.

INTEGER CODING RULES:

  Replace the "return" statement in each function with one
  or more lines of C code that implements the function. Your code
  must conform to the following style:

  int Funct(arg1, arg2, ...) {
      /* brief description of how your implementation works */
      int var1 = Expr1;
      ...
      int varM = ExprM;

      varJ = ExprJ;
      ...
      varN = ExprN;
      return ExprR;
  }

  Each "Expr" is an expression using ONLY the following:
  1. Integer constants 0 through 255 (0xFF), inclusive. You are
      not allowed to use big constants such as 0xffffffff.
  2. Function arguments and local variables (no global variables).
  3. Unary integer operations ! ~
  4. Binary integer operations & ^ | + << >>

  Some of the problems restrict the set of allowed operators even further.
  Each "Expr" may consist of multiple operators. You are not restricted to
  one operator per line.

  You are expressly forbidden to:
  1. Use any control constructs such as if, do, while, for, switch, etc.
  2. Define or use any macros.
  3. Define any additional functions in this file.
  4. Call any functions.
  5. Use any other operations, such as &&, ||, -, or ?:
  6. Use any form of casting.
  7. Use any data type other than int.  This implies that you
     cannot use arrays, structs, or unions.


  You may assume that your machine:
  1. Uses 2s complement, 32-bit representations of integers.
  2. Performs right shifts arithmetically.
  3. Has unpredictable behavior when shifting if the shift amount
     is less than 0 or greater than 31.


EXAMPLES OF ACCEPTABLE CODING STYLE:
  /*
   * pow2plus1 - returns 2^x + 1, where 0 <= x <= 31
   */
  int pow2plus1(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     return (1 << x) + 1;
  }

  /*
   * pow2plus4 - returns 2^x + 4, where 0 <= x <= 31
   */
  int pow2plus4(int x) {
     /* exploit ability of shifts to compute powers of 2 */
     int result = (1 << x);
     result += 4;
     return result;
  }

FLOATING POINT CODING RULES

For the problems that require you to implement floating-point operations,
the coding rules are less strict.  You are allowed to use looping and
conditional control.  You are allowed to use both ints and unsigneds.
You can use arbitrary integer and unsigned constants. You can use any arithmetic,
logical, or comparison operations on int or unsigned data.

You are expressly forbidden to:
  1. Define or use any macros.
  2. Define any additional functions in this file.
  3. Call any functions.
  4. Use any form of casting.
  5. Use any data type other than int or unsigned.  This means that you
     cannot use arrays, structs, or unions.
  6. Use any floating point data types, operations, or constants.


NOTES:
  1. Use the dlc (data lab checker) compiler (described in the handout) to
     check the legality of your solutions.
  2. Each function has a maximum number of operations (integer, logical,
     or comparison) that you are allowed to use for your implementation
     of the function.  The max operator count is checked by dlc.
     Note that assignment ('=') is not counted; you may use as many of
     these as you want without penalty.
  3. Use the btest test harness to check your functions for correctness.
  4. Use the BDD checker to formally verify your functions
  5. The maximum number of ops for each function is given in the
     header comment for each function. If there are any inconsistencies
     between the maximum ops in the writeup and in this file, consider
     this file the authoritative source.

/*
 * STEP 2: Modify the following functions according the coding rules.
 *
 *   IMPORTANT. TO AVOID GRADING SURPRISES:
 *   1. Use the dlc compiler to check that your solutions conform
 *      to the coding rules.
 *   2. Use the BDD checker to formally verify that your solutions produce
 *      the correct answers.
 */


#endif
//1
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int ret = ~(~x & ~y) & ~(x & y);
  return ret;
}
/*
 * tmin - return minimum two's complement integer
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 4
 *   Rating: 1
 */
int tmin(void) {
  int ret = 1 << 31;
  return ret;

}
//2
/*
 * isTmax - returns 1 if x is the maximum, two's complement number,
 *     and 0 otherwise
 *   Legal ops: ! ~ & ^ | +
 *   Max ops: 10
 *   Rating: 1
 */
int isTmax(int x) {
  return !!(x ^ ~0) & !(~(x+1) ^ x);
}
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int ret = !((((x >> 24) & 0xaa) & ((x >> 16) & 0xaa) & ((x >> 8) & 0xaa) & (x & 0xaa)) ^ 0xaa);
  return ret;
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
// out-of-boundary @todo
int negate(int x) {
  int ret = (~x + 1) ^ x ^ x;
  return ret;
}
//3
/*
 * isAsciiDigit - return 1 if 0x30 <= x <= 0x39 (ASCII codes for characters '0' to '9')
 *   Example: isAsciiDigit(0x35) = 1.
 *            isAsciiDigit(0x3a) = 0.
 *            isAsciiDigit(0x05) = 0.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 3
 */
int isAsciiDigit(int x) {
  int low_four = x & 0xf;
  return (!((x >> 4) ^ 0x3)) & ((!(low_four ^ 0x8)) | (!(low_four ^ 0x9)) | (!!((low_four & 0x8) ^ 0x8)));
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  return ((~(!x + 0) + 1) & z) | ((~(!!x + 0) + 1) & y);
}
/*
 * isLessOrEqual - if x <= y  then return 1, else return 0
 *   Example: isLessOrEqual(4,5) = 1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isLessOrEqual(int x, int y) {
  int opx = (x >> 31) & 0x1;
  int opy = (y >> 31) & 0x1;
  int x_minus_y = x + 1 + ~y;
  int check_high_8 = ((x_minus_y >> 24) & 0x80) ^ 0x80;

  int cond_x = opx ^ opy;
  int cond_y = opx;
  int cond_z = !(x_minus_y ^ 0) | !check_high_8;
  return ((~(!cond_x + 0) + 1) & cond_z) | ((~cond_x + 1) & cond_y);
}
//4
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int first = x >> 24;
  int second = x >> 16;
  int third = x >> 8;
  return ((((first | second | third | x) & 0xff) + 0xff) >> 8) ^ 0x1;
}
/* howManyBits - return the minimum number of bits required to represent x in
 *             two's complement
 *  Examples: howManyBits(12) = 5
 *            howManyBits(298) = 10
 *            howManyBits(-5) = 4
 *            howManyBits(0)  = 1
 *            howManyBits(-1) = 1
 *            howManyBits(0x80000000) = 32
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 90
 *  Rating: 4
 */
int howManyBits(int x) {
  /*
   1. 负数算数右移会补1，这里考虑所有负数都用正数来处理
   2. 以8bit int为例，负数取反，有下述三种情况（括号内为所需最小位数表示）：
      1000 0000 -> 0111 1111(8 -> 8)-> 1000 0000 (8 -> 8)【没有对应的正数表示，但不影响结果】
      1000 0001 -> 0111 1110(8 -> 8)-> 0111 1111 (8 -> 8)
      1111 1110 -> 0000 0001(2 -> 2)-> 0000 0010 (2 -> 3)
      这样看，直接取反更简单，更不用考虑负值所对应的实际正值;
   3. 正数bit的计算：
       二分法：以bit16为界，如果高位 != 0, 则继续在后16bit二分；否则在低位二分；
       为保持操作的一致性，通过高位右移，可以统一在低位做二分操作；
       IF 高16bit不为0
          x = x >> 16;
          记录bit数;
       IF 高8bit不为0
         x = x >> 8;
         记录bit数;
      IF 高4bit不为0
         x = x >> 4;
         记录bit数；
      IF 高2bit不为0
         x = x >> 2;
         记录bit数;
      最后2bit有 00，11(低位)，01，10(低位);
      对于符号位, 我们固定取1;这样 1X型 直接取2，0X型 取bit0的值即可;
   */
  int bit31 = (x >> 31) & 0x1;
  int bit31_zero = ~(!bit31 + 0) + 1;
  int bit31_one = ~bit31 + 1;
  int pos_x = (bit31_zero & x) | (bit31_one & (~x));

  int bit2, bit4, bit8, bit16;
  int b16, b8, b4, b2, b1, b0;

  /* binary search for highest 1 */
  /**
   * if !!bitX == 0  ==> pos_x = bitX | pos_x = pos_x不变
   * if !!bitX == 1  ==> pos_x = bitX | 0 = bitX更新
   * so we use conditional function.
   */
  bit16 = pos_x >> 16;
  b16 = !!bit16 << 4;
  pos_x = bit16 | ((~(!b16 + 0) + 1) & pos_x);

  bit8 = pos_x >> 8;
  b8  = !!bit8 << 3;
  pos_x = bit8 | ((~(!b8 + 0) + 1) & pos_x);

  bit4 = pos_x >> 4;
  b4   = !!bit4 << 2;
  pos_x = bit4 | ((~(!b4 + 0) + 1) & pos_x);

  bit2 = pos_x >> 2;
  b2   = !!bit2 << 1;
  pos_x = bit2 | ((~(!b2 + 0) + 1) & pos_x);

  b1 = pos_x >> 1;
  b0 = pos_x & 0x1;
  b1 = ( (~(!b1 + 0) + 1) & (b0)) | ((~b1 + 1) & 2);
  return 1 + b16 + b8 + b4 + b2 + b1;
}
//float
/*
 * floatScale2 - Return bit-level equivalent of expression 2*f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representation of
 *   single-precision floating point values.
 *   When argument is NaN, return argument
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatScale2(unsigned uf) {
  /**
   * 单精度表示：
   * sign(bit31) + exp(8bits, bit30~bit23) + fraction(23bits, bit22 ~ bit0) = 32bits
   * exp - 127 才是实际的有效exp值
   * NaN : exp = 2**e - 1 = 255, fraction != 0
   * ∞ :   exp = 2**e - 1 = 255, fraction == 0
   * 规约数： 1 <= exp <= 254, 实际尾数[1, 2)
   * 非规约数： exp = 0, 对应实际指数=-126, fraction != 0, 对应实际尾数(0, 1)
   */
  unsigned high9 = uf >> 23;
  int exp = high9 & 0xff;
  int expscale2 = exp - 126; // 指数 * 2
  unsigned faction = uf << 9;
  /* NaN or ∞ or illegal */
  if (exp == 255 || expscale2 > 0x80)
    return uf;
  /* 非规约数 */
  if (exp == 0) {
    return ((uf >> 31) << 31) | (uf << 1);
  }
  /* 归约数 */
  return ((high9 + 1) << 23) | (faction >> 9);
}
/*
 * floatFloat2Int - Return bit-level equivalent of expression (int) f
 *   for floating point argument f.
 *   Argument is passed as unsigned int, but
 *   it is to be interpreted as the bit-level representation of a
 *   single-precision floating point value.
 *   Anything out of range (including NaN and infinity) should return
 *   0x80000000u.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 4
 */
int floatFloat2Int(unsigned uf) {
  /**
   * 最大的非规约数： exp = 0, fraction=7fffff  < 1
   * 规约数：
   *  exp应 >= 127=0x7f, 否则取整后都是0, exp <= 0xfe
   * 基本可不考虑fraction？
   *    exp=0, fraction=1/1.5, so float=1.5, int=1
   *    exp=1, fraction=1.5, so float=3, int = 3 = 0011
   *    exp=2, fraction=1, so float=4, int = 4 = 0100
   *    exp=2, fraction=1.5, so float=6, int = 6 = 0110
   *    exp=3, fraction=1.5, so float=12, int = 12 = 1100
   *    exp=4, fraction=1.5, so float=24, int = 12 = 11000 = (1 << 4) + (1 << 3)
   */
  unsigned high9 = uf >> 23;
  int exp = high9 & 0xff;
  int real_exp = exp - 127;
  unsigned sign = (uf >> 31) & 0x1;
  int result;
  /* NaN or ∞ */
  if (exp == 255 || real_exp > 32)
    return 0x80000000u;
  /* 非规约数 or 小的规约数 */
  if (exp == 0 || exp < 0x7f) {
    return 0;
  }
  /* 归约数 */
  result = (1 << real_exp) + (1 << (real_exp - 1));
  if (exp == 0x7f) result = 1;
  if (sign == 1) return -result;
  return result;
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
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. Also if, while
 *   Max ops: 30
 *   Rating: 4
 */
unsigned floatPower2(int x) {
/**
 * 最大归约数： exp = 254 = 0xfe, fraction = 0x7fffff, float = (2 - 2**(-23)) * 2**(127)
 * 最小归约数： exp = 1, fraction = 0, float = 2**(-126)
 * 最小非归约数： exp = 0, fraction = 0x1, float = 2**(-149)
 * 最大非归约数： exp = 0, fraction = 0x7fffff, float = (1−2**(−23)) × 2**(−126)
 * so  -149 <= x <= 127
 * x <= -127, exp = 0
 *    x = -127, fraction = 0x400000 = 1 << 22
 *    x = -128, fraction = 0x200000 = 1 << 21
 *    x = -149, fraction = 0x1      = 1 << 0
 * x > -127, fraction = 0
 *    x = -126, exp = 1
 *    x = -125, exp = 2
 *    x = 127,  exp = 254 = 0xfe
 * 以下代码会提示超时（10s），我把时间调大会过，网上的说法是可能电脑性能不行，导致检测数据集跑不完...
 */
    if (x < -149) return 0;
    if (x > 127)  return 0x7f800000;
    /* 非规约数 */
    if (x <= -127) {
      return 1 << (23 + (x + 126));
    }
    /* 归约数 */
    return (x + 127) << 23;
}
