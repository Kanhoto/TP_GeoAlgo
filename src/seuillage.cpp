#include "sharedType.hpp"

void GenerateRandomColorClasses(std::vector<Color_t> & vec_i, int n){
	Color_t c;
	
	for(int i=0; i<n; ++i){
		c.red = (double)rand() / RAND_MAX;
		c.green = (double)rand() / RAND_MAX;
		c.blue = (double)rand() / RAND_MAX;

		vec_i.push_back(c);
	}

	/*
	// RED
	c.red = 1;
	c.green = 0;
	c.blue = 0;
	vec_i.push_back(c);

	// GREEN
	c.red = 0;
	c.green = 1;
	c.blue = 0;
	vec_i.push_back(c);
	
	// BLUE
	c.red = 0;
	c.green = 0;
	c.blue = 1;
	vec_i.push_back(c);
	*/
}

Facet_int_map simpleThreshold(const Polyhedron & mesh, const Facet_double_map & values){
    Facet_int_map result;
    std::vector<double> vecValues;
    vecValues.reserve(values.size());

    for ( auto it = values.begin(); it != values.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        double value = it->second;
        vecValues.push_back(value);
    }

    auto average = std::accumulate(vecValues.begin(), vecValues.end(), 0.0) / vecValues.size();

     for (auto it = values.begin(); it != values.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        double value = it->second;
        result[facet] = value >= average ? 1 : 0;
    }
    return result;
}

Facet_int_map multipleThreshold(const Polyhedron & mesh, const Facet_double_map & values){
    Facet_int_map result;
    std::vector<double> vecValues;
    vecValues.reserve(values.size());

    for ( auto it = values.begin(); it != values.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        double value = it->second;
        vecValues.push_back(value);
    }

    auto average = std::accumulate(vecValues.begin(), vecValues.end(), 0.0) / vecValues.size();

	auto firstpart = (2*average) * (double)1/(double)3;
	auto secondpart = (2*average) * (double)2/(double)3;

	for (auto it = values.begin(); it != values.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        double value = it->second;
		if(value <= firstpart){
			result[facet] = 0;
		}
		else if(value > firstpart && value <= secondpart){
			result[facet] = 1;
		}else if(value > secondpart){
			result[facet] = 2;
		}
    }
    return result;
}

/*
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Il manque un paramètre au programme. Veuillez lui donner en entrée un nom de fichier au format off." << std::endl;
		return 1;
	}

	Polyhedron mesh;

	std::ifstream input(argv[1]);
	
	if (!input || !(input >> mesh) || mesh.is_empty())
	{
		std::cerr << "Le fichier donné n'est pas un fichier off valide." << std::endl;
		return 1;
	}

    Facet_double_map mapPerim = computePerimMap(mesh);
	
    Facet_int_map result = multipleThreshold(mesh,mapPerim);

    for (auto it = result.begin(); it != result.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        int integer = it->second;
        std::cout  << integer << std::endl;
    }

	return 0;
}
*/