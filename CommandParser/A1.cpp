#include<iostream>
#include<algorithm>
#include<cstring>
#include<string>
#include<vector>
#include<stack>
#include<sstream>
#include<exception>
#include<set>
using namespace std;


struct MyException : public exception{
    const char* IncorrectArguments() const throw(){
        return "Incorrect Number of Arguments\n";
    }
    
    const char* IncorrectType() const throw(){
        return "Incorrect Data Type\n";
    }



};

//make a vector of words where each index contains a single word with no white spaces
//understand more returning of vector
vector<string> words_vector;
vector<string> vectorOfWords(string line){
    string word="";
    for(int i=0 ; i < line.size(); i++){
        if(line[i] != ' ' && line[i] != '\t'){
            word += line[i];
        }

        else if(!word.empty()){
            words_vector.push_back(word);
            word="";
        }
        
    }

    if(!word.empty())
        words_vector.push_back(word);


    return words_vector;

}

string printCommand(){
    int counter=0;
    string word="";

    string result="";
    int i;
    for (i = 0; i < words_vector.size() - 1; i++)
        result += words_vector[i] + " ";

    result += words_vector[i]; // to avoid white space
    
    return result;

}

// function that returns a vector that contains words
string reverseCommand(){
    stack<string> reverse_words;
    string result="";
    for (int i = 0; i < words_vector.size(); i++){
        reverse_words.push(words_vector[i]);
    }
    
    while(!reverse_words.empty()){
        result += reverse_words.top() + " ";
        reverse_words.pop();
    }

    return result;
    
}

string upperCommand(string line){
    string upperString = "";
    string result="";
    short num;
    int counter=0;
    while(line[counter] != '\0'){
        char currentCharachter = line[counter];
        num = currentCharachter;
        if(num >= 97 && num <= 123)
            result += currentCharachter - 32; 
        else
            result += currentCharachter;
                
        counter++;
    
    }


    return result;
    
}

string shuffleWord(string line){
    string result="";
    short counter = 0;
    //(line.size()%2*2) if the word's count is odd it will give us -2 which will be useful to avoid swapping last char
    // if its even it will give us zero and we will shuffle all chars
    // equal in case of string.size()==2
    while(counter <= line.size() - 1 - (line.size()%2)  ){
        if(counter + 1 <= line.size())
            result += line[counter+1];
        result += line[counter];
        counter += 2;
    }
    if(counter < line.size()){ 
        result += line[counter];
    }

    return result;
}

string shuffleStatement(){
    string result="";
    int i = 0;
    for ( ; i < words_vector.size() - (words_vector.size()%2); i += 2){
        result += words_vector[i+1] + " ";
        result += words_vector[i] + " ";
    }
    for(; i < words_vector.size() && (words_vector.size() %2) ; i++)
        result += words_vector[i] + " ";
    

    return result;

}

string deleteStatement(int position){
    string result="";
    
    for (int i = 1; i < words_vector.size(); i++){
        //raise out of range error
        if(i == position && position < words_vector.size()){
            //cout<<i<<":"<<words_vector[i]<<endl;
            continue;
        }
        result += words_vector[i] + " ";
    }

    return result;

}

void middleStatement(){
    string result="";
    int numberOfMiddles = 1;
    int size = words_vector.size();
    if(size % 2)
         numberOfMiddles = 0;
    
    int middle = size / 2;
    if(numberOfMiddles){
        cout<<words_vector[middle-1];
        cout<<" "<<words_vector[middle];
    }
    else
        cout<<words_vector[middle];

    cout<<endl;
}

bool checkIfDigits(string str)
{
    if(str[0] == '-')
        str = str.erase(0,1);
    return all_of(str.begin(),str.end(),::isdigit);
}

long long addStatement(){
    long long result = 0;
    
    for (int i = 0; i < words_vector.size(); i++){
        //raise error  if number isn't integer
        string current = words_vector[i];
        if(!checkIfDigits(current)){
            return -1;
            break;
        }
        stringstream ss;
        ss<<current;
        int num;
        ss>>num;
        result += num;
    }

    return result;

}


int main(int argc,char** argv){

    string command;
    string commandLine="";
    string line, result;
    if(argc>=2)
        command = argv[1];
    if(argc>2)
        line = argv[2];

    for(int i=2;i<argc && argc >= 3;i++){
        words_vector.push_back(argv[i]);
        commandLine += argv[i];
        if(argc-1 != i)     // in order to avoid adding extra ' ' single space
            commandLine += ' ';
    }

    set<string> commands_set = {"print","reverse","upper","shuffle","shuffleStatement","delete","middle","add","random"};
    auto it = commands_set.find(command);
    if(argc <= 2 && *it == command){
        cout<<"Incorrect Number of Arguments\n";
        return 0;
    }

    if(command == "print"){
        result = printCommand();
        cout<<result<<endl;
    }

    else if(command == "reverse"){
        result = reverseCommand();
        cout<<result<<endl;
    }

    else if(command == "upper"){
        result = upperCommand(commandLine);
        cout<<result<<endl;
    }

    else if(command == "shuffle"){
    
        try{
            if(words_vector.size() > 1)
                throw MyException();

            result = shuffleWord(commandLine);
            cout<<result<<endl;

        }catch(MyException &e){
            cout<<e.IncorrectArguments();
        }
    }

    else if(command == "shuffleStatement"){
        result = shuffleStatement();
        cout<<result<<endl;
    }

    else if(command == "delete"){
        int end = commandLine.find(' ');
        string num_str = commandLine.substr(0, end);
        stringstream ss;
        ss<<num_str;
        int num_int;
        ss>>num_int;

        try{
            if(num_int <= 0){
                throw "Incorrect Data Type\n";
            }
            if(num_int >= words_vector.size() || num_int < 1){
                throw MyException();
            }
            result = deleteStatement(num_int);
            cout<<result<<endl;

        }
        catch(const char* msg){
            cout<<msg;
        }
        catch(MyException &e){
            cout<<e.IncorrectArguments();
        }
    }

    else if(command == "middle"){
        middleStatement();
    }

    else if(command == "add"){
        try{
            long long res = addStatement();
            if(res == -1)
                throw MyException();
            cout<<res<<endl;

        }catch(MyException &e){
            cout<<e.IncorrectType();
        }
    }
    
    else
        cout<<"Undefined Command\n";
    


    

    return 0;
}