#include <CGAL/Exact_predicates_inexact_constructions_kernel.h>
#include <CGAL/boost/graph/graph_traits_Polyhedron_3.h>
#include <CGAL/IO/Polyhedron_iostream.h>

#include <iostream>
#include <fstream>
#include <map>
#include <algorithm>
#include <numeric>
#include <vector>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef CGAL::Polyhedron_3<Kernel> Polyhedron;

typedef Polyhedron::Facet_const_iterator Facet_iterator;
typedef Polyhedron::Vertex_const_iterator Vertex_iterator;
typedef Polyhedron::Halfedge_const_iterator Halfedge_iterator;
typedef Polyhedron::Halfedge_around_facet_const_circulator Halfedge_facet_circulator;

typedef std::map<Polyhedron::Facet_const_handle, double> Facet_double_map;
typedef std::map<Polyhedron::Facet_const_handle, int> Facet_int_map;

void normalizeMap(Facet_double_map &facetMap)
{
	double maxValue = facetMap.begin()->second;
	double minValue = facetMap.begin()->second;

	// look for min and max value in the map
	for (const auto &elem : facetMap)
	{
		if (elem.second > maxValue)
		{
			maxValue = elem.second;
		}
		if (elem.second < minValue)
		{
			minValue = elem.second;
		}
	}

	for (auto &elem : facetMap)
	{
		elem.second -= minValue;
		elem.second /= (maxValue-minValue);
	}
}

Facet_int_map simpleThreshold(Polyhedron & mesh, Facet_double_map & values) {
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


Facet_double_map computePerimMap(const Polyhedron &mesh)
{
	Facet_double_map out;

	for (Facet_iterator i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	{
		double current_perimeter = 0.;
		Halfedge_facet_circulator j = i->facet_begin();
		do
		{
			current_perimeter += std::sqrt(CGAL::squared_distance(j->vertex()->point(), j->opposite()->vertex()->point()));
		} while (++j != i->facet_begin());

		std::cout << "perim(" << std::distance(mesh.facets_begin(), i) << ")=" << current_perimeter << std::endl;

		out[i] = current_perimeter;
	}

	return out;
}

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
	
    Facet_int_map result = simpleThreshold(mesh,mapPerim);

    for (auto it = result.begin(); it != result.end(); ++it) {
        Polyhedron::Facet_const_handle facet = it->first;
        int integer = it->second;
        std::cout  << integer << std::endl;
    }

	return 0;
}
