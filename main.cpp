#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Map.h"
#include "ThreatObject.h"
#include "BossObject.h"
#include "TextObject.h"
#include "PlayPower.h"
using namespace std;

BaseObject gBackground;
BaseObject dan;
BaseObject rasengan;
MainObject main_obj;
GameMap game_map;
TTF_Font* font_time=NULL;

//ThreatObject p_threat;

bool init() {
    bool succes=true;
   gWindow=SDL_CreateWindow("GPA 4.0",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
   gScreen=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
   if(TTF_Init()==-1) {
    return false;
   }
   if(gScreen==NULL) {
    succes=false;
   }
   font_time=TTF_OpenFont("VHANTIQ.ttf",15);
   if(font_time==NULL)
   {
       succes=false;
   }
   int imgFlags = IMG_INIT_PNG;
				if( !( IMG_Init( imgFlags ) & imgFlags ) )
				{
					printf( "SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError() );
					succes = false;
				}

				 //Initialize SDL_mixer
				if( Mix_OpenAudio( 44100, MIX_DEFAULT_FORMAT, 2, 2048 ) < 0 )
				{
					printf( "SDL_mixer could not initialize! SDL_mixer Error: %s\n", Mix_GetError() );
					succes = false;
				}
   return succes;
}
bool loadmedia() {
   gBackground.LoadImg("nen_den.jpg",gScreen);
}
void close() {
   SDL_DestroyRenderer(gScreen);
   gScreen=NULL;
   SDL_DestroyWindow(gWindow);
   gWindow=NULL;
   SDL_DestroyTexture(gText);
   gText=NULL;
}
int main(int argc,char* args[])
{

    int cnt_dan=0;
    int cnt_rasengan=0;
    std::string val_cnt_dan;
    std::string strDan="     : ";
    std::string val_cnt_rasengan;
    std::string strRasengan="      : ";
    std::string str_time="Time: ";
    std::string str_val;


    int num_threat=25;
    int num_boss=3;
    int num_die=0;
    if(init()) {
        if(loadmedia())
        {
            main_obj.LoadImg("naruto_main.png",gScreen);
            main_obj.SetClip();
            main_obj.settocdo(2);

            dan.LoadImg("laser_.png",gScreen);
            rasengan.LoadImg("sphere_.png",gScreen);
            dan.SetRect(337,15);
            rasengan.SetRect(270,15);


            std::vector<BossObject*> p_boss_ob;
            for(int i=0;i<3;i++)
            {
             BossObject* p_boss=new BossObject();
             p_boss->LoadImg("Boss.png",gScreen);
             p_boss->SetClip();
             if(i==0) {p_boss->Set_pos(BOSS_POS_X,BOSS_POS_Y);}
             else if(i==1) {p_boss->Set_pos(BOSS_POS_X_1,BOSS_POS_Y_1);}
             else if(i==2) {p_boss->Set_pos(BOSS_POS_X_2,BOSS_POS_Y_2);}
             p_boss_ob.push_back(p_boss);

            }


            for(int j=0;j<3;j++)
            {
                std::vector<Bullet*> p_bullet_boss;
            for(int i=0;i<16;i++) {
                Bullet* p_bullet_boss_=new Bullet();
               bool check= p_bullet_boss_->LoadImg("Threat_bullet.png",gScreen);
                if(!check) {
                    std::cout<<"loi load bom"<<'\n';
                }
                p_bullet_boss_->set_pos(BOSS_POS_X,BOSS_POS_Y);
                if(i<8) {p_bullet_boss_->set_pos(BOSS_POS_X,BOSS_POS_Y);}
                else if(i>=8) {p_bullet_boss_->set_pos(BOSS_POS_X-10,BOSS_POS_Y+10);}
                if(i<8)
                {
                   p_bullet_boss_->set_val_bullet(dx[i]);
                p_bullet_boss_->set_val_bullet_y(dy[i]);
                }
                else {
                    p_bullet_boss_->set_val_bullet(dx[i]);
                p_bullet_boss_->set_val_bullet_y(dy[i]);
                }

                p_bullet_boss_->set_is_move(true);
                p_bullet_boss.push_back(p_bullet_boss_);

            }
            p_boss_ob[j]->Set_amo_list(p_bullet_boss);
            p_boss_ob[j]->Set_p_bullet_du_phong(p_bullet_boss);
            }

             std::vector<ThreatObject*> p_threat;

             for(int i=0;i<NUM_THREAT;i++) {
                ThreatObject* p_threat_=new ThreatObject();

                p_threat_->LoadImg("Threat1.png",gScreen);

                p_threat_->SetClip();
                p_threat.push_back(p_threat_);

                p_threat_=NULL;
             }
             for(int i=0;i<5;i++) {
                p_threat[i]->set_x_pos(1664);
                p_threat[i]->set_y_pos(832);
               /* Bullet* p_amo=new Bullet();
                 p_threat[i]->InitBullet(p_amo,gScreen);
             */
             }
             for(int i=5;i<10;i++) {
                p_threat[i]->set_x_pos(768);
                p_threat[i]->set_y_pos(1344);
                /*Bullet* p_amo=new Bullet();
                p_threat[i]->InitBullet(p_amo,gScreen);
             */
             }
             for(int i=10;i<15;i++) {
                p_threat[i]->set_x_pos(1216);
                p_threat[i]->set_y_pos(448);
                /*Bullet* p_amo=new Bullet();
                p_threat[i]->InitBullet(p_amo,gScreen);*/
             }

            game_map.LoadMap("map.txt");
            game_map.LoadTiles(gScreen);
           Map mapX=game_map.getMap();

           PlayPower play_power;
           play_power.Init(gScreen);

            //game_map.xuatMap();

            TextObject time_game;
            time_game.SetColor(TextObject::WHITE_TEXT);
            TextObject so_dan;
            so_dan.SetColor(TextObject::RED_TEXT);

            TextObject so_rasengan;
            so_rasengan.SetColor(TextObject::RED_TEXT);

            bool quit=false;
            bool is_win=false;
            while(!quit&&!is_win)
            {

                //createGhost++;
                while(SDL_PollEvent(&gevent)!=0)
                {
                    if(gevent.type==SDL_QUIT)
                    {
                        quit=true;
                    }
                  main_obj.handle(gevent,gScreen);
                }

                gBackground.Render(gScreen);

                Map map_data=game_map.getMap();
                //const Map map_data1=game_map.getMap();
               // std::cout<<map_data.max_x_<<" "<<map_data.max_y_<<'\n';
                main_obj.SetmapXY(map_data.start_x_,map_data.start_y_);
                /*for(int i=0;i<NUM_THREAT;i++) {
                    p_threat[i]->SetMapXY(map_data.start_x_,map_data.start_y_);
                }*/
                //p_threat.SetMapXY(map_data.start_x_,map_data.start_y_);
                main_obj.DoPlayer(map_data);
               //p_boss.SetMapXY(map_data.start_x_,map_data.start_y_);

                game_map.SetMap(map_data);
                 game_map.DrawMap(gScreen);
                 play_power.Show(gScreen);

                 main_obj.Show(gScreen);



                 main_obj.HandleBullet(gScreen,map_data);

                 /* p_threat[20]->SetMapXY(map_data.start_x_,map_data.start_y_);
                    p_threat[20]->DoPlayer(map_data);
                    //p_threat[20]->MakeBullet(gScreen,SCREEN_WIDTH,SCREEN_HEIGHT);
                    p_threat[20]->Show(gScreen);
                  bool check=p_threat[20]->CheckToBullet(main_obj);

                  */
                  for(int i=0;i<p_boss_ob.size();i++)
                {

                    p_boss_ob[i]->SetMapXY(map_data.start_x_,map_data.start_y_);
                    p_boss_ob[i]->Show(gScreen);
                    p_boss_ob[i]->MakeBullet(map_data,gScreen);
                    p_boss_ob[i]->CheckToBullet(main_obj);
                    //if(!main_obj.get_a_live()) {p_boss_ob[i]->Reset_amo_list();}
                }
                for(int i=0;i<p_boss_ob.size();i++)
                {
                    if(!p_boss_ob[i]->get_alive())
                    {
                        std::cout<<i<<'\n';
                        p_boss_ob.erase(p_boss_ob.begin() + i);
                    }
                }
                for(int i=0;i<p_threat.size();i++) {
                    p_threat[i]->SetMapXY(map_data.start_x_,map_data.start_y_);
                    p_threat[i]->DoPlayer(map_data);
                    p_threat[i]->Show(gScreen);
                    bool check=p_threat[i]->CheckToBullet(main_obj);
                    if(check) {
                            std::cout<<p_threat.size()<<'\n';
                        num_threat--;
                    }
                }
        for(int i = 0; i < p_threat.size(); i++){
            if(!p_threat[i]->is_alive()){
                    std::cout<<"da chet"<<'\n';
                 p_threat.erase(p_threat.begin() + i);
            }
        }
        if(p_threat.size()==0&&p_boss_ob.size()==0) {
            std::cout<<"da win";
            p_threat.clear();
            p_boss_ob.clear();
            is_win=true;
        }
        if(!main_obj.get_a_live())
        {
            num_die++;

            if(num_die<=3) {
                play_power.Decrease();
                play_power.Show(gScreen);
            }
            main_obj.set_alive(true);
            std::cout<<"da hoi sinh"<<'\n';
        }
        if(main_obj.Get_blood_main()!=0)
        {
            num_die--;
            play_power.Increase();
            play_power.Show(gScreen);
            main_obj.Set_blood_main(0);
        }

        cnt_dan=main_obj.get_sodan();
        cnt_rasengan=main_obj.get_sorasengan();
          val_cnt_dan=std::to_string(cnt_dan);

         strDan+=val_cnt_dan;
          so_dan.SetText(strDan);
          so_dan.LoadFromRenderText(font_time,gScreen);
          dan.Render(gScreen);
         so_dan.RenderText(gScreen,SCREEN_WIDTH*0.6-50,20);
         //val_cnt_dan="";
         so_dan.Free();
         strDan="";

        val_cnt_rasengan=std::to_string(cnt_rasengan);
         strRasengan+=val_cnt_rasengan;
         so_rasengan.SetText(strRasengan);

         rasengan.Render(gScreen);
         so_rasengan.LoadFromRenderText(font_time,gScreen);
         so_rasengan.RenderText(gScreen,SCREEN_WIDTH*0.5-50,20);
         val_cnt_rasengan="";
         strRasengan="";
         so_rasengan.Free();
        //std::cout<<main_obj.Get_blood_main()<<'\n';
                 SDL_Delay(10);

                 Uint32 time_val=SDL_GetTicks()/1000;
                 Uint32 val_time=300-time_val;
                 if(val_time<=0)
                 {
                 std::cout<<"het time";
                 quit=true;
                 break;
                 }
                 else{
                    str_val=std::to_string(val_time);
                    str_time+=str_val;
                    time_game.SetText(str_time);
                    time_game.LoadFromRenderText(font_time,gScreen);
                    time_game.RenderText(gScreen,SCREEN_WIDTH-100,15);
                    time_game.Free();
                    str_time="Time : ";
                 }
                  SDL_RenderPresent(gScreen);
            }
        }
        else {cout<<"loi day ne";}
    }
    else {cout<<"losi day";}
    close();
    return 0;
}
