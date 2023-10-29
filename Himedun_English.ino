#include <Arduboy2.h>
#include "bitmap.h"
//#include "misaki_font.h"

Arduboy2 arduboy;


#define ARDBITMAP_SBUF arduboy.getBuffer()//突っ込むバッファ
#include <ArdBitmap.h>
ArdBitmap<WIDTH, HEIGHT> ardbitmap;//ビットマップの奴

//立ち絵切り替え
uint8_t T_no=0;
//サイコロ
uint8_t DR[3]={0,0,0};
uint8_t DT=0;
int DX[3]={0,0,0};
int DY[3]={0,0,0};

//便利君
int B=0;
uint8_t RR=0;

uint8_t DC=0;

uint8_t tktk=0;//とことこ

uint8_t FLR=0;//フロア分岐確認

//アイテム斧
uint8_t ItemA=0;
//アイテム盾
uint8_t ItemB=0;
//アイテム目
uint8_t ItemC=0;
//アイテム呪い
uint8_t ItemD=0;

//目隠し用
uint8_t QR=0;

int DAME=0;
//バトルフェイズ 0:無し 1:技選択 2:攻撃エフェクト 3:敵攻撃エフェクト 4:自分ダイス判定 5:敵ダイス判定 6:勝利判定 7:敵出現 8:スタート画面 9:部屋が分かれてる 10:消える 11-13:罠 20: 30: 100:ゲームオーバー
//さきゅばす はーぴー うぃっち どらごん ふぇありー すらいむ しょくぶつ
uint8_t Mty=7;
uint8_t MtyHP[8]={150,120,100,90,50,50,60,0};
uint8_t MtyN1[8]={2,2,2,3,2,1,3,0};
uint8_t MtyN2[8]={2,2,1,3,2,1,2,0};
uint8_t MtyN3[8]={3,4,2,1,1,4,3,0};

//1:敵 2:罠 3:宝箱 4:店 5:シスター
//uint8_t MAPA[21]={1,2,1,4,1,2,1,5,1,2,1,4,1,2,1,3,1,2,1,3};
//uint8_t MAPB[21]={1,2,1,3,1,2,1,5,1,2,1,3,1,2,1,3,1,2,1,3};
//uint8_t MAPA[21][2]={{1,2,1,4,1,2,2,5,2,2,1,4,1,1,3,3,3,2,1,3,1},{1,2,1,3,1,2,3,5,2,2,1,3,1,1,3,3,1,2,1,3,1}};
//uint8_t MAPA[22][2]={{1,1},{2,2},{1,1},{3,4},{1,1},{2,2},{2,3},{3,3},{2,2},{2,2},{1,1},{4,3},{1,1},{1,1},{3,3},{3,3},{3,1},{2,2},{1,1},{5,5},{1,1},{1,1}};

//uint8_t STMAPA[21][2]={{1,2,1,4,1,2,2,5,2,2,1,4,1,1,3,3,3,2,1,3,1},
//                       {1,2,1,3,1,2,3,5,2,2,1,3,1,1,3,3,1,2,1,3,1}};

uint8_t STMAPA[21][2]={{1,1},{3,2},{2,1},{1,4},
                       {3,1},{2,2},{1,2},{3,5},
                       {1,2},{1,2},{2,1},{2,3},
                       {2,1},{1,1},{3,3},{3,4},
                       {1,1},{2,1},{1,1},{5,1},{1,1}};
uint8_t LR=0;

uint8_t BF=8;

int HP=300;
int NHP=300;
int MHP=1;
int NMHP=1;
int AP=2;
int MP=10;

uint8_t NPC=0;

uint8_t LEVEL=0;

uint8_t F=0;

uint8_t ATKty=0;

uint8_t seiko=0;

uint8_t SEL=0;

uint8_t L=0;

uint8_t KAIHI=0;

//攻撃アニメーション
uint8_t ANT=5;//8;
//エフェクト種類
uint8_t EF=0;//26;
int AX=0;
int AX_T=0;
int AY_T=0;

