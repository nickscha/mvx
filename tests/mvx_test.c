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

void mvx_test_voxelize_icosphere(void)
{
  /*
   * The array of vertex positions (x, y, z) for the mesh.
   * This icosphere has 42 vertices (12 initial vertices + 30 edge midpoints).
   */
  float icosphere_vertices[] = {
      -0.525731f, 0.850651f, 0.0f,        /* 0 */
      0.525731f, 0.850651f, 0.0f,         /* 1 */
      -0.525731f, -0.850651f, 0.0f,       /* 2 */
      0.525731f, -0.850651f, 0.0f,        /* 3 */
      0.0f, -0.525731f, 0.850651f,        /* 4 */
      0.0f, 0.525731f, 0.850651f,         /* 5 */
      0.0f, -0.525731f, -0.850651f,       /* 6 */
      0.0f, 0.525731f, -0.850651f,        /* 7 */
      0.850651f, 0.0f, -0.525731f,        /* 8 */
      0.850651f, 0.0f, 0.525731f,         /* 9 */
      -0.850651f, 0.0f, -0.525731f,       /* 10 */
      -0.850651f, 0.0f, 0.525731f,        /* 11 */
      0.0f, 0.894427f, 0.447214f,         /* 12 - Subdivision vertices start here */
      -0.447214f, 0.894427f, 0.0f,        /* 13 */
      -0.447214f, 0.447214f, 0.894427f,   /* 14 */
      0.447214f, 0.894427f, 0.0f,         /* 15 */
      0.447214f, 0.447214f, 0.894427f,    /* 16 */
      -0.447214f, -0.447214f, 0.894427f,  /* 17 */
      0.447214f, -0.447214f, 0.894427f,   /* 18 */
      0.0f, -0.894427f, 0.447214f,        /* 19 */
      0.0f, -0.894427f, -0.447214f,       /* 20 */
      -0.447214f, -0.894427f, 0.0f,       /* 21 */
      -0.447214f, -0.447214f, -0.894427f, /* 22 */
      0.447214f, -0.447214f, -0.894427f,  /* 23 */
      -0.894427f, 0.447214f, 0.0f,        /* 24 */
      -0.894427f, 0.0f, 0.447214f,        /* 25 */
      -0.894427f, 0.0f, -0.447214f,       /* 26 */
      -0.447214f, 0.447214f, -0.894427f,  /* 27 */
      -0.894427f, -0.447214f, 0.0f,       /* 28 */
      0.894427f, 0.447214f, 0.0f,         /* 29 */
      0.894427f, 0.0f, 0.447214f,         /* 30 */
      0.447214f, 0.447214f, -0.894427f,   /* 31 */
      0.894427f, -0.447214f, 0.0f,        /* 32 */
      0.894427f, 0.0f, -0.447214f,        /* 33 */
      -0.525731f, 0.0f, -0.850651f,       /* 34 */
      0.525731f, 0.0f, -0.850651f,        /* 35 */
      -0.525731f, 0.0f, 0.850651f,        /* 36 */
      0.525731f, 0.0f, 0.850651f,         /* 37 */
      0.0f, 0.525731f, 0.850651f,         /* 38 */
      0.0f, 0.525731f, -0.850651f,        /* 39 */
      -0.525731f, -0.850651f, 0.0f,       /* 40 */
      0.525731f, -0.850651f, 0.0f         /* 41 */
  };

  /*
   * The array of triangle indices. Each triplet of indices forms a triangle.
   * This icosphere has 80 triangles, so 240 indices.
   */
  int icosphere_indices[] = {
      11, 10, 24, 11, 24, 13, 11, 13, 5, 13, 0, 12, 13, 12, 1, 13, 1, 7,
      14, 11, 5, 14, 5, 12, 14, 12, 0, 14, 0, 24, 14, 24, 10, 14, 10, 22,
      1, 8, 29, 1, 29, 15, 1, 15, 7, 7, 15, 31, 7, 31, 8, 8, 31, 33,
      9, 1, 16, 9, 16, 29, 9, 29, 8, 9, 8, 33, 9, 33, 30, 9, 30, 4,
      2, 22, 23, 2, 23, 3, 2, 3, 20, 3, 18, 19, 3, 19, 20, 3, 20, 18,
      4, 30, 16, 4, 16, 5, 4, 5, 14, 4, 14, 25, 4, 25, 30, 4, 30, 16,
      2, 23, 20, 2, 20, 6, 2, 6, 22, 6, 20, 3, 6, 3, 18, 6, 18, 19,
      11, 10, 26, 11, 26, 22, 11, 22, 2, 10, 2, 21, 10, 21, 26, 10, 26, 22,
      11, 24, 13, 11, 13, 5, 11, 5, 14, 11, 14, 25, 11, 25, 24, 11, 24, 13,
      0, 13, 12, 0, 12, 1, 0, 1, 7, 0, 7, 10, 0, 10, 11, 0, 11, 5,
      1, 15, 31, 1, 31, 7, 1, 7, 13, 1, 13, 0, 1, 0, 12, 1, 12, 15,
      2, 21, 28, 2, 28, 40, 2, 40, 2, 2, 2, 21, 2, 21, 22, 2, 22, 23,
      3, 18, 19, 3, 19, 20, 3, 20, 18, 3, 18, 9, 3, 9, 8, 3, 8, 29,
      4, 36, 37, 4, 37, 9, 4, 9, 30, 4, 30, 36, 4, 36, 37, 4, 37, 9,
      2, 23, 3, 2, 3, 20, 2, 20, 6, 2, 6, 22, 2, 22, 23, 2, 23, 3,
      6, 22, 2, 6, 2, 21, 6, 21, 28, 6, 28, 20, 6, 20, 19, 6, 19, 23,
      10, 26, 11, 10, 11, 24, 10, 24, 0, 10, 0, 13, 10, 13, 5, 10, 5, 14,
      11, 10, 26, 11, 26, 22, 11, 22, 2, 11, 2, 21, 11, 21, 28, 11, 28, 40,
      1, 29, 15, 1, 15, 7, 1, 7, 13, 1, 13, 0, 1, 0, 12, 1, 12, 15,
      3, 18, 9, 3, 9, 8, 3, 8, 29, 3, 29, 15, 3, 15, 16, 3, 16, 9};

  unsigned long vertices_size = sizeof(icosphere_vertices) / sizeof(icosphere_vertices[0]);
  unsigned long indices_size = sizeof(icosphere_indices) / sizeof(icosphere_indices[0]);

  /* Define a grid size to accommodate the icosphere */
#define ico_grid_x 10
#define ico_grid_y 10
#define ico_grid_z 10
  unsigned char voxels[ico_grid_x * ico_grid_y * ico_grid_z];

  /* Voxelize the mesh with 1 cell padding */
  mvx_voxelize_mesh(
      icosphere_vertices, vertices_size,  /* Mesh Vertices     */
      icosphere_indices, indices_size,    /* Mesh Indices      */
      ico_grid_x, ico_grid_y, ico_grid_z, /* Grid Size         */
      1, 1, 1,                            /* Grid Cell Padding */
      voxels                              /* Output Voxels     */
  );

  /* Afterwards you can access the voxels data */

  mvx_test_print_voxels(voxels, ico_grid_x, ico_grid_y, ico_grid_z);
}

int main(void)
{
  mvx_test_voxelize_cube();
  mvx_test_voxelize_icosphere();

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
