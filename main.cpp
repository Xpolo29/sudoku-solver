#include <iostream>
#include <time.h>


//grid var init
const int N = 81;

//Input grid here
int grid[N] = {6,-1,-1,9,-1,-1,-1,-1,4,-1,8,3,-1,-1,-1,-1,6,-1,-1,-1,2,7,-1,-1,3,-1,-1,-1,-1,-1,-1,-1,1,-1,5,-1,-1,-1,5,-1,-1,2,-1,-1,9,1,-1,-1,-1,3,-1,2,-1,-1,5,-1,9,1,-1,-1,-1,-1,3,-1,-1,-1,2,-1,-1,-1,-1,-1,-1,-1,-1,-1,8,4,-1,-1,-1};

struct list{
    int e[9] = {-1,-1,-1,-1,-1,-1,-1,-1,-1};
};

list getRow(int n){
    list res;
    for(int i=0;i<9;i++){
        res.e[i] = grid[9*n+i];
    }
    return res;
}

list getColumn(int n){
    list res;
    for(int i=0;i<9;i++){
        res.e[i] = grid[n+i*9];
    }
    return res;
}

list getMiniGrid(int n){
    list res;
    int j=(n/3)*27+3*(n%3);
    for(int i=0;i<9;i++){
        res.e[i] = grid[i+j];
        if((i+1)%3==0){j+=6;}
    }
    return res;
}

void printGrid(){
    for(int i=0;i<N;i++){
        std::cout << grid[i];
        if(((i+1)%9!=0)&&((i+1)%3==0)){std::cout << "|";}
        if((i+1)%9==0){std::cout << std::endl;}
        if((i==26) || (i==53)){for(int k=0;k<11;k++){std::cout<<"-";}std::cout<<std::endl;}
    }
    for(int j=0;j<40;j++){std::cout << "_";}
    std::cout << std::endl;
}

//mode 1 : complete mode
bool check(char type,int n,int mode=0){
    list res;
    if(type == 'c'){res = getColumn(n);}
    if(type == 'r'){res = getRow(n);}
    if(type == 'g'){res = getMiniGrid(n);}

    if(mode == 1){
        int s=0;
        for(int i=0;i<9;i++){
            s+=res.e[i];
        }
        if(s==45){return true;}
        return false;
    }

    list v;
    for(int i=0;i<9;i++){
        if(res.e[i] == -1){continue;}
        //if(type == 'c'){std::cout << res.e[i] << " and " << i << std::endl;}

        if(v.e[res.e[i]-1] != -1){return false;};
        v.e[res.e[i]-1] = 0;   
    }
    return true;
}

//check if map is valid
bool valid(){
    for(int i=0;i<9;i++){
        bool b1 = check('r',i);
        bool b2 = check('c',i);
        bool b3 = check('g',i);
        //std::cout << i << " and " << b1 << " " << b2 << " " << b3 << std::endl;
        if(!(b1 && b2 && b3 )){return false;}
    }
    return true;
}

bool completed(){
    for(int i=0;i<9;i++){
        bool b1 = check('r',i,1);
        bool b2 = check('c',i,1);
        bool b3 = check('g',i,1);
        if(!(b1 && b2 && b3 )){return false;}
    }
    return true;
}

int rd(){
    return std::rand()%9;
}

int main(){
    //init timer for generation
    std::srand(time(NULL));
    /*
    for(int i=0;i<N;i++){
        grid[i] = -1;
    }
    */
    

    printGrid();
    

    if(!valid()){return 0x01;} //init map not valid error

    list pGrid[81];
    int histo[81];
    int D=0;
    bool goBack = false;
    for(int l=0;l<81;l++){histo[l] = -1;}

    while(!completed()){

        int i=-1;
        for(int l=0;l<81;l++){if(grid[l] == -1){i=l;break;}}
        if(i==-1){printGrid();return 0x03;} //map full but false error

        for(int j=0;j<9;j++){
            if(pGrid[i].e[j]==-1){
                grid[i] = j+1;pGrid[i].e[j] = 2;
                if(valid()){break;}
                else{grid[i] =-1;}
            }
            //go back one layer
            if((j==8) && (grid[i] ==-1)){
                
                for(int k=0;k<9;k++){pGrid[i].e[k]=-1;}
                if(histo[0] == -1){printGrid();return 0x04;} //backtracking problem
                grid[histo[0]] = -1;
                for(int h=0;h<80;h++){
                    histo[h]=histo[h+1];
                    histo[80] = -1;
                }
                goBack = true;
            }
        }

        if((!goBack)){
            for(int h=N-1;h>0;h--){
                histo[h]=histo[h-1];
            }
            histo[0] = i;
        }
        
        //std::cout << i <<  " i and ";
        //for(int d=0;d<81;d++){std::cout << histo[d] << " ";}
        //for(int f=0;f<9;f++){std::cout << pGrid[59].e[f] << " ";}
        //std::cout << std::endl;

        D++;
        if(D==10000){printGrid();return 0x02;} //infinite while boucle
        //printGrid();

        goBack = false;
    }
    printGrid();
    std::cout << std::endl << "In " << D << " iterations " << std::endl;
    return 0x00;
}