/*
//おの
PROGMEM const uint8_t ward1[] ={ 0xf0, 0x4c,0x70, };
//だめーじ
PROGMEM const uint8_t ward2[] ={ 0xf0, 0x62,0x83,0xee,0x5a, };
//だいす　はんてい
PROGMEM const uint8_t ward3[] ={ 0xf0, 0x62,0x46,0x5b,0x00,0x71,0x95,0x68,0x46, };
//きっく
PROGMEM const uint8_t ward4[] ={ 0xf0, 0x4f,0x65,0x51, };
//まほう
PROGMEM const uint8_t ward5[] ={ 0xf0, 0x80,0x7d,0x48, };
//さきゅばす
PROGMEM const uint8_t M_SA[] ={ 0xf0, 0x57,0x4f,0x87,0x72,0x5b, };
//はーぴー
PROGMEM const uint8_t M_H[] ={ 0xf0, 0x71,0xee,0x76,0xee, };
//うぃっち
PROGMEM const uint8_t M_W[] ={ 0xf0, 0x48,0x45,0x65,0x63, };
//どらごん
PROGMEM const uint8_t M_D[] ={ 0xf0, 0x6b,0x8b,0x56,0x95, };
//ふぇありー
PROGMEM const uint8_t M_F[] ={ 0xf0, 0x77,0x49,0x44,0x8c,0xee, };
//すらいむ
PROGMEM const uint8_t M_SU[] ={ 0xf0, 0x5b,0x8b,0x46,0x82, };
//しょくぶつ
PROGMEM const uint8_t M_SI[] ={ 0xf0, 0x59,0x89,0x51,0x78,0x66, };
//　おの　　きっく　まほう
PROGMEM const uint8_t W_atk[] ={ 0xf0, 0x00,0x4c,0x70,0x00,0x00,0x4f,0x65,0x51,0x00,0x80,0x7d,0x48, };
//→
PROGMEM const uint8_t Migi[] ={ 0xf0, 0x35, };
//こうげき
PROGMEM const uint8_t atk[] ={ 0xf0, 0x55,0x48,0x54,0x4f, };
//てきの
PROGMEM const uint8_t teki[] ={ 0xf0, 0x68,0x4f,0x70, };
//せいこう！！
PROGMEM const uint8_t good[] ={ 0xf0, 0x5d,0x46,0x55,0x48,0x09,0x09, };
//しっぱい……
PROGMEM const uint8_t bad[] ={ 0xf0, 0x59,0x65,0x73,0x46,0xed,0xed, };
//くりてぃかる
PROGMEM const uint8_t sugoi[] ={ 0xf0, 0x51,0x8c,0x68,0x45,0x4d,0x8d, };
//てきをたおした
PROGMEM const uint8_t taosu[] ={ 0xf0, 0x68,0x4f,0x94,0x61,0x4c,0x59,0x61, };
//てきがあらわれた
PROGMEM const uint8_t deru[] ={ 0xf0, 0x68,0x4f,0x4e,0x44,0x8b,0x91,0x8e,0x61, };
//をよけた
PROGMEM const uint8_t yokeru[] ={ 0xf0, 0x94,0x8a,0x53,0x61, };

//ひめだん！
PROGMEM const uint8_t title1[] ={ 0xf0, 0x74,0x83,0x62,0x95,0x09, };
//のめいきゅう
PROGMEM const uint8_t title2[] ={ 0xf0, 0x70,0x83,0x46,0x4f,0x87,0x48, };

//さゆうにへやがわかれてる
PROGMEM const uint8_t wakare1[] ={ 0xf0, 0x57,0x88,0x48,0x6d,0x7a,0x86,0x4e,0x91,0x4d,0x8e,0x68,0x8d, };
//ひだりにいく　みぎにいく
PROGMEM const uint8_t wakare2[] ={ 0xf0, 0x74,0x62,0x8c,0x6d,0x46,0x51,0x00,0x81,0x50,0x6d,0x46,0x51, };

//とらっぷだ！
PROGMEM const uint8_t wana[] ={ 0xf0, 0x6a,0x8b,0x65,0x79,0x62,0x09, };

//のろいをうけた
PROGMEM const uint8_t noroi[] ={ 0xf0, 0x70,0x8f,0x46,0x94,0x48,0x53,0x61, };

/*
//たからばこがある
PROGMEM const uint8_t takara1[] ={ 0xf0, 0x61,0x4d,0x8b,0x72,0x55,0x4e,0x44,0x8d, };
//あける　あけない
PROGMEM const uint8_t takara2[] ={ 0xf0, 0x44,0x53,0x8d,0x00,0x44,0x53,0x6c,0x46, };
*/
/*
//くすりだ！
PROGMEM const uint8_t BIN1[] ={ 0xf0, 0x51,0x5b,0x8c,0x62,0x09, };
//くすりをのんで
PROGMEM const uint8_t BIN2[] ={ 0xf0, 0x51,0x5b,0x8c,0x94,0x70,0x95,0x69, };
//かいふくした
PROGMEM const uint8_t BIN3[] ={ 0xf0, 0x4d,0x46,0x77,0x51,0x59,0x61, };

//しすたー
PROGMEM const uint8_t NPC_S_W[] ={ 0xf0, 0x59,0x5b,0x61,0xee, };
//てんいんさん
PROGMEM const uint8_t NPC_W_W[] ={ 0xf0, 0x68,0x95,0x46,0x95,0x57,0x95, };
//いらっしゃいませ
PROGMEM const uint8_t NPC_W_W1[] ={ 0xf0, 0x46,0x8b,0x65,0x59,0x85,0x46,0x80,0x5d, };

//いどうちゅう……
PROGMEM const uint8_t tokotoko[] ={ 0xf0, 0x46,0x6b,0x48,0x63,0x87,0x48,0xed,0xed, };

//なにをかいますか？
PROGMEM const uint8_t NPC_W_W2[] ={ 0xf0, 0x6c,0x6d,0x94,0x4d,0x46,0x80,0x5b,0x4d,0x08, };
//おの　たて　くすり
PROGMEM const uint8_t NPC_W_W3[] ={ 0xf0, 0x4c,0x70,0x00,0x61,0x68,0x00,0x51,0x5b,0x8c, };
//ありがとうございました
PROGMEM const uint8_t NPC_W_W4[] ={ 0xf0, 0x44,0x8c,0x4e,0x6a,0x48,0x56,0x58,0x46,0x80,0x59,0x61, };

//いのりをささげます
PROGMEM const uint8_t NPC_S_W1[] ={ 0xf0, 0x46,0x70,0x8c,0x94,0x57,0x57,0x54,0x80,0x5b, };
//てあてをしますね
//PROGMEM const uint8_t NPC_S_W2[] ={ 0xf0, 0x68,0x44,0x68,0x94,0x59,0x80,0x5b,0x6f, };
//かみのごかごを
PROGMEM const uint8_t NPC_S_W3[] ={ 0xf0, 0x4d,0x81,0x70,0x56,0x4d,0x56,0x94, };
//きょうはどのようなようけんで？
PROGMEM const uint8_t NPC_S_W4[] ={ 0xf0, 0x4f,0x89,0x48,0x71,0x6b,0x70,0x8a,0x48,0x6c,0x8a,0x48,0x53,0x95,0x69,0x08, };
//かいふく　のろいをといて
PROGMEM const uint8_t NPC_S_W5[] ={ 0xf0, 0x4d,0x46,0x77,0x51,0x00,0x70,0x8f,0x46,0x94,0x6a,0x46,0x68, };

//わたくしのかちよ！
PROGMEM const uint8_t ED_W[] ={ 0xf0, 0x91,0x61,0x51,0x59,0x70,0x4d,0x63,0x8a,0x09, };
*/
/*
//姫立ち絵10
uint8_t hime_A;
uint8_t hime_A_M;
//姫立ち絵10
uint8_t hime_B;
uint8_t hime_B_M;
//姫立ち絵10
uint8_t hime_C;
uint8_t hime_C_M;
//姫立ち絵10
uint8_t hime_D;
uint8_t hime_D_M;
//姫立ち絵10
uint8_t hime_E;
uint8_t hime_E_M;
//姫立ち絵10
uint8_t hime_F;
uint8_t hime_F_M;
//姫立ち絵10
uint8_t hime_G;
uint8_t hime_G_M;
//姫立ち絵10
uint8_t hime_H;
uint8_t hime_H_M;
*/

/*
//日本語
void drawText(uint8_t x, uint8_t y, const uint8_t *mes, uint8_t cnt,uint8_t Wb)
{
  uint8_t pb;
  uint8_t page;
  uint8_t screen_start = 0;
  uint8_t screen_end = 128;
  

  if (x < screen_start) {
    x = screen_start;
  }
  
  for (uint8_t i = 0; i < cnt; i++) {
    pb = pgm_read_byte_near(mes + i);

    switch (pb) {
      case MISAKI_FONT_F0_PAGE:
        page = MISAKI_FONT_F0_PAGE;
        continue;
      case MISAKI_FONT_F1_PAGE:
        page = MISAKI_FONT_F1_PAGE;
        continue;
      case MISAKI_FONT_F2_PAGE:
        page = MISAKI_FONT_F2_PAGE;
        continue;
    }

    if (!page) {
      continue;
    }

    switch (page) {
      #ifdef MISAKI_FONT_F0_H
        case MISAKI_FONT_F0_PAGE:
          if (pb > MISAKI_FONT_F0_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f0[ pb ], MISAKI_FONT_F0_W, 8, Wb);
          x = x + 8;    
          break;
      #endif
      #ifdef MISAKI_FONT_F1_H
        case MISAKI_FONT_F1_PAGE:
          if (pb > MISAKI_FONT_F1_SIZE) {
            continue;
          }      
          if ((x + 4) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f1[ pb ], MISAKI_FONT_F1_W, 8, Wb);
          arduboy.drawBitmap(x + 3, y, misaki_font_0x00, 1, 8, Wb);
          x = x + 4;  
          break;
      #endif
      #ifdef MISAKI_FONT_F2_H
        case MISAKI_FONT_F2_PAGE:
          if (pb > MISAKI_FONT_F2_SIZE) {
            continue;
          }      
          if ((x + 8) > screen_end) {
            x = screen_start;   
            y = y + 8;
          }
          arduboy.drawBitmap(x, y,  misaki_font_f2[ pb ], MISAKI_FONT_F2_W, 8, Wb);
          arduboy.drawBitmap(x + 7, y, misaki_font_0x00, 1, 8, Wb);
          x = x + 8;    
          break;
      #endif
    }
  }
}
*/


