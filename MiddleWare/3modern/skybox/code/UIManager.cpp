/*
ADRIAN PONCE BALSEIRO
ESNE G4.3 DDVJ
adrianpb95@gmail.com
10 / 06 / 2018
*/


////////////////////////////////////////////////////////////
// Headers
////////////////////////////////////////////////////////////
#include "UIManager.hpp"
#include <iostream>
#include <fstream>


////////////////////////////////////////////////////////////
// NameSpaces
////////////////////////////////////////////////////////////
namespace example
{

	UIManager::UIManager(vector<string> arguments_aux) 
	{
		//Guardo los argumentos de comandos o xml
		for (size_t i = 0; i < arguments_aux.size(); i++)
		{
			arguments.push_back(arguments_aux[i]);
		}
				
		//Guardo la ruta del directorio de trabajo deseado
		char buf[256];
		GetCurrentDirectoryA(256, buf);
		dir = string(buf);
	}



	MyScreen *  UIManager::create_UI(const string & path)
	{
		 //Read file content

		fstream xml_file(path, fstream::in);

		if (xml_file.good())
		{
			vector< char > xml_content;

			bool finished = false;

			do
			{
				int character = xml_file.get();

				if (character != -1)
				{
					xml_content.push_back((char)character);
				} else
					finished = true;
			} while (!finished);

			// Add a 0 at the end

			xml_content.push_back(0);

			// Create document model (DOM):

			xml_document< > document;

			document.parse< 0 >(xml_content.data());

			// Check if previous step worked

			xml_node< > * root = document.first_node();

			if (root && string(root->name()) == "Screen")
			{
				create_screen(root);
			}
		}
		
		return screen;
	}
	
