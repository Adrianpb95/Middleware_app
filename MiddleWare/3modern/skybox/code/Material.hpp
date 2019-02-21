/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


#ifndef MATERIAL_HEADERS
#define MATERIAL_HEADERS

////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
	#include <memory>
	#include "Shader_Program.hpp"
	#include "Vertex_Shader.hpp"
	#include "Fragment_Shader.hpp"	

extern "C"
{
	#include "targa.h"
}

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
	class Material
	{
		////////////////////////////////////////////////////////////
		// Declaracion de variables			
		////////////////////////////////////////////////////////////

	private:

		std::shared_ptr< Texture > texture;			///<Color buffer para la textura

		bool   has_texture;							///<El material tiene textura (?)
		GLuint texture_id;							///<ID del buffer de textura

		GLint model_view_matrix_id;					///<ID para la matriz de transformacion
		GLint projection_matrix_id;					///<ID para la matriz de proyeccion
		GLint normal_matrix_id;						///<ID para la matriz de normales
		
		Shader_Program shader_program;				///<Shader que va a usar este material

		float height;								///<Altura de la malla
		Point3f mesh_color;							///<Color de la malla
		Point3f light_pos;							///<Posicion de la luz
		float light_intensity;						///<Intensidad de la luz ambiente
		float light_diffuse;						///<Diffuse de la luz ambiente
		Point3f light_color;						///<Color de la luz

		////////////////////////////////////////////////////////////
		// Declaracion de funciones			
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Constructor de Material:	Compila los shaders y la textura pasada por parametros
		/// @param	vertex_shader				Vertex shader elegido
		///	@param	fragment_shader				Fragment shader elegido
		///	@param	path						Ruta de la textura
		///	@param	y							Altura de la malla
		///	@param	color						Color de la malla
		///	@param	ligth_pos					Posicion de la luz
		///	@param	light_intensity				Intensidad luz ambiente
		///	@param	light_diffuse				Diffuse luz ambiente
		///	@param	light_color					Color de la luz
		
		////////////////////////////////////////////////////////////
		Material(const std::string & vertex_shader, const std::string & fragment_shader, const char * path, float y, Point3f color, Point3f light_pos, float light_intensity, float light_diffuse, Point3f light_color);

		////////////////////////////////////////////////////////////
		/// \brief	Destructor de Material: Se liberan la textura
		////////////////////////////////////////////////////////////
		~Material();
		
		////////////////////////////////////////////////////////////
		/// \brief	Configura la luz del shader
		///	@param	pos						Posicion de la luz
		///	@param	light_intensity			Intensidad de la luz ambiente
		///	@param	light_diffuse			Diffuse de la luz ambiente
		///	@param	light_color				Color de la luz
		////////////////////////////////////////////////////////////
		void configure_light(Point3f pos, float light_intensity, float light_diffuse, Point3f light_color);

		////////////////////////////////////////////////////////////
		/// \brief	Getter de la textura
		////////////////////////////////////////////////////////////
		std::shared_ptr< Texture > get_texture() { return texture;	}

		////////////////////////////////////////////////////////////
		/// \brief	Getter del ID de la matriz de transformacion
		////////////////////////////////////////////////////////////
		GLint get_model_view_id()				 { return model_view_matrix_id;  }		

		////////////////////////////////////////////////////////////
		/// \brief	Getter del ID de la matriz de proyeccion
		////////////////////////////////////////////////////////////
		GLint get_projection_id()				 { return projection_matrix_id;  }

		////////////////////////////////////////////////////////////
		/// \brief	Getter del ID de la matriz de normales
		////////////////////////////////////////////////////////////
		GLint get_normal_matrix_id()			 { return normal_matrix_id;		 }


		////////////////////////////////////////////////////////////
		/// \brief	Actualiza la altura de la malla
		///	@param	height				Altura de la malla
		////////////////////////////////////////////////////////////
		void change_y(float height);


		////////////////////////////////////////////////////////////
		/// \brief	Actualiza el color de la malla
		///	@param	color				Color de la malla
		////////////////////////////////////////////////////////////
		void change_color(Point3f color);

		////////////////////////////////////////////////////////////
		/// \brief	Activa el shader y actualiza sus cambios
		////////////////////////////////////////////////////////////
		void use()
		{			
			shader_program.use();
			configure_light(light_pos, light_intensity, light_diffuse, light_color);
			change_y(height);
			change_color(mesh_color);

			if (has_texture)
			{
				glBindTexture(GL_TEXTURE_2D, texture_id);
			}
		}		

		////////////////////////////////////////////////////////////
		/// \brief	Getter de la posicion de la luz
		////////////////////////////////////////////////////////////
		Point3f get_light_pos()			 { return light_pos; }

		////////////////////////////////////////////////////////////
		/// \brief	Getter del color de la luz
		////////////////////////////////////////////////////////////
		Point3f get_light_color()		 { return light_color; }

		////////////////////////////////////////////////////////////
		/// \brief	Getter de la intensidad ambiente de la luz
		////////////////////////////////////////////////////////////
		float	get_light_intensity()	 { return light_intensity; }

		////////////////////////////////////////////////////////////
		/// \brief	Getter del diffuse de la luz ambiente
		////////////////////////////////////////////////////////////
		float	get_light_diffuse()		 { return light_diffuse; }
		
				

	private:
		////////////////////////////////////////////////////////////
		/// \brief	Carga la textura copiando los pixeles en el buffer de textura
		///	@param	texture_file_path		Ruta de la textura
		////////////////////////////////////////////////////////////
		std::shared_ptr< Texture > load_texture(const char * texture_file_path);
	};
}
#endif