//ダイスふる
uint8_t daiceR(uint8_t R1)
{
  uint8_t R2;
  R2=random(6);
  if (R2==R1){R2=(R2+1)%6;}

  return R2;
  }

//現れるアニメ
void ANIME1() {
EF=26;ANT=8;T_no=0;
}
//倒すアニメ
void ANIME2() {
EF=25;ANT=8;T_no=0;
}
//アニメ無し
void ANIME0() {
EF=0;ANT=1;T_no=0;Mty=7;
}

void setup() {
  // put your setup code here, to run once:

  arduboy.begin();
  arduboy.setFrameRate(60);
  arduboy.initRandomSeed();
  
  
}

void loop() {
  // put your main code here, to run repeatedly:
    if (!arduboy.nextFrame()) return;
  arduboy.clear();

  
AX=0;
AX_T=0;
AY_T=0;

if (NHP<0){NHP=0;}
if (NMHP<0){NMHP=0;}
  for (uint8_t i = 0; i < 4; i++) {
if (NHP<HP){HP--;}
//if (NHP>HP){HP++;}
if (NMHP<MHP){MHP--;}
if (NMHP>MHP){MHP++;}
  }
  arduboy.pollButtons();
if (arduboy.justPressed(LEFT_BUTTON)){
  //T_no=(T_no+1)%8;
  if ((BF!=9)and(BF!=41)){SEL=(SEL+2)%3;}else{SEL=(SEL+1)%2;}
  if (BF==8){LEVEL=(LEVEL+2)%3;ANT=4;}
  
}
  
if (arduboy.justPressed(RIGHT_BUTTON)){
  //DR=(DR+1)%6;
  //DR=random(6);
  //DR=daiceR(DR);
  //DT=25;
  if ((BF!=9)and(BF!=41)){SEL=(SEL+1)%3;}else{SEL=(SEL+1)%2;}
  if (BF==8){LEVEL=(LEVEL+1)%3;ANT=4;}
}


if (arduboy.justPressed(A_BUTTON)){
  if (BF==8){
  T_no=(T_no+1)%8;
  }
  if ((BF>=100)and(ANT==0)){BF=8;EF=0;ANT=5;T_no=0;}
}
if (arduboy.justPressed(B_BUTTON)){
  //DT=25;
  if ((ANT==0)and(BF!=6)){//戦闘系
    if (NHP>0){
    if (NMHP>0){
  if ( BF==7){BF=1;EF=0;ANT=1;}
  else if ((BF==1)and(SEL==0)){EF=21;ANT=32;T_no=0;BF=4;DC=2;DT=25;ATKty=0;}//6+1=7 >2
  else if ((BF==1)and(SEL==1)){EF=2;ANT=12;T_no=2;BF=2;ATKty=1;DAME=10*MtyN2[Mty];}//20
  else if ((BF==1)and(SEL==2)and(MP!=0)){EF=3;ANT=16;T_no=3;BF=2;ATKty=2;DAME=15*MtyN3[Mty];MP--;}//30
  else if ( BF==4){EF=1;ANT=12;T_no=1;BF=2;DC=0;
  DAME=5*MtyN1[Mty];//10
  if(DR[1]+DR[0]+2>=AP){DAME=20*MtyN1[Mty];}//40
  if(DR[1]+DR[0]+2==12){DAME=30*MtyN1[Mty];AP=0;}//60
  
  }
  else if (BF==2){EF=22;ANT=32;T_no=0;BF=5;DC=3;DT=25;}//if (ATKty==0){AP=AP+seiko;}
  else if (BF==5){EF=11;ANT=20;T_no=0;BF=3;DAME=(DR[2]+DR[1]+DR[0]+3)*(1+ItemD);DC=0;}
  else if (BF==3){EF=0;ANT=1;T_no=0;BF=1;}
  KAIHI=daiceR(KAIHI);
  if (ATKty==1){KAIHI=0;}
    }else{BF=6;EF=25;ANT=8;}
  }else{BF=100;T_no=7;}
  }


  if ((BF==6)and(ANT==0)){//敵倒す
    Mty=7;NMHP=1;
    if (F==20){BF=101;T_no=0;}
    else{EF=0;ANT=1;T_no=0;BF=10;F++;}
    }
    
  //if ((BF==6)and(ANT==0)){EF=26;ANT=8;T_no=0;Mty=(Mty+6)%7;NMHP=MtyHP[Mty];BF=7;F++;}
  if (ANT==0){//イベント系
  if (BF==8){ANIME1();NPC=1;BF=9;SEL=0;}//EF=26;ANT=8;T_no=0;//Mty=7;
  else if (BF==9){ANIME2();Mty=7;BF=10;LR=SEL;SEL=0;FLR++;QR=random(4);}//EF=25;ANT=8;T_no=0;
  
  else if (BF==10){//フロア変更区間
      if ((FLR*4==F)and(F!=20)){ANIME1();Mty=7;NPC=1;BF=9;SEL=0;//EF=26;ANT=8;T_no=0;
      }else {
        Mty=7;SEL=0;//敵出現パターン20Fサキュバス Rハーピーからフェアリー L触手からウィッチ
    if(STMAPA[F][LR]==1){ANIME1();NPC=0;Mty=(3+random(4)-2*LR);
                         if (F==20){Mty=0;}
                         NMHP=MtyHP[Mty];BF=7;}//EF=26;ANT=8;T_no=0;
    if(STMAPA[F][LR]==2){ANIME1();NPC=2;BF=11;}//EF=26;ANT=8;T_no=0;
    if(STMAPA[F][LR]==3){ANIME1();NPC=3;BF=20;}//EF=26;ANT=8;T_no=0;
    if(STMAPA[F][LR]==4){ANIME1();NPC=5;BF=30;}//EF=26;ANT=8;T_no=0;
    if(STMAPA[F][LR]==5){ANIME1();NPC=6;BF=40;}//EF=26;ANT=8;T_no=0;
      }
    }
  
  else if (BF==11){RR=random(3);ATKty=0;
   if (RR!=2){EF=22;ANT=32;T_no=0;BF=12;DC=3;DT=25;}
   else{EF=11;ANT=20;T_no=0;BF=13;DAME=0;DC=0;KAIHI=1;}
  }
  else if (BF==12){EF=11;ANT=20;T_no=0;BF=13;DAME=(DR[2]+DR[1]+DR[0]+3)*(1+ItemD);DC=0;KAIHI=1;}
  else if (BF==13){ANIME2();Mty=7;BF=10;SEL=0;F++;if(RR==2){ItemD++;}}//EF=25;ANT=8;T_no=0;
  
  else if (BF==20){ANIME0();BF=21;AP=AP-2;}//EF=0;ANT=1;T_no=0;Mty=7;
  else if (BF==21){ANIME2();Mty=7;BF=10;SEL=0;F++;}//EF=25;ANT=8;T_no=0;
  
  else if (BF==30){ANIME0();BF=31;}//EF=0;ANT=1;T_no=0;Mty=7;
  else if (BF==31){ANIME0();BF=32;//EF=0;ANT=1;T_no=0;Mty=7;
    if (SEL==0){ItemA=1;}
    if (SEL==1){ItemB=1;}
    if (SEL==2){AP=AP-4;}}
  else if (BF==32){ANIME2();Mty=7;BF=10;SEL=0;F++;}//EF=25;ANT=8;T_no=0;

  else if (BF==40){ANIME0();BF=41;}//EF=0;ANT=1;T_no=0;Mty=7;
  
  else if (BF==41){ANIME0();BF=42;//EF=0;ANT=1;T_no=0;Mty=7;
    if (SEL==0){MP=MP+6;}
    if (SEL==1){ItemD=0;}}
  else if (BF==42){ANIME2();Mty=7;BF=10;SEL=0;F++;}//EF=25;ANT=8;T_no=0;
  }
  
  //EF=11;
  //ANT=16;
}

if ((BF==2)and(ANT==1)){if (ATKty==0){AP=AP+seiko;}}

if ((BF==8)and(ANT==3)){//リセット処理
  for (uint8_t i = 0; i < 40; i++) {
    RR=random(25);
    
    B=STMAPA[RR/5*4+i%4][i/20];
    STMAPA[RR/5*4+i%4][i/20]=STMAPA[RR%5*4+i%4][i/20];
    STMAPA[RR%5*4+i%4][i/20]=B;
    }
HP=300;
NHP=300;
MHP=1;
NMHP=1;
AP=2;
MP=10;
ItemA=0;
ItemB=0;
ItemC=0;
ItemD=0;
F=0;
Mty=7;
FLR=0;

if (LEVEL>=1){AP=random(6)+3;MP=AP;}
if (LEVEL==2){ItemD=1;}
}

//AP:MP-にならないようにする
if (AP<0){AP=0;}
if (MP<0){MP=0;}
if (AP>12){AP=12;}
if (MP>12){MP=12;}

//ダメージ判定
if ((EF>=1)and(EF<=3)and(ANT==1)){NMHP=NMHP-DAME;}
if ((EF>=11)and(EF<=13)and(ANT==1)){NHP=NHP-DAME;//魔力吸収
if ((ATKty==1)and(ItemB==1)and(DAME>=6)){MP++;}
}

arduboy.fillRect(0,0,128,64,1);
//攻撃揺れ
if ((EF>=1)and(EF<=3)and(ANT>=8)and(ANT<12)){AX=(12-ANT)*2;}
if ((EF>=1)and(EF<=3)and(ANT>=6)and(ANT<8)){AX=(ANT-6)*4;}
if ((EF==1)and(ANT<=4)and(seiko==1)){AX_T=(ANT%2)*2;}
if (((EF==2)or(EF==3))and(ANT<=4)){AX_T=(ANT%2)*2;}

if (EF==11){
if (ANT>=16){AX_T=(20-ANT)*2;}
if ((ANT>=14)and(ANT<16)){AX_T=(ANT-14)*4;}
if (ANT<=16){AX=((ANT%2)*2*(1-2*((ANT%4)/2)));
}
  if (ANT==16){T_no=6;}
  if (KAIHI==5){T_no=5;AX=0;DAME=0;}
  if ((ATKty==1)and(ANT==16)){T_no=4;DAME=DAME/2;}
  
  }

  for (uint8_t i = 0; i < DC; i++) {
DX[i]=0;DY[i]=0;
if (DT>0){
if (DT%10==1){//アイテム効果
  if ((BF==4)and(ItemA==1)and(i==1)){DR[1]=5-DR[1]%2;}
  else{DR[i]=daiceR(DR[i]);}}
DY[i]=(((5-(DT%10))*(5-(DT%10)))-25)/(3-DT/10);
DX[i]=DT;
}
  }
  
  if (BF==10){
    if (ANT==1){NPC=0;}//NPC消す
    tktk=(tktk+1)%8;
    }else {tktk=0;}
if (DT>0){DT--;}
//if (DT==0){DAME=DR[0];}

//テキスト

arduboy.setCursor(0,0);
arduboy.setTextColor(1);
arduboy.print("1F  HP:    \nMP:   DP:  ");
arduboy.setCursor(0,0);
arduboy.print(F+1);
if (F+1>=10){arduboy.setCursor(12,0);arduboy.print("F");};

if (F==20){arduboy.setCursor(0,0);arduboy.print("Last");}
arduboy.setCursor(42,0);
arduboy.print(HP);
arduboy.setCursor(18,8);
arduboy.print(MP);
arduboy.setCursor(54,8);
arduboy.print(AP);
 


  
//arduboy.setTextColor(1);
//arduboy.setCursor(0,48);
//  arduboy.print("ax attack  \n   damag   ");

arduboy.fillRect(0,48,64,16,0);
if ((EF>=1)and(EF<=3)){
if (EF==1){arduboy.setCursor(0,48);arduboy.print("Ax atk");}//drawText(0, 48, ward1, sizeof(ward1),WHITE);
if (EF==2){arduboy.setCursor(0,48);arduboy.print("Kick atk");}//drawText(0, 48, ward4, sizeof(ward4),WHITE);
if (EF==3){arduboy.setCursor(0,48);arduboy.print("Magic atk");}//drawText(0, 48, ward5, sizeof(ward5),WHITE);

//arduboy.setCursor(36,48);arduboy.print("atk");//drawText(24, 48, atk, sizeof(atk),WHITE);

arduboy.setCursor(18,56);arduboy.print("damage");//drawText(16, 56, ward2, sizeof(ward2),WHITE);
arduboy.setCursor(0,56);
  arduboy.print(DAME);
  
if (ANT>8){arduboy.fillRect(0,56,64,8,0);}
if (ANT<=8){arduboy.fillRect((8-ANT)*8,56,64-(8-ANT)*8,8,0);}

}
if (EF==11){
arduboy.setCursor(0,48);arduboy.print("Enemy atk");
//drawText(0, 48, teki, sizeof(teki),WHITE);
//drawText(24, 48, atk, sizeof(atk),WHITE);
if (KAIHI!=5){
arduboy.setCursor(18,56);arduboy.print("damage");//drawText(16, 56, ward2, sizeof(ward2),WHITE);
arduboy.setCursor(0,56);
  arduboy.print(DAME);
}else{

//drawText(0, 56, atk, sizeof(atk),WHITE);
arduboy.setCursor(0,56);arduboy.print("Avoid atk");//drawText(32, 56, yokeru, sizeof(yokeru),WHITE);
}
  
if (ANT>8){arduboy.fillRect(0,56,64,8,0);}
if (ANT<=8){arduboy.fillRect((8-ANT)*8,56,64-(8-ANT)*8,8,0);}
}
if (EF==21){//おの攻撃ダイス
if (ANT<=6){arduboy.setCursor(0,56);arduboy.print(DR[0]+1);}
if (ANT<=5){arduboy.setCursor(6,56);arduboy.print("+");}
if (ANT<=4){arduboy.setCursor(12,56);arduboy.print(DR[1]+1);}
if (ANT<=3){arduboy.setCursor(18,56);arduboy.print("=");}
if (ANT<=2){arduboy.setCursor(24,56);arduboy.print(DR[1]+DR[0]+2);}
if ((ANT<=1)and(DR[1]+DR[0]+2<AP)){arduboy.setCursor(36,56);arduboy.print("<");}
if ((ANT<=1)and(DR[1]+DR[0]+2>AP)){arduboy.setCursor(36,56);arduboy.print(">");}
if ((ANT<=1)and(DR[1]+DR[0]+2==AP)){arduboy.setCursor(36,56);arduboy.print("=");}
if (ANT<=1){arduboy.setCursor(42,56);arduboy.print(AP);}

if (ANT!=0){arduboy.setCursor(0,48);arduboy.print("Dice roll");//drawText(0, 48, ward3, sizeof(ward3),WHITE);
  }else{
    if (DR[1]+DR[0]+2!=12){
    if ((DR[1]+DR[0]+2<AP)){arduboy.setCursor(0,48);arduboy.print("Bad");seiko=0;}//drawText(0, 48, bad, sizeof(bad),WHITE);
    if ((DR[1]+DR[0]+2>=AP)){arduboy.setCursor(0,48);arduboy.print("Good");seiko=1;}//drawText(0, 48, good, sizeof(good),WHITE);
    }else{arduboy.setCursor(0,48);arduboy.print("Critical");seiko=1;}//drawText(0, 48, sugoi, sizeof(sugoi),WHITE);
  }
}
if (EF==25){//敵倒す
  arduboy.setCursor(0,48);arduboy.print("Enemy down");//drawText(0, 48, taosu, sizeof(taosu),WHITE);
  arduboy.fillRect((8-ANT)*8,48,64-(8-ANT)*8,8,0);
  AY_T=(8-ANT)*4;
  } 
  
if (EF==26){//敵現る
  if (BF!=11){
  arduboy.setCursor(0,48);arduboy.print("Enemy\n   appear");//drawText(0, 48, deru, sizeof(deru),WHITE);
  }
  arduboy.fillRect((8-ANT)*8,48,64-(8-ANT)*8,8,0);
  AY_T=(ANT)*4;
  } 

if (EF==22){//敵ダイス
arduboy.setCursor(0,48);arduboy.print("Enemy atk");
//drawText(0, 48, teki, sizeof(teki),WHITE);
//drawText(24, 48, atk, sizeof(atk),WHITE);
if (ANT<=6){arduboy.setCursor(0,56);arduboy.print(DR[0]+1);}
if (ANT<=5){arduboy.setCursor(6,56);arduboy.print("+");}
if (ANT<=4){arduboy.setCursor(12,56);arduboy.print(DR[1]+1);}
if (ANT<=3){arduboy.setCursor(18,56);arduboy.print("+");}
if (ANT<=2){arduboy.setCursor(24,56);arduboy.print(DR[2]+1);}
if (ANT<=1){arduboy.setCursor(30,56);arduboy.print("=");}
if (ANT<=1){arduboy.setCursor(36,56);arduboy.print(DR[2]+DR[1]+DR[0]+3);}
}
  
arduboy.setTextColor(0);
//arduboy.setCursor(0,16);
  //arduboy.print("Succubus\nHP:100");
  if (Mty!=7){
arduboy.setCursor(0,24);
  arduboy.print("HP:");
arduboy.setCursor(18,24);
  arduboy.print(MHP);
  }

if (Mty==0){arduboy.setCursor(0,16);arduboy.print("Succubus");//drawText(0, 16, M_SA, sizeof(M_SA),BLACK);
}else if (Mty==1){arduboy.setCursor(0,16);arduboy.print("Harpy");//drawText(0, 16, M_H, sizeof(M_H),BLACK);
}else if (Mty==3){arduboy.setCursor(0,16);arduboy.print("Witch");//drawText(0, 16, M_W, sizeof(M_W),BLACK);
}else if (Mty==2){arduboy.setCursor(0,16);arduboy.print("Dragon");//drawText(0, 16, M_D, sizeof(M_D),BLACK);
}else if (Mty==4){arduboy.setCursor(0,16);arduboy.print("Fairy");//drawText(0, 16, M_F, sizeof(M_F),BLACK);
}else if (Mty==5){arduboy.setCursor(0,16);arduboy.print("Slime");//drawText(0, 16, M_SU, sizeof(M_SU),BLACK);
}else if (Mty==6){arduboy.setCursor(0,16);arduboy.print("Plant");//drawText(0, 16, M_SI, sizeof(M_SI),BLACK);
}else if (NPC==5){arduboy.setCursor(0,16);arduboy.print("Clerk");//drawText(0, 16, NPC_W_W, sizeof(NPC_W_W),BLACK);
}else if (NPC==6){arduboy.setCursor(0,16);arduboy.print("Nun");//drawText(0, 16, NPC_S_W, sizeof(NPC_S_W),BLACK);
}



  arduboy.setTextColor(1);
if (BF==8){//タイトル画面
  arduboy.fillRect(0,0,88,16,0);
  //arduboy.setCursor(12,0);arduboy.print("Himedun!\nSuccubus Labyrinth");
  arduboy.setCursor(12,0);arduboy.print("Himedun!\nSuccubus Maze");
  //drawText(8, 0, title1, sizeof(title1),WHITE);
  //drawText(0, 8, M_SA, sizeof(M_SA),WHITE);
  //drawText(40, 8, title2, sizeof(title2),WHITE);
  Sprites::drawExternalMask(32, 31, EN_SA,EN_SA_M, 0, 0);
  Sprites::drawExternalMask(8, 31, EN_W,EN_W_M, 0, 0);
  Sprites::drawExternalMask(20, 17, EN_H,EN_H_M, 0, 0);
  
  arduboy.setCursor(0,48);
  arduboy.print(" LEVEL-\nGAME START");
  arduboy.setCursor(42,48);
  arduboy.print(LEVEL+1);
  //arduboy.setCursor(0,56);
  //arduboy.print("(C)SUMA");
  
  }

/*
arduboy.setCursor(10+50,25-4);

arduboy.setTextColor(0);
  arduboy.print(DR+1);
arduboy.drawFastVLine(8+50, 24-4, 9, 0);
arduboy.drawFastVLine(16+50, 24-4, 9, 0);
arduboy.drawFastHLine(8+50, 24-4, 9, 0);
arduboy.drawFastHLine(8+50, 32-4, 9, 0);
*/


//姫
  if (T_no==0){
//Sprites::drawExternalMask(67, 0+tktk/3, hime_A,hime_A_M, 0, 0);
Sprites::drawExternalMask(116, 15+tktk/3, hime_A3,hime_A3_M, 0, 0);
Sprites::drawExternalMask(89, 1+tktk/3, hime_A1,hime_A1_M, 0, 0);
Sprites::drawExternalMask(67, 42+tktk/3, hime_A2,hime_A2_M, 0, 0);
}else if (T_no==1){
//Sprites::drawExternalMask(64+AX, 0, hime_B,hime_B_M, 0, 0);
Sprites::drawExternalMask(83+AX, 0, hime_B1,hime_B1_M, 0, 0);
Sprites::drawExternalMask(64+AX, 23, hime_B2,hime_B2_M, 0, 0);
Sprites::drawExternalMask(109+AX, 23, hime_B3,hime_B3_M, 0, 0);
//arduboy.drawFastHLine(111+AX, 63, 1, 0);
arduboy.drawPixel(111+AX,63,BLACK);
}else if (T_no==2){
//Sprites::drawExternalMask(64+AX, 0, hime_C,hime_C_M, 0, 0);
Sprites::drawExternalMask(64+AX, 1, hime_C1,hime_C1_M, 0, 0);
Sprites::drawExternalMask(77+AX, 24, hime_C2,hime_C2_M, 0, 0);
Sprites::drawExternalMask(74+AX, 47, hime_C3,hime_C3_M, 0, 0);
}else if (T_no==3){
//Sprites::drawExternalMask(56+AX, 0, hime_D,hime_D_M, 0, 0);
Sprites::drawExternalMask(83+AX, 1, hime_D1,hime_D1_M, 0, 0);
Sprites::drawExternalMask(56+AX, 24, hime_D2,hime_D2_M, 0, 0);
Sprites::drawExternalMask(65+AX, 38, hime_D3,hime_D3_M, 0, 0);
}else if (T_no==4){
//Sprites::drawExternalMask(67+AX, 0, hime_E,hime_E_M, 0, 0);
Sprites::drawExternalMask(94+AX, 0, hime_E1,hime_E1_M, 0, 0);
Sprites::drawExternalMask(85+AX, 14, hime_E2,hime_E2_M, 0, 0);
Sprites::drawExternalMask(84+AX, 25, hime_E3,hime_E3_M, 0, 0);
Sprites::drawExternalMask(67+AX, 41, hime_E4,hime_E4_M, 0, 0);
}else if (T_no==5){
//Sprites::drawExternalMask(71+AX, 0, hime_F,hime_F_M, 0, 0);
Sprites::drawExternalMask(83+AX, 1, hime_F1,hime_F1_M, 0, 0);
Sprites::drawExternalMask(108+AX, 22, hime_F2,hime_F2_M, 0, 0);
Sprites::drawExternalMask(71+AX, 34, hime_F3,hime_F3_M, 0, 0);
}else if (T_no==6){
//Sprites::drawExternalMask(65+AX, 0, hime_G,hime_G_M, 0, 0);
Sprites::drawExternalMask(81+AX, 1, hime_G1,hime_G1_M, 0, 0);
Sprites::drawExternalMask(65+AX, 29, hime_G2,hime_G2_M, 0, 0);
Sprites::drawExternalMask(106+AX, 15, hime_G3,hime_G3_M, 0, 0);
Sprites::drawExternalMask(71+AX, 49, hime_G4,hime_G4_M, 0, 0);
}

//攻撃コマンド
if (BF==1){
  arduboy.fillRect(0,48,96,16,0);
  arduboy.setCursor(0,48);arduboy.print("Atk");
  arduboy.setCursor(6,56);arduboy.print("Ax   Kick Magic");
  arduboy.setCursor(30*SEL,56);arduboy.print(">");
  //drawText(0, 48, atk, sizeof(atk),WHITE);
  //drawText(0, 56, W_atk, sizeof(W_atk),WHITE);
  //drawText(0+SEL*32, 56, Migi, sizeof(Migi),WHITE);
}


//左右分岐
if (BF==9){
  arduboy.fillRect(0,48,105,16,0);
  arduboy.setCursor(0,48);arduboy.print("Which way going?\n Left Right");
  //drawText(0, 48, wakare1, sizeof(wakare1),WHITE);
  //drawText(8, 56, wakare2, sizeof(wakare2),WHITE);
  arduboy.setCursor(30*SEL,56);arduboy.print(">");
  //drawText(0+SEL*56, 56, Migi, sizeof(Migi),WHITE);
 if (ANT==0){
  for (uint8_t ii = 0; ii < 2; ii++) {
  for (uint8_t i = 0; i < 4; i++) {
    if (STMAPA[(F/4)*4+i][ii]==1){Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_E,MAP_E_M, 0, 0);}
    if (STMAPA[(F/4)*4+i][ii]==2){Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_T,MAP_T_M, 0, 0);}
    if (STMAPA[(F/4)*4+i][ii]==3){Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_I,MAP_I_M, 0, 0);}
    if (STMAPA[(F/4)*4+i][ii]==4){Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_W,MAP_W_M, 0, 0);}
    if (STMAPA[(F/4)*4+i][ii]==5){Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_S,MAP_S_M, 0, 0);}
    if (LEVEL!=0){
    if ((i==(QR+ii)%4)or((i==(QR+2+ii)%4))){arduboy.fillRect(0+(i%2)*9+ii*34, 24+(i/2)*9,8,8,1);Sprites::drawExternalMask(0+(i%2)*9+ii*34, 24+(i/2)*9, MAP_Q,MAP_Q_M, 0, 0);}//目隠し
    }
    /*
    if (STMAPB[(F/4)*4+i]==1){Sprites::drawExternalMask(34+(i%2)*9, 24+(i/2)*9, MAP_E,MAP_E_M, 0, 0);}
    if (STMAPB[(F/4)*4+i]==2){Sprites::drawExternalMask(34+(i%2)*9, 24+(i/2)*9, MAP_T,MAP_T_M, 0, 0);}
    if (STMAPB[(F/4)*4+i]==3){Sprites::drawExternalMask(34+(i%2)*9, 24+(i/2)*9, MAP_I,MAP_I_M, 0, 0);}
    if (STMAPB[(F/4)*4+i]==4){Sprites::drawExternalMask(34+(i%2)*9, 24+(i/2)*9, MAP_W,MAP_W_M, 0, 0);}
    if (STMAPB[(F/4)*4+i]==5){Sprites::drawExternalMask(34+(i%2)*9, 24+(i/2)*9, MAP_S,MAP_S_M, 0, 0);}
    */
  }
  }
 }
}