	//Se lee la estructura del xml y se crean los elementos de la UI siguiendola
	MyScreen * UIManager::create_screen (const rapidxml::xml_node<> * screen_node)
	{
		string name;
		string width;
		string height;

		for (xml_attribute<> * attribute = screen_node->first_attribute (); attribute; attribute = attribute->next_attribute ())
		{
			if		(string(attribute->name()) == "name"  ) name    = attribute->value(); 
			else if (string(attribute->name()) == "width" ) width	= attribute->value(); 
			else if (string(attribute->name()) == "height") height  = attribute->value(); 			
		}
		
		screen = new MyScreen(name, stoi(width), stoi(height));
		int window_count = 0;
		for (xml_node<> * Window_node = screen_node->first_node(); Window_node; Window_node = Window_node->next_sibling())
		{					
			if (Window_node->type() == node_element)
			{
				if (string(Window_node->name()) == "Window")
				{		
					string name = Window_node->first_attribute("name")->value();
					int visible = stoi(Window_node->first_attribute("visible")->value());
					windows[window_count] = create_window(name, visible);

					for (xml_node<> * child_node = Window_node->first_node(); child_node; child_node = child_node->next_sibling())
					{
						if (child_node->type() == node_element)
						{
							if (string(child_node->name()) == "Label")
							{		
								char * name = child_node->first_attribute("name")->value();
								char * caption = child_node->first_attribute("caption")->value();
								create_label(windows[window_count], name, caption);
							}

							else if (string(child_node->name()) == "Layout")
							{				
								string type = child_node->first_attribute("type")->value();
								string orientation = child_node->first_attribute("orientation")->value();
								int size = stoi(child_node->first_attribute("size")->value());
								string alignment = child_node->first_attribute("alignment")->value();
								int margin = stoi(child_node->first_attribute("margin")->value());
								int spacing = stoi(child_node->first_attribute("spacing")->value());
								create_layout(windows[window_count], type, orientation, size, alignment, margin, spacing);
							}

							else if (string(child_node->name()) == "IntBox")
							{								
								int editable = stoi(child_node->first_attribute("editable")->value());
								int width = stoi(child_node->first_attribute("width")->value());
								int height = stoi(child_node->first_attribute("height")->value());
								int value = stoi(child_node->first_attribute("value")->value());
								int font = stoi(child_node->first_attribute("font")->value());
								string units = child_node->first_attribute("units")->value();
								string format = child_node->first_attribute("format")->value();
								int spinnable = stoi(child_node->first_attribute("spinnable")->value());
								int min = stoi(child_node->first_attribute("min")->value());
								int max = stoi(child_node->first_attribute("max")->value());
								int increment = stoi(child_node->first_attribute("increment")->value());

								create_intbox(windows[window_count], editable, width, height,value,  font, units, format, spinnable, min, max, increment);
							}

							else if (string(child_node->name()) == "Button")
							{						
								string name = child_node->first_attribute("name")->value();
								int width = stoi(child_node->first_attribute("width")->value());
								int height = stoi(child_node->first_attribute("height")->value());
								int enable = stoi(child_node->first_attribute("enable")->value());
								int value = stoi(child_node->first_attribute("value")->value());

								create_button(windows[window_count], name, value, width, height, enable);
							}

							else if (string(child_node->name()) == "ColorPicker")
							{
								int r = stoi(child_node->first_attribute("r")->value());
								int g = stoi(child_node->first_attribute("g")->value());
								int b = stoi(child_node->first_attribute("b")->value());
								int width = stoi(child_node->first_attribute("width")->value());
								int height = stoi(child_node->first_attribute("height")->value());
								string side = child_node->first_attribute("side")->value();

								create_colorpicker(windows[window_count], r, g, b, width, height, side);								
							}

							else if (string(child_node->name()) == "Widget")
							{								
								Widget * widget = create_widget(windows[window_count]);

								for (xml_node<> * Widget_child_node = child_node->first_node(); Widget_child_node; Widget_child_node = Widget_child_node->next_sibling())
								{
									if (Widget_child_node->type() == node_element)
									{
										if (string(Widget_child_node->name()) == "Layout")
										{
											string type = Widget_child_node->first_attribute("type")->value();
											string orientation = Widget_child_node->first_attribute("orientation")->value();
											string alignment = Widget_child_node->first_attribute("alignment")->value();
											int margin = stoi(Widget_child_node->first_attribute("margin")->value());
											int spacing = stoi(Widget_child_node->first_attribute("spacing")->value());
											int size;

											string aux = Widget_child_node->first_attribute("size")->value();

											if (aux != "")
												size = stoi(Widget_child_node->first_attribute("size")->value());
											else
												size = 0;

											create_layout(widget, type, orientation, size, alignment, margin, spacing);
										}

										else if (string(Widget_child_node->name()) == "IntBox")
										{
											int editable = stoi(Widget_child_node->first_attribute("editable")->value());
											int width = stoi(Widget_child_node->first_attribute("width")->value());
											int height = stoi(Widget_child_node->first_attribute("height")->value());
											int value = stoi(Widget_child_node->first_attribute("value")->value());
											int font = stoi(Widget_child_node->first_attribute("font")->value());
											string units = Widget_child_node->first_attribute("units")->value();
											string format = Widget_child_node->first_attribute("format")->value();
											int spinnable = stoi(Widget_child_node->first_attribute("spinnable")->value());
											int min = stoi(Widget_child_node->first_attribute("min")->value());
											int max = stoi(Widget_child_node->first_attribute("max")->value());
											int increment = stoi(Widget_child_node->first_attribute("increment")->value());

											create_intbox(windows[window_count], editable, width, height, value, font, units, format, spinnable, min, max, increment);
										}

										else if (string(Widget_child_node->name()) == "Slider")
										{
											int value = stoi(Widget_child_node->first_attribute("value")->value());
											int width = stoi(Widget_child_node->first_attribute("width")->value());											
											create_slider(widget, value, width);
										}

										else if (string(Widget_child_node->name()) == "Button")
										{
											string name = Widget_child_node->first_attribute("name")->value();
											int width = stoi(Widget_child_node->first_attribute("width")->value());
											int height = stoi(Widget_child_node->first_attribute("height")->value());
											int enable = stoi(Widget_child_node->first_attribute("enable")->value());
											int value = stoi(Widget_child_node->first_attribute("value")->value());

											create_button(widget, name, value, width, height, enable);
										}


										else if (string(Widget_child_node->name()) == "CheckBox")
										{						
											string name = Widget_child_node->first_attribute("name")->value();
											int font = stoi(Widget_child_node->first_attribute("font")->value());
											int check = stoi(Widget_child_node->first_attribute("check")->value());											

											create_checkbox(widget, name, font, check);
										}
									}
								}
							}
						}
					}
				}
			}
			window_count++;
		}
		
		screen->performLayout();

		windows[0]->setPosition(Vector2i(screen->width() * 0.01, screen->height() * 0.01));
		windows[1]->setPosition(Vector2i((screen->width() * 0.99) - windows[1]->width(), screen->height() * 0.01));
		windows[2]->setPosition(Vector2i(screen->width() * 0.01, screen->height() * 0.99 - windows[2]->height()));		

		if (with_texture)
			texture_button->setEnabled(true);
		else
			texture_button->setEnabled(false);

		return screen;
	}

