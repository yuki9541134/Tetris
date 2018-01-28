#include <stdio.h>
#include <stdlib.h>


void initialize();
void newBlock();
void fieldPrint();
void blockmove();
void movedown();
void moveleft();
void moveright();
void rotation();
int isCollision();
int isFixed();
void fixBlock();
void clearLine();

void stageInPreStage();
void preStageInStage();




int stage[21][12];
int preStage[21][12];

int block[4][4];
int preBlock[4][4];
int selectedBlock[4][4][4];
       
int carveBlock[4][4][4]={
  
  {
  {0,0,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,1,0}
  },
  
  {
  {0,0,0,0},
  {0,0,0,1},
  {0,1,1,1},
  {0,0,0,0}
  },
  
  {
  {0,1,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,0,0}
  },
  
  {
  {0,0,0,0},
  {1,1,1,0},
  {1,0,0,0},
  {0,0,0,0}
  }
  
};

int squareBlock[4][4][4]={
  
  {
  {0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}
  },
  
  {
  {0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}
  },
  
  {
  {0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}
  },
  
  {
  {0,0,0,0},
  {0,1,1,0},
  {0,1,1,0},
  {0,0,0,0}
  }
  
};

int stickBlock[4][4][4]={
  
  {
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0},
  {0,1,0,0}
  },
  
  {
  {0,0,0,0},
  {0,0,0,0},
  {1,1,1,1},
  {0,0,0,0}
  },
  
  {
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0},
  {0,0,1,0}
  },
  
  {
  {0,0,0,0},
  {1,1,1,1},
  {0,0,0,0},
  {0,0,0,0}
  }
  
};

int triangleBlock[4][4][4]={
  
  {
  {0,0,0,0},
  {0,0,1,0},
  {0,1,1,1},
  {0,0,0,0}
  },
  
  {
  {0,0,0,0},
  {0,0,1,0},
  {0,1,1,0},
  {0,0,1,0}
  },
  
  {
  {0,0,0,0},
  {1,1,1,0},
  {0,1,0,0},
  {0,0,0,0}
  },
  
  {
  {0,1,0,0},
  {0,1,1,0},
  {0,1,0,0},
  {0,0,0,0}
  }
  
};




int command;

int x,y,z;

/*ブロックの位置座標を示す*/
int dx;
int dy;


int randa=0;

int isClear;
int isFixedd;



/**********************************************************************************************/
int main(){


  /*初期設定*/
 initialize();

 while(isClear==0){
   isFixedd=0;
   newBlock();
   
   while(isFixedd==0){
     fieldPrint();
     blockmove();
   }
   
 }
  
 return 0;

}

/**********************************************************************************************/
/*初期設定*/
void initialize(){

  
  isClear=0;
  isFixedd=0;

  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      if(x==0 || y==20 || x==11){
	stage[y][x] = 9;
      }
      else{
	stage[y][x] = 0;
      }
    }
  }

}

/*****************************************************************************************************/
void newBlock(){

  dx=3;
  dy=0;

  randa += 1;


  /*ブロックの種類*/
  
 int selectNumber = rand() % 4;
 
 for(z=0;z<4;z++){
   for(y=0;y<4;y++){
     for(x=0;x<4;x++){
       if(selectNumber==0){
	 selectedBlock[z][y][x]=carveBlock[z][y][x];
       }
       if(selectNumber==1){
	 selectedBlock[z][y][x]=squareBlock[z][y][x];
       }
       if(selectNumber==2){
	 selectedBlock[z][y][x]=stickBlock[z][y][x];
       }
       if(selectNumber==3){
	 selectedBlock[z][y][x]=triangleBlock[z][y][x];
       }
       
     }
   }
 }
 

  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      block[y][x] = selectedBlock[randa%4][y][x];
    }
  }

  
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      stage[y+dy][x+dx] += block[y][x];
    }
  }

}

/**************************************************************************************/
/*画面の表示*/
void fieldPrint(){
  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      if(stage[y][x]==0){
        printf("　");
      }else if(stage[y][x]==1){
        printf("□");
      }else if(stage[y][x]==5){
        printf("□");
      }else if(stage[y][x]==9){
        printf("■");
      }else{
	printf("?");
      }
    }
    printf("\n");
  }

  return;
}

