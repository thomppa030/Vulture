#!/bin/bash

/home/thomppa/vulkansdk-linux-x86_64-1.3.224.1/1.3.224.1/x86_64/bin/glslc -fshader-stage=vert -o vert.spv shader.vert
/home/thomppa/vulkansdk-linux-x86_64-1.3.224.1/1.3.224.1/x86_64/bin/glslc -fshader-stage=frag -o frag.spv shader.frag
