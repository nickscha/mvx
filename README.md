# mvx
A C89 standard compliant, single header, nostdlib (no C Standard Library) mesh voxelizer (MVX).

<p align="center">
<a href="https://github.com/nickscha/mvx"><img src="assets/mvx.png"></a>
</p>

For more information please look at the "mvx.h" file or take a look at the "examples" or "tests" folder.

> [!WARNING]
> THIS PROJECT IS A WORK IN PROGRESS! ANYTHING CAN CHANGE AT ANY MOMENT WITHOUT ANY NOTICE! USE THIS PROJECT AT YOUR OWN RISK!

This is an example of a voxelized teddy .obj file (grid 100x100x100).

<p align="center">
<a href="https://github.com/nickscha/mvx"><img src="assets/teddy_voxel.png"></a>
</p>

## Quick Start

Download or clone mvx.h and include it in your project.

```C
#include "mvx.h" /* Mesh Voxelizer */

int main() {
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
        4, 5, 6, 4, 6, 7, /* top    */
        0, 1, 5, 0, 5, 4, /* front  */
        1, 2, 6, 1, 6, 5, /* right  */
        2, 3, 7, 2, 7, 6, /* back   */
        3, 0, 4, 3, 4, 7  /* left   */
    };

    unsigned long indices_size = sizeof(indices) / sizeof(indices[0]);

    /* Define a grid size where the voxelized mesh should fit into */
    #define grid_x 20
    #define grid_y 10
    #define grid_z 10
    unsigned char voxels[grid_x * grid_y * grid_z];

    /* Voxelize the mesh with 1 cell padding */
    if(!mvx_voxelize_mesh(
        vertices, vertices_size, /* Mesh Vertices     */
        indices, indices_size,   /* Mesh Indices      */
        grid_x, grid_y, grid_z,  /* Grid Size         */
        1, 1, 1,                 /* Grid Cell Padding */
        voxels                   /* Output Voxels     */
    )) {
        return 1;
    }

    /* Afterwards you can access the voxels data */

    return 0;
}
```

## Run Example: nostdlib, freestsanding

In this repo you will find the "examples/mvx_win32_nostdlib.c" with the corresponding "build.bat" file which
creates an executable only linked to "kernel32" and is not using the C standard library and executes the program afterwards.

## "nostdlib" Motivation & Purpose

nostdlib is a lightweight, minimalistic approach to C development that removes dependencies on the standard library. The motivation behind this project is to provide developers with greater control over their code by eliminating unnecessary overhead, reducing binary size, and enabling deployment in resource-constrained environments.

Many modern development environments rely heavily on the standard library, which, while convenient, introduces unnecessary bloat, security risks, and unpredictable dependencies. nostdlib aims to give developers fine-grained control over memory management, execution flow, and system calls by working directly with the underlying platform.

### Benefits

#### Minimal overhead
By removing the standard library, nostdlib significantly reduces runtime overhead, allowing for faster execution and smaller binary sizes.

#### Increased security
Standard libraries often include unnecessary functions that increase the attack surface of an application. nostdlib mitigates security risks by removing unused and potentially vulnerable components.

#### Reduced binary size
Without linking to the standard library, binaries are smaller, making them ideal for embedded systems, bootloaders, and operating systems where storage is limited.

#### Enhanced performance
Direct control over system calls and memory management leads to performance gains by eliminating abstraction layers imposed by standard libraries.

#### Better portability
By relying only on fundamental system interfaces, nostdlib allows for easier porting across different platforms without worrying about standard library availability.