//消える
if (BF==10){
  arduboy.fillRect(0,48,64,16,0);
  arduboy.setCursor(0,48);arduboy.print("Moving...");
  //drawText(0, 48, tokotoko, sizeof(tokotoko),WHITE);
  
}

//罠だ!
if ((BF==11)or(BF==12)or(BF==13)){
  arduboy.fillRect(0,48,64,8,0);
  arduboy.setCursor(0,48);arduboy.print("Trap!?");
  //drawText(0, 48, wana, sizeof(wana),WHITE); 
}
if ((BF==13)and(RR==2)){
  arduboy.fillRect(0,56,64,8,0);
  arduboy.setCursor(0,56);arduboy.print("Cursed");
  //drawText(0, 56, noroi, sizeof(noroi),WHITE); 
}

arduboy.setTextColor(1);
//宝箱//くすり
if ((BF==20)or(BF==21)){
  arduboy.fillRect(0,48,64,16,0);
  if (BF==20){arduboy.setCursor(0,48);arduboy.print("Medicine");}//drawText(0, 48, BIN1, sizeof(BIN1),WHITE);
  
  if (BF==21){arduboy.fillRect(0,48,78,16,0);arduboy.setCursor(0,48);arduboy.print("Take medicine\nReduced DP");
              //drawText(0, 48, BIN2, sizeof(BIN2),WHITE); 
              //drawText(16, 56, BIN3, sizeof(BIN3),WHITE);
              //arduboy.setCursor(0,56);
              //arduboy.print("DP");
              }
}
//ウエイトレス
if ((BF==30)or(BF==31)or(BF==32)){
  arduboy.fillRect(0,48,84,16,0);
  if (BF==30){arduboy.setCursor(0,48);arduboy.print("Hello");}//drawText(0, 48, NPC_W_W1, sizeof(NPC_W_W1),WHITE);
  if (BF==31){arduboy.setCursor(0,48);arduboy.print("Which do want?");//drawText(0, 48, NPC_W_W2, sizeof(NPC_W_W2),WHITE);
              arduboy.setCursor(6,56);arduboy.print("Ax  Def Heal");//drawText(8, 56, NPC_W_W3, sizeof(NPC_W_W3),WHITE);
              arduboy.setCursor(24*SEL,56);arduboy.print(">");//drawText(0+SEL*24, 56, Migi, sizeof(Migi),WHITE);
              }
  if (BF==32){arduboy.setCursor(0,48);arduboy.print("Thanks");//drawText(0, 48, NPC_W_W4, sizeof(NPC_W_W4),WHITE);
  }
  
}

