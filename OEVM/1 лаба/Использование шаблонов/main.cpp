#include <iostream>
using namespace std;

union doubleUn //8 байтов //1098247045
{
   double number;
   char arr[sizeof(number)];//осущ.доступ к !!!байтам!!!
   unsigned long long inum;
};
union longUn // 4 байта
{
   long number;
   char arr[sizeof(number)];
};

template <typename T>
void printUn( T ldc )
{
   unsigned char c;
   int i, j;

   for (i=sizeof(ldc)-1; i>=0; --i)
   {
      c = ldc.arr[i]; //4 байтное знаковое число
      //здесь с просто переводится в 2 сс
      for ( j = 0; j < 8; ++j )
         if (c & (128>>j)) cout<<"1";
         else cout<<"0";
      cout<<" ";
   }
   cout << "= " << ldc.number << endl;
}
template <typename T>
void menu(int &right, int &index, int &length, int &count, T a2)
{
   do
   {cout << "What direction do you want to move?\n[0] left\n[1] right\nEnter: ";
   cin >> right;} while (right!=0 && right!=1);
   do
   {cout << "Enter the index of high digit[0..31]: ";
   cin >> index;} while (index<0 || index>sizeof(a2)*8-1);
   do
   {cout << "Enter number of required bits: ";
   cin >> length;}while (length<0 || length>sizeof(a2)*8-index);
   do
   {cout << "Enter number of shifting: "; //внутри среза
   cin >> count;} while(count<0);
}

void calculating(longUn &a2, int right, int index, int length, int count)
{
   int size = sizeof(a2)*8; //кол-во битов в числе
   long result = a2.number;
   result >>= size-(index+length);//сдвигаю для удаления битов справа
   result %= 1<<length;//удаляю биты слева, получая срез
   //cout << "This is srez: "<<result<<endl;
   if (right) result >>=count;
   else result <<=count; //сдвигается в нужную сторону
   //cout << "This is sdvinutyy srez: "<<result<<endl;
   result %= (1<<length);//еще раз удаляю биты слева
   //cout <<"This is itogovyy srez: "<< result<<endl;
   for (int i=size-(index+length); i<size-index; i++) a2.number &= ~(1<<i);
   result <<= (size -(index+length));
   length = size-index;
   //cout <<"This is vstavlyaemyy srez: "<<result<<endl;
   a2.number |= result;
}


int main()
{
   doubleUn a1; longUn a2;
   a1.number = 15.37;
   a2.number = 7098;
   printUn(a1);
   printUn(a2);
   //cout << a1.inum<<endl;
   for(int i = 63; i >= 0; i--)
		{
		   cout << ((a1.inum & ((unsigned long long)1 << i))?1:0);
		   if (i%8==0) cout << " ";
		}
   cout << " == "<<a1.inum<< endl;

   int right, choice;
   int index, length, count;

   do
   {cout << "What number do you want to change?\n[0] double\n[1] long\nEnter: ";
   cin >> choice;} while (choice!=0 && choice!=1);
   menu(right, index, length, count, a1);


   calculating(a2, right, index, length, count);
   printUn(a2);
   return 0;
}
