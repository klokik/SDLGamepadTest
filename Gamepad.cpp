#include <SDL2/SDL.h>
#include <iostream>


SDL_GameController *pad;

void onControllerAdd(const SDL_ControllerDeviceEvent sdlEvent);
void onControllerRemove(const SDL_ControllerDeviceEvent sdlEvent);
void onAxisChange(const SDL_ControllerAxisEvent sdlEvent);
void onButtonChange(const SDL_ControllerButtonEvent sdlEvent);

void init(void)
{
	SDL_InitSubSystem(SDL_INIT_GAMECONTROLLER);
}

void loop()
{
	bool done = false;
	SDL_Event event;

	while(SDL_WaitEvent(&event)&&!done)
	{
		switch(event.type)
		{
		case SDL_CONTROLLERDEVICEADDED:
			onControllerAdd(event.cdevice);
			break;
		case SDL_CONTROLLERDEVICEREMOVED:
			onControllerRemove(event.cdevice);
			break;
		case SDL_CONTROLLERBUTTONDOWN:
        case SDL_CONTROLLERBUTTONUP:
        	onButtonChange(event.cbutton);

        	if(event.cbutton.button == 5)
        	{
        		std::cout<<"Desired key pressed, exiting."<<std::endl;
        		done = true;
        	}
			break;

		case SDL_CONTROLLERAXISMOTION:
			onAxisChange(event.caxis);
			break;
		}
	}
}

void onControllerAdd(const SDL_ControllerDeviceEvent sdlEvent)
{
	auto id = sdlEvent.which;

	if(SDL_IsGameController(id))
	{
		/*SDL_GameController **/pad = SDL_GameControllerOpen(id);

		if(pad)
		{
			SDL_Joystick *joy = SDL_GameControllerGetJoystick(pad);
			int instanceID = SDL_JoystickInstanceID(joy);

			std::cout<<"Joystick added: id"<<instanceID<<" "<<SDL_GameControllerName(pad)<<std::endl;
		}
	}
}

void onControllerRemove(const SDL_ControllerDeviceEvent sdlEvent)
{
	SDL_GameControllerClose(pad);
	std::cout<<"Gamepad disconnected"<<std::endl;
}

void onAxisChange(const SDL_ControllerAxisEvent sdlEvent)
{
	std::cout<<"Axis "<<(int)sdlEvent.axis<<" changed: "<<sdlEvent.value<<std::endl;
}

void onButtonChange(const SDL_ControllerButtonEvent sdlEvent)
{
	std::cout<<"Button "<<(int)sdlEvent.button<<" changed: "<<(int)sdlEvent.state<<std::endl;
}

int main(void)
{
	init();

	loop();

	if(SDL_WasInit(SDL_INIT_GAMECONTROLLER))
		SDL_QuitSubSystem(SDL_INIT_GAMECONTROLLER);

	SDL_Quit();
}