//シスター
if ((BF==40)or(BF==41)or(BF==42)){
  arduboy.fillRect(0,48,72,16,0);
  if (BF==40){arduboy.setCursor(0,48);arduboy.print("Hello");}//drawText(0, 48, NPC_S_W1, sizeof(NPC_S_W1),WHITE);
  if (BF==41){arduboy.fillRect(0,48,126,16,0);arduboy.setCursor(0,48);arduboy.print("Hello");//drawText(0, 48, NPC_S_W4, sizeof(NPC_S_W4),WHITE);
                                              arduboy.setCursor(0,48);arduboy.print("What kind of request?");//drawText(24, 56, NPC_S_W5, sizeof(NPC_S_W5),WHITE);
                                              arduboy.setCursor(6,56);
                                              arduboy.print("MP add Break curse");
                                              arduboy.setCursor(42*SEL,56);arduboy.print(">");
                                              //drawText(0+SEL*56, 56, Migi, sizeof(Migi),WHITE);
                                              }
  if (BF==42){arduboy.fillRect(0,48,90,16,0);arduboy.setCursor(0,48);arduboy.print("Have a nice day");//drawText(0, 48, NPC_S_W3, sizeof(NPC_S_W3),WHITE); 
  }

}

//ゲームクリア
if (BF==101){
//Sprites::drawExternalMask(98, 11+tktk/3, ED_F,ED_F_M, 0, 0);
Sprites::drawExternalMask(98, 11, ED_F,ED_F_M, 0, 0);
  arduboy.fillRect(0,48,72,16,0);
arduboy.setCursor(0,48);arduboy.print("It's my win");//drawText(0, 48, ED_W, sizeof(ED_W),WHITE);
arduboy.setCursor(8,56);
  arduboy.print("GAME CLEAR");


}

