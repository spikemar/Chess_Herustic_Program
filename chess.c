#include<stdio.h>

#define INF 10000



typedef struct piece
{
    int no,name,color,alive,loc_i,loc_j,val;
}piece;

piece P[35];
int board[9][9];
int deadPiecesBoard[9][9];
int Hi,Hj,Ti,Tj;
char printPiece[10]={' ','P','R','H','B','K','Q'};
void initializeBoard();
void displayBoard();
int otherMove();
int myMove();

piece make_piece(int no,int name,int color,int alive,int loc_i,int loc_j,int val)
{
    piece a;
    a.no=no; a.name=name; a.color=color; a.alive=alive; a.loc_i=loc_i; a.loc_j=loc_j; a.val=val;
    return a;
}
void movePiece()
{
    int i,j,fi,fj;
    char a,b;
    int valid=0, sameplace=0;
    printf("\n\nFrom-To:");
    do
    {

        if(valid) printf("Please repeat your move!\nFrom-To:");
        valid=0;
        sameplace=0;
        scanf(" %c %d %c %d",&a,&i,&b,&fi);
        j=a-'A'+1; fj=b-'A'+1;
        if(a<'A' || a>'H' || b<'A' || b>'H' || i<1 || i>8 || j<1 || j>8 || fi<1 || fi >8 || fj<1 || fj>8 || !board[i][j] || board[fi][fj] )
        {
        if(!board[i][j] || board[fi][fj])
        sameplace=1;
            valid=1;
        }
        if(valid==1 && P[board[i][j]].color!=P[board[fi][fj]].color && sameplace==1)
        {
            valid=0;
            P[board[fi][fj]].alive=0;
            if(P[board[i][j]].name==1 && fj==j)
            valid=1;
            //P[board[fi][fj]].name deadleri dizdir buraya
        }
        
        switch(P[board[i][j]].name)
        {
            case 1:
                if(j-fj) {
                         valid=1;
                         if(P[board[i][j]].color!=P[board[fi][fj]].color && sameplace==1 && abs(i-fi)==1 && abs(j-fj)==1)
                         {
                         valid=0;
                         if(P[board[i][j]].color==0 && fi>i)
                         valid=1;
                         if(P[board[i][j]].color==1 && fi<i)
                         valid=1;
                         } 
                         break;
                         }
                if(!P[board[i][j]].color)
                {
                    if(fi>i) valid=1;
                    if(i==7)
                    {
                        if(fi-i<-2)
                            valid=1;
                    }
                    else if(fi-i<-1)
                        valid=1;
                }
                else
                {
                    if(fi<i) valid=1;
                    if(i==2)
                    {
                        if(fi-i>2)
                            valid=1;
                    }
                    else if(fi-i>1)
                        valid=1;
                }
                if(CheckW()) valid=1;
                
                
                break;
            case 2: if(CheckW() || abs(i-fi) && abs(j-fj)) valid=1;break;
            case 3: if(CheckW() || abs(i-fi)*abs(i-fi)+abs(j-fj)*abs(j-fj)!=5) valid=1; break;
            case 4: if(CheckW() || abs(i-fi)!=abs(j-fj)) valid=1; break;
            case 5: if(CheckW() || abs(i-fi)>1 || abs(j-fj)>1) valid=1; break;
            case 6: if(CheckW() || !(abs(i-fi)==abs(j-fj) || !abs(fj-j) || !abs(fi-i) )) valid=1; break;
        }

        if(P[board[i][j]].name==3) continue;

        int di=0,dj=0,tempi=i,tempj=j;

        if(fi-i) di=(fi-i)/abs(fi-i);
        if(fj-j) dj=(fj-j)/abs(fj-j);

        tempi+=di;
        tempj+=dj;

        while(tempi!=fi || tempj!=fj)
        {
            if(board[tempi][tempj]) {valid=1; break;}
            tempi+=di;
            tempj+=dj;
        }
    }while(valid);
    board[fi][fj]=board[i][j];
    board[i][j]=0;
    P[board[fi][fj]].loc_i=fi;
    P[board[fi][fj]].loc_j=fj;
}
void movecomputerPiece(char a, int i, char b, int fi)
{
    int j,fj;
    int valid=0, sameplace=0;
    printf("\n\nFrom-To:");
    do
    
    {

        if(valid) printf("Please repeat your move!\nFrom-To:");
        valid=0;
        sameplace=0;
        j=a-'A'+1; fj=b-'A'+1;
        if(a<'A' || a>'H' || b<'A' || b>'H' || i<1 || i>8 || j<1 || j>8 || fi<1 || fi >8 || fj<1 || fj>8 || !board[i][j] || board[fi][fj] )
        {
        if(!board[i][j] || board[fi][fj])
        sameplace=1;
            valid=1;
        }
        if(valid==1 && P[board[i][j]].color!=P[board[fi][fj]].color && sameplace==1)
        {
            valid=0;
            P[board[fi][fj]].alive=0;
            if(P[board[i][j]].name==1 && fj==j)
            valid=1;
            //P[board[fi][fj]].name deadleri dizdir buraya
        }
        
        switch(P[board[i][j]].name)
        {
            case 1:
                if(j-fj) {
                         valid=1;
                         if(P[board[i][j]].color!=P[board[fi][fj]].color && sameplace==1 && abs(i-fi)==1 && abs(j-fj)==1)
                         {
                         valid=0;
                         if(P[board[i][j]].color==0 && fi>i)
                         valid=1;
                         if(P[board[i][j]].color==1 && fi<i)
                         valid=1;
                         } 
                         break;
                         }
                if(!P[board[i][j]].color)
                {
                    if(fi>i) valid=1;
                    if(i==7)
                    {
                        if(fi-i<-2)
                            valid=1;
                    }
                    else if(fi-i<-1)
                        valid=1;
                }
                else
                {
                    if(fi<i) valid=1;
                    if(i==2)
                    {
                        if(fi-i>2)
                            valid=1;
                    }
                    else if(fi-i>1)
                        valid=1;
                }
                if(CheckB()) valid=1;
                
                
                break;
            case 2: if(CheckB() || abs(i-fi) && abs(j-fj)) valid=1;break;
            case 3: if(CheckB() || abs(i-fi)*abs(i-fi)+abs(j-fj)*abs(j-fj)!=5) valid=1; break;
            case 4: if(CheckB() || abs(i-fi)!=abs(j-fj)) valid=1; break;
            case 5: if(CheckB() || abs(i-fi)>1 || abs(j-fj)>1) valid=1; break;
            case 6: if(CheckB() || !(abs(i-fi)==abs(j-fj) || !abs(fj-j) || !abs(fi-i) )) valid=1; break;
        }

        if(P[board[i][j]].name==3) continue;

        int di=0,dj=0,tempi=i,tempj=j;

        if(fi-i) di=(fi-i)/abs(fi-i);
        if(fj-j) dj=(fj-j)/abs(fj-j);

        tempi+=di;
        tempj+=dj;

        while(tempi!=fi || tempj!=fj)
        {
            if(board[tempi][tempj]) {valid=1; break;}
            tempi+=di;
            tempj+=dj;
        }
    }while(valid);
    board[fi][fj]=board[i][j];
    board[i][j]=0;
    P[board[fi][fj]].loc_i=fi;
    P[board[fi][fj]].loc_j=fj;
}
void openingfunc ()
{
     if(P[board[4][5]].name==1)
    {
        movecomputerPiece('C', 7 , 'C' ,5); 
        system("cls");
        displayBoard();
        movePiece();
        system("cls");
        displayBoard();
        movecomputerPiece('D', 7 , 'D' ,6); 
        if(P[board[3][4]].name==1)
        {
        system("cls");
        displayBoard();
        movecomputerPiece('G', 7 , 'G' ,6);
        }
    }
    else
    {
        movecomputerPiece('E', 7 , 'E' ,6); 
        system("cls");
        displayBoard();
        movePiece();
        system("cls");
        displayBoard();
        movecomputerPiece('D', 7 , 'D' ,5); 
    }
}

