#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Map.h"
#include "ThreatObject.h"
#include "BossObject.h"
#include "TextObject.h"
#include "PlayPower.h"
#include "Audio.h"

using namespace std;

BaseObject gBackground;
BaseObject dan;
BaseObject rasengan;
BaseObject threat;
BaseObject boss;
BaseObject Menu;
BaseObject Win_even;
BaseObject Lose_even;
BaseObject back_menu;
BaseObject play_;
BaseObject pause_;

TextObject menu[3];

TextObject introduction_;

MainObject main_obj;
GameMap game_map;
Mix_Music* game_sound_total=NULL;
Mix_Chunk* game_sound_rasengan=NULL;
Mix_Music* win_game=NULL;

TTF_Font* font_time=NULL;
TTF_Font* font_game_menu=NULL;

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
   font_time=TTF_OpenFont("font/VHANTIQ.ttf",15);
   if(font_time==NULL)
   {
       succes=false;
   }
   font_game_menu=TTF_OpenFont("font/STONB.ttf",40);
   if(font_game_menu==NULL)
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
   game_sound_total=Mix_LoadMUS("sound/y2mate_music.mp3");
   game_sound_rasengan=Mix_LoadWAV("sound/Rasengan.wav");
   win_game=Mix_LoadMUS("sound/win_sound.mp3");
   if(win_game==NULL)
   {
       std::cout<<"loi load wingame"<<'\n';
   }
  play_.LoadImg("image/play.jpg",gScreen);

   pause_.LoadImg("image/pause.jpg",gScreen);
   play_.SetRect(0,600);
   pause_.SetRect(0,600);
   if(game_sound_total==NULL)
   {
       std::cout<<"game soung =null"<<'\n';
   }
   //Menu.LoadImg("menu.png",gScreen);
   return game_sound_total!=NULL;
}
void close() {
    Mix_FreeMusic(game_sound_total);
    game_sound_total=NULL;
    Mix_FreeChunk(game_sound_rasengan);
    game_sound_rasengan=NULL;
    Mix_FreeMusic(win_game);
    win_game=NULL;

   SDL_DestroyRenderer(gScreen);
   gScreen=NULL;
   SDL_DestroyWindow(gWindow);
   gWindow=NULL;
   SDL_DestroyTexture(gText);
   gText=NULL;
}



