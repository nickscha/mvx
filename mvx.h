/* mvx.h - v0.1 - public domain data structures - nickscha 2025

A C89 standard compliant, single header, nostdlib (no C Standard Library) mesh voxelizer (MVX).

LICENSE

  Placed in the public domain and also MIT licensed.
  See end of file for detailed license information.

*/
#ifndef MVX_H
#define MVX_H

/* #############################################################################
 * # COMPILER SETTINGS
 * #############################################################################
 */
#if __STDC_VERSION__ >= 199901L
#define MVX_INLINE inline
#define MVX_API extern
#elif defined(__GNUC__) || defined(__clang__)
#define MVX_INLINE __inline__
#define MVX_API static
#elif defined(_MSC_VER)
#define MVX_INLINE __inline
#define MVX_API static
#else
#define MVX_INLINE
#define MVX_API static
#endif

/* #############################################################################
 * # Linear Algebra & Math functions
 * #############################################################################
 */
typedef struct mvx_v3
{
  float x;
  float y;
  float z;

} mvx_v3;

typedef struct mvx_v3i
{
  int x;
  int y;
  int z;

} mvx_v3i;

MVX_API MVX_INLINE float mvx_absf(float a)
{
  return (a < 0.0f) ? -a : a;
}

MVX_API MVX_INLINE float mvx_minf(float a, float b)
{
  return (a < b) ? a : b;
}

MVX_API MVX_INLINE float mvx_maxf(float a, float b)
{
  return (a > b) ? a : b;
}

MVX_API MVX_INLINE float mvx_clampf(float v, float min, float max)
{
  return mvx_minf(max, mvx_maxf(v, min));
}

MVX_API MVX_INLINE int mvx_min_int(int a, int b)
{
  return (a < b) ? a : b;
}

MVX_API MVX_INLINE int mvx_max_int(int a, int b)
{
  return (a > b) ? a : b;
}

MVX_API MVX_INLINE int mvx_floorf(float v)
{
  int i = (int)v;
  if (v < 0.0f && (float)i != v)
  {
    return i - 1;
  }
  return i;
}

MVX_API MVX_INLINE int mvx_ceilf(float v)
{
  return -mvx_floorf(-v);
}

