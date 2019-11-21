#include<iostream>
#include<fstream>
#include<string>
using namespace std;
const int wc=3;//count of symbols for win
const int sizeX=25;
const int sizeY=21;
const int w=7;
const int h=5;
const int sizeFX=3;
const int sizeFY=3;
int F[sizeFY][sizeFX]={0};//0-free,1-X,2-O
char a[sizeY][sizeX];
char X[h][w];
char O[h][w];
int p;//1-X, 2-O;
ifstream f;
void getSymbol(char a[h][w]);
void set();
void printField();
inline int min(int a,int b);
bool win();
void writeSymbol(int y, int x);
//void printSymbol(char a[h][w]);
int main(){
	try{
		f.open("data.txt");
		if(!f.is_open()) throw 1;
	}
	catch(...){
		cout<<"The file haven't been opened!"<<endl;
		return 0;
	}
	getSymbol(X);
	getSymbol(O);
	f.close();
	set();
	printField();
	while(!win()){
		p=p==1?p+1:1;
		int x,y;
		do{
			if(p==1) cout<<"X's ";
			else cout<<"O's ";
			cout<<"move"<<endl;
			cout<<"Enter the x coordinate in the range from 0 to "<<sizeFX-1<<":"<<endl;
			cin>>x;
			cout<<"Enter the y coordinate in the range from 0 to "<<sizeFY-1<<":"<<endl;
			cin>>y;
		}while((x>=0 && x<sizeFX && y>=0 && y<sizeFY)?(F[x][y]!=0):true);
		F[y][x]=p;
		writeSymbol(y,x);
		system("clear");
		printField();
	}
	if(p==1) cout<<"X won!"<<endl;
	else cout<<"O won!"<<endl;
	return 0;
}

void getSymbol(char a[h][w]){
	string str;
	for(int j=0;j<h;j++){
		getline(f,str);
		for(int i=0;i<w;i++)
			a[j][i]=str[i];
	}
}

void set(){
	for(int j=0;j<sizeY;j++)
		for(int i=0;i<sizeX;i++){
			if((j+1)%7==0 && j!=sizeY-1 && i%8!=0)
				a[j][i]='_';
			else if(i%8==0) a[j][i]='|';
			else a[j][i]=' ';
		}
	for(int j=0;j<sizeFY;j++)
		for(int i=0;i<sizeFX;i++)
			F[j][i]=0;
	p=-1;
}
void printField(){
	for(int j=0;j<sizeY;j++){
		for(int i=0;i<sizeX;i++)
			cout<<a[j][i];
		cout<<endl;
	}
}
inline int min(int a,int b){
	return a<=b?a:b;
}
bool win(){
	int k;
	for(int i=0;i<sizeFX;i++){
		k=0;
		for(int j=0;j<sizeFY;j++)
			if(p==F[j][i]) k++;
		if(k>=wc) return true;
	}
	for(int j=0;j<sizeFY;j++){
		k=0;
		for(int i=0;i<sizeFX;i++)
			if(p==F[j][i]) k++;
		if(k>=wc) return true;
	}
	k=0;
	int m=0;
	for(int i=0;i<min(sizeFX,sizeFY);i++){
		if(p==F[i][i]) k++;
		if(p==F[sizeFY-i-1][i]) m++;
	}
	if(k>=wc|| p>=wc) return true;
	return false;
}
void writeSymbol(int y, int x){
	//char b[h][w];
	//char** b;
	/*if(F[y][x]==1) b=X;
	else if(F[y][x]==2) b=O;
	for(int j=0;j<h;j++)
		for(int i=0;i<w;i++)
			a[7*y+j][8*x+i+1]=b[j][i];*/
	if(F[y][x]==1)
		for(int j=0;j<h;j++)
			for(int i=0;i<w;i++)
				a[7*y+j][8*x+i+1]=X[j][i];
	else if(F[y][x]==2)
		for(int j=0;j<h;j++)
			for(int i=0;i<w;i++)
				a[7*y+j][8*x+i+1]=O[j][i];
}
/*void printSymbol(char a[h][w]){
	for(int j=0;j<h;j++){
		for(int i=0;i<w;i++)
			cout<<a[j][i];
		cout<<endl;
	}

}*/

