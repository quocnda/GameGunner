#include "CommonFunc.h"
#include "BaseObject.h"
#include "MainObject.h"
#include "Map.h"
#include "ThreatObject.h"
#include "BossObject.h"


using namespace std;

BaseObject gBackground;
MainObject main_obj;
GameMap game_map;
BossObject p_boss;
//ThreatObject p_threat;

bool init() {
   gWindow=SDL_CreateWindow("GPA 4.0",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,SCREEN_WIDTH,SCREEN_HEIGHT,SDL_WINDOW_SHOWN);
   gScreen=SDL_CreateRenderer(gWindow,-1,SDL_RENDERER_ACCELERATED);
   return gScreen!=NULL;
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
    int num_threat=25;
    if(init()) {
        if(loadmedia())
        {
            main_obj.LoadImg("naruto1.png",gScreen);
            main_obj.SetClip();
            main_obj.settocdo(2);
            p_boss.LoadImg("Boss.png",gScreen);
            p_boss.SetClip();
            p_boss.Set_pos(2240,448);

            std::vector<Bullet*> p_bullet_boss;
            for(int i=0;i<16;i++) {
                Bullet* p_bullet_boss_=new Bullet();
                p_bullet_boss_->LoadImg("laser.png",gScreen);
                p_bullet_boss_->set_pos(2240,448);
                p_bullet_boss_->set_val_bullet(dx[i]);
                p_bullet_boss_->set_val_bullet_y(dy[i]);
                p_bullet_boss_->set_is_move(true);
                p_bullet_boss.push_back(p_bullet_boss_);

            }
            p_boss.Set_amo_list(p_bullet_boss);

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
            std::cout<<mapX.max_x_<<" "<<mapX.max_y_<<'\n';
            //game_map.xuatMap();
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
               p_boss.SetMapXY(map_data.start_x_,map_data.start_y_);

                game_map.SetMap(map_data);
                 game_map.DrawMap(gScreen);
                 main_obj.Show(gScreen);

                 p_boss.Show(gScreen);
                 p_boss.MakeBullet(map_data,gScreen);

                 main_obj.HandleBullet(gScreen,map_data);

                 /* p_threat[20]->SetMapXY(map_data.start_x_,map_data.start_y_);
                    p_threat[20]->DoPlayer(map_data);
                    //p_threat[20]->MakeBullet(gScreen,SCREEN_WIDTH,SCREEN_HEIGHT);
                    p_threat[20]->Show(gScreen);
                  bool check=p_threat[20]->CheckToBullet(main_obj);

                  */
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
                 if(num_threat<=0&&p_threat.size()==0) {
                            std::cout<<"ban da thang";
                    }


        for(int i = 0; i < p_threat.size(); i++){
            if(!p_threat[i]->is_alive()){
                    std::cout<<"da chet"<<'\n';
                p_threat.erase(p_threat.begin() + i);
            }
        }




                 SDL_Delay(10);
                  SDL_RenderPresent(gScreen);




            }
        }
        else {cout<<"loi day ne";}
    }
    else {cout<<"losi day";}
    close();
    return 0;
}
