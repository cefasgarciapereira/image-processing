#include<stdio.h>

int main(){
    FILE *streamIn;
    streamIn = fopen("lena.bmp", "rb"); // abre o arquivo

    unsigned char header[54]; // define a estrutura para salvar o header da imagem
    unsigned char colorTable[1024];  // define a estrutura para salvar colorTable, caso exista

    for (int i = 0; i < 54; i++) {
        header[i] = getc(streamIn); // remove o header
    }

    int width = *(int *) &header[18]; // lê a largura da imagem
    int height = *(int *) &header[22]; // lê a altura da imagem
    int bitDepth = *(int *) &header[28]; // lê o bitDepth do header

    if (bitDepth <= 8){
	    fread(colorTable, sizeof(unsigned char), 1024, streamIn);
    }

    unsigned char buf[height * width]; // define a estrutura para salvar os dados da imagem
    fread(buf, sizeof(unsigned char), (height * width), streamIn);

    FILE *fo = fopen("lena_copy.bmp", "wb"); // arquivo de saída

    fwrite(header, sizeof(unsigned char), 54, fo); // insere o header no arquivo de saída

    if (bitDepth <= 8){
	    fwrite(colorTable, sizeof(unsigned char), 1024, fo); // insere a colorTable no arquivo de saída
    }

    fwrite(buf, sizeof(unsigned char), (height * width), fo); // insere os dados da imagem

    fclose(fo);
    fclose(streamIn);

    return 0;
}