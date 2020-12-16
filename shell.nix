
{ pkgs ? import <nixpkgs> {} }:

with pkgs;

/* I need to override stdenv in order to use a specific clang version. If I just add it to buildInputs it will
not be on the path because the stdenv clang takes precendence. If I add it to nativeBuildInputs then I can use
clang_9 but if I want to compile a simple helloWorld it fails with errors, probably because it has two libc++
version linked, namely the one from nativeBuildInputs and the one from clangWrapper in stdenv.

I could use this in vsCode with the following task definition: Notice the single quotes because of the --run flag.
Unfortunately I then couldn't use the debugger because the launch.json opens in a new shell where it has no
access to the nix-shell envs including libc++. So I gave up and use my impure apple clang with ccls.
{
    "version": "2.0.0",
    "tasks": [
        {
            "label": "Build and Run C++",
            "type": "shell",
            "command": "nix-shell",
            "args": [
                "--run",
                "'clang++
                "-v",
                "-std=c++17",
                "-stdlib=libc++",
                "-g",
                "${file}",
                "-o",
                "${workspaceFolder}/bin/${fileBasenameNoExtension}'",
                "&&",
                "${workspaceFolder}/bin/${fileBasenameNoExtension}",
            ],
            "problemMatcher": [],
            "options": {
                "cwd": "${workspaceFolder}"
            }
        },
        {
        "label":"Enter nix-shell",
        "type": "shell",
        "command": "nix-shell",
        "problemMatcher": []
        } 
    ]
}
 */
mkShell { 
  buildInputs = [ (ccls.override { llvmPackages = llvmPackages_9; }) ]
    ++ stdenv.lib.optionals stdenv.isLinux [ llvmPackages_9.libcxxClang ];
  shellHook = ''
  '';
}