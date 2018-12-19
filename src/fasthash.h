/*
   The MIT License

   Copyright (C) 2012 Zilong Tan (eric.zltan@gmail.com)
   Copyright (C) 2018 Harold Freeman (haroldfreeman@protonmail.com)

   Permission is hereby granted, free of charge, to any person
   obtaining a copy of this software and associated documentation
   files (the "Software"), to deal in the Software without
   restriction, including without limitation the rights to use, copy,
   modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is
   furnished to do so, subject to the following conditions:

   The above copyright notice and this permission notice shall be
   included in all copies or substantial portions of the Software.

   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
   EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
   MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
   NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS
   BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
   CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
*/

#ifndef EDCOUNT_FASTHASH_H
#define EDCOUNT_FASTHASH_H

#include <stdint.h>
#include <stdio.h>

/**
 * 64-bit implementation of fasthash.
 * @param buf Data buffer.
 * @param len Data size.
 * @param seed The seed.
 * @return Hash value.
 */
uint64_t fasthash64(const void *buf, size_t len, uint64_t seed);

#endif
