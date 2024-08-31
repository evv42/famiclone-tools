#include <stdio.h>
#include <stdlib.h>

//NOTE: Won't compute PRG rom size correctly if it's 2 mibs, which is unlikely anyway

int main(int argc, char** argv){

	if(argc != 6){
		printf("usage: %s @4100 @410A @410B @2018 @201A\n", argv[0]);
		return 1;
	}

	unsigned int prg_o, prg_m, prg_s, chr_i, chr_m, chr_s;

	prg_o = strtol(argv[1], NULL, 0);
	prg_m = strtol(argv[2], NULL, 0);
	prg_s = strtol(argv[3], NULL, 0);
	chr_i = strtol(argv[4], NULL, 0);
	chr_m = strtol(argv[5], NULL, 0);

	prg_s = prg_s & 0x07;
	unsigned int offset = ((prg_m & (0xFC0 >> prg_s) ) | ( (prg_o & 0xF0) << 4)) * 8192;
	printf("PRG: %d kibs @ %d\n", 512 >> prg_s,  offset);
	
	chr_i = chr_i & 0x70;
	chr_s = chr_m & 0x07;
	if(chr_s > 2)chr_s--;
	switch(chr_m & 0x07){
		case 1: chr_m = chr_m & 0x80;break;
		case 2: chr_m = chr_m & 0xC0;break;
		case 4: chr_m = chr_m & 0xE0;break;
		case 5: chr_m = chr_m & 0xF0;break;
		case 6: chr_m = chr_m & 0xF8;break;
		default:break;
	}
	printf("CHR: %d kibs @ %d\n", 256 >> chr_s, ((chr_m & 0xF8) | ((chr_i & 0x70)<<4) | ((prg_o & 0x0F) << 11)) * 1024);

	return 0;
}
