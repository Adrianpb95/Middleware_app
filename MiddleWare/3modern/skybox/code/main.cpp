
/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


#include "App.hpp"

using namespace example;
int main(int number_of_arguments, char * arguments[]) 
{
	try {
		nanogui::init();

		{
		//Creacion de la aplicacion, con valores de comandos predefinidos como argumentos
			nanogui::ref<App> app = new App(number_of_arguments, arguments);
			app->launch();	
			nanogui::mainloop();
		}
		nanogui::shutdown();
	}
	catch (const std::runtime_error &e) {
		std::string error_msg = std::string("Caught a fatal error: ") + std::string(e.what());
#if defined(_WIN32)
		MessageBoxA(nullptr, error_msg.c_str(), NULL, MB_ICONERROR | MB_OK);
#else
		std::cerr << error_msg << endl;
#endif
		return -1;
	}

	return 0;
}
