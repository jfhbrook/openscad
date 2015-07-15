#include "lex.h"
#include <fstream>
#include <iostream>
Lex::Lex()
{
	
}

void Lex::rules(){

	int s_size = sizeof(std::string);
	std::string keywords[] = {"var", "module", "function", "use", "echo", "include", "import", "group", "projection", "render", "surface","def", "enum", "struct", "fn", "typedef", "file", "namespace", "package", "interface", "param", "see","return", "class", "brief", "if", "else", "let", "for", "undef"};
	int keywords_count = (sizeof(keywords)/s_size);

	std::string transformations[] = {"translate", "rotate", "child", "scale", "linear_extrude", "rotate_extrude", "resize", "mirror", "multmatrix", "color", "offset", "hull", "minkowski", "children", "assign", "intersection_for"};
	int transformations_count = (sizeof(transformations)/s_size);

	 std::string booleans[] = {"union", "difference", "intersection", "true", "false"};
	int booleans_count = (sizeof(booleans)/s_size);

	std::string functions[] = {"abs", "sign", "rands", "min", "max", "sin", "cos", "asin", "acos", "tan", "atan", "atan2", "round", "ceil", "floor", "pow", "sqrt", "exp", "len", "log", "ln", "str", "chr", "concat", "lookup", "search", "version", "version_num", "norm", "cross", "parent_module", "dxf_dim", "dxf_cross"};
	int functions_count = (sizeof(functions)/s_size);
	 
	std::string models[] = {"sphere", "cube", "cylinder", "polyhedron", "square", "polygon", "text", "circle"};
	int models_count = (sizeof(models)/s_size);

	 std::string operators[] = {"<=", ">=", "==", "!=", "&&"};
	int operators_count = (sizeof(operators)/s_size);


	rules_.push_state("COMMENT");
	rules_.push_state("MODIFIER");
	rules_.push_state("BLOCK");
	rules_.push("[/][/].*$", 1);
	defineRules(keywords, keywords_count, 2);
	defineRules(transformations, transformations_count, 3);
	defineRules(booleans, booleans_count, 6);
	defineRules(functions, functions_count, 7); 
	defineRules(models, models_count, 4);
	defineRules(operators, operators_count, 5);
 
	//rules_.push("[0-9]+", 8);
	rules_.push("[a-zA-Z0-9_]+", 9);
	
	rules_.push("[$][a-zA-Z0-9_]+", 11);

	rules_.push("INITIAL", "#", "MODIFIER");
	rules_.push("MODIFIER","[{]", "BLOCK");
	rules_.push("MODIFIER","[^;]+", "MODIFIER");
	rules_.push("BLOCK", "[^\\}]+|." , "BLOCK");	
	rules_.push("BLOCK", "[}]", 8, "INITIAL");
	rules_.push("MODIFIER", ";", 8, "INITIAL");

	rules_.push("INITIAL", "\"/*\"",  "COMMENT");
	rules_.push("COMMENT", "[^*]+|.",  "COMMENT");
	rules_.push("COMMENT", "\"*/\"", 1 , "INITIAL");

	rules_.push(".|\n", 10);
	lexertl::generator::build(rules_, sm);
	std::ofstream fout("file1.txt", std::fstream::trunc);
	lexertl::debug::dump(sm, fout);

}

void Lex::defineRules(std::string words[], int size, int id){

	for(int it = 0; it < size; it++){
		rules_.push(words[it], id);	
	}
}

void Lex::lex_results(const std::string& input, int start, LexInterface* const obj, int startState, int posState){
	
	lexertl::smatch results (input.begin(), input.end());
	if((posState == 1) || (startState == 1)){
		results.state = 1;
	} else if((posState == 8) || (startState == 8)){
		results.state = 2;
	}
	lexertl::lookup(sm, results);	

	while(results.id != 0)
	{
		switch(results.id)
		{
			case 2:
		 	token = results.str();
		 	 obj->highlighting(start, input, results, results.id);
		 	 break;
		
			case 1:
		  	token = results.str();
		  	 obj->highlighting(start, input, results, results.id);
			 break;
			
			case 3:
		  	token = results.str();
		  	 obj->highlighting(start, input, results, results.id);
			 break;

			case 4:
		  	token = results.str();
		  	 obj->highlighting(start, input, results, results.id);
			 break;
			
			case 5:
		  	token = results.str();
		  	 obj->highlighting(start, input, results, results.id);
			 break;

			case 6:
		  	token = results.str();
		  	 obj->highlighting(start, input, results, results.id);
			 break;
			
			case 7:
			token = results.str();
			 obj->highlighting(start, input, results, results.id);
			break;

			case 8:
			token = results.str();
			 obj->highlighting(start, input, results, results.id);
			break;
		
			case 9:
			token = results.str();
			 obj->highlighting(start, input, results, results.id);
			break;
			
			case 10:
			token = results.str();
			  obj->highlighting(start, input, results, results.id);
			break;

			case 11:
			token = results.str();
			obj->highlighting(start, input, results, results.id);
			break;
	       }
		lexertl::lookup(sm, results);
	}
}