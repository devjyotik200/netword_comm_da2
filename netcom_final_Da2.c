
#include<stdio.h>

void lrc(){
    int N=32;
    int m=N-1;
    int input[N+8];
    int temp[8]={0};
    printf("\nEnter the 32 bit dataword: ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d",&input[i]);
    }
    for (int i=0;i<N;i++){
        if(input[i]==1){
            temp[i%8]=temp[i%8]+1;
        }
    }
    for(int i=0;i<8;i++){
        if (temp[i]%2==0){
            m=m+1;
            input[m]=0;
        }
        else{
            m=m+1;
            input[m]=1;
        }
    }
    printf("\nThe parity bits are: ");
    for(int i=N;i<m;i++){
        printf("%d",input[i]);
    }
    printf("\nThe word to be transmitted is: ");
    for (int i = 0; i < m; i++)
    {
        printf("%d",input[i]);
    }

}


void vrc(){
    int N;
    int c=0;
    int input[N+1];
    printf("\nEnter the no. of bits");
    scanf("%d",&N);

    printf("\nEnter the dataword: ");
    for (int i = 0; i < N; i++)
    {
        scanf("%d",&input[i]);
        if (input[i]==1){
            c=c+1;
        }
    }
    if(c%2!=0){
        input[N]=1;
    }
    else{
        input[N]=0;
    }
    for (int i = 0; i <= N; i++)
    {
        printf("%d",input[i]);
    }
}

 int rem(int,int);
 void reciver(int[],int[]);
 void sender();

 int rem(int x, int y)
 {
  if(x==y)
   return 0;
  else
   return 1;
 }


 void reciever(int dl,int dil,int revdata[100],int div[100]){

  int i,j,k;

  int remd[dil], data[dl];
  for(i=0;i<dl;i++)
     data[i]=revdata[i];

   for(j=0;j<=dl;j++){
        for(i=0;i<dil;i++)
            {
                remd[i]=revdata[i+j];
                if(remd[0]==1)
                revdata[i+j]=rem(revdata[i+j],div[i]);
                else
                revdata[i+j]=rem(revdata[i+j],0);
            }

        }
  printf("\n The reminder is : ");
  k=0;
  for(i=0;i<dil-1;i++)
   {
   printf("%d",remd[i]);
    if(remd[i]==0)
     k++;
   }
  if(k==dil-1){
  printf("\n No error, Dataword is:  ");
  for(i=0;i<dl;i++)
    printf("%d",data[i]);
  }else
  printf("\n There is error found.\n");

 }

 void sender()
 {
   int i,j,k,dl,dil;
   int data[10],div[5],newdata[15],crc[5],datacrc[15];

   printf("\n Enter the data length= ");
   scanf("%d",&dl);
   printf("\n Enter the divisor  length= ");
   scanf("%d",&dil);
   printf("\n Enter the data : ");
   for(i=0;i<dl;i++)
    scanf("%d",&data[i]);
   printf("\n Enter the divisor : ");
   for(i=0;i<dil;i++)
    scanf("%d",&div[i]);
   printf("\n The new data is : ");
   for(i=0;i<(dl+dil-1);i++)
   {
     if(i<dl)
      newdata[i]=data[i];
     else
      newdata[i]=0;
     printf("%d",newdata[i]);
   }
  for(j=0;j<=dl;j++)
  {
     for(i=0;i<dil;i++)
     {
         crc[i]=newdata[i+j];
         if(crc[0]==1)
         newdata[i+j]=rem(newdata[i+j],div[i]);
         else
         newdata[i+j]=rem(newdata[i+j],0);
     }
  }
  printf("\n The Crc is : ");
  for(i=0;i<dil-1;i++)
  printf("%d",crc[i]);

  printf("\n The data to be send is : ");
  for(i=0;i<(dl+dil-1);i++)
  {
   if(i<dl)
    datacrc[i]=data[i];
   else
    datacrc[i]=crc[i-dl];
   printf("%d",datacrc[i]);
  }
  reciever(dl,dil,datacrc,div);
 }



int input[32];

int code[32];

// int ham_calc(int, int);
 void solve(int input[], int);
 void reciever2(int ,int );


 int ham_calc(int position, int c_l)
 {
     int count = 0, i, j;
     i = position - 1;

     while (i < c_l) {

         for (j = i; j < i + position; j++) {

             if (code[j] == 1)
                 count++;
         }

         i = i + 2 * position;
     }

     if (count % 2 != 0)
         return 0;
     else
         return 1;
 }

 void solve(int input[], int n)
 {
     int i, p_n = 0, c_l, j, k;
     i = 0;

     while (n > (int)pow(2, i) - (i + 1)) {
         p_n++;
         i++;
     }

     c_l = p_n + n;

     printf("No. of redundant bits: %d\n",p_n);
     printf("No. of bits in hamming code: %d\n",c_l);

     j = k = 0;

     for (i = 0; i < c_l; i++) {

         if (i == ((int)pow(2, k) - 1)) {
             code[i] = 0;
             k++;
         }

         else {
             code[i] = input[j];
             j++;
         }
     }

     for (i = 0; i < p_n; i++) {

         int position = (int)pow(2, i);

         int value = ham_calc(position, c_l);

         code[position - 1] = value;
     }

     printf("The generated Code Word is: ");
     for (i = 0; i < c_l; i++) {
         printf("%d", code[i]);
     }
     printf("\n");

     //creating error at position 6 (index 5)
     code[5]=1-code[5];

     printf("\nx-----Sending------x\n");

     reciever2(p_n,c_l);
 }

 void reciever2(int r,int c_l){

     printf("\nThe recieved Code Word is: ");
     for (int i = 0; i < c_l; i++) {
         printf("%d", code[i]);
     }
     printf("\n");

     int parity[r];
     for(int i=0;i<r;i++) parity[i]=1;

     for(int i=0;i<r;i++){
         for(int j=1;j<=c_l;j++){
             if(j & (1<<i)){
                 parity[i]=parity[i]^code[j-1];
             }
         }
     }
     printf("Syndrome bits: ");
     for(int i=0;i<r;i++) printf("%d",parity[i]);

     int ac=0;
     for(int i=0;i<r;i++){
         ac+=parity[i]*pow(2,i);
     }
     printf("\nError at position: %d\n",ac);

     code[ac-1]=1-code[ac-1];

     printf("The corrected Code Word is: ");
     for (int i = 0; i < c_l; i++) {
         printf("%d", code[i]);
     }
     printf("\n");

 }



