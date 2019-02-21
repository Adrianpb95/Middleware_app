/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#pragma once
#include <map>
#include <memory>
#include <string>
#include <functional>
#include "rapidxml.hpp"
#include <nanogui/nanogui.h>

#include "MyScreen.hpp"
#include <direct.h>
#include <windows.h>

#include "../../3modern/skybox/projects/vs-2017-DLL/code/xml_Reader.hpp"


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace std;
using namespace nanogui;
using namespace rapidxml;
using namespace x;
namespace example
{
	class UIManager
	{

	////////////////////////////////////////////////////////////
	// Declaracion de variables			
	////////////////////////////////////////////////////////////

	private:
		MyScreen * screen;						///<Pantalla sobre la que la aplicacion trabaja, y sobre la que realiza los cambios	

		Window *windows[2];						///<Ventanas de la aplicacion. Se guardan para poder ocultarlas y colocarlas como se desee

		vector<string> arguments;				///<Valores de la aplicacion, ya sean pasados por comando o por xml

		Button * texture_button;				///<Guardo el boton de la textura de la malla, para poder activarlo y desactivarlo con el checkbox
		bool with_texture;						///<Valor del checkbox del boton

		ColorPicker * mesh_color;				///<Guardo el colorpicker de la mesh para poder deshabilitarlo si la malla tiene textura

		string dir;								///<Guardo el directorio de trabajo para poder usar rutas relativas

		xml_Reader xml_reader;					///<DLL para poder poder leer y guardar xmls




	////////////////////////////////////////////////////////////
	// Declaracion de funciones			
	////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de UIManager: 	Guarda los argumentos de la aplicacion ya sean procedentes de comando o xml
		///	@param	arguments		Argumentos de la aplicacion
		////////////////////////////////////////////////////////////
		UIManager(vector<string> arguments);					

		////////////////////////////////////////////////////////////
		/// \brief	Lee el xml con la informacion de la UI y crea la pantalla 
		///	@param	path		Ruta del archivo xml con los layouts
		////////////////////////////////////////////////////////////
		MyScreen * create_UI(const string & path);			

		////////////////////////////////////////////////////////////
		/// \brief	Crea la pantalla con la estructura leida del xml de layouts
		///	@param	screen_node		Nodo raiz del layout, la escena
		////////////////////////////////////////////////////////////
		MyScreen * create_screen(const xml_node<> * screen_node);

		////////////////////////////////////////////////////////////
		/// \brief	Crea una ventana en la UI --> puede ser padre de otro elementos por eso se retorna y guarda
		///	@param	name		Nombre de la ventana
		///	@param	visible		Bool: se ve la ventana?
		////////////////////////////////////////////////////////////
		Window * create_window(string name, int visible);

		////////////////////////////////////////////////////////////
		/// \brief	Crea una widget en la UI --> puede ser padre de otro elementos por eso se retorna y guarda
		///	@param	parent		Padre del elemento
		////////////////////////////////////////////////////////////
		Widget * create_widget(Widget * parent);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un layout en la UI
		///	@param	parent			Padre del elemento
		///	@param	type			Tipo de layout
		///	@param	orientation		Orientacion del layout
		///	@param	size			Tamaño del layout
		///	@param	alignment		Alineacion del layout
		///	@param	margin			Margenes por los lados
		///	@param	spacing			Espaciado de elementos
		////////////////////////////////////////////////////////////
		void create_layout(Widget * parent, string type, string orientation, int size, string alignment, int margin, int spacing);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un label en al UI
		///	@param	parent			Padre del elemento
		///	@param	name			Nombre del label
		///	@param	caption			Formato de txt
		////////////////////////////////////////////////////////////
		void create_label(Widget * parent, string name, string caption);		

		////////////////////////////////////////////////////////////
		/// \brief	Crea un slider en al UI
		///	@param	parent			Padre del elemento
		///	@param	value			Nombre del slider
		///	@param	width			Ancho del slider
		////////////////////////////////////////////////////////////
		void create_slider(Widget * parent, int value, int width);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un intbox en al UI
		///	@param	parent			Padre del elemento
		///	@param	editable		Bool: es editable?
		///	@param	width			Ancho del intbox
		///	@param	height			Alto del intbox
		///	@param	value			Valor de su argumento
		///	@param	font			Tamaño de letra
		///	@param	units			Unidades
		///	@param	format			Formato de texto
		///	@param	spinnable		Bool: tiene spin?
		///	@param	min				Minimo valor
		///	@param	max				Maximo valor
		///	@param	increment		Incremento por spin
		////////////////////////////////////////////////////////////
		void create_intbox(Widget * parent, int editable, int width, int height, int value, int font, string units, string format, int spinnable, int min, int max, int increment);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un boton en al UI
		///	@param	parent			Padre del elemento
		///	@param	name			Nombre
		///	@param	value			Valor de su argumento
		///	@param	width			Ancho
		///	@param	height			Alto
		///	@param	enable			Bool: esta habilitado?
		////////////////////////////////////////////////////////////
		void create_button(Widget * parent, string name, int value, int width, int height, int enable);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un checkbox en al UI
		///	@param	parent			Padre del elemento
		///	@param	name			Nombre
		///	@param	font			Tamaño del txt
		///	@param	check			Bool: esta marcada?
		////////////////////////////////////////////////////////////
		void create_checkbox(Widget * parent, string name, int font, int check);