int fvalid(int bi,int bj,int ei,int ej)
{
	int i,j;
	if(bi==ei)
	{
		if(bj < ej)
		{
			for(i=bj+1;i<ej;i++)
			{
				if(board[bi][i]) return 0;
			}
			return 1;
		}
		if(ej < bj)
		{
			for(i=ej+1;i<bj;i++)
			{
				if(board[bi][i]) return 0;
			}
			return 1;
		}
		return 0;
	}

	if(bj==ej)
	{
		if(bi < ei)
		{
			for(i=bi+1;i<ei;i++)
			{
				if(board[i][bj]) return 0;
			}
			return 1;
		}
		if(ei < bi)
		{
			for(i=ei+1;i<bi;i++)
			{
				if(board[i][bj]) return 0;
			}
			return 1;
		}
		return 0;
	}

	if(bi+bj == ei+ej)
	{
		if(bj < ej)
		{
			for(i=1;bj+i<ej;i++)
			{
				if(board[bi-i][bj+i]) return 0;
			}
			return 1;
		}
		if(ej < bj)
		{
			for(i=1;ej+i<bj;i++)
			{
				if(board[ei-i][ej+i]) return 0;
			}
			return 1;
		}
	}

	if(bi-bj == ei-ej)
	{
		if(bj < ej)
		{
			for(i=1;bj+i<ej;i++)
			{
				if(board[bi+i][bj+i]) return 0;
			}
			return 1;
		}

		if(ej < bj)
		{
			for(i=1;ej+i<bj;i++)
			{
				if(board[ei+i][ej+i]) return 0;
			}
			return 1;
		}
	}


	return 0;
}
int otherMove(int t)
{
	if(t==5) return 0;
    int i,j,fi,fj;
	int minworth=3*INF,worth,valid,temp;
	for(fi=1;fi<=8;fi++)
		for(fj=1;fj<=8;fj++)
		{
			if(board[fi][fj] && P[board[fi][fj]].color == 1)
			{
				for(i=1;i<=8;i++)
					for(j=1;j<=8;j++)
					{
						valid=0;
						if(i==fi && j==fj) continue;
						if(board[i][j] && P[board[i][j]].color == P[board[fi][fj]].color) continue;
						
						switch(P[board[fi][fj]].name)
	                	{
	            		
	            		case 1:
	                		if(j-fj) 
	                		{
	                        	valid=1;
	                        	if(abs(i-fi)==1 && abs(j-fj)==1)
	                        	{

	                        		valid=0;
	                        		if(!board[i][j]) valid=1;
	                        		if(fi>i) valid=1;
	                         	} 
	                         	break;
	                        }
	                        if(board[i][j]) valid=1;
	                		if(fi > i) valid=1;
	                    	if(fi==2)
	                    	{
	                    		if(fi+2 < i) valid=1;
	                    	}
	                    	else
	                    		if(fi+1 < i) valid=1;

	                		if(CheckW() || !fvalid(fi,fj,i,j)) valid=1;
	                
	                		break;
	            		case 2: if(CheckW() || !fvalid(fi,fj,i,j) || abs(i-fi) && abs(j-fj)) valid=1;break;
	            		case 3: if(CheckW() || abs(i-fi)*abs(i-fi)+abs(j-fj)*abs(j-fj)!=5) valid=1; break;
	            		case 4: if(CheckW() || !fvalid(fi,fj,i,j) || abs(i-fi)!=abs(j-fj) && abs(i+fi)!=abs(j+fj)) valid=1; break;
	            		case 5: if(CheckW() || !fvalid(fi,fj,i,j) || abs(i-fi)>1 || abs(j-fj)>1) valid=1; break;
	            		case 6: if(CheckW() || !fvalid(fi,fj,i,j)) valid=1; break;
	        			}
	        			if(!valid)
	        			{
	        				worth=-P[board[i][j]].val;
	        				temp=board[i][j];
	        				board[i][j]=board[fi][fj];
	        				board[fi][fj]=0;
	        				worth=worth+myMove(t+1);

	        				if(minworth > worth) minworth=worth;
	        				board[fi][fj]=board[i][j];
	        				board[i][j]=temp;


	        			}
	        		}

			}
		}
		return minworth;
}

