#include <iostream>
#include <cmath>
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

   for ( i = sizeof( ldc ) - 1; i >= 0; --i )
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
   doubleUn a1;
   a1.number = 15.375;
   print_double(a1);

   longUn a2;
   a2.number = 7098;
   print_long(a2);

   bool right;
   int index, length, count, i, j=0, k;
   long result = 0;
   /*cout << "What direction do you want to move?\n[0] left\n[1] right\nEnter: ";
   cin >> right;
   cout << "Enter the index of high digit[0..31]: ";
   cin >> index;
   cout << "Enter number of required bits: ";
   cin >> length;
   cout << "Enter number of shifting: ";
   cin >> count;*/
   right = 0; index = 22; length=8; count=3;

   int size = sizeof(a2)*8;
   result = a2.number;
   result >>= size-(index+length);
   result = result%(long)pow(2, length);
   cout << "This is srez: "<<result<<endl;
   if (right) result >>=count;
   else result <<=count;
   cout << "This is sdvinutyy srez: "<<result<<"  11101110000"<<endl;
   result %= (long)pow(2, length);
   cout <<"This is itogovyy srez: "<< result<<"  1110000"<<endl;
   //с = ~(a^b); // опер. эквивалентности

   //a2.number= ~( (a2.number << (size -(index+length)) ) ^ result);
   result <<= (size -(index+length));
   cout <<"This is vstavlyaemyy srez: "<<result<<"  111000000"<<endl;
   length = size -index;
   for (i=0; i<length; i++)
   {
      if (!(result>>i)&1) a2.number &= ((result<<i)&1);
      else if (((result>>i)&1)) a2.number |= ((result<<i)&1);
   }
   print_long(a2);

   return 0;
}
