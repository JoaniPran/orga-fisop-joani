/*
 * CS:APP Data Lab
 *
 * <Please put your name and userid here>
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
 * bitAnd - x&y using only ~ and |
 *   Example: bitAnd(6, 5) = 4
 *   Legal ops: ~ |
 *   Max ops: 8
 *   Rating: 1
 */
int bitAnd(int x, int y) {
  int res = (~x) | (~y);
  return ~res;
}
/*
 * bitMatch - Create mask indicating which bits in x match those in y
 *            using only ~ and &
 *   Example: bitMatch(0x7, 0xE) = 0x6
 *   Legal ops: ~ & |
 *   Max ops: 14
 *   Rating: 1
 */
int bitMatch(int x, int y) {
  int op1 = x & y;
  int op2 = ~(x | y);
  int res = op1 | op2;
  return res;
}
/*
 * bitNor - ~(x|y) using only ~ and &
 *   Example: bitNor(0x6, 0x5) = 0xFFFFFFF8
 *   Legal ops: ~ &
 *   Max ops: 8
 *   Rating: 1
 */
int bitNor(int x, int y) {
  int res = (~x) & (~y);
  return res;
}
/*
 * bitXor - x^y using only ~ and &
 *   Example: bitXor(4, 5) = 1
 *   Legal ops: ~ &
 *   Max ops: 14
 *   Rating: 1
 */
int bitXor(int x, int y) {
  int op1 = x & y;
  int op2 = (~x) & (~y);
  int res = (~op1) & (~op2);
  return res;
}
//2
/*
 * allOddBits - return 1 if all odd-numbered bits in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples allOddBits(0xFFFFFFFD) = 0, allOddBits(0xAAAAAAAA) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int allOddBits(int x) {
  int m8 = 0xAA;
  int m16 = m8 | m8 << 8;
  int m32 = m16 | m16 << 16;
  int op1 = x & m32;
  int res = op1 ^ m32;
  return !res;
}
/*
 * anyEvenBit - return 1 if any even-numbered bit in word set to 1
 *   where bits are numbered from 0 (least significant) to 31 (most significant)
 *   Examples anyEvenBit(0xA) = 0, anyEvenBit(0xE) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 2
 */
int anyEvenBit(int x) {
  int m8 = 0x55;
  int m16 = m8 | m8 << 8;
  int m32 = m16 | m16 << 16;
  int res = x & m32;
  return !!res;
}
/*
 * byteSwap - swaps the nth byte and the mth byte
 *  Examples: byteSwap(0x12345678, 1, 3) = 0x56341278
 *            byteSwap(0xDEADBEEF, 0, 2) = 0xDEEFBEAD
 *  You may assume that 0 <= n <= 3, 0 <= m <= 3
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 25
 *  Rating: 2
 */
int byteSwap(int x, int n, int m) {
    int shiftN, shiftM;
    int mN, mM;
    int byteN, byteM;
    int mascaraAuxiliar1, mascaraAuxiliar2;
    int res;

    shiftN = n << 3;
    shiftM = m << 3;
    mN = 0xFF << shiftN;
    mM = 0xFF << shiftM;
    byteN = x & mN;
    byteM = x & mM;
    byteN = byteN >> shiftN;
    byteM = byteM >> shiftM;
    byteN = byteN & 0xFF;
    byteM = byteM & 0xFF;
    byteN = byteN << shiftM;
    byteM = byteM << shiftN;

    mascaraAuxiliar1 = byteN | byteM;
    mascaraAuxiliar2 = x & (~(mN | mM));
    res = mascaraAuxiliar1 | mascaraAuxiliar2;
    return res;
}
/*
 * fitsBits - return 1 if x can be represented as an
 *  n-bit, two's complement integer.
 *   1 <= n <= 32
 *   Examples: fitsBits(5,3) = 0, fitsBits(-4,3) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 15
 *   Rating: 2
 */
int fitsBits(int x, int n) {
  int shift = 32 + (~n + 1); 
  return !(x ^ ((x << shift) >> shift));
}
/*
 * negate - return -x
 *   Example: negate(1) = -1.
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 5
 *   Rating: 2
 */
int negate(int x) {
  int m8 = 0x01;
  int m16 = m8 << 8;
  int m32 = m16 << 16;
  int negado_mas_uno;

  m32 = m32 >> 24;
  negado_mas_uno = ~x + m32;
  return (negado_mas_uno); 
}
/*
 * sign - return 1 if positive, 0 if zero, and -1 if negative
 *  Examples: sign(130) = 1
 *            sign(-23) = -1
 *  Legal ops: ! ~ & ^ | + << >>
 *  Max ops: 10
 *  Rating: 2
 */
