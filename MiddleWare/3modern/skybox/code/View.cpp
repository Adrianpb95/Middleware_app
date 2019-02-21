
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


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "View.hpp"
#include <glm/glm.hpp>                          // vec3, vec4, ivec4, mat4
#include <glm/gtc/matrix_transform.hpp>         // translate, rotate, scale, perspective
#include <glm/gtc/type_ptr.hpp>                 // value_ptr

#include "Vertex_Shader.hpp"
#include "Fragment_Shader.hpp"
#include "Material_Shaders.hpp"

#include <iostream>								 // std::cout
#include <sstream>								 // std::istringstream
#include <string>								 // std::string



////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{
    View::View(int width, int height, std::vector<std::string> arguments_aux)
    {	
		
		//Variables cargadas desde parametros / xml
		bool with_texture = atoi(arguments_aux.at(5).c_str());
		Point3f color = { atoi(arguments_aux.at(9).c_str()), atoi(arguments_aux.at(10).c_str()), atoi(arguments_aux.at(11).c_str()) };
		Point3f light_pos = { atoi(arguments_aux.at(12).c_str()), atoi(arguments_aux.at(13).c_str()), atoi(arguments_aux.at(14).c_str()) };
		float intensity = stof(arguments_aux.at(15).c_str()) / 100;
		float diffuse = stof(arguments_aux.at(16).c_str()) / 100;
		Point3f light_color = { atoi(arguments_aux.at(17).c_str()), atoi(arguments_aux.at(18).c_str()), atoi(arguments_aux.at(19).c_str()) };
		int scale = atoi(arguments_aux.at(8).c_str());

		//mapa de altura
		materials["mapa"] = make_shared<Material>(vertex_shader_code, fragment_shader_code, arguments_aux.at(4).c_str(), 1.f, Point3f{1.f,1.f,1.f}, light_pos, intensity, diffuse, light_color);

		//Si la malla lleva textura, se elige el material con shader normal, por el contrario, se elige uno con color plano
		if (with_texture) { materials["eleccion"] = make_shared<Material>(vertex_shader_code, fragment_shader_code, arguments_aux.at(6).c_str(), atoi(arguments_aux.at(7).c_str()), color, light_pos, intensity, diffuse, light_color);	}			
		else { materials["eleccion"] = make_shared<Material>(vertex_shader_code_color, fragment_shader_code_color, arguments_aux.at(6).c_str(), atoi(arguments_aux.at(7).c_str()), color, light_pos, intensity, diffuse, light_color);	}
			
		//Creacion de los elementos de la escena
		camera.reset(new Camera());			
		
		elevation_mesh.reset(new Elevation_Mesh(materials["mapa"], materials["eleccion"], glm::vec3(0.f, -1.5f, -8.f), color, glm::vec3(1.f * scale, 1.f * scale, 1.f * scale),
							atoi(arguments_aux.at(1).c_str()), atoi(arguments_aux.at(1).c_str()), atoi(arguments_aux.at(2).c_str()),
							atoi(arguments_aux.at(3).c_str()), atoi(arguments_aux.at(7).c_str())));
				
		//Configuracion de elementos de OpenGL
        glEnable (GL_DEPTH_TEST);
        glEnable (GL_CULL_FACE);
				
		//Configuracion de la ventana
        resize (width, height);
    }

    void View::update ()
    {
		//Update de los elementos
		elevation_mesh->update();	
    }

    void View::render ()
    {		
		glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);		
      
		glClear(GL_DEPTH_BUFFER_BIT);			

		//Cada elemento tiene su propio material que gestiona los shaders
		elevation_mesh->render(*camera);		
    }

    void View::resize (int new_width, int new_height)
    {
        width  = new_width;
        height = new_height;		

        camera->set_ratio (float(width) / height);

		for (auto & mat : materials)
		{
			mat.second->use();
			glm::mat4 projection_matrix = camera->get_projection();
			glUniformMatrix4fv(mat.second->get_projection_id(), 1, GL_FALSE, glm::value_ptr(projection_matrix));
		}
		
        glViewport (0, 0, width, height);		
    }
}
