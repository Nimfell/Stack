//---------------------------------------------------------------------------
#include <vcl.h>
#include <typeinfo.h>
#include <excpt.h>
#include <vector.h>
#pragma hdrstop
#include "Stack.h"

//---------------------------------------------------------------------------
#pragma package(smart_init)
#pragma resource "*.dfm"
TForm1 *Form1;
//---------------------------------------------------------------------------
__fastcall TForm1::TForm1(TComponent* Owner)
     : TForm(Owner) {}
//---------------------------------------------------------------------------

template <class T>
class Stack
{
     class Node
     {
          public:
          T value;
          Node* prev;

          Node(T val=0)
          {
              value = val;
              prev = NULL;
          }
     };
     int stackSize;
     Node* head;
     
     public:
     Stack()
     {
          head = NULL;
          stackSize = 0;
     }

     int size();             //-- получить размер стека
     void push(T val);       //-- поместить элемент на верх стека.
     T pop();                //-- извлечь последний установленный в стек элемент.
     T peek();               //-- получить верхний элемент стека, не удаляя его.
     AnsiString print();     //-- получить содержимое стека в формате AnsiString 
};
//стеки в которые ведется запись из формы
Stack<char> *stackCHAR = new Stack<char>;
Stack<int> *stackINT = new Stack<int>;

//дополнительные стеки для решения задачи
Stack<int> *stackINT_temp = new Stack<int>;
Stack<int> *stackBOOL = new Stack<int>;

//---------------------------- поместить ---------------------------------------
template <class T>
      void Stack<T> :: push(T val)
      {
          Node *node = new Node(val);
          if (head == NULL)             //если это первый элемент
               node -> prev = NULL;
          else
               node -> prev = head;

          head = node;
          stackSize += 1;
      }

//-----------------------------получить размер стека----------------------------
template <class T>
     int Stack<T>:: size()
     {
       return stackSize;
     }

//---------------------------- извлечь -----------------------------------------
template <class T>
      T Stack<T>:: pop()

      {   if(head != NULL)
          {
               T val = head->value;
               head = head->prev;
          stackSize -= 1;
          return (val);
          }
          return NULL;
      }

//---------------------------- получить ----------------------------------------
template <class T>
     T Stack<T> :: peek()
     {
          if(head !=NULL)
          {
               int val = head->value;
               return (val);
          }
          return NULL;
     }

//---------------------------- печать -----------------------------------------
template <class T>
      AnsiString Stack<T> :: print()
      {
          AnsiString string = "";
          Node* tempHead = head;
          while(head != NULL)
          {
               string = string + " " + head->value + " ";
               head = head->prev;
          }
          head = tempHead;
          return string;
      }

//---------------------------- обработка вводимых данных ----------------------

  int r_Int;
  char r_Char;
  int* const resultInt = &r_Int;
  char* const resultChar = &r_Char;

  void convert(AnsiString String_a)
      {
          int key = 0;
          int len = String_a.Length();

          if (len>=1)
          {
               for (int i=len-1; i>=0; i--)
               {
                    try
                    {
                         int Int;
                         AnsiString String_b = String_a.SubString(i+1,1).c_str();
                         Int = String_b.ToInt();

                         if (key == 1) //если в AnsiString две цифры идут подряд
                         {
                              stackBOOL-> pop();                //сбрасываем логический стек
                              AnsiString String_c;
                              String_c = stackINT->pop();       //забираем из стека цифру в строку
                              String_c = String_b + String_c;   //соединяем в строке цифры
                              Int = String_c.ToInt();           //конвертируем в int
                         }
                         stackINT->push( Int );
                         key = 1;
                         stackBOOL-> push(0);
                    }
                    catch (...)
                    {
                              stackCHAR->push( *String_a.SubString(i+1,1).c_str() ); //кидаем в стек символ из AnsiString
                              stackBOOL-> push(1);
                              key = 0;
                    }
               }
          }
          else Form1->MemoSIS->Text = "Заполните поле <Ввод>";
      }
void printAllStacks()
{
     Form1->MemoINT->Text = stackINT -> print();
     Form1->MemoCHAR->Text = stackCHAR->print();
     Form1->MemoBOOL->Text = stackBOOL->print();
}
                   /*/==   КНОПКИ   ==/*/