int sign(int x) {
  int op1 = x >> 31;
  int op2 = !!x;
  int res = op1 | op2;
  return res;
}
//3
/*
 * addOK - Determine if can compute x+y without overflow
 *   Example: addOK(0x80000000,0x80000000) = 0,
 *            addOK(0x80000000,0x70000000) = 1,
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 20
 *   Rating: 3
 */
int addOK(int x, int y) {
  int sum = x + y;
  int sign_x = x >> 31;
  int sign_y = y >> 31;
  int sign_sum = sum >> 31;

  return !((sign_x ^ sign_sum) & (sign_y ^ sign_sum));
}
/*
 * bitMask - Generate a mask consisting of all 1's
 *   lowbit and highbit
 *   Examples: bitMask(5,3) = 0x38
 *   Assume 0 <= lowbit <= 31, and 0 <= highbit <= 31
 *   If lowbit > highbit, then mask should be all 0's
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int bitMask(int highbit, int lowbit) {
  int pre_condicion, condicion;
  int mascara;
  int primeraMascara, segundaMascara;
  int resultado;

  int m8 = 0xFF;
  int m16 = m8 | m8 << 8;
  int m_0xFFFFFFFF = m16 | m16 << 16;
  int m_0xFFFFFF00 = m_0xFFFFFFFF << 8;
  mascara = m_0xFFFFFF00 | 0xFE;

  pre_condicion = (highbit + (~lowbit + 1));
  pre_condicion = pre_condicion >> 31;
  condicion = ~pre_condicion;

  primeraMascara = mascara << highbit;
  primeraMascara = ~primeraMascara;
  segundaMascara = condicion << lowbit;
  resultado = primeraMascara & segundaMascara;

  return resultado;
}
/*
 * conditional - same as x ? y : z
 *   Example: conditional(2,4,5) = 4
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 16
 *   Rating: 3
 */
int conditional(int x, int y, int z) {
  int res;

  x = !!x;
  x = ~x + 1;
  res = (x & y) | (~x & z);
  return res;
}
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
  int mayorIgualA0x30 = !((x + ~0x30 + 1) >> 31);
  int menorIgualA0x39 = !((0x39 + ~x + 1) >> 31);
  return (mayorIgualA0x30 & menorIgualA0x39);
}
/*
 * isGreater - if x > y  then return 1, else return 0
 *   Example: isGreater(4,5) = 0, isGreater(5,4) = 1
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 24
 *   Rating: 3
 */
int isGreater(int x, int y) {
  int signo_x = x >> 31;
  int signo_y = y >> 31;
  int signo_diferente = signo_x & (!signo_y);
  int signo_igual = (!(signo_x ^ signo_y)) & ((x + (~y + 1)) >> 31);
  int son_iguales = !(x ^ y);
  return !(son_iguales | signo_diferente | signo_igual);
}
/*
 * replaceByte(x,n,c) - Replace byte n in x with c
 *   Bytes numbered from 0 (LSB) to 3 (MSB)
 *   Examples: replaceByte(0x12345678,1,0xab) = 0x1234ab78
 *   You can assume 0 <= n <= 3 and 0 <= c <= 255
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 3
 */
int replaceByte(int x, int n, int c) {
  int shift = n << 3;
  int mascara = 0xFF << shift;
  int ceros_en_posicion_a_cambiar = x & (~mascara);
  int posicion_de_c = c << shift;
  return (ceros_en_posicion_a_cambiar | posicion_de_c); 
}
//4
/*
 * absVal - absolute value of x
 *   Example: absVal(-1) = 1.
 *   You may assume -TMax <= x <= TMax
 *   Legal ops: ! ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int absVal(int x) {
  int mascara = x >> 31;
  return (x ^ mascara) + (~mascara + 1);
}
/*
 * bang - Compute !x without using !
 *   Examples: bang(3) = 0, bang(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int bang(int x) {
  int numero_a_negar = ((x | (~x + 1)) >> 31) & 1;
  return ~numero_a_negar & 1;
}
/*
 * isNonZero - Check whether x is nonzero using
 *              the legal operators except !
 *   Examples: isNonZero(3) = 1, isNonZero(0) = 0
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 10
 *   Rating: 4
 */
int isNonZero(int x) {
  return ((x | (~x + 1)) >> 31) & 1;
}
/*
 * logicalNeg - implement the ! operator, using all of
 *              the legal operators except !
 *   Examples: logicalNeg(3) = 0, logicalNeg(0) = 1
 *   Legal ops: ~ & ^ | + << >>
 *   Max ops: 12
 *   Rating: 4
 */
