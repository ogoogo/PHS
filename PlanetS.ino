
#include <vector>
bool going = true;
int wayNumber = 1;
int wayNumberFirst = 1;
int wayNumberSecond = 0;
std::vector<std::vector<int> > intersections;
std::vector<int> currentIntersection(7);



void setup(){

}

void loop(){
    linetrace();
    if (going){
        if (/*カラーセンサー感知あり*/){

        
            if(colorCheck()==-1){
                std::vector<int> currentIntersection(7,0);
                currentIntersection[0]=wayNumber;
                //currentIntersection[4~6]に色情報代入
                currentIntersection=findWay(currentIntersection);
                intersections.push_back(currentIntersection);

                if (currentIntersection[1]==1){
                    wayNumber=wayNumber*10+1;
                    turn(1);
                    goStraightALittle();
                }else if (currentIntersection[2]==1){
                    wayNumber=wayNumber*10+2;
                    goStraightALittle();
                }else if (currentIntersection[3]==1){
                    wayNumber=wayNumber*10+3;
                    turn(3);
                    goStraightALittle();
                }else{
                    going=false;
                    uTurn();
                    goStraightALittle();
                }
                
            }else{
                if (intersections[colorCheck()][3]==1){
                    intersections[colorCheck()][3]=0;
                }else{
                    intersections[colorCheck()][2]=0;
                }
                going=false;
                uTurn();
                goStraightALittle();
            }

       
        }
    }else{
        ohajiki();
        if(/*カラーセンサー感知あり*/){
            if (wayNumber==1){
                //終了！！！！！
            }else{
                wayNumberFirst=wayNumber%10;
                wayNumber=wayNumber/10;
                if (wayNumberFirst==1){
                    intersections[findIntersection(wayNumber)][1]=0;
                    currentIntersection=intersections[findIntersection(wayNumber)];
                    if(currentIntersection[2]==1){
                        turn(1);
                        wayNumber=wayNumber*10+2;
                        going=true;
                        goStraightALittle();
                    }else if(currentIntersection[3]==1){
                        wayNumber=wayNumber*10+3;
                        going=true;
                        goStraightALittle();
                    }else{
                        turn(3);
                        goStraightALittle();
                    }

                }else if(wayNumberFirst==2){
                    intersections[findIntersection(wayNumber)][2]=0;
                    currentIntersection=intersections[findIntersection(wayNumber)];
                    if(currentIntersection[3]==1){
                        turn(1);
                        wayNumber=wayNumber*10+3;
                        going=true;
                        goStraightALittle();
                    }else{
                        goStraightALittle();
                    }
                }else{
                    intersections[findIntersection(wayNumber)][3]=0;
                    currentIntersection=intersections[findIntersection(wayNumber)];
                    turn(1);
                    goStraightALittle();
                }

            }
        }

    }

    
}

void linetrace(){
//ライントレース
}

void ohajiki(){
//おはじきとうか
}

std::vector<int> findWay(std::vector<int> vector){
//交差点からの道情報を格納させる
    return vector;
}

void turn(int u){
    //1だったら右に、3だったら左に回転

}

void goStraightALittle(){
    //少し進めるだけ

}

void uTurn(){
    //Uターンさせる。出力センサとかモータの向きを全部ここで反転

}

int findIntersection(int number){
    //wayNumberから、配列の番号を出力
    int key;
    return key;
}

int colorCheck(){
    int key;
    return key;
    //当てはまるkeyなければ-1を返す
}