/*********************************************************************************************/
/*ブロックの移動*/
void blockmove(){
  
  printf("コマンドを入力:");
  scanf("%d",&command);

  if(command==2) movedown();
  if(command==3) moveright();
  if(command==1) moveleft();
  if(command==5) rotation();

}

/**********************************************************************************************/
void movedown(){
  
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      stage[y+dy][x+dx] += -block[y][x];  /*動かす前のブロックを消去する*/
    }
  }

  dy += 1;

  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      stage[y+dy][x+dx] += block[y][x];
    }
  }

  if(isFixed()==1){
    clearLine();
  }
  

}


/************************************************************************************************/
void moveleft(){

  /*仮想ステージとブロックに現在のステージとブロックを代入*/
  stageInPreStage();
    
  /*動かす前のブロックを消去する*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += -preBlock[y][x];  
    }
  }

  dx += -1;

  /*入れ替えたブロックをステージに入れる*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += preBlock[y][x];
    }
  }
    
  if(isCollision()==0) {
    randa += 1;
    preStageInStage();
  }

  if(isCollision()==1) {
    dx += 1;
  }



  if(isFixed()==1){
    clearLine();
  }
  
}


/******************************************************************************************************/
void moveright(){
   /*仮想ステージとブロックに現在のステージとブロックを代入*/
  stageInPreStage();
    
  /*動かす前のブロックを消去する*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += -preBlock[y][x];  
    }
  }

  dx += 1;

  /*入れ替えたブロックをステージに入れる*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += preBlock[y][x];
    }
  }
    
  if(isCollision()==0) {
    randa += 1;
    preStageInStage();
  }

  if(isCollision()==1) {
    dx += -1;
  }



  if(isFixed()==1){
    clearLine();
  }
  
 

}


/*****************************************************************************************************/
void rotation(){


  /*仮想ステージとブロックに現在のステージとブロックを代入*/
  stageInPreStage();
    
  /*動かす前のブロックを消去する*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += -preBlock[y][x];  
    }
  }
    
  /*ブロックを回転*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preBlock[y][x] = selectedBlock[(randa+1)%4][y][x];
    }
  }

  /*入れ替えたブロックをステージに入れる*/
  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preStage[y+dy][x+dx] += preBlock[y][x];
    }
  }
    
  if(isCollision()==0) {
    randa += 1;
    preStageInStage();
  }

  if(isFixed()==1){
    clearLine();
  }
 
}


/*****************************************************************************************************/
int isCollision(){
  
  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      if(preStage[y][x]!=0 && preStage[y][x]!=1 && preStage[y][x]!=5 && preStage[y][x]!=9 ) {
	return 1;
      }
    }
  }
 
  return 0;
  
}
/*****************************************************************************************************/
void stageInPreStage(){
  
  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      preStage[y][x]=stage[y][x];
    }
  }

  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      preBlock[y][x]=block[y][x];
    }
  }
  
}
/*****************************************************************************************************/
void preStageInStage(){
  
  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      stage[y][x]=preStage[y][x];
    }
  }

  for(y=0;y<4;y++){
    for(x=0;x<4;x++){
      block[y][x]=preBlock[y][x];
    }
  }
      
}

/*****************************************************************************************************/
int isFixed(){

  for(y=0;y<20;y++){
    for(x=1;x<11;x++){
      if(stage[y][x]==1 && (stage[y+1][x]==5 ||  stage[y+1][x]==9 )){
        isFixedd = 1;
	fixBlock();
        return 1;
      }  
    }
  }


  return 0;
}


/*****************************************************************************************************/
void fixBlock(){
  
  for(y=0;y<21;y++){
    for(x=0;x<12;x++){
      if(stage[y][x]==1){
        stage[y][x] = 5;
      }  
    }
  }

}


/*****************************************************************************************************/
void clearLine(){
  
   for(y=0;y<20;y++){
     
     int isSpace=0;
	
     for(x=1;x<11;x++){
       if(stage[y][x] == 0) isSpace=1;
     }

     if(isSpace==0){
       int line=y;
       for(y=line;y>0;y--){
	 for(x=1;x<11;x++){
	   stage[y][x]=stage[y-1][x];
         }
       }
       for(x=1;x<11;x++){
         stage[0][x]=0;
       }
     }
   
   }

}
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
/*****************************************************************************************************/
