#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(){
    FILE *ip,*op;
    char str[300], len[10];
    int i = 0, j, start, st, byte_count;
    ip = fopen("objcode.txt", "r");
    op = fopen("Absout.txt", "w");
    fscanf(ip, "%s\n", str);
    fprintf(op, "MEMORY ADDRESS\n");

    while (fscanf(ip, "%s\n", str) >= 1) {
        if (str[0] == 'E') break;
        for (int k = 2; k < 8; k++) {
            len[k - 2] = str[k];
        }
        len[6] = '\0';
        start = (int)strtoul(len, NULL, 16);

        i = 12;
        while (str[i] != '\0') {
            for (byte_count = 0; byte_count < 16 && str[i] != '\0'; byte_count++, start++) {
                fprintf(op, "%06x ", start);
                i += 2;
            }
            fprintf(op, "\n");
            start -= byte_count;  // Reset start to the beginning of the line
            i -= (byte_count * 2);  // Reset i to the beginning of the line
            for (byte_count = 0; byte_count < 16 && str[i] != '\0'; byte_count++, start++) {
                for (j = 0; j < 2; j++) {
                    fprintf(op, "%c", str[i + j]);
                }
                fprintf(op, "\t  ");
                i += 2;
            }
            fprintf(op, "\n\n");
        }
    }

    printf("Output is in Absout.txt\n");
    fclose(ip);
    fclose(op);
    return 0;
}



























// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// int main(){
//     FILE *ip,*op;
//     char str[300],len[10];
//     int i=0,j,start,temp,st;
//     ip=fopen("output.txt","r");
//     op=fopen("Absout.txt","w");
//     fscanf(ip,"%s\n",str);
//     fprintf(op,"MEMORY ADDRESS\t\tCONTENTS\n");
//     if(str[i]=='H'){
//         for(;str[i]!='^';i++);
//         i++;
//         for(;str[i]!='^';i++);
//         i++;
//         for(j=0;j<6;j++)
//         len[j]=str[i+j];
//         len[6]='\0';
//     }
//     st=(int)strtoul(len,NULL,16);
//     while(fscanf(ip,"%s\n",str)>=1){
//         if(str[0]=='E') break;
//         for(int k=2;k<8;k++){
//             len[k-2]=str[k];
//         }
//         len[6]='\0';
//         //start=(int)strtoul(len, NULL, 16)-st;
//         start=(int)strtoul(len, NULL, 16);
//         for(i=12;str[i]!='\0';){
//             fprintf(op,"\n%06x\t\t\t\t    ",start);
//             for(j=0;j<2;j++){
//                 fprintf(op,"%c",str[i+j]);
//             }
//             i+=2;
//             start+=1;
//         }
//     }
//     printf("Output is in Absout.txt\n");
//     return 0;
// }
