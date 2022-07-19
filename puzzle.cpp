#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>
#include <vector>

//this function gets all the data in the file choosed by user and stores in a string
//parameter: filename(user input)
//returns data as string
std::string getMsg(const std::string &filename){
    std::ifstream in;
    in.open(filename);
    std::string line, msg="";
    if(in.is_open())
    {
        while(in>>line)
        {
            msg+=line+" ";
        }
        in.close();
    }
    return msg;
}


//this functions asks user for inputs
//stores all the data from file in respective variables
//parameters: msg(empty string), row(empty int), column(empty int)
void getInputs(std::string &msg,int &row,int &column){
    std::string filename;
    std::cout<< "Name of file "<<std::endl;
    std::cin>>filename;
    std::string msg1=getMsg(filename);
    int x=msg1.find_first_of(" ");
    //std::cout << x;
    row = std::stoi(msg1.substr (0,x));
    std::string msg2=msg1.substr(x+1,msg1.length());
   // std::cout << msg1 << ' ' << msg2 << std::endl ;
    int y=msg2.find_first_of(" ");
    column = std::stoi(msg2.substr (0,y));
    msg=msg2.substr(y+1,msg2.length());
    
   // std::cout <<  msg ;
    msg.erase(remove(msg.begin(), msg.end(), ' '), msg.end());
    
    
}


//this function use recursion to search for a path in matrix
//stores path in a vector of string
//keeps count of addition of elements of matrix in the path
//parameter: matrix(extracted from file), row(number of rows of matrix),column(number of columns of matrix),input(string according to which  path to be followed), s(string to store elements in path), k(string to store row and columns in path), l(stores row and column in string format)
//returns true if length equals path size and sum equals zero else false
bool path_finder(const std::vector<std::vector<char> > matrix,const int row,const int column,const std::string input,std::string &s,std::vector<std::string> &k,std::string &l,int r=0,int c=0){
    l=std::to_string(r)+" "+std::to_string(c);
    if(r<0 || c<0 || r>row-1 || c>column-1){
        return false;
    }
    if(std::find(k.begin(),k.end(),l)!=k.end()){
        return false;
    }
    s+=matrix[r][c];
    int size_s=s.size();
    if(size_s==input.size() && s==input){
        k.push_back(l);
        return true;
    }
    k.push_back(l);
    int size=k.size();
    if(size<input.size()){
        if(path_finder(matrix,row,column,input,s,k,l,r+1,c)){
            return true;
        }
        if(path_finder(matrix,row,column,input,s,k,l,r,c-1)){
            return true;
        }
        if(path_finder(matrix,row,column,input,s,k,l,r-1,c)){
            return true;
        }
        if(path_finder(matrix,row,column,input,s,k,l,r,c+1)){
            return true;
        }
    }
    k.pop_back();
    s.resize(s.size() - 1);
    if(s.size()==0){
        if(path_finder(matrix,row,column,input,s,k,l,r+1,c)){
            return true;
        }
        if(path_finder(matrix,row,column,input,s,k,l,r,c+1)){
            return true;
        }
    }
    return false;
}




//this function prints matrix
//parameters: matrix(to be printed), row(number of rows of matrix), column(number of columns of matrix)
void printMatrix(std::vector<std::vector<char> > a,int row,int column){
    for(int i = 0; i < row; i++)
    {
        for(int j = 0; j < column; j++)
        {
            std::cout << a[i][j] << " ";
        }
        std::cout << std::endl;
    }
}


//this function changes the elements of a matrix to 'v','^','>' or'<' according to path followed
//parameters: v(matrix with all elements= '-'), row(number of rows of matrix), column(number of column of matrix), k(vector conating path as string)
void setMatrix(std::vector<std::vector<char> > &v,const int row,const int column,const std::vector<std::string> k){
    for(int i = 0; i < row; i++)
    {
        v[i] = std::vector<char>(column);
        for(int j = 0; j < column; j++)
        {
            v[i][j] = '-';
        }
    }
    int size=k.size();
    std::vector<int>r;
    std::vector<int>c;
    for(int a=0;a<size;a++){
        int i1=k[a].find_first_of(" ");
        r.push_back(std::stoi(k[a].substr (0,i1)));
        c.push_back(std::stoi(k[a].substr(i1+1,k[a].length())));
    }
    for (int b=0;b<size-1;b++) {
        if(r[b]<r[b+1] && c[b]==c[b+1]){
            v[r[b]][c[b]]='v';
        }
        else if(r[b]>r[b+1] && c[b]==c[b+1]){
            v[r[b]][c[b]]='^';
        }
        else if(r[b]==r[b+1] && c[b]<c[b+1]){
            v[r[b]][c[b]]='>';
        }
        else{
            v[r[b]][c[b]]='<';
        }
    }
    v[r[size-1]][c[size-1]]='x';
}


//calls various different functions to get input, store, print, find path
//calls printmatrix metod to print path if found else print "No path found"
//parameters: row(store number of rows),column(store number of columns), msg(string to store data in file), matrix(vector to store matrix from file), input(user input), v(new matrix with all elements as '-'), k(vector to store path), l(string to store path), s(string to store addition of elements in path)
//returns 0
int main(){
    int row;
    int column;
    std::string msg; 
    getInputs(msg,row,column);
    std::vector<std::vector<char> > matrix(row);
    int c;
    for(int i = 0; i < row; i++)
    {
        matrix[i] = std::vector<char>(column);
        for(int j = 0; j < column; j++)
        {
            matrix[i][j] = msg[i+j+c];
        }
        c+=column-1;
    }
    printMatrix(matrix,row,column);
    std::string input;
    std::cout << "What word are you looking for?" <<std::endl;
    std::cin >> input;
    std::vector<std::vector<char> > v(row);
    std::vector<std::string> k;
    std::string s;
    std::string l;
    for(int i=0; i<input.size(); i++){
        input[i]=std::toupper(input[i]);
    }
    if(path_finder(matrix,row,column,input,s,k,l)){
        setMatrix(v,row,column,k);
        printMatrix(v,row,column);
    }
    else{
        std::cout<<"No path found"<<std::endl;
    }
    return 0;
    
}
