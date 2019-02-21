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
#include "Config.hpp"
#include "rapidxml.hpp"
#include <string.h>
#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "rapidxml_print.hpp"
#include "rapidxml_iterators.hpp"
#include "rapidxml_utils.hpp"

#include <sstream>

////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
using namespace std;
using namespace rapidxml;
namespace x
{
	class xml_Reader
	{

		////////////////////////////////////////////////////////////
		// Declaracion de funciones		
		////////////////////////////////////////////////////////////

	public:

		////////////////////////////////////////////////////////////
		/// \brief	Carga los valores de la malla desde un xml
		///	@param	number_of_arguments		numero de valores
		///	@param	arguments				array de valores
		///	@param	file_path				path del xml
		////////////////////////////////////////////////////////////
		vector<string> API load_values_from_XML(int number_of_arguments, char *arguments[], string file_path);
		

		////////////////////////////////////////////////////////////
		/// \brief	Guarda los valores actuales de la malla en un xml
		///	@param	arguments		valores de cada argumento
		////////////////////////////////////////////////////////////
		void API save_values_to_XML(vector<string> arguments);
	};
}