int myMove(int t)
{
	int hi,hj,ti,tj;
    int i,j,fi,fj;
	int maxworth=3*(-INF),worth,valid,temp;
	for(fi=1;fi<=8;fi++)
		for(fj=1;fj<=8;fj++)
		{
			if(board[fi][fj] && P[board[fi][fj]].color == 0)
			{
				for(i=1;i<=8;i++)
					for(j=1;j<=8;j++)
					{
						valid=0;
						if(i==fi && j==fj) continue;
						if(board[i][j] && P[board[i][j]].color == P[board[fi][fj]].color) continue;
						
						switch(P[board[fi][fj]].name)
	                	{
	            		
	            		case 1:
	                		if(j-fj) 
	                		{
	                        	valid=1;
	                        	if(abs(i-fi)==1 && abs(j-fj)==1)
	                        	{

	                        		valid=0;
	                        		if(!board[i][j]) valid=1;
	                        		if(fi<i) valid=1;
	                         	} 
	                         	break;
	                        }
	                        if(board[i][j]) valid=1;
	                		if(fi < i) valid=1;
	                    	if(fi==7)
	                    	{
	                    		if(fi-2 > i) valid=1;
	                    	}
	                    	else
	                    		if(fi-1 > i) valid=1;

	                		if(!fvalid(fi,fj,i,j)) valid=1;
	                		if(CheckB()) valid=1;
	                
	                		break;
	            		case 2: if(!fvalid(fi,fj,i,j) || CheckW() || abs(i-fi) && abs(j-fj)) valid=1;break;
	            		case 3: if(CheckB() || abs(i-fi)*abs(i-fi)+abs(j-fj)*abs(j-fj)!=5) valid=1; break;
	            		case 4: if(CheckB() || !fvalid(fi,fj,i,j) || abs(i-fi)!=abs(j-fj) && abs(i+fi)!=abs(j+fj)) valid=1; break;
	            		case 5: if(CheckB() || !fvalid(fi,fj,i,j) || abs(i-fi)>1 || abs(j-fj)>1) valid=1; break;
	            		case 6: if(CheckB() || !fvalid(fi,fj,i,j)) valid=1; break;
	        			}
	        			if(!valid)
	        			{
	        				worth=P[board[i][j]].val;
	        				temp=board[i][j];
	        				board[i][j]=board[fi][fj];
	        				board[fi][fj]=0;
	        			    worth=worth+otherMove(t+1);
	        				if(maxworth < worth)
                            {
                                maxworth=worth;
	        				    hi=fi; hj=fj;
                                ti=i;  tj=j;   
                            }
                            board[fi][fj]=board[i][j];
	        				board[i][j]=temp;


	        			}
	        		}

			}
		}
        Hi=hi; Hj=hj;
        Ti=ti; Tj=tj;
		return maxworth;
}

