/*
Copyright (c) 2015-2016 Advanced Micro Devices, Inc. All rights reserved.

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
*/

#ifndef HIP_FP16_H
#define HIP_FP16_H

#include "hip/hip_runtime.h"

#if __clang_major__ == 4

typedef __fp16 __half;

typedef struct __attribute__((aligned(4))){
  union {
    __half p[2];
    unsigned int q;
  };
} __half2;

struct holder{
  union {
    __half h;
    unsigned short s;
  };
};

#define HINF 65504

static struct holder hInf = {HINF};

extern "C" __half __hip_hc_ir_hadd_half(__half, __half);
extern "C" __half __hip_hc_ir_hfma_half(__half, __half, __half);
extern "C" __half __hip_hc_ir_hmul_half(__half, __half);
extern "C" __half __hip_hc_ir_hsub_half(__half, __half);

extern "C" int __hip_hc_ir_hadd2_int(int, int);
extern "C" int __hip_hc_ir_hfma2_int(int, int, int);
extern "C" int __hip_hc_ir_hmul2_int(int, int);
extern "C" int __hip_hc_ir_hsub2_int(int, int);

__device__ static inline __half __hadd(const __half a, const __half b) {
  return __hip_hc_ir_hadd_half(a, b);
}

__device__ static inline __half __hadd_sat(__half a, __half b) {
  return __hip_hc_ir_hadd_half(a, b);
}

__device__ static inline __half __hfma(__half a, __half b, __half c) {
  return __hip_hc_ir_hfma_half(a, b, c);
}

__device__ static inline __half __hfma_sat(__half a, __half b, __half c) {
  return __hip_hc_ir_hfma_half(a, b, c);
}

__device__ static inline __half __hmul(__half a, __half b) {
  return __hip_hc_ir_hmul_half(a, b);
}

__device__ static inline __half __hmul_sat(__half a, __half b) {
  return __hip_hc_ir_hmul_half(a, b);
}

__device__ static inline __half __hneg(__half a) {
  return -a;
}

__device__ static inline __half __hsub(__half a, __half b) {
  return __hip_hc_ir_hsub_half(a, b);
}

__device__ static inline __half __hsub_sat(__half a, __half b) {
  return __hip_hc_ir_hsub_half(a, b);
}

__device__ static inline __half hdiv(__half a, __half b) {
  return a/b;
}

/*
  Half2 Arithmetic Functions
*/

__device__ static inline __half2 __hadd2(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hadd2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 __hadd2_sat(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hadd2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 __hfma2(__half2 a, __half2 b, __half2 c) {
  __half2 d;
  d.q = __hip_hc_ir_hfma2_int(a.q, b.q, c.q);
  return d;
}

__device__ static inline __half2 __hfma2_sat(__half2 a, __half2 b, __half2 c) {
  __half2 d;
  d.q = __hip_hc_ir_hfma2_int(a.q, b.q, c.q);
  return d;
}

__device__ static inline __half2 __hmul2(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hmul2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 __hmul2_sat(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hmul2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 __hsub2(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hsub2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 __hneg2(__half2 a) {
  __half2 c;
  c.p[0] = - a.p[0];
  c.p[1] = - a.p[1];
  return c;
}

__device__ static inline __half2 __hsub2_sat(__half2 a, __half2 b) {
  __half2 c;
  c.q = __hip_hc_ir_hsub2_int(a.q, b.q);
  return c;
}

__device__ static inline __half2 h2div(__half2 a, __half2 b) {
  __half2 c;
  c.p[0] = a.p[0] / b.p[0];
  c.p[1] = a.p[1] / b.p[1];
  return c;
}

/*
Half comparision Functions
*/

__device__ static inline bool __heq(__half a, __half b) {
  return a == b ? true : false;
}

__device__ static inline bool __hge(__half a, __half b) {
  return a >= b ? true : false;
}

__device__ static inline bool __hgt(__half a, __half b) {
  return a > b ? true : false;
}

__device__ static inline bool __hisinf(__half a) {
  return a == hInf.s ? true : false;
}

__device__ static inline bool __hisnan(__half a) {
  return a > hInf.s ? true : false;
}

__device__ static inline bool __hle(__half a, __half b) {
  return a <= b ? true : false;
}

__device__ static inline bool __hlt(__half a, __half b) {
  return a < b ? true : false;
}

__device__ static inline bool __hne(__half a, __half b) {
  return a != b ? true : false;
}

/*
Half2 Comparision Functions
*/

__device__ static inline bool __hbeq2(__half2 a, __half2 b) {
  return (a.p[0] == b.p[0] ? true : false) && (a.p[1] == b.p[1] ? true : false);
}

__device__ static inline bool __hbge2(__half2 a, __half2 b) {
  return (a.p[0] >= b.p[0] ? true : false) && (a.p[1] >= b.p[1] ? true : false);
}

__device__ static inline bool __hbgt2(__half2 a, __half2 b) {
  return (a.p[0] > b.p[0] ? true : false) && (a.p[1] > b.p[1] ? true : false);
}

__device__ static inline bool __hble2(__half2 a, __half2 b) {
  return (a.p[0] <= b.p[0] ? true : false) && (a.p[1] <= b.p[1] ? true : false);
}

__device__ static inline bool __hblt2(__half2 a, __half2 b) {
  return (a.p[0] < b.p[0] ? true : false) && (a.p[1] < b.p[1] ? true : false);
}

__device__ static inline bool __hbne2(__half2 a, __half2 b) {
  return (a.p[0] != b.p[0] ? true : false) && (a.p[1] != b.p[1] ? true : false);
}

#endif

#if __clang_major__ == 3

typedef struct {
  unsigned x: 16;
} __half;

typedef struct __attribute__((aligned(4))){
  union {
    __half p[2];
    unsigned int q;
  };
} __half2;




#endif


#endif