//敵
if (Mty==0){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_SA,EN_SA_M, 0, 0);
}else if (Mty==1){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_H,EN_H_M, 0, 0);
}else if (Mty==3){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_W,EN_W_M, 0, 0);
}else if (Mty==2){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_D,EN_D_M, 0, 0);
}else if (Mty==4){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_F,EN_F_M, 0, 0);
}else if (Mty==5){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_SU,EN_SU_M, 0, 0);
}else if (Mty==6){Sprites::drawExternalMask(16+AX_T, 31+AY_T, EN_SI,EN_SI_M, 0, 0);
}else if (NPC==1){Sprites::drawExternalMask(20+AX_T, 31+AY_T, NPC_K,NPC_K_M, 0, 0);
}else if (NPC==2){Sprites::drawExternalMask(18+AX_T, 31+AY_T, NPC_TR,NPC_TR_M, 0, 0);
}else if (NPC==3){Sprites::drawExternalMask(18+AX_T, 31+AY_T, NPC_BI,NPC_BI_M, 0, 0);
}else if (NPC==5){Sprites::drawExternalMask(18+AX_T, 31+AY_T, NPC_W,NPC_W_M, 0, 0);
}else if (NPC==6){Sprites::drawExternalMask(18+AX_T, 31+AY_T, NPC_S,NPC_S_M, 0, 0);
}

