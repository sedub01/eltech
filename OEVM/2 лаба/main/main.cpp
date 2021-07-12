#include <iostream>
#include <conio.h>
#include<windows.h>
#include<dos.h>
using namespace std;

union doubleUn
{//8 байтов
   double number;
   long long inum;
};

void printBin(doubleUn ldc)
{
   int i;
   for (i=sizeof(ldc)*8-1; i>=0; i--)
   {
      cout << ((ldc.inum & ((unsigned long long)1 << i))?1:0);
      if (i%8==0) cout << " ";
   }
   cout << "= " << ldc.number << endl;
}

void printBin(long ldc)
{
   int i;
   for (i=sizeof(ldc)*8-1; i>=0; i--)
   {
      cout << ((ldc & ((unsigned long long)1 << i))?1:0);
      if (i%8==0) cout << " ";
   }
   cout << "= " << ldc << endl;
}
template <typename T>
void menu(int &right, int &index, int &length, int &count, T number)
{
   do
   {cout << "What direction do you want to move?\n[0] left\n[1] right\nEnter: ";
   cin >> right;} while (right!=0 && right!=1);
   do
   {cout << "Enter the index of high digit[0.." << sizeof(number)*8-1<<"]: ";
   cin >> index;} while (index<0 || index>sizeof(number)*8-1);
   index = sizeof(number)*8-1-index;
   do
   {cout << "Enter number of required bits: ";
   cin >> length;}while (length<0 || length>sizeof(number)*8-index);
   do
   {cout << "Enter number of shifting: "; //внутри среза
   cin >> count;} while(count<0);
   if (count > length) count %= length;
   system("cls");
   cout << "You've chosen "<<(right? "right ":"left ")<< "direction with high bit "<<sizeof(number)*8-1-index<<", length "<<length<< " and move on "<<count<<" position(s)\n";
}
template <typename T>
void calculating(T &a2, int right, int index, int length, int count)
{
   int size = sizeof(a2)*8; //кол-во битов в числе
   T result = a2, tmp, tmp2=0;
   result >>= size-(index+length);//сдвигаю для удаления битов справа
   result %= (unsigned long long)1<<length;//удаляю биты слева, получая срез
   if (right)
   {
      tmp= result%((unsigned long long)1<<count);//длина среза = count
      result >>=count;
      for (int i=0; i<count; i++)
         tmp2 |= tmp&(unsigned long long)1<<(count -1 -i);
      tmp <<=(length-count);
      result |=tmp;
   }
   else
   {
      tmp=result>>(length - count);
      result <<=count;
      result |=tmp;
   }
   result %= ((unsigned long long)1<<length);//еще раз удаляю биты слева
   for (int i=size-(index+length); i<size-index; i++) a2 &= ~((unsigned long long)1<<i);//зануляю нужные биты
   result <<= (size -(index+length));//добавляю последними нули
   a2 |= result;
}
/*void window(int dummy, int dummy2, int columns, int lines)
  {
  CONSOLE_SCREEN_BUFFER_INFO csbi;
  if (GetConsoleScreenBufferInfo(
        GetStdHandle( STD_OUTPUT_HANDLE ),
        &csbi
        ))
    {
    csbi.srWindow.Top = 0;
    csbi.srWindow.Left = 0;
    csbi.srWindow.Bottom = lines - 1;
    csbi.srWindow.Right = columns - 1;
    COORD tmp;
    tmp.X = csbi.srWindow.Right + 1;
    tmp.Y = csbi.srWindow.Bottom + 1;
    if( lines > csbi.dwSize.Y || columns > csbi.dwSize.X)
    {
        if(!SetConsoleScreenBufferSize(GetStdHandle( STD_OUTPUT_HANDLE ), tmp))
        {
            std::cout << tmp.X  << " " << csbi.srWindow.Right << std::endl;
            std::cout << tmp.Y  << " " << csbi.srWindow.Bottom << std::endl;
        }
        if(!SetConsoleWindowInfo(GetStdHandle( STD_OUTPUT_HANDLE ), true, &csbi.srWindow))
        {
            std::cout << "Test" << std::endl;
        }
    }
    else
    {
        if(!SetConsoleWindowInfo(GetStdHandle( STD_OUTPUT_HANDLE ), true, &csbi.srWindow))
        {
            std::cout << "Test" << std::endl;
        }
        if(!SetConsoleScreenBufferSize(GetStdHandle( STD_OUTPUT_HANDLE ), tmp))
        {
            std::cout << tmp.X  << " " << csbi.srWindow.Right << std::endl;
            std::cout << tmp.Y  << " " << csbi.srWindow.Bottom << std::endl;
        }

    }

  }
}*/

int main()
{
   //MessageBox(0,"Wake uo, Neo\nTy obosralsya","WinAPI is simple",MB_OK);
   doubleUn a1; long a2;
   int right, choice;
   int index, length, count;
//   window(0, 0, 80, 80);
   cout << "Enter double number: ";
   cin >> a1.number;
   cout << "Enter long number: ";
   cin >> a2;
   system("cls");
   cout << "There are two numbers:\n";
   printBin(a1);
   printBin(a2);

   do
   {cout << "What number do you want to change?\n[0] double\n[1] long\nEnter: ";
   cin >> choice;} while (choice!=0 && choice!=1);

   if (choice)
   {
      menu(right, index, length, count, a2);
      printBin(a2); cout << "\t\t ||\n";
      calculating(a2, right, index, length, count);
      printBin(a2);
   }
   else
   {
      menu(right, index, length, count, a1.inum);
      printBin(a1); cout << "\t\t |\n";
      calculating(a1.inum, right, index, length, count);
      printBin(a1);
   }
   return 0;
}
