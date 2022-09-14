#include <bits/stdc++.h>
#include <unordered_map>
using namespace std;

int nl,nq,nd=0;

void printArray(int arr[],int size){
    for(int i=0;i<size;i++){
        cout<<arr[i]<<" ";
    }
    cout<<endl;
}


void linearInsert(int linear[], int value, int size) {
    int i=0;
    while(i<size){
        int j=(value+i)%size;
        if(linear[j] == -1){
            linear[j]=value;
            nl++;
            return;
        }
        i++;
    }
    return;
}

void quadInsert(int quad[], int value, int size) {
    int i=0;
    while(i<size){
        int j=(value+i+2*(i*i))%size;
        if(quad[j] == -1){
            quad[j]=value;
            nq++;
            return;
        }
        i++;
    }
    return;
}

void doubleInsert(int doub[], int value, int size) {
    int i=0;
    int digits=0;
    int num=value;
    while(num != 0){
        digits=digits+num%10;
        num=num/10;
    }

    while(i<size){
        int j=(value+i*digits)%size;
        if(doub[j] == -1){
            doub[j]=value;
            nq++;
            return;
        }
        i++;
    }
    return;
}

int main(int argc, char **argv){
    int linear[8]={-1,-1,-1,-1,-1,-1,-1,-1};
    int quad[8]={-1,-1,-1,-1,-1,-1,-1,-1};
    int doub[8]={-1,-1,-1,-1,-1,-1,-1,-1};
    int size = 8;
    int sizearr=0;
    int value;

    
    int arr[100];
    for(int i=0;i<argc-1;i++){
        arr[i] = atoi(argv[i+1]);
        sizearr++;
    }

    int j=0;
    while(j<sizearr){
           
            value=arr[j];
            linearInsert(linear,value,size);
            quadInsert(quad,value,size);
            doubleInsert(doub,value,size);
            j++;
    }   
        cout<<"linear probing: ";
        printArray(linear,size);
        cout<<"quadratic probing: ";
        printArray(quad,size);
        cout<<"doubly hashed: ";
        printArray(doub,size);
}   