#include<stdio.h>

int i,j;
int turn = 1;
int nullboard,countwhite,countblack = 0;
//オセロ盤を定義
int board[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 1, -1, 0, 0, 0},
                   {0, 0, 0, -1, 1, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0},
                   {0, 0, 0, 0, 0, 0, 0, 0}}; //1が白、-1が黒

//碁盤を描く
void draw(){
    printf("   |");
    for(i=0; i<8; i++){
        printf("%2d |",i);
    }
    printf("\n");

    for(i=0; i<8; i++){
        printf("%2d |",i);
        for(j=0; j<8; j++){
            switch(board[i][j]){
                case 0:
                    printf("   |");
                    break;
                case -1:
                    printf(" ● |");
                    break;
                case 1:
                    printf(" ◯ |");
                    break;
                default:
                    break;
            }
        }
        printf("\n");
    }
}

//中心からの距離を返す
int distance(int x, int y){
	int distance_x = x-4;
	int distance_y = y-3;
	if(distance_x < 0) distance_x = -distance_x;
	if(distance_y < 0) distance_y = -distance_y;
	return distance_y + distance_x;
}

//1方向において、石が置けるか判定し、取れる石の数を返す
int flip_line_count(int x, int y, int dir_x, int dir_y){
    int count = 0;
    if(board[y][x] != 0) return 0; //既に石が置かれていたら置けない
	x += dir_x;
	y += dir_y;
	if(x>7 || y>7 || x<0 || y<0) return 0; //隣が盤面の外だったら置けない
	if(board[y][x] == turn) return 0; //隣が自分の石だったら置けない

	while(board[y][x] == ((-1) * turn)){
	    x += dir_x;
	    y += dir_y;
	    count++;
	    if(x>7 || y>7 || x<0 || y<0) return 0;
	}
	if(board[y][x] != turn) return 0; //自分の石で挟めなかったら置けない

	return count;
}


//取れる石の数を返す
int flip_count(int x, int y){
	int sumcount = flip_line_count(x, y, 1, 0);
	sumcount += flip_line_count(x, y, 1, 1);
	sumcount += flip_line_count(x, y, 0, 1);
	sumcount += flip_line_count(x, y, -1, 1);
	sumcount += flip_line_count(x, y, -1, 0);
	sumcount += flip_line_count(x, y, -1, -1);
	sumcount += flip_line_count(x, y, 0, -1);
	sumcount += flip_line_count(x, y, 1, -1);
	return sumcount;
}

//石を置き、ひっくり返す
void flip(int x, int y){
    int east = flip_line_count(x, y, 1, 0);
    int southeast = flip_line_count(x, y, 1, 1);
    int south = flip_line_count(x, y, 0, 1);
    int southwest = flip_line_count(x, y, -1, 1);
    int west = flip_line_count(x, y, -1, 0);
    int northwest = flip_line_count(x, y, -1, -1);
    int north = flip_line_count(x, y, 0, -1);
    int northeast = flip_line_count(x, y, 1, -1);

    if(east!=0){
        for(i=1;i<=east;i++){
            board[y][x+i]=turn;
        }
    }
    if(southeast!=0){
        for(i=1;i<=southeast;i++){
            board[y+i][x+i]=turn;
        }
    }
    if(south!=0){
        for(i=0;i<=south;i++){
            board[y+i][x]=turn;
        }
    }
    if(southwest!=0){
        for(i=0;i<=southwest;i++){
            board[y+i][x-i]=turn;
        }
    }
    if(west!=0){
        for(i=0;i<=west;i++){
            board[y][x-i]=turn;

        }
    }
    if(northwest!=0){
        for(i=0;i<=northwest;i++){
            board[y-i][x-i]=turn;
        }
    }
    if(north!=0){
        for(i=0;i<=north;i++){
            board[y-i][x]=turn;
        }
    }
    if(northeast!=0){
        for(i=0;i<=northeast;i++){
            board[y-i][x+i]=turn;
        }
    }
    board[y][x]=turn;
    draw();
    turn = (-1)*turn;//相手のターンにする
}

