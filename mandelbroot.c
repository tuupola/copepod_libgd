/*

MIT No Attribution

Copyright (c) 2018-2020 Mika Tuupola

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS
OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

-cut-

SPDX-License-Identifier: MIT-0

*/

#include <time.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <hagl_hal.h>
#include <hagl.h>


int main()
{
    uint16_t max_x = DISPLAY_WIDTH;
    uint16_t max_y = DISPLAY_HEIGHT;
    uint16_t max_iters = 1024;

    uint16_t n = 0;
    uint16_t px;
    uint16_t py;

    double x;
    double y;
    double x0;
    double y0;
    double xx;
    double yy;
    double xtemp;

    double zoom = 1.0;

    clock_t start;
    clock_t end;
    double time_spent;

    hagl_init();

    start = clock();

    for (py = 1; py <= max_y; py++)  {
        for (px = 1; px <= max_x; px++)  {
            x0 = (((float) px) / ((float) max_x) - 0.5) / zoom * 3.0 - 0.7;
            y0 = (((float) py) / ((float) max_y) - 0.5) / zoom * 3.0;
            x = 0.0;
            y = 0.0;
            n = 0;

            // xx = x * x;
            // yy = y * y;

            while ((x * x + y * y < 4) && (n != max_iters)) {
                xtemp = x * x - y * y + x0;
                y = 2.0 * x * y + y0;
                x = xtemp;
                n++;
            }

            // while ((xx + yy < 4) && (n != max_iters)) {
            //     y = (x + x) * y + y0;
            //     x = xx - yy + x0;

            //     xx = x * x;
            //     yy = y * y;
            //     n++;
            // }

            if (n < max_iters) {
                hagl_put_pixel(px, py, n);
            } else {
                hagl_put_pixel(px, py, 0);
            }
        }
    }

    end = clock();
    time_spent = (double)(end - start) / CLOCKS_PER_SEC;
    printf("\nGenerated in %g seconds.\n\n", time_spent);
    hagl_flush();
    hagl_close();

    return 0;
}

