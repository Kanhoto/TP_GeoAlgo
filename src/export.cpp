#include "sharedType.hpp"

std::vector<Color_t> colorClasses;

/// @brief Generate in a .off file a colored mesh according to a value map (green to red shades)
/// @param mesh the input mesh
/// @param facetMap map of values between 0 and 1 (see "normalize()") for each facet of mesh
/// @param filePath path to the colored .off file to be generated
void writeOFFfromValueMap(const Polyhedron& mesh, const Facet_int_map& facetMap, std::string filePath){
	std::ofstream in_myfile;
	in_myfile.open(filePath);

	CGAL::set_ascii_mode(in_myfile);

	in_myfile << "COFF" << std::endl // "COFF" makes the file support color informations
			  << mesh.size_of_vertices() << ' ' 
			  << mesh.size_of_facets() << " 0" << std::endl; 
			  // nb of vertices, faces and edges (the latter is optional, thus 0)

	std::copy(mesh.points_begin(), mesh.points_end(),
			  std::ostream_iterator<Kernel::Point_3>(in_myfile, "\n"));

	//Facet_int_map result = multipleThreshold(mesh, facetMap);

	Color_t c;
	for (auto i = facetMap.begin(); i != facetMap.end(); ++i)
	{
		Halfedge_facet_circulator j = i->first->facet_begin();

		CGAL_assertion(CGAL::circulator_size(j) >= 3);

		in_myfile << CGAL::circulator_size(j) << ' ';
		do
		{
			in_myfile << ' ' << std::distance(mesh.vertices_begin(), j->vertex());

		} while (++j != i->first->facet_begin());

		in_myfile << std::setprecision(5) << std::fixed; //set the format of floats to X.XXXXX
		
		int faceClass = i->second;
		
		c.red = colorClasses[faceClass].red; // low values will be closer to red
		c.green = colorClasses[faceClass].green; // high values will be closer to green
		c.blue = colorClasses[faceClass].blue;

		in_myfile << " " << c.red << " " << c.green << " " << c.blue;

		in_myfile << std::endl;
	}

	in_myfile.close();

	std::cout << "Le résultat a été exporté dans " << filePath << " !" << std::endl;
}