int main()
{   
    initializeBoard();
    displayBoard();
    movePiece();
    system("cls");
    displayBoard();
    openingfunc();
    while(1)
    {
    	system("cls");
        displayBoard();
        movePiece();
        system("cls");
        displayBoard();
        //myMove(0);
        //movecomputerPiece('A'+Hj-1,Hi,'A'+Tj-1,Ti);
        //file log lazim
    }
}
void initializeBoard()
{
    int i,j;
    for(j=1;j<=8;j++) board[7][j]=j;
    for(j=1;j<=8;j++) board[8][j]=8+j;
    for(j=1;j<=8;j++) board[2][j]=16+j;
    for(j=1;j<=8;j++) board[1][j]=24+j;

    for(i=1;i<=8;i++)                         
    {
        P[i]=make_piece(i,1,0,1,7,i,1);
        P[16+i]=make_piece(16+i,1,1,1,2,i,1);
    }

      P[9]=make_piece(9,2,0,1,8,1,5);        
    P[10]=make_piece(10,3,0,1,8,2,3);
    P[11]=make_piece(11,4,0,1,8,3,3);
    P[12]=make_piece(12,6,0,1,8,4,9);
    P[13]=make_piece(13,5,0,1,8,5,INF);
    P[14]=make_piece(14,4,0,1,8,6,3);
    P[15]=make_piece(15,3,0,1,8,7,3);
    P[16]=make_piece(16,2,0,1,8,8,5);

    P[25]=make_piece(25,2,1,1,1,1,5);       
    P[26]=make_piece(26,3,1,1,1,2,3);
    P[27]=make_piece(27,4,1,1,1,3,3);
    P[28]=make_piece(28,6,1,1,1,4,9);
    P[29]=make_piece(29,5,1,1,1,5,INF);
    P[30]=make_piece(30,4,1,1,1,6,3);
    P[31]=make_piece(31,3,1,1,1,7,3);
    P[32]=make_piece(32,2,1,1,1,8,5);   
}
void displayBoard()
{
    int i,j;
    printf("Active pieces:\t\tDead pieces:\n\n");
    for(i=8;i>0;i--,printf("\n")){
    	printf("%d   ", i);
        for(j=1;j<=8;j++){
            if(board[i][j])
                printf("%c ",printPiece[P[board[i][j]].name]+(1-P[board[i][j]].color)*32);
            else if((i+j)%2==0)
                printf("x ");
            else
                printf("  ");}
                printf("\t");
		for(j=1;j<=8;j++){
			if(i==1 || i==2|| i==7 || i==8)
				printf("%c ", deadPiecesBoard[i][j] = '_');
			else
				printf("  ");
		}
            }
    printf("\n    A B C D E F G H");
}
int CheckB() 
{
	int i, j, n, m;
	for(i=1; i<9; i++)
		for(j=1; j<9; j++)
 {
	if(P[board[i][j]].name==5 && P[board[i][j]].color==0)
	{
		if(P[board[i-1][j-1]].name==1 && P[board[i-1][j-1]].color==1)
		return 1;
		if(P[board[i-1][j+1]].name==1 && P[board[i-1][j+1]].color==1)
		return 1;
		if(P[board[i-2][j-1]].name==3 && P[board[i-2][j-1]].color==1)
		return 1;
		if(P[board[i-2][j+1]].name==3 && P[board[i-2][j+1]].color==1)
		return 1;
		if(P[board[i+2][j-1]].name==3 && P[board[i+2][j-1]].color==1)
		return 1;
		if(P[board[i+2][j+1]].name==3 && P[board[i+2][j+1]].color==1)
		return 1;
		if(P[board[i-1][j-2]].name==3 && P[board[i-1][j-2]].color==1)
		return 1;
		if(P[board[i-1][j+2]].name==3 && P[board[i-1][j+2]].color==1)
		return 1;
		if(P[board[i+1][j-2]].name==3 && P[board[i+1][j-2]].color==1)
		return 1;
		if(P[board[i+1][j+2]].name==3 && P[board[i+1][j+2]].color==1)
		return 1;
		for(n=1; n<9; n++)
		{
			if(P[board[n][j]].name==2 && P[board[n][j]].color==1)
			{
			m=n;
			if(fvalid(i,j,m,j))
			return 1;
			}
			if(P[board[i][n]].name==2 && P[board[i][n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i,m))
			return 1;
			}
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j+n]].name==4 && P[board[i+n][j+n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i+m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j-n]].name==4 && P[board[i-n][j-n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i-m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j+n]].name==4 && P[board[i-n][j+n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i-m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j-n]].name==4 && P[board[i+n][j-n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i+m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<9; n++)
		{
			if(P[board[n][j]].name==6 && P[board[n][j]].color==1)
			{
			m=n;
			if(fvalid(i,j,m,j))
			return 1;
			}
			if(P[board[i][n]].name==6 && P[board[i][n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i,m))
			return 1;
			}
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j+n]].name==6 && P[board[i+n][j+n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i+m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j-n]].name==6 && P[board[i-n][j-n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i-m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j+n]].name==6 && P[board[i-n][j+n]].color==1)
			{
			m=n;
			if(fvalid(i,j,i-m,j+m))
			return 1;
			}
			
		}
		
}
}
return 0;
}
int CheckW() 
{
	int i, j, n, m;
	for(i=1; i<9; i++)
		for(j=1; j<9; j++)
 {
	if(P[board[i][j]].name==5 && P[board[i][j]].color==1)
	{
		if(P[board[i+1][j-1]].name==1 && P[board[i+1][j-1]].color==0)
		return 1;
		if(P[board[i+1][j+1]].name==1 && P[board[i+1][j+1]].color==0)
		return 1;
		if(P[board[i-2][j-1]].name==3 && P[board[i-2][j-1]].color==0)
		return 1;
		if(P[board[i-2][j+1]].name==3 && P[board[i-2][j+1]].color==0)
		return 1;
		if(P[board[i+2][j-1]].name==3 && P[board[i+2][j-1]].color==0)
		return 1;
		if(P[board[i+2][j+1]].name==3 && P[board[i+2][j+1]].color==0)
		return 1;
		if(P[board[i-1][j-2]].name==3 && P[board[i-1][j-2]].color==0)
		return 1;
		if(P[board[i-1][j+2]].name==3 && P[board[i-1][j+2]].color==0)
		return 1;
		if(P[board[i+1][j-2]].name==3 && P[board[i+1][j-2]].color==0)
		return 1;
		if(P[board[i+1][j+2]].name==3 && P[board[i+1][j+2]].color==0)
		return 1;
		for(n=1; n<9; n++)
		{
			if(P[board[n][j]].name==2 && P[board[n][j]].color==0)
			{
			m=n;
			if(fvalid(i,j,m,j))
			return 1;
			}
			if(P[board[i][n]].name==2 && P[board[i][n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i,m))
			return 1;
			}
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j+n]].name==4 && P[board[i+n][j+n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i+m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j-n]].name==4 && P[board[i-n][j-n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i-m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j+n]].name==4 && P[board[i-n][j+n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i-m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j-n]].name==4 && P[board[i+n][j-n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i+m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<9; n++)
		{
			if(P[board[n][j]].name==6 && P[board[n][j]].color==0)
			{
			m=n;
			if(fvalid(i,j,m,j))
			return 1;
			}
			if(P[board[i][n]].name==6 && P[board[i][n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i,m))
			return 1;
			}
		}
		for(n=1; n<8; n++){
			if(P[board[i+n][j+n]].name==6 && P[board[i+n][j+n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i+m,j+m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j-n]].name==6 && P[board[i-n][j-n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i-m,j-m))
			return 1;
			}
			
		}
		for(n=1; n<8; n++){
			if(P[board[i-n][j+n]].name==6 && P[board[i-n][j+n]].color==0)
			{
			m=n;
			if(fvalid(i,j,i-m,j+m))
			return 1;
			}
			
		}
		
}
}
return 0;
}
