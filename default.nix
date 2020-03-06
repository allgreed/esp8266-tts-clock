{ pkgs ? import <nixpkgs> {} }:

with pkgs;

mkShell {
  buildInputs = [ git gnumake gtest ];
}
