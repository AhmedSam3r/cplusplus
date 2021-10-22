#include <bits/stdc++.h>
#include <fstream>
using namespace std;


bool checkIfDigits(string str)
{
    if(str[0]=='-')
        str = str.erase(0,1);
    return all_of(str.begin(),str.end(),::isdigit);


}



class BigDecimalInt{

private:
    string decStr;
    bool isNegative;
public:
    BigDecimalInt(){
        decStr="";
        isNegative=0;
    }
    BigDecimalInt(int x){
        string str = to_string(x);
        isNegative = (str[0]=='-'?1:0);
        // remove - sign but marked number as negative
        if(isNegative)
            str = str.erase(0,1);
        decStr = str;
    }


    BigDecimalInt(string str){
        isNegative = (str[0]=='-'?1:0);
        // remove - sign but marked number as negative
        if(isNegative)
            str = str.erase(0,1);
        decStr = str;
    }
    bool operator<(BigDecimalInt big_int)
    {
        string s1= this->decStr , s2=big_int.decStr;
        int len1 = s1.size(), len2= s2.size();

        if(len1<len2)
            return true;
        if(len2<len1)
            return false;

        //both strings equal
        for (int i = 0; i <len1; ++i) {
            // compare every two digit against each other to see which number is smaller

            if(s1[i]<s2[i])
                return true;
            if(s2[i]<s1[i])
                return false;

        }
        //if both strings are equal in everything
        return false;

    }
    BigDecimalInt operator=(BigDecimalInt &second_int){
        this->decStr = second_int.decStr;
        this->isNegative = second_int.isNegative;
        return *this;

    }

    int size(){
        int len ;
        //in case result equals to 0
        bool flag = 1;
        for (int i = 0; i < decStr.size(); ++i) {
            // 0 on the begining of the number is valueless
            if(decStr[i]!= '0'){
                len = decStr.size() - i;
                flag = 0;
            }
        }
        if(flag)
            return 1;

        return len;
    }

    BigDecimalInt operator+(BigDecimalInt &second_int){
        BigDecimalInt big_res;
        BigDecimalInt tmp = *this;

        string s1 = this->decStr;
        string s2 = second_int.decStr;

        // num3 = num1 + (-num2)
        if( !(tmp.isNegative) && (second_int.isNegative) ){
            second_int.isNegative= 0;
            return tmp - second_int;
        }
        // num3 =  num2+ (-num1)
        if( (tmp.isNegative) && !(second_int.isNegative) ){
            tmp.isNegative= 0;
            return second_int - tmp;
        }
        // num3 =  -num2 + (-num1)
        if( (tmp.isNegative) && (second_int.isNegative) ){
            big_res.isNegative=1;
            tmp.isNegative=0;
            second_int.isNegative=0;
        }

        reverse(s1.begin(),s1.end());
        reverse(s2.begin(),s2.end());
        int carry=0;
        int len = min(s1.size(),s2.size());
        for (int i = 0; i < len; ++i) {
            int sum = (s1[i] - '0') + (s2[i] - '0') + carry;
            int res = sum % 10;
            carry = sum > 9 ? 1 : 0;
            big_res.decStr.push_back(res + '0');
        }

        BigDecimalInt bigger = tmp < second_int ? second_int : tmp;
        reverse(bigger.decStr.begin(),bigger.decStr.end());
        for (int i = len; i < max(s1.size(),s2.size()) ; ++i) {
            int add = (bigger.decStr[i] -'0')+ carry;
            big_res.decStr.push_back(add + '0');

        }
        if(carry!=0 && s1.size()==s2.size())
            big_res.decStr.push_back(carry+'0');

        reverse(big_res.decStr.begin(),big_res.decStr.end());

        return big_res;

    }
    BigDecimalInt operator-(BigDecimalInt &second_int) {
        BigDecimalInt big_res;
        BigDecimalInt tmp = *this;

        string s1 = this->decStr, s2 = second_int.decStr;


        if (second_int.isNegative) {
            second_int.isNegative = 0;
            return tmp + second_int;
        }

        if (tmp.isNegative) {
            second_int.isNegative = 1;
            return tmp + second_int;
        }

        if (tmp < second_int) {
            big_res.isNegative = 1;
            swap(s1, s2);
        }
        reverse(s1.begin(), s1.end());
        reverse(s2.begin(), s2.end());
        int carry = 0;
        int len = min(s1.size(), s2.size());
        for (int i = 0; i < len; ++i) {
            int diff = (s1[i] - '0') - (s2[i] - '0') - carry;
            if (diff < 0) {
                diff += 10;
                carry = 1;
            } else
                carry = 0;

            big_res.decStr.push_back(diff + '0');
        }

        BigDecimalInt bigger = tmp < second_int ? second_int : tmp;
        reverse(bigger.decStr.begin(), bigger.decStr.end());
        for (int i = len; i < max(s1.size(), s2.size()); ++i) {
            int diff = (bigger.decStr[i] - '0') - carry;
            big_res.decStr.push_back(diff + '0');

        }

        reverse(big_res.decStr.begin(),big_res.decStr.end());

        return big_res;


    }


