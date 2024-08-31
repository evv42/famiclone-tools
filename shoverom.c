#include <stdio.h>
#include <stdlib.h>

int main(int argc, char** argv){

	unsigned long offset, orgsize, patchsize, tailsize;
	FILE* org;
	FILE* patch;
	FILE* output;

	if(argc != 5){
		printf("usage: %s <org> <patch> <output> <offset>\n", argv[0]);
		return 1;
	}

	offset = strtol(argv[4], NULL, 0);
	printf("%s + %s @ %d > %s\n", argv[1], argv[2], offset, argv[3]);

	org = fopen(argv[1], "rb");
	patch = fopen(argv[2], "rb");
	
	if(org == NULL || patch == NULL){
		printf("incorrect input\n");
		return 2;
	}

	output = fopen(argv[3], "wb");

	//determine original rom size
	fseek(org, 0, SEEK_END);
	orgsize = ftell(org);
	fseek(org, 0, SEEK_SET);
	
	//determine patch rom size
	fseek(patch, 0, SEEK_END);
	patchsize = ftell(patch);
	fseek(patch, 0, SEEK_SET);
	
	if( (patchsize+offset) > orgsize ){
		printf("patch doesn't fit in original rom");
		return 3;
	}

	tailsize = orgsize-patchsize-offset;
	char* buf_head = malloc(offset);
	char* buf_patch = malloc(patchsize);
	char* buf_tail = malloc(tailsize);

	fread(buf_head, offset, 1, org);
	fwrite(buf_head, offset, 1, output);

	fread(buf_patch, patchsize, 1, patch);
	fwrite(buf_patch, patchsize, 1, output);

	fseek(org, patchsize+offset, SEEK_SET);
	fread(buf_tail, tailsize, 1, org);
	fwrite(buf_tail, tailsize, 1, output);
	
	fclose(org);
	fclose(patch);
	fclose(output);

	return 0;

}