	Window * UIManager::create_window(string name, int visible)
	{
		Window * window = new Window(screen, name);
		window->setVisible(visible);
		return window;
	}

	void UIManager::create_label(Widget * parent, string name, string caption)
	{
		new Label(parent, name, caption);
	}

	void UIManager::create_layout(Widget * parent, string type, string orientation, int size, string alignment, int margin, int spacing)
	{
		Orientation orientation_aux;
		if (orientation == "Horizontal")
			orientation_aux = Orientation::Horizontal;
		else if (orientation == "Vertical")
			orientation_aux = Orientation::Vertical;

		Alignment alignment_aux;
		if (alignment == "Fill")
			alignment_aux = Alignment::Fill;
		else if (alignment == "Maximum")
			alignment_aux = Alignment::Maximum;
		else if (alignment == "Minimum")
			alignment_aux = Alignment::Minimum;
		else if (alignment == "Middle")
			alignment_aux = Alignment::Middle;

		if (type == "GridLayout")
		{					
			GridLayout *layout = new GridLayout(orientation_aux, size, alignment_aux, margin, spacing);
			layout->setColAlignment(
				{ Alignment::Maximum, Alignment::Fill });
			layout->setSpacing(0, 10);
			parent->setLayout(layout);
		}
		else if (type == "BoxLayout") 
		{
			BoxLayout *layout = new BoxLayout(orientation_aux, alignment_aux, margin, spacing);
			parent->setLayout(layout);
		}
		else if (type == "GroupLayout")
		{
			GroupLayout *layout = new GroupLayout();
			parent->setLayout(layout);
		}		
	}

	Widget * UIManager::create_widget(Widget * parent) 
	{
		Widget *widget = new Widget(parent);
		return widget;
	}

	void  UIManager::create_slider(Widget * parent, int value_aux, int width)
	{
		Slider *slider = new Slider(parent);		
		slider->setValue(stof(arguments.at(value_aux).c_str()) / 100);
		slider->setFixedWidth(140);	

		slider->setCallback([&, value_aux, this](float value) {				

			//Slider Definicion
			if(value_aux == 1)
			{
				float aux = value * 100;
				set_arguments(value_aux, to_string((int)aux));				
			}
			//Slider intensidad de la luz
			else if(value_aux == 15)
			{
				change_light_intensity(value);
			}
			//Slider diffuse de la luz
			else if (value_aux == 16)
			{
				change_light_diffuse(value);
			}			
		});		
	}