int logicalNeg(int x) {
  int numero_a_negar = ((x | (~x + 1)) >> 31) & 1;
  return ~numero_a_negar & 1;
}
//float
/*
 * floatAbsVal - Return bit-level equivalent of absolute value of f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument..
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatAbsVal(unsigned uf) {
  unsigned mascaraSigno = 0x7FFFFFFF;
  unsigned mascaraExp = 0x7F800000;
  unsigned mascaraMantiza = 0x007FFFFF;

  if ((uf & mascaraExp) == mascaraExp && (uf & mascaraMantiza) != 0) {
    return uf;
  }

  return uf & mascaraSigno;
}
/*
 * floatIsEqual - Compute f == g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 25
 *   Rating: 2
 */
int floatIsEqual(unsigned uf, unsigned ug) { 
  int respuesta;

  int mascaraSigno = 0x80000000;
  unsigned mascaraExp = 0x7F800000;
  unsigned mascaraMantiza = 0x007FFFFF;

  int ufEsCero = !(uf & (~mascaraSigno));
  int ugEsCero = !(ug & (~mascaraSigno));

  int uf_Nan = (uf & mascaraExp) == mascaraExp && (uf & mascaraMantiza) != 0;
  int ug_Nan = (ug & mascaraExp) == mascaraExp && (ug & mascaraMantiza) != 0;

  if(uf_Nan || ug_Nan) {
    return 0;
  }

  if(uf == ug || (ufEsCero && ugEsCero)) {
    respuesta = 1;
  }
  else {
    respuesta = 0;
  }

  return respuesta;
}

/*
 * floatNegate - Return bit-level equivalent of expression -f for
 *   floating point argument f.
 *   Both the argument and result are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   When argument is NaN, return argument.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 10
 *   Rating: 2
 */
unsigned floatNegate(unsigned uf) {
  int signo;
  unsigned ufNegado;

  int mascaraSigno = 0x80000000;
  unsigned mascaraExp = 0x7F800000;
  unsigned mascaraMantiza = 0x007FFFFF;

  if ((uf & mascaraExp) == mascaraExp && (uf & mascaraMantiza) != 0) {
    return uf;
  }

  signo = (~uf) & mascaraSigno;
  ufNegado = signo | (uf & (~mascaraSigno));

 return ufNegado;
}
/*
 * floatIsLess - Compute f < g for floating point arguments f and g.
 *   Both the arguments are passed as unsigned int's, but
 *   they are to be interpreted as the bit-level representations of
 *   single-precision floating point values.
 *   If either argument is NaN, return 0.
 *   +0 and -0 are considered equal.
 *   Legal ops: Any integer/unsigned operations incl. ||, &&. also if, while
 *   Max ops: 30
 *   Rating: 3
 */
int floatIsLess(unsigned uf, unsigned ug) {
  int signoUf;
  int signoUg;
  int signosIguales;
  int respuesta;

  int mascaraSigno = 0x80000000;
  unsigned mascaraExp = 0x7F800000;
  unsigned mascaraMantiza = 0x007FFFFF;

  int ufEsCero = !(uf & (~mascaraSigno));
  int ugEsCero = !(ug & (~mascaraSigno));

  int uf_Nan = (uf & mascaraExp) == mascaraExp && (uf & mascaraMantiza) != 0;
  int ug_Nan = (ug & mascaraExp) == mascaraExp && (ug & mascaraMantiza) != 0;

  if(uf_Nan || ug_Nan || (ufEsCero && ugEsCero)) {
    return 0;
  }

  signoUf = uf & mascaraSigno;
  signoUg = ug & mascaraSigno;
  signosIguales = signoUf == signoUg;

  if(signosIguales) {
    unsigned ufResto = uf & ~mascaraSigno;
    unsigned ugResto = ug & ~mascaraSigno;
    if(signoUf == 0) { 
      respuesta = ufResto < ugResto;
    }
    else { 
      respuesta = ufResto > ugResto;
    }
  }
  else {
    respuesta = signoUf < signoUg;
  }

  return respuesta;
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
  int signo = ((uf >> 31) & 1);
  int exp = ((uf >> 23) & 0xFF);
  int frac = (uf & 0x7FFFFF);
  int bias = 127;
  int e;
  int resultado;

  if (exp < bias) {
    return 0;
  }

  if (exp >= (bias + 31)) {
    return 0x80000000u;
  }

  frac = frac | 0x800000; 

  e = exp + ~bias + 1;

  if (e < 23) {
    frac >>= (23 + ~e + 1 );
  } else {
    frac <<= (e + ~23 + 1 );
  }

  if ((frac >> 31) & 1) {
    return 0x80000000u;
  }

  resultado = frac;
  if (signo) {
    resultado = ~resultado + 1; 
  }

  return resultado;
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
  unsigned INF = 0xFF << 23; 
  unsigned exp;

  if (x < -149) { 
      return 0;
  } else if (x > 127) { 
      return INF;
  } else if (x < -126) { 
      exp = 1 << (x + 149);
  } else { 
      exp = (x + 127) << 23;
  }

  return exp;
}