//配列の0以外の最小値を返す
int Min(int args[8][8]){
    int min = 62;
	for(i=0;i<8;i++){
	    for(j=0;j<8;j++){
		      if(args[i][j] != 0){
            if(args[i][j] <= min) min = args[i][j];
          }
        }
      }
  return min;
}

//配列の0以外の最大値を返す
int Max(int args[8][8]){
	int max = 1;
	for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(args[i][j] != 0){
          if(args[i][j]>=max) max = args[i][j];
        }
    }
	}
	return max;
}

//オセロAI
void AI(){
    int score[8][8] = {{0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0},
                 {0, 0, 0, 0, 0, 0, 0, 0}};

	int nullboard = 0; //石が置かれていないマスの数
	for(i=0;i<8;i++){
		for(j=0;j<8;j++){
			if(board[i][j] == 0) nullboard++;
        }
    }
        //1マスごとに取れる数をscore配列に格納
        for(i=0;i<8;i++){
		    for(j=0;j<8;j++){
			    if(flip_count(j, i) != 0){
                    score[i][j] = flip_count(j, i)+distance(j, i);
                }
			    else score[i][j] = 0;
            }
        }

	    //前半は石を取らず、中心に置く
        if(nullboard >= 15){
		    int minscore = Min(score);
		    int x = 0;
		    int y = 0;
            while(minscore != score[y][x] || score[y][x] == 0){
				x++;
				if(x==8){
				    x=0;
				    y++;
                }
            }
		    //角は最優先
		    if(score[0][0] != 0) flip(0,0);
            else if(score[0][7] != 0) flip(7,0);
		    else if(score[7][7] != 0) flip(7,7);
		    else if(score[7][0] != 0) flip(0,7);
	        else{
                flip(x,y);
            }
        }
        //後半は石を取り、外側に置く
	    else{
		    int maxscore = Max(score);
            int x = 0;
            int y = 0;

            while(maxscore != score[y][x] || score[y][x] == 0){
                x++;
                if(x==8){
                    x=0;
                    y++;
                }
            }

            //角は最優先
		    if(score[0][0] != 0) flip(0,0);
            else if(score[0][7] != 0) flip(7,0);
            else if(score[7][7] != 0) flip(7,7);
            else if(score[7][0] != 0) flip(0,7);
            else{
                flip(x,y);
            }
        }
    }

//終了判定
int isEnd(){
  nullboard = 0;
  countwhite = 0;
  countblack = 0;
for(i=0;i<8;i++){
    for(j=0;j<8;j++){
        if(board[i][j] == 0) nullboard+=1;
            else if(board[i][j]== 1){
               countwhite+=1;
            }
        else if(board[i][j]==-1){
            countblack+=1;
          }
        }
      }
      if(nullboard==0 || countwhite==0 || countblack==0) return 1;
      else return 0;
    }

//石を置けるかどうかの判定
int cantPut(){
  for(i=0;i<8;i++){
      for(j=0;j<8;j++){
        if(flip_count(j, i)!=0){
          return 0;
        }
      }
    }
    return 1;
}


//main部分
int main(void){
    int put_x, put_y;

    printf("AIを倒そう！あなたは◯の石です。\n");
    draw();
    //盤面が埋まるまで繰り返す
    while(isEnd()==0){
      //石が置けなかったら相手のターンになる
      if(cantPut()==1) turn = -1*turn;
        if(turn==1){
            printf("あなたの番です！座標を入力してください。\n");
            printf("<(例) x座標が0、y座標が1の場所に置きたい場合: 0 1>\n");
            scanf("%d %d", &put_x, &put_y);
            if(flip_count(put_x, put_y)!=0) flip(put_x, put_y);
            else printf("その座標には置けません。\n");
        }else{
            printf("AIの番です。\n");
            AI();
        }
    }
    printf("あなた: %d 個\n", countwhite);
    printf("AI: %d 個\n", countblack);
    if(countwhite>countblack) printf("あなたの勝ちです！\n");
    else printf("あなたの負けです...\n");
}
