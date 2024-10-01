#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

typedef struct {
	int id;
	int c1;
	int c2;
} subthr_t;

void adjplace(std::vector<std::vector<int>> &tabellone, int tabsize, int t, int c1, int c2, bool b[]) {
	if((c1>0) and (tabellone[c1-1][c2]==-1)) {
		tabellone[c1-1][c2]=t;
		b[0]=true;
	} else {
		b[0]=false;
	}
	if((c1<(tabsize-1)) and (tabellone[c1+1][c2]==-1)) {
		tabellone[c1+1][c2]=t;
		b[1]=true;
	} else {
		b[1]=false;
	}
	if((c2>0) and (tabellone[c1][c2-1]==-1)) {
		tabellone[c1][c2-1]=t;
		b[2]=true;
	} else {
		b[2]=false;
	}
	if((c2<(tabsize-1)) and (tabellone[c1][c2+1]==-1)) {
		tabellone[c1][c2+1]=t;
		b[3]=true;
	} else {
		b[3]=false;
	}
}

int main(int argc, char* argv[]) {
	int framedelay = 1000/60; //60fps
	int tabsize_v[3] = {7,9,12};
	int tabsize;
	uint8_t colors[12][3] = {
	{0xFF,0,0},
	{0xFF,0x7F,0},
	{0xFF,0xFF,0},
	{0,0xFF,0},
	{0,0xAF,0xFF},
	{0,0,0xFF},
	{0x7F,0,0xFF},
	{0xFF,0,0xFF},
	{0xE7,0x54,0x80},
	{0x99,0x33,0x00},
	{0xD7,0xD7,0xD7},
	{0x00,0xFF,0xFF}};
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distr(tabsize_v[0], tabsize_v[2]);
	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		return -1;
	}
	SDL_Window* window = SDL_CreateWindow("cppQueen", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 175, 175, SDL_WINDOW_SHOWN);
	if (!window) {
		SDL_Quit();
		return -1;
	}
	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* randomsfc = IMG_Load("resources/sizeR.png");
	if(!randomsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* sizeLsfc = IMG_Load("resources/sizeL.png");
	if(!sizeLsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* sizeMsfc = IMG_Load("resources/sizeM.png");
	if(!sizeMsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* sizeSsfc = IMG_Load("resources/sizeS.png");
	if(!sizeSsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* queensfc = IMG_Load("resources/queen50.png");
	if(!queensfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* voidwsfc = IMG_Load("resources/void.png");
	if(!voidwsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Surface* winswsfc = IMG_Load("resources/winner.png");
	if(!winswsfc) {
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		SDL_Quit();
		return -1;
	}
	SDL_Texture* texturerandom = SDL_CreateTextureFromSurface(renderer, randomsfc);
	SDL_Texture* texturesizeL = SDL_CreateTextureFromSurface(renderer, sizeLsfc);
	SDL_Texture* texturesizeM = SDL_CreateTextureFromSurface(renderer, sizeMsfc);
	SDL_Texture* texturesizeS = SDL_CreateTextureFromSurface(renderer, sizeSsfc);
	SDL_Texture* texturequeen = SDL_CreateTextureFromSurface(renderer, queensfc);
	SDL_Texture* texturevoidw = SDL_CreateTextureFromSurface(renderer, voidwsfc);
	SDL_Texture* texturewinsw = SDL_CreateTextureFromSurface(renderer, winswsfc);
	// GameMode
	SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
	SDL_RenderClear(renderer);
	SDL_SetRenderDrawColor(renderer, 0xCF, 0xCF, 0xCF, 255);
	SDL_Rect rect_coord = {25, 25, 50, 50};
	SDL_RenderFillRect(renderer, &rect_coord);
	SDL_RenderCopy(renderer, texturesizeS, NULL, &rect_coord);
	rect_coord = {100, 25, 50, 50};
	SDL_RenderFillRect(renderer, &rect_coord);
	SDL_RenderCopy(renderer, texturesizeM, NULL, &rect_coord);
	rect_coord = {25, 100, 50, 50};
	SDL_RenderFillRect(renderer, &rect_coord);
	SDL_RenderCopy(renderer, texturesizeL, NULL, &rect_coord);
	rect_coord = {100, 100, 50, 50};
	SDL_RenderFillRect(renderer, &rect_coord);
	SDL_RenderCopy(renderer, texturerandom, NULL, &rect_coord);
	SDL_RenderPresent(renderer);
	bool running = true;
	SDL_Event e;
	while(running) {
		uint32_t frameStart = SDL_GetTicks();
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			} else if(e.type == SDL_MOUSEBUTTONDOWN) {
				int mouse_x = e.button.x;
				int mouse_y = e.button.y;
				if((mouse_x>=25) and (mouse_x<75) and (mouse_y>=25) and (mouse_y<75)) {
					tabsize = tabsize_v[0];
					running=false;
				}
				if((mouse_x>=100) and (mouse_x<150) and (mouse_y>=25) and (mouse_y<75)){
					tabsize = tabsize_v[1];
					running=false;
				}
				if((mouse_x>=25) and (mouse_x<75) and (mouse_y>=100) and (mouse_y<150)){
					tabsize = tabsize_v[2];
					running=false;
				}
				if((mouse_x>=100) and (mouse_x<150) and (mouse_y>=100) and (mouse_y<150)){
					tabsize = distr(gen);
					running=false;
				}
			}
		}
		uint32_t frameTime = SDL_GetTicks() - frameStart;
		int32_t frameDiff = (int32_t)(framedelay - frameTime);
		if(frameDiff>0)
			SDL_Delay(frameDiff);
	}
	// Generate empty structures
	std::vector<std::vector<int>> tabellone;
	std::vector<std::vector<int>> spawncoords;
	std::vector<int> spawnpoints1;
	std::vector<int> spawnpoints2;
	std::vector<int> queens_x;
	std::vector<int> queens_y;
	std::vector<bool> queens_cls;
	std::vector<std::vector<int>> queens_pos;
	for (int a=0;a<tabsize;a++) {
		std::vector<int> tmp_v(tabsize);
		std::fill(tmp_v.begin(),tmp_v.end(),-1);
		tabellone.push_back(tmp_v);
		spawnpoints1.push_back(a);
		spawnpoints2.push_back(a);
		queens_x.push_back(-1);
		queens_y.push_back(-1);
		spawncoords.push_back(std::vector<int>());
		queens_cls.push_back(false);
		queens_pos.push_back(std::vector<int>({-1,-1}));
	}
	// Random spawn starting points
	int nspawns = spawnpoints1.size();
	int i=0;
	while(nspawns) {
		std::uniform_int_distribution<> distrsp(0, nspawns-1);
		int r1 = distrsp(gen);
		int r2 = distrsp(gen);
		int c1 = spawnpoints1[r1];
		int c2 = spawnpoints2[r2];
		spawncoords[i].push_back(c1);
		spawncoords[i].push_back(c2);
		tabellone[c1][c2]=i;
		spawnpoints1.erase(spawnpoints1.begin()+r1);
		spawnpoints2.erase(spawnpoints2.begin()+r2);
		nspawns = spawnpoints1.size();
		i++;
	}
	// Popolate cells
	int subthr_cnt=0;
	std::vector<subthr_t> subthr_arr;
	for(subthr_cnt=0;subthr_cnt<tabsize;subthr_cnt++) {
		subthr_arr.push_back({subthr_cnt,spawncoords[subthr_cnt][0],spawncoords[subthr_cnt][1]});
	}
	// Expand cells
	int exp_cycles=0;
	std::uniform_int_distribution<> distyesno(1, 100);
	while(subthr_cnt) {
		int new_cnt=0;
		std::vector<subthr_t> new_vett;
		for(int i=0;i<subthr_cnt;i++) {
			bool ret_vett[4];
			int prob = (exp_cycles>250) ? 100 : distyesno(gen); // expand cycles > 250 : assign 100% prob
			if(prob>25) { // 25% to place cell at this round
				adjplace(tabellone,tabsize,subthr_arr[i].id,subthr_arr[i].c1,subthr_arr[i].c2,ret_vett);
				if(ret_vett[0]) {
					new_vett.push_back({subthr_arr[i].id,subthr_arr[i].c1-1,subthr_arr[i].c2});
					new_cnt=new_cnt+1;
				}
				if(ret_vett[1]) {
					new_vett.push_back({subthr_arr[i].id,subthr_arr[i].c1+1,subthr_arr[i].c2});
					new_cnt=new_cnt+1;
				}
				if(ret_vett[2]) {
					new_vett.push_back({subthr_arr[i].id,subthr_arr[i].c1,subthr_arr[i].c2-1});
					new_cnt=new_cnt+1;
				}
				if(ret_vett[3]) {
					new_vett.push_back({subthr_arr[i].id,subthr_arr[i].c1,subthr_arr[i].c2+1});
					new_cnt=new_cnt+1;
				}
			} else {
				new_vett.push_back({subthr_arr[i].id,subthr_arr[i].c1,subthr_arr[i].c2});
				new_cnt=new_cnt+1;
			}
			exp_cycles++;
		}
		subthr_cnt=new_cnt;
		subthr_arr=new_vett;
		subthr_arr.resize(subthr_cnt);
		auto rng = std::default_random_engine {};
		std::shuffle(std::begin(subthr_arr), std::end(subthr_arr), rng);
	}
	std::cout << "cycles: " << exp_cycles << std::endl;
	// Game Loop
	SDL_SetWindowSize(window,50*tabsize+1,50*tabsize+1);
	SDL_DisplayMode display_mode = SDL_DisplayMode();
	SDL_GetCurrentDisplayMode(0, &display_mode);
	int new_x = (display_mode.w-50*tabsize+1)/2;
	int new_y = (display_mode.h-50*tabsize+1)/2;
	SDL_SetWindowPosition(window, new_x, new_y);
	running = true;
	bool gamelost = false;
	bool needrender = true;
	int queens_cnt = 0;
	while(running) {
		uint32_t frameStart = SDL_GetTicks();
		if(needrender) {
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			SDL_RenderClear(renderer);
			// Colors & cells
			for(int a=0;a<tabsize;a++) {
				for(int b=0;b<tabsize;b++) {
					int csel = tabellone[a][b];
					SDL_SetRenderDrawColor(renderer, colors[csel][0], colors[csel][1], colors[csel][2], 255);
					rect_coord = {50*a, 50*b, 50, 50};
					SDL_RenderFillRect(renderer, &rect_coord);
					if((queens_pos[csel][0]==a) and (queens_pos[csel][1]==b))
						SDL_RenderCopy(renderer, texturequeen, NULL, &rect_coord);
				}
			}
			SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
			for(int a=0;a<(tabsize+1);a++) {
				SDL_RenderDrawLine(renderer,0,50*a,50*tabsize, 50*a);
				SDL_RenderDrawLine(renderer,50*a,0,50*a,50*tabsize);
			}
			// Game status
			rect_coord = {0,0, 50*tabsize+1, 50*tabsize+1};
			if(gamelost)
				SDL_RenderCopy(renderer, texturevoidw, NULL, &rect_coord);
			else if(queens_cnt==tabsize)
				SDL_RenderCopy(renderer, texturewinsw, NULL, &rect_coord);
			SDL_RenderPresent(renderer);
			needrender=false;
		}
		while (SDL_PollEvent(&e) != 0) {
			if (e.type == SDL_QUIT) {
				running = false;
				SDL_DestroyRenderer(renderer);
				SDL_DestroyWindow(window);
				SDL_Quit();
				return 0;
			} else if ((e.type == SDL_MOUSEBUTTONDOWN) and (!gamelost)) {
				int mouse_x = e.button.x;
				int mouse_y = e.button.y;
				int inp_a = mouse_x/50;
				int inp_b = mouse_y/50;
				int color_id = tabellone[inp_a][inp_b];
				bool succ = true;
				if(queens_pos[color_id][0]==-1) {
					queens_pos[color_id][0] = inp_a;
					queens_pos[color_id][1] = inp_b;
					if(queens_x[inp_a]==-1) {
						queens_x[inp_a]=color_id;
					} else {
						gamelost=true;
						succ=false;
					}
					if(queens_y[inp_b]==-1) {
						queens_y[inp_b]=color_id;
					} else {
						gamelost=true;
						succ=false;
					}
					if(succ)
						queens_cnt++;
					needrender=true;
				}
			}
		}
		uint32_t frameTime = SDL_GetTicks() - frameStart;
		int32_t frameDiff = (int32_t)(framedelay - frameTime);
		if(frameDiff>0)
			SDL_Delay(frameDiff);
	}
	// Close
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	SDL_Quit();
	return 0;
}