void reciever1(int n,int inputs[n]){
        printf("\nx-----Reciever-----x\n");
       int input[n];

        //reversing
        for(int i=0;i<n;i++){
            input[n-i-1]=inputs[i];
        }
        //initialising
        int k=n/5;
        int check[k];
        memset( check, 0, k*sizeof(int) );

        for(int i=0;i<n;i+=k){
            int s=0,r=0;

            for(int j=i;j<i+k;j++){
                s=input[j]+check[j%k]+r;
                check[j%k]=s%2;
                r=s/2;
            }

            int j=i;
            while(r!=0){
                s=check[j%k]+r;
                check[j%k]=s%2;
                r=s/2;
                j++;
            }
         }

        //reversing checksum and taking 1's complement
        int checkSum[k];
        int flag=1;
        printf("\nCheckSum: ");

        for(int i=0;i<k;i++){
            checkSum[i]=1- check[k-i-1];
            printf("%d",checkSum[i]);
        }
        printf("\n");
        for(int i=0;i<k;i++){
            if(checkSum[i]==1){
                flag=0;
                break;
            }
        }
        if(flag){
            printf("Data word: ");
            for(int i=0;i<4*k;i++) printf("%d",inputs[i]);
            printf("\n");
        }else printf("Error detected\n");
    }



void sender1(int n,int inputs[n]){
        printf("\nx-----Sender-----x\n");

        int input[n];

        //reversing
        for(int i=0;i<n;i++){
            input[n-i-1]=inputs[i];
        }
        //initialising
        int k=n/4;
        int check[k];
        memset( check, 0, k*sizeof(int) );

        for(int i=0;i<n;i+=k){
            int s=0,r=0;

            for(int j=i;j<i+k;j++){
                s=input[j]+check[j%k]+r;
                check[j%k]=s%2;
                r=s/2;
            }

            int j=i;
            while(r!=0){
                s=check[j%k]+r;
                check[j%k]=s%2;
                r=s/2;
                j++;
            }
         }

        //reversing checksum and taking 1's complement
        int checkSum[k];
        printf("\nCheckSum: ");

        for(int i=0;i<k;i++){
            checkSum[i]=1- check[k-i-1];
            printf("%d",checkSum[i]);
        }
        printf("\n");

        //forming the code word
        int code[(int)1.25*n];
        int l=0;
        for(int i=0;i<n;i++){
            code[l++]=inputs[i];
        }
        for(int i=0;i<k;i++){
            code[l++]=checkSum[i];
        }

        reciever1(l,code);
        //changing 6th bit (index 5) and sending to reciever
        code[5]=1-code[5];
        reciever1(l,code);
    }





void menu()
{
    printf("\nPress 1 for VRC\n");
    printf("\nPress 2 for LRC\n");
    printf("\nPress 3 checksum\n");
    printf("\nPress 4 crc\n");
    printf("\nPress 5 hamming\n");
}
int main(){
    int choice;
    menu();
    printf("\nEnter your choice: ");
    scanf("%d",&choice);
    switch(choice){
        case 1:{
            int N;
            int c=0;
            int input[N+1];
            printf("\nEnter the no. of bits");
            scanf("%d",&N);
            printf("\nEnter the dataword: ");
            for (int i = 0; i < N; i++)
            {
                scanf("%d",&input[i]);
                if (input[i]==1){
                    c=c+1;
                }
            }
            if(c%2!=0){
                input[N]=1;
            }
            else{
                input[N]=0;
            }
            for (int i = 0; i <= N; i++)
            {
                printf("%d",input[i]);
        }
        case 2:{
            lrc();
        }
        case 3:{
            int n=32;
            int input[n];
            printf("\nEnter the dataword: ");
            for(int i=0;i<n;i++){
                scanf("%d",&input[i]);
            }
            printf("\nDataword: ");
            for(int i=0;i<n;i++){
                printf("%d",input[i]);
            }
            sender1(n,input);
        }
        case 4:{
            sender();
        }
        case 5:{
            int N;
            printf("\nenter the no. of bits");
            scanf("%d",&N);

            printf("\nEnter the dataword: ");
            for (int i = 0; i < N; i++)
            {
                scanf("%d",&input[i]);
            }
            solve(input, N);
            }
    }
    return 0;
}
