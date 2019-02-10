#include<iostream>
#include<vector>
#include<algorithm>
#include<random>
#include<limits>
#include<cassert>
#include<string>
#include<memory>
using std::default_random_engine;
using std::numeric_limits;
using std::random_device;
using std::uniform_int_distribution;


using namespace std;

template<typename T>
struct Node {
  T data;
  Node<T> *next;
};

template<typename T>
struct List {
  Node<T>* root;
  List(Node<T>* n):root(n){}
  Node<T>* get()const {
    return root;
  }
  ~List(){
    while(root != nullptr){
      Node<T>* nxt = root->next;
      delete root;
      root = nxt;
  }
  }
};
template< typename T>
List<T> reverse(const List<T> & lst){
  
  Node<T>* res = nullptr;
  Node<T>* cur = lst.get();
  while(cur != nullptr) {
    if(res == nullptr){
//      cout << "start" << endl;
      res = new Node<T>;
      res->data = cur->data;
      res->next == nullptr;
  //    cout << "starte" << endl;
    }else {
    //  cout << "next" << endl;
      Node<T>* temp = new Node<T>;
      temp->data = cur->data;
      temp->next = res;
      res = temp;
      //cout << "nexte" << endl;
      
    }
    //cout << "cur=" << cur->data << endl;
    cur = cur->next;

  }
  return List<T>(res);

}

List<int> sumInts(const List<int> &a, const List<int>& b){
  Node<int>* n1 = a.get();
  Node<int>* n2 = b.get();
  Node<int>* res = nullptr;
  Node<int>* prev = nullptr;
  int carry = 0;
  while(n1 != nullptr || n2 != nullptr || carry > 0) {
  //  cout << "begin" << endl;
    int sum = carry;
    if(n1 != nullptr){
      sum += n1->data;
    }
    if(n2 != nullptr) {
      sum += n2->data;
    }
    int low = sum % 10;
    if(sum >= 10) carry =1;
    else carry = 0;
    if(res == nullptr){
    //  cout << "start" << endl;
      res = new Node<int>;
      res->data = low;
      res->next = nullptr;
      prev = res;
      //cout << "starte" << endl;

    }
    else {
     // cout << "nxt" << endl;
      Node<int> *n  = new Node<int>;
      n->data = low;
      n->next = nullptr;
      prev->next = n;
      prev = n;
     // cout << "nxte" << endl;
    }

    n1 = n1 != nullptr ? n1->next : n1;
    n2 = n2 != nullptr ? n2->next : n2;
    //cout << "loop" << endl;
  }
  return List<int>(res);

}
List<int> genIntList(int length){
  Node<int> *head = nullptr;
  Node<int>* prev = nullptr;

  default_random_engine gen((random_device())());
  uniform_int_distribution<int> dis(0,9 );
  for(int i =0; i < length; i++) {
    int x = dis(gen);
    Node<int>* n = new Node<int>;
    n->data = x;
    n->next = nullptr;
    if(head == nullptr) {
      head = prev = n;
    }
    else 
    {
      prev->next = n;
      prev = n;
    }

  }
  return List<int>(head);

}
template<typename T>
void show(const List<T> &in){
  Node<T>* n =in.get(); 
  while(n != nullptr){
    cout << n->data << ",";
    n = n->next;
  }
  cout << endl;
}

int main(int arg, char* argv[])
{
  List<int> lst = genIntList(3);
  List<int> lst2 = genIntList(3);
  List<int> res = sumInts(lst,lst2);
  show(lst);
  show(lst2);
  show(res);

  List<int> rev = reverse(res);
  show(rev);



  return 0;
}

