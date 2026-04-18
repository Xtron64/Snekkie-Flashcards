{ pkgs ? import <nixpkgs> {} }: 
pkgs.mkShell {
	name = "snekkie-flashcards-dev";
	buildInputs = with pkgs.buildPackages; [
		bash
		gcc
		gnumake
		gdb
		valgrind
		just
	];
	shellHook = ''
		echo "🐍 Snekkie-Flashcards dev shell loaded"
		just --list
	'';
}
