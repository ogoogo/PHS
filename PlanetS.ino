#define LTRIGHT 2
#define LTLEFT 3
#define RIGHT 4
#define FRONT 5
#define LEFT 6

#define IN1R 7
#define IN2R 8
#define IN1L 9
#define IN2L 10
#include <vector>
bool going = true;
int wayNumber = 1;
int wayNumberFirst = 1;
int wayNumberSecond = 0;
std::vector<std::vector<int> > intersections;
std::vector<int> currentIntersection(7);



void setup(){
    Serial.begin(9600);
    pinMode(LTRIGHT, INPUT);
    pinMode(LTLEFT, INPUT);
    pinMode(RIGHT, INPUT);
    pinMode(FRONT, INPUT);
    pinMode(LEFT, INPUT);
    pinMode(IN1R, OUTPUT);
    pinMode(IN2R, OUTPUT);
    pinMode(IN1L, OUTPUT);
    pinMode(IN2L, OUTPUT);

}

void loop(){
    linetrace();
    if (going){
        if (/*カラーセンサー感知あり*/){

        
            if(colorCheck()=-1){
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
    goStraightALittle();

    if(digitalRead(LTRIGHT)==LOW && digitalRead(LTLEFT)==HIGH){
        digitalWrite(IN1R, HIGH);
        digitalWrite(IN2R, LOW);
        digitalWrite(IN1L, LOW);
        digitalWrite(IN2L, HIGH);
        delay(500);
    }else if(digitalRead(LTRIGHT)==HIGH && digitalRead(LTLEFT)==LOW){
        digitalWrite(IN1R, LOW);
        digitalWrite(IN2R, HIGH);
        digitalWrite(IN1L, HIGH);
        digitalWrite(IN2L, LOW);
        delay(500);
    }
}

void ohajiki(){
//おはじきとうか
}

std::vector<int> findWay(std::vector<int> vector){
//交差点からの道情報を格納させる
    if (digitalRead(RIGHT)==HIGH){
        vector[1]=1;
    }
    if (digitalRead(FRONT)==HIGH){
        vector[2]=1;
    }
    if (digitalRead(LEFT)==HIGH){
        vector[3]=1;
    }
    return vector;
}

void turn(int u){
    //1だったら右に、3だったら左に回転
    if (u==1){
        digitalWrite(IN1R, HIGH);
        digitalWrite(IN2R, LOW);
        digitalWrite(IN1L, LOW);
        digitalWrite(IN2L, HIGH);
        delay(2800);
    }else if(u==3){
        digitalWrite(IN1R, LOW);
        digitalWrite(IN2R, HIGH);
        digitalWrite(IN1L, HIGH);
        digitalWrite(IN2L, LOW);
        delay(2800);
    }

}

void goStraightALittle(){
    //少し進めるだけ
    digitalWrite(IN1R, LOW);
    digitalWrite(IN2R, HIGH);
    digitalWrite(IN1L, LOW);
    digitalWrite(IN2L, HIGH);
    delay(1000);
}

void uTurn(){
    //Uターンさせる。出力センサとかモータの向きを全部ここで反転

}

int findIntersection(int number){
    //wayNumberから、配列の番号を出力
    for (int i=0, i<=instructions.size(); i++){
        if (instructions[i][0]==number){
            return i;
        }
    }
    
}

int colorCheck(){
    int key;
    return key;
    //当てはまるkeyなければ-1を返す
}