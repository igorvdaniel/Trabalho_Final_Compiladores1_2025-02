{
  pkgs,
  lib,
  config,
  inputs,
  ...
}:

{
  packages = with pkgs; [
    bison
    cmake
    flex
    gcc
    just
    ninja
  ];

  env.LD_LIBRARY_PATH = lib.makeLibraryPath [
    pkgs.flex
  ];
}
