{ pkgs }: {
	deps = [
		pkgs.xterm
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}