//斬撃
if (EF==1){
  /*if (ANT>11){
    B=25-ANT;//-B*(B/7-1)*2
  arduboy.drawLine(17+B/7*(B-7)*2,32+B/7*(B-7)*2,17+15+(-7+B)*(1-B/7)*2,32+15+(-7+B)*(1-B/7)*2,BLACK);
  arduboy.drawLine(16+B/7*(B-7)*2,32+B/7*(B-7)*2,16+16+(-7+B)*(1-B/7)*2,32+16+(-7+B)*(1-B/7)*2,WHITE);
  arduboy.drawLine(16+B/7*(B-7)*2,33+B/7*(B-7)*2,16+15+(-7+B)*(1-B/7)*2,33+15+(-7+B)*(1-B/7)*2,BLACK);
  }*/
  if (ANT>0){
    if(ANT<=8){
      B=8-ANT;//-B*(B/7-1)*2
      arduboy.drawLine(17+B/4*(B-4)*4,32+B/4*(B-4)*4,17+15+(-4+B)*(1-B/4)*4,32+15+(-4+B)*(1-B/4)*4,BLACK);
      arduboy.drawLine(16+B/4*(B-4)*4,32+B/4*(B-4)*4,16+16+(-4+B)*(1-B/4)*4,32+16+(-4+B)*(1-B/4)*4,WHITE);
      arduboy.drawLine(16+B/4*(B-4)*4,33+B/4*(B-4)*4,16+15+(-4+B)*(1-B/4)*4,33+15+(-4+B)*(1-B/4)*4,BLACK);
      if (ANT<=4){
      if (seiko==1){Sprites::drawExternalMask(16+10, 32+10, EF_A_2,EF_A_2_M, 0, 0);}
      }
    }
  }
}
if (EF==2){//キック
  if (ANT>0){
    if(ANT<=8){
      if (ANT/2==3){Sprites::drawExternalMask(16+10, 32+10, EF_A_2,EF_A_2_M, 0, 0);}
      if (ANT/2==2){Sprites::drawExternalMask(16+3, 32+3, EF_A_2,EF_A_2_M, 0, 0);}
      if (ANT<=4){
        Sprites::drawExternalMask(16-7, 32-7, EF_A_1,EF_A_1_M, 0, 0);
      }
    }
  }
}
if (EF==3){//魔法
  if (ANT>0){
    B=16-ANT;
    if(ANT>12){
    arduboy.fillCircle(128-72-8,36,B*2,WHITE);
    arduboy.drawCircle(128-72-8,36,B*2,BLACK);
    }else if(ANT>8){
    arduboy.fillCircle(128-72-8,36,8,WHITE);
    arduboy.drawCircle(128-72-8,36,8,BLACK);
    }
    if((ANT<=8)and(ANT>4)){//48-24 36-40
      B=8-ANT;
    arduboy.fillCircle(48-6*B,36+B,8,WHITE);
    arduboy.drawCircle(48-6*B,36+B,8,BLACK);
    }
    if(ANT<=4){//24-32 36-48
      B=4-ANT;
    arduboy.fillCircle(24+B*16,40,4,WHITE);
    arduboy.drawCircle(24+B*16,40,4,BLACK);
    
    arduboy.fillCircle(24-B*16,40,4,WHITE);
    arduboy.drawCircle(24-B*16,40,4,BLACK);

    arduboy.fillCircle(24+B*6,40+B*8,4,WHITE);
    arduboy.drawCircle(24+B*6,40+B*8,4,BLACK);
    
    arduboy.fillCircle(24-B*6,40+B*8,4,WHITE);
    arduboy.drawCircle(24-B*6,40+B*8,4,BLACK);

    arduboy.fillCircle(24+B*6,40-B*8,4,WHITE);
    arduboy.drawCircle(24+B*6,40-B*8,4,BLACK);
    
    arduboy.fillCircle(24-B*6,40-B*8,4,WHITE);
    arduboy.drawCircle(24-B*6,40-B*8,4,BLACK);
    
    }
    
  }
}