		////////////////////////////////////////////////////////////
		/// \brief	Crea un colorpicker en al UI
		///	@param	parent			Padre del elemento
		///	@param	r				Valor de su argumento R
		///	@param	g				Valor de su argumento G
		///	@param	b				Valor de su argumento B
		///	@param	width			Ancho
		///	@param	height			Alto
		///	@param	side			Lado del popup
		////////////////////////////////////////////////////////////
		void create_colorpicker(Widget * parent, int r, int g, int b, int width, int height, string side);
		
		////////////////////////////////////////////////////////////
		/// \brief	Crea la pantalla de trabajo de la aplicacion (la pantalla la mesh), y actualiza la UI
		////////////////////////////////////////////////////////////
		void createView()
		{
			screen->set_done(true, arguments);

			windows[0]->setVisible(false);
			windows[1]->setVisible(true);
			windows[2]->setVisible(true);

			if (atoi(arguments.at(5).c_str()))
				mesh_color->setEnabled(false);
		}

		////////////////////////////////////////////////////////////
		/// \brief	SETTER de un argumento determinado
		///	@param	i		Indice del argumento
		///	@param	argument		Valor del argumento
		////////////////////////////////////////////////////////////
		void set_arguments(size_t i, string argument)
		{
			arguments.at(i) = argument;

			//Si conseguir este argumento, se ha tenido que abrir un archivo, nos aseguramos de volver a directorio de trabajo original
			_chdir(dir.c_str());
		}
		
		////////////////////////////////////////////////////////////
		/// \brief	GETTER del view usado por la pantalla
		////////////////////////////////////////////////////////////
		shared_ptr<View> get_view()
		{
			return screen->get_view();
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la altura de la malla
		///	@param	y		Altura
		////////////////////////////////////////////////////////////
		void change_y(float y)
		{
			set_arguments(7, std::to_string(y));
			screen->change_y(y);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la escala de la malla
		///	@param	value	Escala
		////////////////////////////////////////////////////////////
		void change_scale(float value)
		{
			set_arguments(8, std::to_string(value));
			screen->change_scale(value);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del color de la malla
		///	@param	r	Valor del color R
		///	@param	g	Valor del color G
		///	@param	b	Valor del color B
		////////////////////////////////////////////////////////////
		void change_color(float r, float g, float b)
		{
			set_arguments(9, std::to_string(r));
			set_arguments(10, std::to_string(g));
			set_arguments(11, std::to_string(b));
			screen->change_color(r, g, b);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la posicion X de la luz
		///	@param	x	Pos en X
		////////////////////////////////////////////////////////////
		void change_light_x(float x)
		{
			set_arguments(12, std::to_string(x));
			screen->change_light_pos(x, atoi(arguments.at(13).c_str()), atoi(arguments.at(14).c_str()));
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la posicion Y de la luz
		///	@param	y	Pos en Y
		////////////////////////////////////////////////////////////
		void change_light_y(float y)
		{
			set_arguments(13, std::to_string(y));
			screen->change_light_pos(atoi(arguments.at(12).c_str()), y, atoi(arguments.at(14).c_str()));
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la posicion Z de la luz
		///	@param	z	Pos en Z
		////////////////////////////////////////////////////////////
		void change_light_z(float z)
		{
			set_arguments(14, std::to_string(z));
			screen->change_light_pos(atoi(arguments.at(12).c_str()), atoi(arguments.at(13).c_str()), z);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la intensidad de la luz
		///	@param	intensity	Valor intensidad
		////////////////////////////////////////////////////////////
		void change_light_intensity(float intensity)
		{
			set_arguments(15, std::to_string(intensity * 100));
			screen->change_light_intensity(intensity);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del diffuse de la luz
		///	@param	diffuse		Valor diffuse
		////////////////////////////////////////////////////////////
		void change_light_diffuse(float diffuse)
		{
			set_arguments(16, std::to_string(diffuse * 100));
			screen->change_light_diffuse(diffuse);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del color de la luz
		///	@param	r	Valor del color R
		///	@param	g	Valor del color G
		///	@param	b	Valor del color B
		////////////////////////////////////////////////////////////
		void change_light_color(float r, float g, float b)
		{
			set_arguments(17, std::to_string(r));
			set_arguments(18, std::to_string(g));
			set_arguments(19, std::to_string(b));
			screen->change_light_color(r, g, b);
		}
	};

}