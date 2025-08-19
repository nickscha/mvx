/* mvx.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) mesh voxelizer (MVX).

This Test class defines cases to verify that we don't break the excepted behaviours in the future upon changes.

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#include "../mvx.h" /* Mesh Voxelizer           */
#include "test.h"   /* Simple Testing framework */

void mvx_test_print_voxels(unsigned char *voxels, int grid_x, int grid_y, int grid_z)
{
  int z, y, x;
  for (z = 0; z < grid_z; ++z)
  {
    printf("[mvx] z = %d\n", z);
    for (y = grid_y - 1; y >= 0; --y)
    {
      printf("[mvx] ");
      for (x = 0; x < grid_x; ++x)
      {
        long idx = x + y * grid_x + z * grid_x * grid_y;
        printf("%c", voxels[idx] ? '#' : '.');
      }
      printf("\n");
    }
    printf("\n");
  }
}

void mvx_test_voxelize_cube(void)
{
  /* Example: A unit cube mesh */
  float vertices[] = {
      0.0f, 0.0f, 0.0f,
      1.0f, 0.0f, 0.0f,
      1.0f, 1.0f, 0.0f,
      0.0f, 1.0f, 0.0f,
      0.0f, 0.0f, 1.0f,
      1.0f, 0.0f, 1.0f,
      1.0f, 1.0f, 1.0f,
      0.0f, 1.0f, 1.0f};

  unsigned long vertices_size = sizeof(vertices) / sizeof(vertices[0]);

  /* Example: A unit cube mesh indices (two per face) */
  int indices[] = {
      0, 1, 2, 0, 2, 3, /* bottom */
      4, 5, 6, 4, 6, 7, /* top */
      0, 1, 5, 0, 5, 4, /* front */
      1, 2, 6, 1, 6, 5, /* right */
      2, 3, 7, 2, 7, 6, /* back */
      3, 0, 4, 3, 4, 7  /* left */
  };

  unsigned long indices_size = sizeof(indices) / sizeof(indices[0]);

/* Define a grid size where the voxelized mesh should fit into */
#define grid_x 20
#define grid_y 10
#define grid_z 10
  unsigned char voxels[grid_x * grid_y * grid_z];

  /* Voxelize the mesh with 1 cell padding */
  mvx_voxelize_mesh(
      vertices, vertices_size, /* Mesh Vertices     */
      indices, indices_size,   /* Mesh Indices      */
      grid_x, grid_y, grid_z,  /* Grid Size         */
      1, 1, 1,                 /* Grid Cell Padding */
      voxels                   /* Output Voxels     */
  );

  /* Afterwards you can access the voxels data */

  mvx_test_print_voxels(voxels, grid_x, grid_y, grid_z);
}

int main(void)
{
  mvx_test_voxelize_cube();

  return 0;
}

/*
   ------------------------------------------------------------------------------
   This software is available under 2 licenses -- choose whichever you prefer.
   ------------------------------------------------------------------------------
   ALTERNATIVE A - MIT License
   Copyright (c) 2025 nickscha
   Permission is hereby granted, free of charge, to any person obtaining a copy of
   this software and associated documentation files (the "Software"), to deal in
   the Software without restriction, including without limitation the rights to
   use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies
   of the Software, and to permit persons to whom the Software is furnished to do
   so, subject to the following conditions:
   The above copyright notice and this permission notice shall be included in all
   copies or substantial portions of the Software.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
   LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
   OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
   SOFTWARE.
   ------------------------------------------------------------------------------
   ALTERNATIVE B - Public Domain (www.unlicense.org)
   This is free and unencumbered software released into the public domain.
   Anyone is free to copy, modify, publish, use, compile, sell, or distribute this
   software, either in source code form or as a compiled binary, for any purpose,
   commercial or non-commercial, and by any means.
   In jurisdictions that recognize copyright laws, the author or authors of this
   software dedicate any and all copyright interest in the software to the public
   domain. We make this dedication for the benefit of the public at large and to
   the detriment of our heirs and successors. We intend this dedication to be an
   overt act of relinquishment in perpetuity of all present and future rights to
   this software under copyright law.
   THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
   IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
   FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
   AUTHORS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN
   ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION
   WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
   ------------------------------------------------------------------------------
*/
