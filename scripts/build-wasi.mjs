#!/usr/bin/env zx

// Copyright (c) 2025 Roberto Raggi <roberto.raggi@gmail.com>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in
// all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

import "zx/globals";

$.verbose = true;

const workspacePath = path.join(__dirname, "../");
const docker = await which("docker");
const uid = String(await $`id -u`).trim();

$.cwd = workspacePath;

const dockerRunOpts = [
  "--rm",
  "-t",
  "-v",
  `${workspacePath}:/code`,
  "-w",
  "/code",
  "-u",
  uid,
  "cxx-wasi",
];

const dockerBuildArgs = [
  "-t",
  "cxx-wasi",
  "-f",
  `${workspacePath}/Dockerfile.wasi`,
  workspacePath,
];

const cmakeConfigureOpts = [
  "-G",
  "Ninja",
  "-S",
  ".",
  "-B",
  "build.wasi",
  "-DCMAKE_INSTALL_PREFIX=build.wasi/install/usr",
  "-DCMAKE_TOOLCHAIN_FILE=/opt/wasi-sdk/share/cmake/wasi-sdk.cmake",
  `-DCMAKE_BUILD_TYPE=${argv.debug ? "Debug" : "Release"}`,
  `-DCXX_INTERPROCEDURAL_OPTIMIZATION=${argv.debug ? "OFF" : "ON"}`,
  "-DFLATBUFFERS_FLATC_EXECUTABLE=/usr/bin/flatc",
  "-DCXX_INSTALL_WASI_SYSROOT=ON",
];

const cmakeBuildOpts = ["--build", "build.wasi", "--target", "install"];

async function main() {
  await $`${docker} build ${dockerBuildArgs}`;
  await $`${docker} run ${dockerRunOpts} cmake ${cmakeConfigureOpts}`;
  await $`${docker} run ${dockerRunOpts} cmake ${cmakeBuildOpts}`;
}

main().catch(console.error);