    friend ostream& operator<<(ostream& out ,const BigDecimalInt &bigInt){
        out<<"Result = ";
        if(bigInt.isNegative)
            out<<"-";
        for (int i = 0; i < bigInt.decStr.size(); ++i) {
            out << bigInt.decStr[i];
        }

        return out;
    }

    //convert string that contains numbers into character type & bool flag indicates if number is +ve or -ve



    };

void testFromFile() {
    ifstream infile("input.txt");
    ofstream outfile("output.txt");
    if (!infile.is_open())
        cout << "error\n";
    else {

        int test_cases = 5;
        for (int i = 0; i < test_cases; ++i) {
            int choice = 1;
            infile >> choice;
            string s1, s2;
            infile >> s1;
            infile >> s2;
            BigDecimalInt b1(s1),b2(s2);

            if(choice==1){
                BigDecimalInt b3 = b1 + b2;
                outfile<<"test case #"<<i<<endl;
                outfile<<b3<<endl;

            }
            else if(choice==2){
                BigDecimalInt b3 = b1 - b2;
                outfile<<"test case #"<<i<<endl;
                outfile<<b3<<endl;

            }
        }


    }
}

int main() {
    testFromFile();
    int choice;
    string snum1,snum2;
    bool digit1,digit2;
    while(true){
        cout<<"Welcome to FCI Calculator\n"
              "----------------------------------------\n"
              "1- Perform Addition\n"
              "2- Perform Subtraction\n"
              "3- Exit\n";
        cin>>choice;
        if(choice==3){
            break;
        }
        cout<<"Enter first number(Correct Form in digits)\n";
        cin>>snum1;
        digit1 = checkIfDigits(snum1);
        while(!digit1){
            cout<<"Re-Enter first number(Correct Form in digits)\n";
            cin>>snum1;
            digit1=checkIfDigits(snum1);

        }
        BigDecimalInt num1(snum1);
        cout << "num1 = " << snum1 << endl;

        cout<<"Enter second number(Correct Form in digits)\n";
        cin>>snum2;

        digit2 = checkIfDigits(snum2);
        while(!digit2) {
            cout << "Re-Enter Second number(Correct Form in digits)\n";
            cin >> snum2;
            digit2 = checkIfDigits(snum2);


        }

        BigDecimalInt num2(snum2);
        cout << "num2 = " <<snum2 << endl;

        switch (choice) {
            case 1: {
                BigDecimalInt num3 = num2 + num1;
                cout<<num3<<endl;
                break;
            }
            case 2: {
                BigDecimalInt num4 = num2 - num1;
                cout<<num4<<endl;
                break;
            }
            case 3: {
                return 0;
            }
            default:{
                cout<<"Wrong Number, Please Enter 1 or 2\n";
                break;
            }
        }

    }

    return 0;
}
