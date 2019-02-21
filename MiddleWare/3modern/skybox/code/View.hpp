
/* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * *\
 *                                                                             *
 *  Started by Ángel on march of 2014                                          *
 *                                                                             *
 *  This is free software released into the public domain.                     *
 *                                                                             *
 *  angel.rodriguez@esne.edu                                                   *
 *                                                                             *
\* * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * * */

/*
	EDITED BY:
	ADRIAN PONCE BALSEIRO
	ESNE G4.3 DDVJ
	adrianpb95@gmail.com
	10 / 06 / 2018
*/

#ifndef VIEW_HEADER
#define VIEW_HEADER


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "Camera.hpp"
#include <string>
#include <iostream>
#include "Elevation_Mesh.hpp"
#include "Material.hpp"
#include <map>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace std; 
namespace example
{
    class View
    {

	////////////////////////////////////////////////////////////
	// Declaracion de variables			
	////////////////////////////////////////////////////////////

    private:

		std::shared_ptr< Camera > camera;							///<Elemento camara de la escena       
		std::shared_ptr< Elevation_Mesh > elevation_mesh;			///<Elemento malla de elevacion de la escena
		std::map<std::string, shared_ptr< Material>> materials;		///<Contenedor de materiales
			
        int    width;												///<Ancho ventana			
        int    height;												///<Alto ventana				

		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

    public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor default
		////////////////////////////////////////////////////////////
		View() {};
		////////////////////////////////////////////////////////////
		/// \brief	Constructor de View:	Crea la escena a renderizar y el postproceso de toda la ventana
		///	@param	width			Ancho de la ventana
		///	@param	height			Alto de la ventana
		///	@param	arguments		Valores de la aplicacion para darle a la malla
		////////////////////////////////////////////////////////////
        View(int width, int height, std::vector<std::string> arguments);
		
		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el movimiento de la camara y el movimiento de los elementos de la escena
		////////////////////////////////////////////////////////////
        void update   ();

		////////////////////////////////////////////////////////////
		/// \brief	Dibuja la escena:	Gestiona los diferentes shaders llamando al render de cada elemento
		////////////////////////////////////////////////////////////
        void render   ();

		////////////////////////////////////////////////////////////
		/// \brief	Configura el tamaño de la ventana
		///	@param	width		Ancho de la ventana
		///	@param	height		Alto de la ventana
		////////////////////////////////////////////////////////////
        void resize   (int width, int height);

		////////////////////////////////////////////////////////////
		/// \brief	Actualiza la altura de la malla
		///	@param	height		Altura de la malla
		////////////////////////////////////////////////////////////
		void change_y(int height) { materials["eleccion"]->change_y(height); }

		////////////////////////////////////////////////////////////
		/// \brief	Actualiza la escala de la malla
		///	@param	value		Multiplicador de escala
		////////////////////////////////////////////////////////////
		void change_scale(int value) { elevation_mesh->change_scale(value); }

		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el color de la malla
		///	@param	r		Componente R del color de la malla
		///	@param	g		Componente G del color de la malla
		///	@param	b		Componente B del color de la malla
		////////////////////////////////////////////////////////////
		void change_color(float r, float g, float b) { materials["eleccion"]->change_color(Point3f{ r,g,b }); }


		////////////////////////////////////////////////////////////
		/// \brief	Actualiza la posicion de la luz
		///	@param	x		Posicion x de la luz
		///	@param	y		Posicion y de la luz
		///	@param	z		Posicion z de la luz
		////////////////////////////////////////////////////////////
		void change_light_pos(float x, float y, float z) { materials["eleccion"]->configure_light(Point3f{ x, y, z }, materials["eleccion"]->get_light_intensity(), materials["eleccion"]->get_light_diffuse(), materials["eleccion"]->get_light_color()); }


		////////////////////////////////////////////////////////////
		/// \brief	Actualiza la intensidad de la luz ambiente
		///	@param	intensity		Intensidad de la luz ambiente
		////////////////////////////////////////////////////////////
		void change_light_intensity(float intensity) { materials["eleccion"]->configure_light(materials["eleccion"]->get_light_pos(), intensity, materials["eleccion"]->get_light_diffuse(), materials["eleccion"]->get_light_color());	}


		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el diffuse de la luz ambiente
		///	@param	diffuse		Diffuse de la luz ambiente
		////////////////////////////////////////////////////////////
		void change_light_diffuse(float diffuse) { materials["eleccion"]->configure_light(materials["eleccion"]->get_light_pos(), materials["eleccion"]->get_light_intensity(), diffuse, materials["eleccion"]->get_light_color()); }

		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el color de la luz
		///	@param	r		Componente R del color de la malla
		///	@param	g		Componente G del color de la malla
		///	@param	b		Componente B del color de la malla
		////////////////////////////////////////////////////////////
		void change_light_color(float r, float g, float b) { materials["eleccion"]->configure_light(materials["eleccion"]->get_light_pos(), materials["eleccion"]->get_light_intensity(), materials["eleccion"]->get_light_diffuse(), Point3f{r, g, b});
		}
    };
}

#endif
