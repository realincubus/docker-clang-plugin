struct A{
  int a;
};

int main(){
  int abc;

  A a;
  
  int x[1000];

  for (int i = 0; i < 1000; ++i){
    x[i] = 1;
  }


  for (int i = 1; i < 1000; ++i){
    x[i] = x[i-1];
  }

}

