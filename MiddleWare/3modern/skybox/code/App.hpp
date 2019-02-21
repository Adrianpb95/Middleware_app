
/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

	#include <glm\glm.hpp>
	#include <glm\gtc\matrix_transform.hpp>
	#include <glm\gtc\type_ptr.hpp>
	#include <glm\gtx\normal.hpp>
	#include <algorithm>
	#include <vector>
	#include <direct.h>


	#include <nanogui/glutil.h>
	#include <nanogui/screen.h>
	#include <nanogui/window.h>
	#include <nanogui/layout.h>
	#include <nanogui/label.h>
	#include <nanogui/checkbox.h>
	#include <nanogui/button.h>
	#include <nanogui/toolbutton.h>
	#include <nanogui/popupbutton.h>
	#include <nanogui/combobox.h>
	#include <nanogui/progressbar.h>
	#include <nanogui/entypo.h>
	#include <nanogui/messagedialog.h>
	#include <nanogui/textbox.h>
	#include <nanogui/slider.h>
	#include <nanogui/imagepanel.h>
	#include <nanogui/imageview.h>
	#include <nanogui/vscrollpanel.h>
	#include <nanogui/colorwheel.h>
	#include <nanogui/colorpicker.h>
	#include <nanogui/graph.h>
	#include <nanogui/tabwidget.h>
	#include <iostream>
	#include <string>


	#include "View.hpp"
	#include "Material_Shaders.hpp"
	#include "MyScreen.hpp"
	#include "../../3modern/skybox/projects/vs-2017-DLL/code/xml_Reader.hpp"


	#if defined(__GNUC__)
	#  pragma GCC diagnostic ignored "-Wmissing-field-initializers"
	#endif
	#if defined(_WIN32)
	#  pragma warning(push)
	#  pragma warning(disable: 4457 4456 4005 4312)
	#endif

	#include <stb_image.h>

	#if defined(_WIN32)
	#  pragma warning(pop)
	#endif
	#if defined(_WIN32)
	#  if defined(APIENTRY)
	#    undef APIENTRY
	#  endif
	#  include <windows.h>
	#endif




////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using std::cout;
using std::cerr;
using std::endl;
using std::string;
using std::vector;
using std::pair;
using std::to_string;

using namespace x;
namespace example
{
	class UIManager;
	class App{

		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		MyScreen * load_screen;					///<Pantalla de carga de xmls previa al inicio de la aplicacion
		MyScreen * mesh_screen;					///<Pantalla main de la aplicacion, con la malla de elevacion y todos sus datos

		nanogui::GLShader mShader;				///<Shader usado para el render
		
		UIManager *ui;							///<Manager de la interfaz de usuario

		xml_Reader xml_reader;					///<DLL para leer y guardar xmls con valores para cargar en la malla

		string dir;								///<Ruta del directorio raiz, ya que al abrir y cerrar carpetas, se cambia constantemente y las rutas relativas no funcionan

		bool mesh_screen_up;					///<Bool para indicar cuando pintar una pantalla y cuando otra




	////////////////////////////////////////////////////////////
	// Declaracion de funciones			
	////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de la aplicacion: Crea la interfaz de usuario y actualiza la malla con la informacion de los comandos/xmls
		///	@param	number_of_arguments		Cantidad de argumentos recibidos por comando
		///	@param	arguments				Array de argumentos por comando que usara la aplicacion
		////////////////////////////////////////////////////////////
		App(int number_of_arguments, char *arguments[]);

		////////////////////////////////////////////////////////////
		/// \brief	Destructor de la aplicacion: Se libera el shader
		////////////////////////////////////////////////////////////
		~App() 
		{
			mShader.free();
		}

		////////////////////////////////////////////////////////////
		/// \brief	Run de la aplicacion, pinta los elementos por pantalla
		////////////////////////////////////////////////////////////
		void launch()
		{			
			//Segunda pantalla --> La mesh y la UI completa (el core de la aplicacion)
			if (mesh_screen_up)
			{
				mesh_screen->drawAll();
				mesh_screen->setVisible(true);				
			}
			//Primera pantalla --> Opciones para cargar xml
			else
			{
				load_screen->drawAll();
				load_screen->setVisible(true);				
			}				
		}		
	};
}