//------------------------добавить-------------------------------------------
void __fastcall TForm1::BtnPushClick(TObject *Sender)
{
     Form1->MemoSIS->Text = "";
     AnsiString a = Form1->Edit->Text; 

     convert(a);   //обрабатываем введенные данные
     printAllStacks();
     Form1->Edit->Text = "";

}
//------------------------извлечь--------------------------------------------

void __fastcall TForm1::BtnPopClick(TObject *Sender)
{
     Form1->MemoSIS->Text = "";
     if (stackBOOL->pop() == 1)
     {
          Form1->Edit1->Text = (AnsiString)(stackCHAR->pop()); //запись в окно "Вывод"
     }
     else
     {
          Form1->Edit1->Text = (AnsiString)(stackINT->pop()); //запись в окно "Вывод"
     }
     printAllStacks();
}
//----------------------- Взять ---------------------------------------------

void __fastcall TForm1::BtnPeekClick(TObject *Sender)
{
     Form1->MemoSIS->Text = "";
     Form1->Edit1->Text = (AnsiString)(stackCHAR->peek());
     printAllStacks();
}

//---------------------------------------------------------------------------
void __fastcall TForm1::BtnSizeClick(TObject *Sender)
{
     Form1->MemoSIS->Text = "";
     Form1->MemoSIS->Text = "Размер стека BOOL: " + (AnsiString)stackBOOL->size();
     printAllStacks();
}

//---------------- ЗАДАЧА СО СКОБКАМИ ---------------------------------------

void __fastcall TForm1::Button1Click(TObject *Sender)
{
     int count = 0;
     char val = stackCHAR->pop();
     stackBOOL->pop();  //сброс логического стеке

     if (stackCHAR->size() == 0)     //прове
     {    Form1->MemoSIS->Text = "Заполните стек";
          return;
     }

     if (val == '(' )    //проверяем первый элемент
          count++;
     else
          Form1->MemoSIS->Text = "Несбалансировано";

     while (stackCHAR->size() != NULL)    //проверяем середину
     {
          val = stackCHAR->pop();
          if (val == '(') count++;
          if (val == ')') count--;
          stackBOOL->pop();  //сброс логического стеке
     }

     if (val == ')' && count == 0)   //проверяем последний элемент и четность
          Form1->MemoSIS->Text = "Сбалансировано";
     else
          Form1->MemoSIS->Text = "Несбалансировано";
     printAllStacks();
}
//----------------- ЗАДАЧА С ПРИМЕРАМИ --------------------------------------

//пример для решения забивается в форму и сортируется между 2мя стеками записи
//данные сортировки отмечаются в стеке BOOL
//далее в соответствии с содержимым BOOL в определенной последовательности
//забираются данные из 2х стеков записи и обрабатываются по алгоритму
// P.S. Осторожно решение сделано через ... - вырвите руки афтору!

void __fastcall TForm1::Button2Click(TObject *Sender)
{
     Form1->MemoSIS->Text = "";
     char sign;
     int result;
     AnsiString stringWithResult = stackINT->peek();  //первый символ должен быть цифрой

     while(stackBOOL->size())
     {
       int key = stackBOOL->pop();

       if (key == 0)
       {
          stackINT_temp->push( stackINT->pop() ); //записываем число из основного стека во временный
       }
       else
       {
          sign = stackCHAR->pop();
          if ( sign == '+' || sign == '-' || sign == '*' || sign == '/' )
          {
               int a = stackINT_temp->pop();
               int b = stackINT_temp->pop();
               if      (sign == '*') result = a * b;
               else if (sign == '/') result = a / b;
               else if (sign == '+') result = a + b;
               else if (sign == '-') result = a - b;
               stackINT_temp->push(result);
               stringWithResult = stringWithResult + sign + a;
          }
          else if (sign == '=')
          {
               AnsiString answer = stackINT_temp->pop();
               stringWithResult = stringWithResult + sign;
               Form1->MemoSIS->Text =  stringWithResult +  answer;
          }
               else  Form1->MemoSIS->Text = "Отсутствует знак равенства";

          printAllStacks();
       }
    }
}
//--------------------------------------------------------------------------- 


