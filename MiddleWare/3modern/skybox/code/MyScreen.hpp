
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
#include "View.hpp"
#include <memory>
#include <nanogui\nanogui.h>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example {

	class MyScreen : public nanogui::Screen {


		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		bool view_done = false;					///<Bool: La malla se ha creado ya?
		nanogui::GLShader mShader;				///<Shader activo 
		std::shared_ptr<View> view;				///<Referencia a View, para poder pintarla y actualizarla en el update


		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de MyScreen:	Default, crea una screen con un cierto width y height
		///	@param	material_height		Material: mapa de altura
		////////////////////////////////////////////////////////////
		MyScreen(string name, int width, int heigth) : nanogui::Screen(Eigen::Vector2i(width, heigth), "ElevationTool"){}
		
		////////////////////////////////////////////////////////////
		/// \brief	Update: Actualiza el shader y la View para pintar por pantalla
		///	@param	flag				Bool: se actualiza view_done
		///	@param	arguments_aux		Argumentos para crear la malla
		////////////////////////////////////////////////////////////
		virtual void drawContents() {

			if (view_done)
			{
				mShader.bind();
				view->update();
				view->render();
			}

		}

		////////////////////////////////////////////////////////////
		/// \brief	SETTER del shader y la view una vez creados
		///	@param	mShader_aux			shader activo
		///	@param	view_aux			referencia a la view 
		////////////////////////////////////////////////////////////
		void launch(nanogui::GLShader mShader_aux, std::shared_ptr<View> view_aux)
		{
			mShader = mShader_aux;
			view = view_aux;
		}

		////////////////////////////////////////////////////////////
		/// \brief	Se crea el view y dentro la mesh
		///	@param	flag				Bool: se actualiza view_done
		///	@param	arguments_aux		Argumentos para crear la malla
		////////////////////////////////////////////////////////////
		void set_done(bool flag, std::vector<std::string> arguments_aux)
		{
			view_done = flag;
			view.reset(new View(1600, 900, arguments_aux));
		}

		////////////////////////////////////////////////////////////
		/// \brief	GETTER del view
		////////////////////////////////////////////////////////////
		std::shared_ptr<View> get_view()
		{
			return view;
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la altura de la malla
		///	@param	y		Altura
		////////////////////////////////////////////////////////////
		void change_y(float y)
		{			
			view->change_y(y);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la escala de la malla
		///	@param	value	Escala
		////////////////////////////////////////////////////////////
		void change_scale(float value)
		{			
			view->change_scale(value);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del color de la malla
		///	@param	r	Valor del color R
		///	@param	g	Valor del color G
		///	@param	b	Valor del color B
		////////////////////////////////////////////////////////////
		void change_color(float r, float g, float b)
		{			
			view->change_color(r, g, b);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la posicion de la luz
		///	@param	x	Pos en X
		///	@param	y	Pos en Y
		///	@param	z	Pos en Z
		////////////////////////////////////////////////////////////
		void change_light_pos(float x, float y, float z)
		{			
			view->change_light_pos(x, y, z);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION de la intensidad de la luz
		///	@param	intensity	Valor intensidad
		////////////////////////////////////////////////////////////
		void change_light_intensity(float intensity)
		{			
			view->change_light_intensity(intensity);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del diffuse de la luz
		///	@param	diffuse		Valor diffuse
		////////////////////////////////////////////////////////////
		void change_light_diffuse(float diffuse)
		{			
			view->change_light_diffuse(diffuse);
		}

		////////////////////////////////////////////////////////////
		/// \brief	ACTUALIZACION del color de la luz
		///	@param	r	Valor del color R
		///	@param	g	Valor del color G
		///	@param	b	Valor del color B
		////////////////////////////////////////////////////////////
		void change_light_color(float r, float g, float b)
		{			
			view->change_light_color(r, g, b);
		}
	};
}

