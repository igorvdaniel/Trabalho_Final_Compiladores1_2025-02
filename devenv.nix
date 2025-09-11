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
    flex
    gcc
    just
  ];

  env.LD_LIBRARY_PATH = lib.makeLibraryPath [
    pkgs.flex
  ];
}