	void UIManager::create_intbox(Widget * parent, int editable, int width, int height, int value_aux, int font, string units, string format, int spinnable, int min, int max, int increment) 
	{
		auto intBox = new IntBox<int>(parent);
		intBox->setEditable(editable);
		intBox->setFixedSize(Vector2i(width, height));		
		intBox->setFontSize(font);		
		intBox->setSpinnable(spinnable);
		intBox->setMinValue(min);	
		intBox->setMaxValue(max);
		intBox->setValueIncrement(increment);

		//Width, Heitgh del mesh antes de crearlo
		if(value_aux < 4)
		intBox->setCallback([&, value_aux](float value){set_arguments(value_aux, std::to_string((int)(value))); });

		//valor de la altura
		else if (value_aux == 7)
			intBox->setCallback([&, value_aux](float value) {change_y(value); });

		//valor de la escala
		else if (value_aux == 8)
			intBox->setCallback([&, value_aux](float value) {change_scale(value); });

		//valor de la x de la luz
		else if (value_aux == 12)
			intBox->setCallback([&, value_aux](float value) {change_light_x(value); });

		//valor de la y de la luz
		else if (value_aux == 13)
			intBox->setCallback([&, value_aux](float value) {change_light_y(value); });

		//valor de la z de la luz
		else if (value_aux == 14)
			intBox->setCallback([&, value_aux](float value) {change_light_z(value); });
		

		if (units != "")
			intBox->setUnits(units);
		if (format != "")
			intBox->setFormat(format);
		if(value_aux != 0)
			intBox->setValue(atoi(arguments.at(value_aux).c_str()));
	}

	void UIManager::create_button(Widget * parent, string name, int value, int width, int height, int enable) 
	{
		Button *b = new Button(parent, name);		
		b->setFixedSize(Vector2i(width, height));

		//Abren ficheros tga : Mapa de altura, Textura
		if (value > 0)
		{ 
			if (value == 6)
				texture_button = b;

			b->setCallback([&, value] {
				string aux = file_dialog({ { "tga", "TARGA" } }, false);
				set_arguments(value, aux);
			});
		}
		
		else if (value < 0) 
		{
			//Guarda todos los arguemtos en un xml
			if (value == -1) 
			{
				b->setCallback([&, value] {
					xml_reader.save_values_to_XML(arguments);
					_chdir(dir.c_str());
				});				
			}
			//Crea la malla y actualiza la UI
			else 
			{
				b->setCallback([&, value] {
					createView();
				});
			}

		}		
		b->setEnabled(enable);
	
	}

	void UIManager::create_checkbox(Widget * parent, string name, int font, int check) 
	{
		Button * b = texture_button;
		CheckBox *cb = new CheckBox(parent, name);
		cb->setCallback([&, b](bool state)
		{
			cout << "Check box 1 state: " << state << endl;
			
			//Habilita/Deshabilita el boton de carga de textura
			if (state)
			{
				b->setEnabled(true);
				set_arguments(5, std::to_string(state));
			}
			else 
			{
				b->setEnabled(false);
				set_arguments(5, std::to_string(state));
			}
					
		});
		cb->setFontSize(font);
		cb->setChecked(atoi(arguments.at(5).c_str()));
		with_texture = (atoi(arguments.at(5).c_str()));
	}

	void UIManager::create_colorpicker(Widget * parent, int r, int g, int b, int width, int height, string side) 
	{
		Popup::Side side_aux;
		if (side == "Left")
			side_aux = Popup::Side::Left;
		else if (side == "Rigth")
			side_aux = Popup::Side::Right;	

		ColorPicker * cp_color = new nanogui::ColorPicker(parent, { atoi(arguments.at(r).c_str()) * 255, atoi(arguments.at(g).c_str()) * 255, atoi(arguments.at(b).c_str()) * 255, 255 });
		cp_color->setFixedSize({ width, height });
		cp_color->setSide(side_aux);

		//Color picker de la malla
		if (r == 9)
		{
			mesh_color = cp_color;
			cp_color->setFinalCallback([&](const nanogui::Color &c) {change_color(c.r(), c.g(), c.b()); });
		}
		//Color picker de la luz 
		else if(r == 17)
		{			
			cp_color->setFinalCallback([&](const nanogui::Color &c) {change_light_color(c.r(), c.g(), c.b()); });
		}		
	}	
}
