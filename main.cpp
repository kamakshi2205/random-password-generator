#include <conio.h>
#include <stdio.h>
#include <cstdlib>
#include <Windows.h> 
#include <winuser.h>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <complex>
#include <string.h>
  using namespace std;

  void toClipboard(HWND hwnd, const std::string &s){
  	OpenClipboard(hwnd);
  	EmptyClipboard();
  	HGLOBAL hg=GlobalAlloc(GMEM_MOVEABLE,s.size()+1);
  	if (!hg){
  		CloseClipboard();
  		return;
  	}
  	memcpy(GlobalLock(hg),s.c_str(),s.size()+1);
  	GlobalUnlock(hg);
  	SetClipboardData(CF_TEXT,hg);
  	CloseClipboard();
  	GlobalFree(hg);
  }

  unsigned int MyRand(unsigned int start_range,unsigned int end_range)
    {
      static unsigned int rand = 0xACE1U; /* Any nonzero start state will work. */

      /*check for valid range.*/
      if(start_range == end_range) {
          return start_range;
      }

      /*get the random in end-range.*/
      rand += 0x3AD;
      rand %= end_range;

      /*get the random in start-range.*/
      while(rand < start_range){
          rand = rand + end_range - start_range;
      }

      return rand;
    }

  //selectArray is  a utility function that is used to
  //randomly generate a integer in the range 1 to 4 (both inclusive)
  int selectArray()
  {

      int i = MyRand(0,5);
      if (i == 0)
          i++;
      return i;
  }

  //getKey() is another utility function that is used to randomly generate
  //an integer in the range 0 to 25 (both inclusive)
  int getKey()
  {


      int key = MyRand(0,25);
      return key;
  }
  void generate_password(int length)
  {
      //Intializing result string password as NULL.
      string password = "";

      //Strings whose characters will be used to build password
      string alphabet = "abcdefghijklmnopqrstuvwxyz";
      string ALPHABET = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
      string s_symbol = "!@#$%&";
      string number = "0123456789";

      //initializing local variables
      int key, count_alphabet = 0, count_ALPHABET = 0, count_number = 0, count_s_symbol = 0;

      //Count will store the length of the password being created,
      //initially this will be zero(0)
      int count = 0;
      while (count < length) {
          // selectArray() function will return a number 1 to 4
          // and will use to select one of the above defined string
          //(i.e alphabet or ALPHABET or s_symbol or number )
          // 1 is for string alphabet
          // 2 is for string ALPHABET
          // 3 is for string number
          // and 4 is for string s_symbol

          int k = selectArray();

          //for the first character of password it is mentioned that,
          //it should be a letter
          //so the string that should be selected is either alphabet or
          //ALPHABET (i.e 1 or 2)
          //following if condition will take care of it.
          if (count == 0) {
              k = k % 3;
              if (k == 0)
                  k++;
          }
          switch (k) {
          case 1:
              // following if condition will check if minimum requirement of alphabet
              // character has been fulfilled or not
              // in case it has been fulfilled and minimum requirements of other
              // characters is still left then it will break ;
              if ((count_alphabet == 2) && (count_number == 0 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_s_symbol == 0))
                  break;

              key = getKey();
              password = password + alphabet[key];
              count_alphabet++;
              count++;
              break;

          case 2:
              // following if condition will check if minimum requirement of
              // ALPHABET character has been fulfilled or not
              // in case it has been fulfilled and minimum requirements of
              // other characters is still left then it will break ;
              if ((count_ALPHABET == 2) && (count_number == 0 || count_alphabet == 0 || count_alphabet == 1 || count_s_symbol == 0))
                  break;
              key = getKey();
              password = password + ALPHABET[key];
              count_ALPHABET++;
              count++;
              break;

          case 3:
              // following if condition will check if minimum requirement
              // of Numbers  has been fulfilled or not
              // in case it has been fulfilled and minimum requirements of
              // other characters is still left then it will break ;
              if ((count_number == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 1 || count_ALPHABET == 0 || count_s_symbol == 0))
                  break;

              key = getKey();
              key = key % 10;
              password = password + number[key];
              count_number++;
              count++;
              break;

          case 4:
              // following if condition will check if minimum requirement of
              // Special symbol character has been fulfilled or not
              // in case it has been fulfilled and minimum requirements of
              // other characters is still left then it will break ;
              if ((count_s_symbol == 1) && (count_alphabet == 0 || count_alphabet == 1 || count_ALPHABET == 0 || count_ALPHABET == 1 || count_number == 0))
                  break;

              key = getKey();
              key = key % 6;
              password = password + s_symbol[key];
              count_s_symbol++;
              count++;
              break;
          }
      }

      cout << "\n-----------------------------\n";
      cout << "         Password             \n";
      cout << "------------------------------\n\n";

       int len =0;
       len= password.size();

  for(int i=0;i<len;i++)
  {
      if(i==0||i==(len-1))
      {
        if(!((password[i]>='a' && password[i]<='z') || (password[i]>='A' && password[i]<='Z')))
        {
          key = getKey();
          password[i] = alphabet[key];
        }
      }

  }

  for(int i=0;i<len;i++)
  {
      if(i==0)
      password[i]=tolower(password[i]);
      else if(i==(len-1))
      password[i]=toupper(password[i]);

  }

      cout << " " << password<<endl <<endl;
      char ch;

      cout<<"Do you want to copy the password to clipboard?";
      cout<<endl<<"Choose y or n \n";
      cin>>ch;
      if(ch=='y'||ch=='n')
        {if (ch=='y'){
          // get desktop windows and the call toClipboard
           HWND hwnd = GetDesktopWindow();
           toClipboard(hwnd, password);
           cout<<endl<<"Password copied to clipboard.";
        }
       }
       else
       cout<<endl<<"Invalid choice\n";

      size_t leng = strlen(password.c_str());
      cout << leng << " char(s)" << endl;

      cout << "\n\nPress any key continue \n";
      getchar();


  }
  int main()
  {
      int opt, length;

      //Menu
      do {
          cout << "\n-----------------------------\n";
          cout << "  Random Password Generator\n";
          cout << "------------------------------\n\n";
          cout << "    1. Generate Password"
               << "\n";
          cout << "    2. Exit"
               << "\n\n";
          cout << "Press key 1 to Generate Password and key 2 to exit  : ";
          cin >> opt;

          switch (opt) {
          case 1:
              cout << "Enter Length :  ";
              cin >> length;
              //if length is less than 12 , program  will show error
              if (length < 12) {
                  cout << "\nError : Password Length Should be atleast 7\n";
                  cout << "Press any key to try again \n";
                  getchar();
              }
              // Length should not exceed 32 , program should show error if it exceeds
              else if (length > 32) {
                  cout << "\nError : Maximum length of password should be 100\n";
                  cout << "Press any key to try again \n";
                  getchar();
              }
              //Otherwise call generate_password() function to generate password
              else
                 generate_password(length);

              break;



          default:
              // If invalid option is chosen by user it will also show error
              if (opt != 2) {
                  printf("\nInvalid choice\n");
                  printf("Please Press ( 1 ) to generate password and ( 2 ) to exit.\n");
                  cout << "Press any key to try again \n";
                  getchar();
              }
              break;
          }
      } while (opt != 2);

      return 0;
  }
