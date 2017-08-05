#include "game.h"

Game::Game()
{
  quit=false;
}
int Game::init()
{
  //sdl img init
  if ((IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG) != IMG_INIT_PNG){
    logSDLError(std::cout, "IMG_Init");
    SDL_Quit();
    return 1;
  }
  //sdl init
  if (SDL_Init(SDL_INIT_EVERYTHING) != 0){
    logSDLError(std::cout, "SDL_Init");
    return 1;
  }
  //make window
  window = SDL_CreateWindow("v1", 100, 100, SCREEN_WIDTH,
  SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
  if (window == nullptr){
    logSDLError(std::cout, "CreateWindow");
    SDL_Quit();
    return 1;
  }
  //link renderer
  renderer = SDL_CreateRenderer(window, -1,SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (renderer == nullptr){
    logSDLError(std::cout, "CreateRenderer");
    cleanup(window);
    SDL_Quit();
    return 1;
  }
  GraphicLib::init(renderer);
  w= new Window;
  //xml analysis
  file<> xmlFile("texture.xml");
  xml_document<> doc;    // character type defaults to char
  doc.parse<0>(xmlFile.data());    // 0 means default parse flags
  xml_node <>*root=doc.first_node();
  xml_node<>*texture=root->first_node();
  //Layer
  Layer* l0=new Layer(stoi(texture->first_node("source_id")->value()),
  renderer,
  stoi(texture->first_node("x")->value()),
  stoi(texture->first_node("y")->value()),"bg");
  w->add(l0);

  texture=texture->next_sibling();
  Layer* l1=new Layer(stoi(texture->first_node("source_id")->value()),
  renderer,
  stoi(texture->first_node("x")->value()),
  stoi(texture->first_node("y")->value()),"circle");
  w->add(l1);
  return 0;
}
void Game::run()
{
  thread f(menu,this);
  render();
  f.join();
}
void Game::render()
{
  	//main loop init

    int count=0;
  	SDL_Event e;
  	while (!quit)
  	{
  		//logic
      count++;
  		while (SDL_PollEvent(&e))
  		{

  			if (e.type == SDL_QUIT)
  				quit = true;
  			//Use number input to select which clip should be drawn
  			if (e.type == SDL_KEYDOWN)
  			{
  				switch (e.key.keysym.sym){
  					case SDLK_ESCAPE:
  						quit = true;
  						break;
  					default:
  						break;
  				}
  			}
  		}
  		//render
  		SDL_RenderClear(renderer);
      w->render(renderer);
  		//l0.render(renderer);
  		//renderTexture(l1.getTexture(), renderer, 0, 0, &clips[useClip]);
  		SDL_RenderPresent(renderer);
  		SDL_Delay(50);
  	}
    cleanup(renderer, window);
    IMG_Quit();
    SDL_Quit();
}
void Game::menu()
{
  int choice=0;
  while(true)
  {
    for(int i=0;i<w->getSize();i++)
    {
      cout<<i<<". Name: "<<w->getName(i)<<" Status: "<<w->getRender(i)<<endl;
    }
    cout<<"Choose:"<<endl;
    cin>>choice;
    if(choice==-1)
    {
      quit=true;
      break;
    }
    else
      w->toggleRender(choice);
  }
}
