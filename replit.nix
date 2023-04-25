{ pkgs }: {
	deps = [
		pkgs.imagemagick6_light
  pkgs.xterm
  pkgs.clang_12
		pkgs.ccls
		pkgs.gdb
		pkgs.gnumake
	];
}