
/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////

#include "App.hpp"
#include "UIManager.hpp"


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace nanogui;
namespace example
{

	App::App(int number_of_arguments, char *arguments[])
	{
		//Guardo la direccion de la solucion para no perder el working directory
		char buf[256];
		GetCurrentDirectoryA(256, buf);
		dir = string(buf);		

		//Se crea la primera pantalla
		mesh_screen_up = false;
		load_screen = new MyScreen("Load Files", 300, 300);

		//Se crea una ventana sencilla con dos botones. La creo aqui en vez de en el xml, ya al solo usarse una vez, simplifica la aplicacion
		//Ventana
		Window * window = new Window(load_screen, "Load Files");

		//Layout
		GridLayout *layout = new GridLayout(Orientation::Horizontal, 1,	Alignment::Middle, 15, 15);
		window->setLayout(layout);

		//Boton de Open --> Abre xml con valores de la malla para cargarlos en la aplicacion
		Button *b = new Button(window, "Open");
		b->setFixedSize(Vector2i(150, 30));
		b->setCallback([&, number_of_arguments, arguments] {
			//Abre el fichero
			string file = file_dialog({ { "xml", "XML" } }, false);	
			//Vuelve a colocar el directorio de trabajo
			_chdir(dir.c_str());
			//Parsea los valores del xml a los argumentos de la aplicacion
			vector<string> aux = xml_reader.load_values_from_XML(number_of_arguments, arguments, file);
			//Y crea la UI con ellos y la Mesh
			ui = new UIManager(aux);
			mesh_screen = ui->create_UI("../../../../assets/UI_Layout.xml");
			mesh_screen->launch(mShader, ui->get_view());
			mesh_screen->setVisible(true);
			mesh_screen->performLayout();
			load_screen->setVisible(false);
			mesh_screen_up = true;
		});


		//Boton de Next --> Continua con la aplicacion: crea la UI y la malla sin cargar valores por xml, usara los pasados por comando. 
		b = new Button(window, "Next");
		b->setFixedSize(Vector2i(150, 30));
		b->setCallback([&, number_of_arguments, arguments] {

			//Se recogen los valores de los comandos
			vector<string> aux;
			for (size_t i = 0; i < number_of_arguments; i++)
			{
				aux.push_back(arguments[i]);
			}

			//Se crea la UI y la Mesh
			ui = new UIManager(aux);
			mesh_screen = ui->create_UI("../../../../assets/UI_Layout.xml");
			mesh_screen->launch(mShader, ui->get_view());
			mesh_screen->setVisible(true);
			mesh_screen->performLayout();
			load_screen->setVisible(false);
			mesh_screen_up = true;
		});

		
		//Coloca la primera pantalla en el centro 
		load_screen->performLayout();
		window->setPosition(Vector2i(load_screen->width() * 0.5 - window->width() * 0.5, load_screen->height() * 0.5 - window->height() * 0.5));
		
		//Inicializa el shader
		mShader.init(
			/* An identifying name */
			"a_simple_shader",

			/* Vertex shader */
			vertex_shader_code_color,

			/* Fragment shader */
			fragment_shader_code_color
		);

	}
}