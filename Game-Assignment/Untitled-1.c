#include <stdio.h>
#include <math.h>
int main()
{
 int n, array[10000], i, j, count=0, flag=0, sum=0, a=0, b=0;
 scanf("%d",&n);
 for ( i=0 ; i<n ; i++)
 {
  for ( j=0 ; j<n ; j++ )
  {
   scanf("%d",&array[j+ (n*i)]);
  }
 }
 //flag
 flag = (n*(pow(n,2)+1))/2;
 i = 0;
 sum = 0;
 for( j = 0; j < n; j++)
 {
    sum += array[j + (n * i)]; 
 }
 flag = sum;
 sum = 0;
 //horizontal check
 for ( i=0 ; i<n ; i++)
 {
  for ( j=0 ; j<n ; j++ )
  {
   sum += array[j+ ( n*i)];
  }
  if ( sum == flag)
  {
   count+=1;
  }
  sum = 0;
 }
 //vertical check
 for ( i=0 ; i<n ; i++)
 {
  for ( j=0 ; j<n ; j++ )
  {
   sum += array[i+ (n*j)];
  }
  if ( sum == flag)
  {
   count+=1;
  }
  sum = 0;
 }
 //diagonal check line 1
 for ( i=0 ; i<n ; i++)
 {
  sum += array[a+ (n*b)];
  a+=1;
  b+=1;
 }
 if ( sum == flag)
 {
  count+=1;
 }
 sum = 0;
 //diagonal check line 2
 a=n-1;
 b=n-1;
 for ( i=n ; i>0 ; i--)
 {
  sum += array[a+ (n*b)];
  a-=1;
  b-=1;
 }
 if ( sum == flag)
 {
  count+=1;
 }
 sum = 0;
 if (count == (n * 2) + 2)
 {
  printf("Yes");
 }
 else
 {
  printf("%d\n", count);
  printf("%d", flag);
 }
 return 0;
 
}