#include <iostream>
#include<fstream>
#include <string>
#include <sstream>
#include <bits/stdc++.h>
using namespace std;

struct Treap;
struct User;


//Randomized BST = Binary Search tree + priority
struct Treap{
    User* user;
    int priority;
    Treap *left, *right;
    //initializes User(LinkedList users) and Treap(left,right,priority)
    Treap(User* usr,int p){
        left=right= NULL;
        user = usr;
        priority = rand()%100;
        priority = p;}



    Treap *rightRotate(Treap *y)
    {

        Treap *x = y->left,  *T2 = x->right;

        // Perform rotation
        x->right = y;
        y->left = T2;

        // Return new root
        return x;
    }

    Treap *leftRotate(Treap *x)
    {
        Treap *y = x->right, *T2 = y->left;

        // Perform rotation
        y->left = x;
        x->right = T2;

        // Return new root
        return y;
    }
}
;

class User{
public:
    string username,name,email;
    User *nextUser;
    Treap *FreindBST; //every user has its randomized BST that contains his/her friends

    User(){
        nextUser = nullptr;
        FreindBST = nullptr;
    }
    /*
     overloading operators used in comparison for search on certain username or insertion of new user
     */
    bool operator<(User *user){
        return this->username<user->username;
    }
    bool operator<=(User *user){
        return this->username<=user->username;
    }
    bool operator>(User *user){
        return this->username>user->username;
    }
    bool operator>=(User *user){
        return this->username>=user->username;
    }
    bool operator==(User *user){
        return this->username==user->username;
    }
    bool operator<(string un){
        return this->username<un;
    }
    bool operator<=(string un){
        return this->username<=un;
    }
    bool operator>(string un){
        return this->username>un;
    }
    bool operator>=(string un){
        return this->username>=un;
    }
    bool operator==(string un){
        return this->username==un;
    }








    //Search on friends of a certain user if exists or return nullptr in readFileFriends
    Treap* BSTsearch(Treap* friends,string un){
        if(!friends){
            return NULL;
        }
        if(friends->user ->operator<(un)  )
            friends->right = BSTsearch(friends->right,un);
        else if(friends->user->operator>(un) )
            friends->left = BSTsearch(friends->left,un);
        else
            return friends;

    }
    //Insert new friend of a certain user in the treap in readFileFriends
    /*here compare priorities with each other make
         * left right rotations to the bst tree
         */
    Treap* BSTinsert(Treap* friends, User* user){
        if(!friends){
            return new Treap(user,int(rand())%100);
        }
        if(user > friends->user){
            friends->right = BSTinsert(friends->right,user);
            if (friends->right->priority > friends->priority)

                friends = user->FreindBST->leftRotate(friends);
        }



        else if(user < friends->user){
            friends->left = BSTinsert(friends->left,user);
            if (friends->left->priority > friends->priority)
                friends = user->FreindBST->rightRotate(friends);

        }
        else{
            cout<<"value already exists\n";


        }

        return friends;
    }

};


class SocialNetwork{
private:
    User *users,*tail;

public:
    SocialNetwork(){
        users = tail = nullptr;
    }

    void readFileRelationsIn() {
        ifstream relationsIn("all-users.in");
        string line;
        string arr[3];
        int j;
        //read from file all-users.in(username,name,email) and make all users in a linked list called users
        while (getline(relationsIn, line))
        {
            j = 0;
            string word = "";
            for (int i = 0; i <= line.size(); i++) {
                if (line[i] == ','|| line[i]=='\0') {
                    arr[j] = word;
                    j++;
                    word = "";
                } else {
                    if (!(word == "" && line[i] == ' '))
                        word += line[i];
                }
            }
            User *user = new User;
            user->username = arr[0];
            user->name = arr[1];
            user->email = arr[2];
            insert(user);
        }

        relationsIn.close();
    }
    //read from file all-users-relations.in(username,friend) and insert friends of the user into the treap

    void readFileFriends(){
        ifstream friendsIn("all-users-relations.in");
        string line;
        string arr[2];
        int j;
        while (getline(friendsIn, line))
        {
            j = 0;
            string word = "";
            for (int i = 0; i <= line.size(); i++) {
                if (line[i] == ','|| line[i]=='\0') {
                    arr[j] = word;
                    j++;
                    word = "";
                } else {
                    if (!(word == "" && line[i] == ' '))
                        word += line[i];
                }
            }
            User* user1,*user2;
            //takes the first username and his/her friend from file & searchs on them
            user1 = LLSearch(users,arr[0]);
            user2 = LLSearch(users,arr[1]);
            //firstly,they must exist in the social network not made-up names
            if(user1!= nullptr && user2!= nullptr ) {
                //insert both friends on both users
                user1->FreindBST = user1->BSTinsert(user1->FreindBST, user2);
                user2->FreindBST = user2->BSTinsert(user2->FreindBST, user1);
            }
        }

    }
    User* getUserHead(){
        return users;
    }
    User* getUserTail(){
        return users;
    }

    void insert(User* user){

        if(users== nullptr) {
            users = user;
            tail = user;
            return;

        }
        tail->nextUser = user;
        tail = tail->nextUser;

    }
    User* LLSearch(User* friends,string un){
        User* p = users;
        while(p != nullptr){
            if(p->username == un)
                return p;
            p = p->nextUser;
        }


    }
    void printUsers(){
        User* p = users;
        while(p != nullptr){
            cout<<p->username<<"  "<<p->name<<"  "<<p->email<<endl;
            p = p->nextUser;
        }
    }
    void listAllFriends(){
        User* p = users;
        //printPriority(p->FreindBST);
        while(p!= nullptr){
            cout<<p->username<<"'s friends are :- \n";
            inordprint(p->FreindBST);
            cout<<endl;
            p=p->nextUser;
        }
    }
    //print the friends of the user inorder that i'm currently on
    void inordprint(Treap* treap){
        if(treap== nullptr){
            return;
        }
        inordprint(treap->left);
        cout<<treap->user->username<<" & priority = "<<treap->priority<<endl;
        inordprint(treap->right);
    }
    void printPriority(Treap* treap){
        if(treap== nullptr){
            return;
        }
        inordprint(treap->left);
        cout<<"priority = "<<treap->priority<<endl;
        inordprint(treap->right);

    }



};


int main(){
    SocialNetwork project;
    project.readFileRelationsIn();
    project.printUsers();
    project.readFileFriends();
    project.listAllFriends();
    User* u_test = project.getUserHead();
    cout<<"new test user\n";
    cout<<u_test->nextUser->username<<endl;
    project.printPriority(u_test->nextUser->FreindBST);
    return 0;
}


