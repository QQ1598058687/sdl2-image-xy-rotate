#if defined(_WIN32)||defined(_WIN64)
#include <SDL.h>
#include <SDL_image.h>
#else
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#endif

#include <string>
using std::string;
#include <sstream>
using std::stringstream;
#include <iostream>
using std::cout;
using std::endl;

const int SCREEN_WIDTH = 1000, SCREEN_HEIGHT = 1000;
SDL_Window* gWindow;
SDL_Renderer *gRenderer;
SDL_Texture *gTexture;


void init() {
	/* 初始化SDL */
	SDL_Init(SDL_INIT_VIDEO);
	/* 线性纹理 */
	SDL_SetHint(SDL_HINT_MOUSE_TOUCH_EVENTS, "1");
	/* 产生窗口 */
	gWindow = SDL_CreateWindow("SDL Tutorial", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE);

	/* 即将初始化的渲染器驱动程序的索引，如果是-1表示flags标志的第一个可用驱动程序。 */
	gRenderer = SDL_CreateRenderer(gWindow, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	/* 初始化png加载 */
	IMG_Init(IMG_INIT_PNG);

}

void close()
{
	//释放图像
	SDL_DestroyTexture(gTexture);

	//释放窗口
	SDL_DestroyRenderer(gRenderer);
	SDL_DestroyWindow(gWindow);

	//退出子系统
	IMG_Quit();
	SDL_Quit();
}


void free()
{
	//释放纹理（如果存在）
	if (gTexture != NULL)
	{
		SDL_DestroyTexture(gTexture);
		gTexture = NULL;
	}
}

void loadFromFile(std::string path)
{

	free();

	//在指定路径加载图像
	SDL_Surface* loadedSurface = IMG_Load(path.c_str());
	SDL_SetColorKey(loadedSurface, SDL_TRUE, SDL_MapRGB(loadedSurface->format, 0, 0xFF, 0xFF));

	//从表面像素创建纹理
	gTexture = SDL_CreateTextureFromSurface(gRenderer, loadedSurface);

	//获取图像尺寸
// 	mWidth = loadedSurface->w;
// 	mHeight = loadedSurface->h;


	//摆脱旧的加载表面
	SDL_FreeSurface(loadedSurface);


}
int main(int argc, char *argv[]) {

	
	init();
	loadFromFile("Resources/HelloWorld.png");

	bool quit = false;

	//事件处理
	SDL_Event e;


	//三角形的顶点渲染。左上
	SDL_Vertex vertex_1 = { {0, 0}, {255, 255, 255, 255}, {0, 0} };
	//右上
	SDL_Vertex vertex_2 = { {200, 0}, {255, 255, 255, 255}, {1, 0} };
	//左下
	SDL_Vertex vertex_3 = { {0, 200}, {255, 255, 255, 255}, {0, 1} };

	//右下
	SDL_Vertex vertex_6 = { {200, 200}, {255, 255, 255, 255}, {1, 1} };



	SDL_Vertex vertices[] = {
		vertex_1,
		vertex_2,
		vertex_3,
// 		vertex_4,
// 		vertex_5,
		vertex_6
	};
	const int index[] = {
		0,1,2
		,1,2,3};

	//应用程序运行时
	size_t size = sizeof(vertices);

	decltype(vertices) vertices1 ;

	float sx = 1., sy = 1;
	float x = 100, y = 100;
	int cx = 200, cy = 200;
	float rx = 0, ry =-80;
	while (!quit)
	{
		//处理队列上的事件
		while (SDL_PollEvent(&e) != 0)
		{
			//用户请求退出
			if (e.type == SDL_QUIT)
			{
				quit = true;
			}

			//处理窗口事件
		//	handleEvent(e);
		}
		
		//仅在未最小化时绘制
		//if (!mMinimized)
		{
			//清屏
			SDL_SetRenderDrawColor(gRenderer, 0xFF, 0xFF, 0xFF, 0xFF);
			SDL_RenderClear(gRenderer);

			//渲染文本纹理
			//SDL_Rect renderQuadA = { 400,400 ,mWidth, mHeight };


			

			memcpy(vertices1, vertices, size);
			float radiansX = -(rx* 0.01745329252f);
			float radiansY = -(ry* 0.01745329252f);
			float cosx = cosf(radiansX);
			float sinx = sinf(radiansX);
			float cosy = cosf(radiansY);
			float siny = sinf(radiansY);
			cout << "角度 rx =" << rx << " ry =" << ry << endl;
			cout << "角度 radiansX =" << radiansX << " radiansY =" << radiansY << endl;
			cout << "cosX= " << cosx << " sinX = " << sinx << " cosY =" << cosy << " sinY =" << siny << " " << endl;
			cout << "=============================\n";
			

			for (int i =0;i<sizeof(vertices1)/sizeof(*vertices1);++i)
			{
// 				float halfRadx = x / 2.f* 0.01745329252f, halfRady =x / 2.f* 0.01745329252f, 
// 					halfRadz = x == y ? -x / 2.f* 0.01745329252f : 0;
// 				float coshalfRadx = cosf(halfRadx), sinhalfRadx = sinf(halfRadx), coshalfRady = cosf(halfRady), sinhalfRady = sinf(halfRady), coshalfRadz = cosf(halfRadz), sinhalfRadz = sinf(halfRadz);					
				// 0.01745329252f = 3.14/180
				

				cout << "------------------------"<<i<<"-----------------" << endl;
				
				cout <<"position.x="<< vertices1[i].position.x << " position.x=" << vertices1[i].position.y << endl;
				vertices1[i].position = {



					x + (vertices1[i].position.x - x)* cosy - (vertices1[i].position.y - y)*sinx,
					y + (vertices1[i].position.x - x)*siny + (vertices1[i].position.y - y)*cosx

					
				
				};
				cout << "计算后的顶点数值:" << endl;
				cout <<"position.x ="<< vertices1[i].position.x << "  position.y=" << vertices1[i].position.y << endl;
				
			}

			for (int i = 0; i < sizeof(vertices1) / sizeof(*vertices1); ++i)
			{
				vertices1[i].position = {
					vertices1[i].position.x*sx + cx * ( sx) ,
				vertices1[i].position.y*sy + cy * ( sy) 
				};
			}

			ry -=1;
			rx -= 5;
			SDL_Point pointer =  { 0,0  };
			SDL_RenderGeometry(gRenderer, gTexture, vertices1, 4, index, 6);
			//SDL_RenderCopyEx(gRenderer, gTexture, 0, &renderQuadA, r, &pointer, SDL_FLIP_NONE);

			SDL_Rect renderQuadB = { 200,500,200,200 };
			SDL_RenderCopyEx(gRenderer, gTexture, 0, &renderQuadB, 90, nullptr, SDL_FLIP_NONE);
			//更新画面
		
			SDL_RenderPresent(gRenderer);
		}
	}
	
	//释放资源并关闭 SDL
	close();

	return 0;
}
