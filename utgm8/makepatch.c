#include <stdlib.h>
#include <stdio.h>
#include <assert.h>

int main(int argc, char** argv) {
	if(argc != 3) {
		puts("makepatch file1 file2");
		return -1;
	}
	FILE* fp = fopen(argv[1], "rb");
	FILE* fpproof = fopen(argv[2], "rb");
	assert(fp); assert(fpproof);
	fseek(fp, 0, SEEK_END); size_t insize = ftell(fp); rewind(fp);
	fseek(fpproof, 0, SEEK_END); size_t proofsize = ftell(fpproof); rewind(fpproof);
	char* in = (char*)malloc(insize); fread(in, insize, 1, fp); fclose(fp);
	char* proof = (char*)malloc(proofsize); fread(proof, proofsize, 1, fpproof); fclose(fpproof);
	assert(in); assert(proof);
	for(int i = 0; i < insize; i++) {
		in[i] ^= proof[i % proofsize];
	}
	fp = fopen("out.bin", "wb");
	assert(fp);
	fwrite(in, insize, 1, fp);
	fclose(fp);
	return 0;
}