if (EF==11){
  if (ANT>0){
    if(ANT<=16){
      if (ANT/4==3){Sprites::drawExternalMask(65+15, 0+15, EF_A_2,EF_A_2_M, 0, 0);}
      //if ((ANT+2)/4==3){Sprites::drawExternalMask(65+20, 0+20, EF_A_2,EF_A_2_M, 0, 0);}
      if (ANT/4==2){Sprites::drawExternalMask(65+21, 0+21, EF_A_2,EF_A_2_M, 0, 0);}
      if ((ANT+2)/4==2){Sprites::drawExternalMask(65+27, 0+27, EF_A_1,EF_A_1_M, 0, 0);}
      if (ANT/8==0){Sprites::drawExternalMask(65+35, 0+35, EF_A_1,EF_A_1_M, 0, 0);}
    }
  }
  
}

if (ANT>0){ANT--;}



arduboy.setTextColor(0);
//ダイス
  for (uint8_t i = 0; i < DC; i++) {
arduboy.fillRect(8+20+DX[i]+i*15,24-4+DY[i],9,9,1);
arduboy.setCursor(10+20+DX[i]+i*15,25-4+DY[i]);

  arduboy.print(DR[i]+1);
arduboy.drawFastVLine(8+20+DX[i]+i*15, 24-4+DY[i], 9, 0);
arduboy.drawFastVLine(16+20+DX[i]+i*15, 24-4+DY[i], 9, 0);
arduboy.drawFastHLine(8+20+DX[i]+i*15, 24-4+DY[i], 9, 0);
arduboy.drawFastHLine(8+20+DX[i]+i*15, 32-4+DY[i], 9, 0);
  }

//呪い
if (BF!=8){
if (ItemD>=2){arduboy.setCursor(78,1);arduboy.print(ItemD);}
if (ItemD!=0){Sprites::drawExternalMask(68, 1, IT_D,IT_D_M, 0, 0);}
if (ItemA==1){Sprites::drawExternalMask(119, 1, IT_A,IT_A_M, 0, 0);}
if (ItemB==1){Sprites::drawExternalMask(119, 10, IT_G,IT_G_M, 0, 0);}
}

/*
L=0;
if (DR%2==1){arduboy.drawPixel(11, 25, 0);}
while(L==DR/2){
L=L+1;
arduboy.drawPixel(10, 26+(DR/2)*12-(DR/3)*6, 0);
arduboy.drawPixel(12, 26+12-(DR/2)*12+(DR/3)*6, 0);
}
*/
//arduboy.fillRect(0,0,64,16,0);
if (T_no==7){
//arduboy.fillRect(18,0,92,64,1);
//Sprites::drawExternalMask(18, 0, hime_H,hime_H_M, 0, 0);
Sprites::drawExternalMask(18, 7, hime_H_1,hime_H_1_M, 0, 0);
Sprites::drawExternalMask(86, 2, hime_H_2,hime_H_2_M, 0, 0);
Sprites::drawExternalMask(33, 31, hime_H_3,hime_H_3_M, 0, 0);
arduboy.setTextColor(1);
arduboy.setCursor(40,50);
 arduboy.print("GAME OVER");

}


  arduboy.display();
}
