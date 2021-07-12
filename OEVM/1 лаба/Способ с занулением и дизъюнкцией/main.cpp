#include <iostream>
using namespace std;

/*
В зависимости от номера варианта задания
разработать алгоритм ввода с клавиатуры
требуемых типов данных и показать на
экране их внутреннее представление в
двоичной системе счисления.

8 вариант - long ( =signed long int ) и double

Выполнить циклический сдвиг в заданную
пользователем сторону на заданное
количество разрядов в пределах
определённой группы разрядов,
количество которых и номер старшего
разряда в группе задаются с клавиатуры.
1 бит на знак, 11 бит на степень, 52 на мантиссу - double
*/

union doubleUn //8 байтов
{
   double number;
   char arr[sizeof(number)];//осущ.доступ к !!!байтам!!!
};

union longUn // 4 байта
{
   long number;
   char arr[sizeof(number)];
};

void print_double( doubleUn ldc )
{
   unsigned char c;
   int i, j;

   for ( i = sizeof( ldc ) - 1; i >= 0; --i )
   {
      c = ldc.arr[i]; //8 битное знаковое число
      //здесь с просто переводится в 2 сс
      for ( j = 0; j < 8; ++j )
         if (c & (128>>j)) cout<<"1";
         else cout<<"0";
      cout<<" ";
   }
   cout << "= " << ldc.number << endl;
}

void print_long( longUn ldc )
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

int main()
{
   doubleUn a1; longUn a2;
   a1.number = 15.37;
   a2.number = 7098;
   print_double(a1);
   print_long(a2);

   int right;
   int index, length, count, i, j=0;
   long result = 0;

   do
   {cout << "What direction do you want to move?\n[0] left\n[1] right\nEnter: ";
   cin >> right;} while (right!=0 && right!=1);
   do
   {cout << "Enter the index of high digit[0..31]: ";
   cin >> index;} while (index<0 && index>sizeof(a2)*4-1);
   do
   {cout << "Enter number of required bits: ";
   cin >> length;}while (length<0 && length>sizeof(a2)*4-index);
   do
   {cout << "Enter number of shifting: "; //внутри среза
   cin >> count;} while(count<0);
   //right = 0; index = 22; length=8; count=3;

   int size = sizeof(a2)*8; //кол-во битов в числе
   result = a2.number;
   result >>= size-(index+length);//сдвигаю для удаления битов справа
   result %= 1<<length;//удаляю биты слева, получая срез
   cout << "This is srez: "<<result<<endl;
   if (right) result >>=count;
   else result <<=count; //сдвигается в нужную сторону
   cout << "This is sdvinutyy srez: "<<result<<"  11101110000"<<endl;
   result %= (1<<length);//еще раз удаляю биты слева
   cout <<"This is itogovyy srez: "<< result<<"  01110000"<<endl;
   for (i=size-(index+length); i<size-index; i++) a2.number &= ~(1<<i);
   result <<= (size -(index+length));
   length = size-index;
   cout <<"This is vstavlyaemyy srez: "<<result<<"  0111000000"<<endl;
   a2.number |= result;
   print_long(a2);
   return 0;
}
