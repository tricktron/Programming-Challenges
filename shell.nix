
{ pkgs ? import <nixpkgs> {} }:

with pkgs;
let stdenvClang9 = overrideCC stdenv clang_9;
in
mkShell.override{ stdenv = overrideCC stdenv clang_9; } { 
  buildInputs = [ (ccls.override { stdenv = stdenvClang9;  llvmPackages = llvmPackages_9; }) ];
}
  # Sets the build inputs, i.e. what will be available in our
  # local environment.
  #CPATH = "/Applications/Xcode.app/Contents/Developer/Platforms/MacOSX.platform/Developer/SDKs/MacOSX.sdk/usr/include";