int main(int argc,char* args[])
{

init();
loadmedia();
   SetPosMenu();
   int quit1=0;
   back_menu.LoadImg("image/back.png",gScreen);
               back_menu.SetRect(10,10);
                     bool t=Menu.LoadImg("image/menu.png",gScreen);
    if(!t)
    {
        std::cout<<"loi load anh"<<'\n';
    }

   label:
    string introduction="Introduction";
    string Exit="Exit";
    string play="Play";

            menu[0].SetText(play);
            menu[0].LoadFromRenderText(font_game_menu,gScreen);

            menu[1].SetText(Exit);
            menu[1].LoadFromRenderText(font_game_menu,gScreen);

            menu[2].SetText(introduction);
            menu[2].LoadFromRenderText(font_game_menu,gScreen);

    int time_console;

        while(quit1==0)
            {
                time_console=SDL_GetTicks()/1000;

                while (SDL_PollEvent(&gevent) != 0) {
                int xm = gevent.motion.x;
                int ym = gevent.motion.y;
                if (gevent.type == SDL_QUIT) {
                    quit1 = 4;
                }
                if (gevent.type == SDL_MOUSEMOTION) {

                    for (int i = 0; i < 3; i++) {
                          menu_pos[i].w=menu[i].GetWidth();
                          menu_pos[i].h=menu[i].GetHeight();
                        if (check_mouse(xm, ym, menu_pos[i])) {

                            menu[i].Free();
                            menu[i].SetColor(TextObject::RED_TEXT);
                            menu[i].LoadFromRenderText(font_game_menu,gScreen);
                        }
                        else {
                                menu[i].Free();
                            menu[i].SetColor(TextObject::WHITE_TEXT);
                            menu[i].LoadFromRenderText(font_game_menu,gScreen);
                        }
                    }
                }
                if (gevent.type == SDL_MOUSEBUTTONDOWN) {
                        std::cout<<"da vao day"<<'\n';
                    for (int i = 0; i < 3; i++) {
                        if (check_mouse(xm, ym, menu_pos[i]) && gevent.button.button == SDL_BUTTON_LEFT) {
                            quit1 = i + 1;
                            std::cout<<quit1<<'\n';
                        }
                    }
                }
            }
            Menu.Render(gScreen);
            menu[0].RenderText(gScreen,menu_pos[0].x,menu_pos[0].y);
            menu[1].RenderText(gScreen,menu_pos[1].x,menu_pos[1].y);
            menu[2].RenderText(gScreen,menu_pos[2].x,menu_pos[2].y);
            SDL_RenderPresent(gScreen);
        }



    if(quit1==1)
    {
        bool mouse_event=false;
        int pause=0;
        int play_ing=1;
        SDL_RenderClear(gScreen);
        int cnt_threat=0;
        int cnt_boss=0;
        std::string cnt_b="";
        std::string cnt_th="";
    int cnt_dan=0;
    int cnt_rasengan=0;
    std::string val_cnt_dan;
    std::string strDan="  : ";
    std::string val_cnt_rasengan;
    std::string strRasengan=" : ";
    std::string str_time="Time: ";
    std::string str_val;



    int num_threat=25;
    int num_die=0;

            bool is_win=false;
            Mix_PlayMusic(game_sound_total,4);
            //Mix_VolumeMusic(50);



            main_obj.LoadImg("image/naruto_main.png",gScreen);
            main_obj.SetClip();
            main_obj.settocdo(2);

            Win_even.LoadImg("image/you_win.png",gScreen);
            Win_even.SetRect(100,100);

            dan.LoadImg("image/laser_.png",gScreen);
            rasengan.LoadImg("image/sphere_.png",gScreen);
            threat.LoadImg("image/cntthreat.png",gScreen);
            boss.LoadImg("image/boss_pr.png",gScreen);

            dan.SetRect(SCREEN_WIDTH*0.3,15);
            rasengan.SetRect(SCREEN_WIDTH*0.5,15);
            threat.SetRect(SCREEN_WIDTH*0.6,15);
            boss.SetRect(SCREEN_WIDTH*0.7,15);

            Uint32 time_val;
            Uint32 val_time;

            Map map_data;


            std::vector<BossObject*> p_boss_ob;
            for(int i=0;i<3;i++)
            {
             BossObject* p_boss=new BossObject();
             p_boss->LoadImg("image/Boss.png",gScreen);
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
               bool check= p_bullet_boss_->LoadImg("image/Threat_bullet.png",gScreen);
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

                p_threat_->LoadImg("image/Threat1.png",gScreen);

                p_threat_->SetClip();
                p_threat.push_back(p_threat_);

                p_threat_=NULL;
             }
             for(int i=0;i<5;i++) {
                p_threat[i]->set_x_pos(1664);
                p_threat[i]->set_y_pos(832);
             }
             for(int i=5;i<10;i++) {
                p_threat[i]->set_x_pos(768);
                p_threat[i]->set_y_pos(1344);
             }
             for(int i=10;i<15;i++) {
                p_threat[i]->set_x_pos(1216);
                p_threat[i]->set_y_pos(448);
             }


            game_map.LoadMap("map.txt");

            game_map.LoadTiles(gScreen);
         //  Map mapX=game_map.getMap();


           PlayPower play_power;
           play_power.Init(gScreen);



            TextObject time_game;
            time_game.SetColor(TextObject::WHITE_TEXT);
            TextObject so_dan;
            so_dan.SetColor(TextObject::RED_TEXT);

            TextObject so_rasengan;
            so_rasengan.SetColor(TextObject::RED_TEXT);

            TextObject so_threat;
            so_threat.SetColor(TextObject::WHITE_TEXT);
            TextObject so_boss;
            so_boss.SetColor(TextObject::WHITE_TEXT);

            bool quit=false;
            bool is_win_=false;
            while(!quit&&!is_win)
            {



                if (pause == 0) {
                play_.Render(gScreen);
            }
            if (pause == 1) {
                pause_.Render(gScreen);
            }
                 while (pause == 1) {
                        SDL_RenderPresent(gScreen);
                while (SDL_PollEvent(&gevent) != 0) {
                    int xm = gevent.motion.x;
                    int ym = gevent.motion.y;
                    if (gevent.type == SDL_MOUSEBUTTONDOWN) {
                           mouse_event=false;
                        if (gevent.button.button == SDL_BUTTON_LEFT && check_mouse(xm, ym, pause_.GetRect()) ) {
                            std::cout<<"da vao day 1"<<'\n';
                            pause = 0;
                        }
                    }
                }
            }
                while(SDL_PollEvent(&gevent)!=0)
                {
                    if(gevent.type==SDL_QUIT)
                    {
                        quit=true;
                    }

                   if (gevent.type == SDL_MOUSEBUTTONDOWN) {
                            int xm = gevent.motion.x;
                    int ym = gevent.motion.y;
                        if (gevent.button.button == SDL_BUTTON_LEFT && check_mouse(xm, ym, play_.GetRect()) ) {
                            std::cout<<"da vao day 2"<<'\n';
                            pause = 1;
                            mouse_event=true;
                            pause_.Render(gScreen);
                            SDL_RenderPresent(gScreen);
                        }
                    }
                    if(!mouse_event) {main_obj.handle(gevent,gScreen);}

                }



                 time_val=SDL_GetTicks()/1000-time_console;
                  val_time=300-time_val;
                gBackground.Render(gScreen);


                map_data=game_map.getMap();
                main_obj.SetmapXY(map_data.start_x_,map_data.start_y_);
                main_obj.DoPlayer(map_data);


                game_map.SetMap(map_data);
                 game_map.DrawMap(gScreen);
                 play_power.Show(gScreen);

                 main_obj.Show(gScreen);
                 main_obj.HandleBullet(gScreen,map_data);

                  for(int i=0;i<p_boss_ob.size();i++)
                {

                    p_boss_ob[i]->SetMapXY(map_data.start_x_,map_data.start_y_);
                    p_boss_ob[i]->Show(gScreen);
                    p_boss_ob[i]->MakeBullet(map_data,gScreen);
                    p_boss_ob[i]->CheckToBullet(main_obj);
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
        if(p_threat.size()<=20&&p_boss_ob.size()<=2) {
            //std::cout<<"da win";
            game_map.setGate(7,1);
            if(main_obj.is_win_())
            {
                p_threat.clear();
            p_boss_ob.clear();
            if(Mix_PlayingMusic()==1)
            {
                Mix_HaltMusic();
            Mix_PlayMusic(win_game,2);

            Win_even.Render(gScreen);
            is_win_=true;
            }

            }


        }
        if(!main_obj.get_a_live())
        {
            main_obj.Set_sound_die();
            num_die++;

            if(num_die<3) {
                play_power.Decrease();
                play_power.Show(gScreen);
                main_obj.set_alive(true);
            std::cout<<"da hoi sinh"<<'\n';
            }
            /*else if(num_die>=3)
            {
                for(int i=0;i<p_threat.size();i++)
                {
                    p_threat[i]->free();
                }
                for(int i=0;i<p_boss_ob.size();i++)
                {
                    p_boss_ob[i]->free();
                }
                p_threat.clear();
                p_boss_ob.clear();
                quit=true;
            }*/
        }
        if(main_obj.Get_blood_main()!=0)
        {
            num_die--;
            play_power.Increase();
            play_power.Show(gScreen);
            main_obj.Set_blood_main(0);
        }

        if(play_ing==1) {play_.Render(gScreen);}





        cnt_dan=main_obj.get_sorasengan();
        cnt_rasengan=main_obj.get_soshuriken();
          val_cnt_dan=std::to_string(cnt_dan);

         strDan+=val_cnt_dan;
          so_dan.SetText(strDan);
          so_dan.LoadFromRenderText(font_time,gScreen);
          dan.Render(gScreen);
         so_dan.RenderText(gScreen,SCREEN_WIDTH*0.3+32,20);
         //val_cnt_dan="";
         so_dan.Free();
         strDan="";

        val_cnt_rasengan=std::to_string(cnt_rasengan);
         strRasengan+=val_cnt_rasengan;
         so_rasengan.SetText(strRasengan);

         rasengan.Render(gScreen);
         so_rasengan.LoadFromRenderText(font_time,gScreen);
         so_rasengan.RenderText(gScreen,SCREEN_WIDTH*0.5+32,20);
         val_cnt_rasengan="";
         strRasengan="";
         so_rasengan.Free();

         threat.Render(gScreen);
         boss.Render(gScreen);
         cnt_boss=p_boss_ob.size();
         cnt_threat=p_threat.size();

         cnt_b=std::to_string(cnt_boss);
         so_boss.SetText(cnt_b);
         so_boss.LoadFromRenderText(font_time,gScreen);
         so_boss.RenderText(gScreen,SCREEN_WIDTH*0.7+32,20);
         so_boss.Free();

         cnt_th=std::to_string(cnt_threat);
         so_threat.SetText(cnt_th);
         so_threat.LoadFromRenderText(font_time,gScreen);
         so_threat.RenderText(gScreen,SCREEN_WIDTH*0.6+32,20);
         so_threat.Free();
        //std::cout<<main_obj.Get_blood_main()<<'\n';
                 SDL_Delay(3);


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
    else if(quit1==2)
    {
        close();
    return 0;
    }
    else if(quit1==3)
    {

        Menu.SetRect(0,0);
        Menu.Render(gScreen);
        back_menu.Render(gScreen);
        while(quit1==3)
        {
            while(SDL_PollEvent(&gevent)!=0)
            {
                int xm = gevent.motion.x;
                int ym = gevent.motion.y;
                if(gevent.type == SDL_MOUSEBUTTONDOWN)
                {
                    std::cout<<"da vao day"<<'\n';
                    if (check_mouse(xm, ym, back_menu.GetRect()) && gevent.button.button == SDL_BUTTON_LEFT) {
                            quit1 = 0;
                            goto label;
                            std::cout<<quit1<<'\n';
                        }
                }

            }
          SDL_RenderPresent(gScreen);
        }
    }



      //introduction_.xuat_char();





}