MVX_API MVX_INLINE int mvx_clamp_int(int v, int min, int max)
{
  if (v < min)
  {
    return min;
  }
  if (v > max)
  {
    return max;
  }
  return v;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3(float x, float y, float z)
{
  mvx_v3 result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_sub(mvx_v3 a, mvx_v3 b)
{
  mvx_v3 result;
  result.x = a.x - b.x;
  result.y = a.y - b.y;
  result.z = a.z - b.z;
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_add(mvx_v3 a, mvx_v3 b)
{
  mvx_v3 result;
  result.x = a.x + b.x;
  result.y = a.y + b.y;
  result.z = a.z + b.z;
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_cross(mvx_v3 a, mvx_v3 b)
{
  mvx_v3 result;
  result.x = a.y * b.z - a.z * b.y;
  result.y = a.z * b.x - a.x * b.z;
  result.z = a.x * b.y - a.y * b.x;
  return result;
}

MVX_API MVX_INLINE float mvx_mvx_v3_dot(mvx_v3 a, mvx_v3 b)
{
  return a.x * b.x + a.y * b.y + a.z * b.z;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_scale(mvx_v3 a, float s)
{
  mvx_v3 result;
  result.x = a.x * s;
  result.y = a.y * s;
  result.z = a.z * s;
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_abs(mvx_v3 a)
{
  mvx_v3 result;
  result.x = mvx_absf(a.x);
  result.y = mvx_absf(a.y);
  result.z = mvx_absf(a.z);
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_min(mvx_v3 a, mvx_v3 b)
{
  mvx_v3 result;
  result.x = mvx_minf(a.x, b.x);
  result.y = mvx_minf(a.y, b.y);
  result.z = mvx_minf(a.z, b.z);
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_max(mvx_v3 a, mvx_v3 b)
{
  mvx_v3 result;
  result.x = mvx_maxf(a.x, b.x);
  result.y = mvx_maxf(a.y, b.y);
  result.z = mvx_maxf(a.z, b.z);
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_clamp(mvx_v3 v, mvx_v3 min, mvx_v3 max)
{
  mvx_v3 result;
  result.x = mvx_clampf(v.x, min.x, max.x);
  result.y = mvx_clampf(v.y, min.y, max.y);
  result.z = mvx_clampf(v.z, min.z, max.z);
  return result;
}

MVX_API MVX_INLINE mvx_v3 mvx_mvx_v3_max_scalar(mvx_v3 v, float s)
{
  mvx_v3 result;
  result.x = mvx_maxf(v.x, s);
  result.y = mvx_maxf(v.y, s);
  result.z = mvx_maxf(v.z, s);
  return result;
}

MVX_API MVX_INLINE float mvx_mvx_v3_min_element(mvx_v3 v)
{
  return mvx_minf(mvx_minf(v.x, v.y), v.z);
}

MVX_API MVX_INLINE float mvx_mvx_v3_max_element(mvx_v3 v)
{
  return mvx_maxf(mvx_maxf(v.x, v.y), v.z);
}

MVX_API MVX_INLINE mvx_v3i mvx_mvx_v3i(int x, int y, int z)
{
  mvx_v3i result;
  result.x = x;
  result.y = y;
  result.z = z;
  return result;
}

MVX_API MVX_INLINE mvx_v3i mvx_mvx_v3i_min(mvx_v3i a, mvx_v3i b)
{
  mvx_v3i result;
  result.x = mvx_min_int(a.x, b.x);
  result.y = mvx_min_int(a.y, b.y);
  result.z = mvx_min_int(a.z, b.z);
  return result;
}

MVX_API MVX_INLINE mvx_v3i mvx_mvx_v3i_max(mvx_v3i a, mvx_v3i b)
{
  mvx_v3i result;
  result.x = mvx_max_int(a.x, b.x);
  result.y = mvx_max_int(a.y, b.y);
  result.z = mvx_max_int(a.z, b.z);
  return result;
}

/* point inside axis-aligned box (with epsilon) in world space */
MVX_API MVX_INLINE int mvx_point_in_box_eps_world(mvx_v3 p, mvx_v3 c, mvx_v3 h, float eps)
{
  if (p.x < c.x - h.x - eps || p.x > c.x + h.x + eps)
  {
    return 0;
  }
  if (p.y < c.y - h.y - eps || p.y > c.y + h.y + eps)
  {
    return 0;
  }
  if (p.z < c.z - h.z - eps || p.z > c.z + h.z + eps)
  {
    return 0;
  }
  return 1;
}

/* #############################################################################
 * # Mesh Voxelization Algorythm
 * #############################################################################
 */
/* Akenine-Möller triangle-box overlap test */
MVX_API MVX_INLINE int mvx_triangle_box_overlap(
    mvx_v3 boxcenter,
    mvx_v3 boxhalf,
    mvx_v3 triv0,
    mvx_v3 triv1,
    mvx_v3 triv2)
{
  mvx_v3 v0, v1, v2;
  mvx_v3 e0, e1, e2;
  mvx_v3 fexyzez;

  float p0, p1, p2, minp, maxp, rad;
  float minv, maxv;

  /* move triangle to box space */
  v0 = mvx_mvx_v3_sub(triv0, boxcenter);
  v1 = mvx_mvx_v3_sub(triv1, boxcenter);
  v2 = mvx_mvx_v3_sub(triv2, boxcenter);

  e0 = mvx_mvx_v3_sub(v1, v0);
  e1 = mvx_mvx_v3_sub(v2, v1);
  e2 = mvx_mvx_v3_sub(v0, v2);

  /* 9 axis tests */
  fexyzez = mvx_mvx_v3_abs(e0);

  p0 = v0.z * e0.y - v0.y * e0.z;
  p1 = v1.z * e0.y - v1.y * e0.z;
  p2 = v2.z * e0.y - v2.y * e0.z;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.y * fexyzez.z + boxhalf.z * fexyzez.y;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.x * e0.z - v0.z * e0.x;
  p1 = v1.x * e0.z - v1.z * e0.x;
  p2 = v2.x * e0.z - v2.z * e0.x;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.z + boxhalf.z * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.y * e0.x - v0.x * e0.y;
  p1 = v1.y * e0.x - v1.x * e0.y;
  p2 = v2.y * e0.x - v2.x * e0.y;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.y + boxhalf.y * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  fexyzez = mvx_mvx_v3_abs(e1);

  p0 = v0.z * e1.y - v0.y * e1.z;
  p1 = v1.z * e1.y - v1.y * e1.z;
  p2 = v2.z * e1.y - v2.y * e1.z;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.y * fexyzez.z + boxhalf.z * fexyzez.y;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.x * e1.z - v0.z * e1.x;
  p1 = v1.x * e1.z - v1.z * e1.x;
  p2 = v2.x * e1.z - v2.z * e1.x;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.z + boxhalf.z * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.y * e1.x - v0.x * e1.y;
  p1 = v1.y * e1.x - v1.x * e1.y;
  p2 = v2.y * e1.x - v2.x * e1.y;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.y + boxhalf.y * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  fexyzez = mvx_mvx_v3_abs(e2);

  p0 = v0.z * e2.y - v0.y * e2.z;
  p1 = v1.z * e2.y - v1.y * e2.z;
  p2 = v2.z * e2.y - v2.y * e2.z;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.y * fexyzez.z + boxhalf.z * fexyzez.y;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.x * e2.z - v0.z * e2.x;
  p1 = v1.x * e2.z - v1.z * e2.x;
  p2 = v2.x * e2.z - v2.z * e2.x;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.z + boxhalf.z * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  p0 = v0.y * e2.x - v0.x * e2.y;
  p1 = v1.y * e2.x - v1.x * e2.y;
  p2 = v2.y * e2.x - v2.x * e2.y;

  minp = mvx_minf(mvx_minf(p0, p1), p2);
  maxp = mvx_maxf(mvx_maxf(p0, p1), p2);

  rad = boxhalf.x * fexyzez.y + boxhalf.y * fexyzez.x;

  if (minp > rad || maxp < -rad)
  {
    return 0;
  }

  /* test overlap in box axes */
  minv = mvx_mvx_v3_min_element(v0);
  minv = mvx_minf(minv, mvx_mvx_v3_min_element(v1));
  minv = mvx_minf(minv, mvx_mvx_v3_min_element(v2));

  maxv = mvx_mvx_v3_max_element(v0);
  maxv = mvx_maxf(maxv, mvx_mvx_v3_max_element(v1));
  maxv = mvx_maxf(maxv, mvx_mvx_v3_max_element(v2));

  if (minv > mvx_mvx_v3_max_element(boxhalf) || maxv < -mvx_mvx_v3_max_element(boxhalf))
  {
    return 0;
  }

  /* plane-box overlap */
  {
    mvx_v3 n;
    n = mvx_mvx_v3_cross(e0, e1);

    /* distance from origin (box center) to triangle plane */
    p0 = -mvx_mvx_v3_dot(n, v0);
    rad = mvx_mvx_v3_dot(boxhalf, mvx_mvx_v3_abs(n));

    if (p0 > rad || p0 < -rad)
    {
      return 0;
    }
  }
  return 1;
}

/* Aspect-ratio preserving, centered voxelizer with padding */
MVX_API MVX_INLINE int mvx_voxelize_mesh(
    float *vertices,              /* The array of vertex positions (x, y, z) for the mesh. */
    unsigned long vertices_size,  /* The number of floats in the vertices array. This should be 3 times the number of vertices. */
    int *indices,                 /* The array of triangle indices. Each triplet of indices forms a triangle. */
    unsigned long indices_size,   /* The number of integers in the indices array. This should be 3 times the number of triangles. */
    int grid_x,                   /* The total number of voxels along the x-axis of the grid. */
    int grid_y,                   /* The total number of voxels along the y-axis of the grid. */
    int grid_z,                   /* The total number of voxels along the z-axis of the grid. */
    int grid_pad_x,               /* The number of empty voxels to pad on both the left and right sides of the grid. */
    int grid_pad_y,               /* The number of empty voxels to pad on both the bottom and top sides of the grid. */
    int grid_pad_z,               /* The number of empty voxels to pad on both the front and back sides of the grid. */
    unsigned char *output_voxels) /* The output array of unsigned characters where the voxelized mesh will be stored. A value of 1 means the voxel is occupied. */
{
  unsigned long vcount = vertices_size / 3;
  unsigned long tricount = indices_size / 3;

  mvx_v3 min_b = mvx_mvx_v3(0, 0, 0);
  mvx_v3 max_b = mvx_mvx_v3(0, 0, 0);

  int first = 1;
  long total = (long)grid_x * (long)grid_y * (long)grid_z;
  long q;
  unsigned long t;
  float vxsize;

  mvx_v3 size;
  mvx_v3 effective_grid;
  mvx_v3 need_v;
  mvx_v3i margin;

  int ia, ib, ic;

  mvx_v3 v0, v1, v2;
  mvx_v3 tmin_b, tmax_b;
  mvx_v3i i_min, i_max;

  int x, y, z;

  if (!vertices || !indices || vcount == 0 || tricount == 0 || grid_x <= 0 || grid_y <= 0 || grid_z <= 0)
  {
    return 0;
  }

  /* clear voxels */
  for (q = 0; q < total; ++q)
  {
    output_voxels[q] = 0;
  }

  /* grid gap must be at least 1 */
  grid_pad_x = mvx_max_int(grid_pad_x, 1);
  grid_pad_y = mvx_max_int(grid_pad_y, 1);
  grid_pad_z = mvx_max_int(grid_pad_z, 1);

  /* mesh bounds */
  for (t = 0; t < vcount; ++t)
  {
    mvx_v3 current_v = mvx_mvx_v3(vertices[3 * t + 0], vertices[3 * t + 1], vertices[3 * t + 2]);

    if (first)
    {
      min_b = max_b = current_v;
      first = 0;
    }
    else
    {
      min_b = mvx_mvx_v3_min(min_b, current_v);
      max_b = mvx_mvx_v3_max(max_b, current_v);
    }
  }
  if (max_b.x <= min_b.x)
  {
    max_b.x = min_b.x + 1e-6f;
  }
  if (max_b.y <= min_b.y)
  {
    max_b.y = min_b.y + 1e-6f;
  }
  if (max_b.z <= min_b.z)
  {
    max_b.z = min_b.z + 1e-6f;
  }

  /* uniform voxel size (keep aspect ratio) */
  size = mvx_mvx_v3_sub(max_b, min_b);

  /* effective grid size after accounting for the gap */
  effective_grid = mvx_mvx_v3(
      (float)(grid_x - grid_pad_x * 2),
      (float)(grid_y - grid_pad_y * 2),
      (float)(grid_z - grid_pad_z * 2));

  effective_grid = mvx_mvx_v3_max_scalar(effective_grid, 1.0f);

  vxsize = mvx_maxf(size.x / effective_grid.x,
                    mvx_maxf(size.y / effective_grid.y,
                             size.z / effective_grid.z));

  /* how many voxels object actually needs along each axis */
  need_v = mvx_mvx_v3(
      (float)mvx_ceilf(size.x / vxsize),
      (float)mvx_ceilf(size.y / vxsize),
      (float)mvx_ceilf(size.z / vxsize));

  need_v = mvx_mvx_v3_min(need_v, effective_grid);

  /* integer margins: the initial gap plus the centering margin within the effective grid */
  margin = mvx_mvx_v3i(
      grid_pad_x + mvx_floorf((effective_grid.x - need_v.x) / 2.0f),
      grid_pad_y + mvx_floorf((effective_grid.y - need_v.y) / 2.0f),
      grid_pad_z + mvx_floorf((effective_grid.z - need_v.z) / 2.0f));

  /* triangle sweep */
  for (t = 0; t < tricount; ++t)
  {
    ia = indices[3 * t + 0];
    ib = indices[3 * t + 1];
    ic = indices[3 * t + 2];

    if (ia < 0 || ib < 0 || ic < 0)
    {
      continue;
    }

    if ((unsigned long)ia >= vcount || (unsigned long)ib >= vcount || (unsigned long)ic >= vcount)
    {
      continue;
    }

    v0 = mvx_mvx_v3(vertices[3 * ia + 0], vertices[3 * ia + 1], vertices[3 * ia + 2]);
    v1 = mvx_mvx_v3(vertices[3 * ib + 0], vertices[3 * ib + 1], vertices[3 * ib + 2]);
    v2 = mvx_mvx_v3(vertices[3 * ic + 0], vertices[3 * ic + 1], vertices[3 * ic + 2]);

    /* tri AABB in world */
    tmin_b = mvx_mvx_v3(
        mvx_minf(v0.x, mvx_minf(v1.x, v2.x)),
        mvx_minf(v0.y, mvx_minf(v1.y, v2.y)),
        mvx_minf(v0.z, mvx_minf(v1.z, v2.z)));

    tmax_b = mvx_mvx_v3(
        mvx_maxf(v0.x, mvx_maxf(v1.x, v2.x)),
        mvx_maxf(v0.y, mvx_maxf(v1.y, v2.y)),
        mvx_maxf(v0.z, mvx_maxf(v1.z, v2.z)));

    /* map to voxel index range */
    i_min = mvx_mvx_v3i(
        mvx_floorf((tmin_b.x - min_b.x) / vxsize) + margin.x,
        mvx_floorf((tmin_b.y - min_b.y) / vxsize) + margin.y,
        mvx_floorf((tmin_b.z - min_b.z) / vxsize) + margin.z);

    i_max = mvx_mvx_v3i(
        mvx_floorf((tmax_b.x - min_b.x) / vxsize) + margin.x,
        mvx_floorf((tmax_b.y - min_b.y) / vxsize) + margin.y,
        mvx_floorf((tmax_b.z - min_b.z) / vxsize) + margin.z);

    /* clamp to object's voxel range and overall grid */
    i_min.x = mvx_clamp_int(i_min.x, margin.x, margin.x + (int)need_v.x - 1);
    i_min.y = mvx_clamp_int(i_min.y, margin.y, margin.y + (int)need_v.y - 1);
    i_min.z = mvx_clamp_int(i_min.z, margin.z, margin.z + (int)need_v.z - 1);
    i_max.x = mvx_clamp_int(i_max.x, margin.x, margin.x + (int)need_v.x - 1);
    i_max.y = mvx_clamp_int(i_max.y, margin.y, margin.y + (int)need_v.y - 1);
    i_max.z = mvx_clamp_int(i_max.z, margin.z, margin.z + (int)need_v.z - 1);

    i_min.x = mvx_clamp_int(i_min.x, 0, grid_x - 1);
    i_min.y = mvx_clamp_int(i_min.y, 0, grid_y - 1);
    i_min.z = mvx_clamp_int(i_min.z, 0, grid_z - 1);
    i_max.x = mvx_clamp_int(i_max.x, 0, grid_x - 1);
    i_max.y = mvx_clamp_int(i_max.y, 0, grid_y - 1);
    i_max.z = mvx_clamp_int(i_max.z, 0, grid_z - 1);

    if (i_min.x > i_max.x || i_min.y > i_max.y || i_min.z > i_max.z)
    {
      continue;
    }

    /* scan candidate voxels */
    for (z = i_min.z; z <= i_max.z; ++z)
    {
      for (y = i_min.y; y <= i_max.y; ++y)
      {
        for (x = i_min.x; x <= i_max.x; ++x)
        {
          mvx_v3 boxc, boxh;
          float eps = 1e-6f;
          /* world center of voxel (account for margins) */
          boxc.x = min_b.x + ((float)(x - margin.x) + 0.5f) * vxsize;
          boxc.y = min_b.y + ((float)(y - margin.y) + 0.5f) * vxsize;
          boxc.z = min_b.z + ((float)(z - margin.z) + 0.5f) * vxsize;
          boxh.x = boxh.y = boxh.z = 0.5f * vxsize;

          if (mvx_point_in_box_eps_world(v0, boxc, boxh, eps) ||
              mvx_point_in_box_eps_world(v1, boxc, boxh, eps) ||
              mvx_point_in_box_eps_world(v2, boxc, boxh, eps) ||
              mvx_triangle_box_overlap(boxc, boxh, v0, v1, v2))
          {
            long id = (long)x + (long)y * grid_x + (long)z * grid_x * grid_y;

            output_voxels[id] = 1;
          }
        }
      }
    }
  }

  return 1;
}

#endif /* MVX_H */

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
