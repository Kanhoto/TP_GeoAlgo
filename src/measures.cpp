#include "sharedType.hpp"

/// @brief map all the values from [min, max] to [0, 1]
/// @param facetMap non-const reference to the map (it is an in/out parameter)
void normalizeMap(Facet_double_map &facetMap){
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

Facet_double_map computePerimMap(const Polyhedron &mesh){
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

Facet_double_map computeAreaMap(const Polyhedron &mesh){
	Facet_double_map out;

	for (Facet_iterator i = mesh.facets_begin(); i != mesh.facets_end(); ++i)
	{
	
		Halfedge_facet_circulator j = i->facet_begin();
		
		Polyhedron::Vertex_const_handle firstVertex = j->vertex();

		double current_area = 0;
		// a facet is not necessarily a triangle, so we decompose one facet into multiple triangles,
		// and sum up all their areas. Only works for convex faces.
		// (illustration: http://mathbitsnotebook.com/JuniorMath/Polygons/polygons3g.jpg)
		do
		{
			current_area += CGAL::squared_area(firstVertex->point(), j->vertex()->point(), j->opposite()->vertex()->point()); 
		} while (++j != i->facet_begin());

		std::cout << "area(" << std::distance(mesh.facets_begin(), i) << ")=" << current_area << std::endl;

		out[i] = current_area;
	}

	return out;
}

/*
int main(int argc, char *argv[])
{
	if (argc < 2)
	{
		std::cerr << "Il manque un param??tre au programme. Veuillez lui donner en entr??e un nom de fichier au format off." << std::endl;
		return 1;
	}

	Polyhedron mesh;

	std::ifstream input(argv[1]);

	if (!input || !(input >> mesh) || mesh.is_empty())
	{
		std::cerr << "Le fichier donn?? n'est pas un fichier off valide." << std::endl;
		return 1;
	}

	auto mapPerim = computePerimMap(mesh);

	const int numberOfClasses = 3;
	GenerateRandomColorClasses(colorClasses, numberOfClasses);

	//normalizeMap(mapPerim);

	writeOFFfromValueMap(mesh, mapPerim, argc>=3?argv[2]:"result.off");

	return 0;
}
*/