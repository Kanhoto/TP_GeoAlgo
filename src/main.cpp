#include "seuillage.cpp"
#include "measures.cpp"
#include "SegparCC.cpp"
#include "export.cpp"
#include "octree_base.cpp"

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
	/*
	auto mapPerim = computePerimMap(mesh);

	const int numberOfClasses = 3;
	GenerateRandomColorClasses(colorClasses, numberOfClasses);

	//normalizeMap(mapPerim);
    Facet_int_map result = multipleThreshold(mesh, mapPerim);

    segmentationParCC(mesh, result);

	writeOFFfromValueMap(mesh, result, argc>=3?argv[2]:"result.off");
	*/

	const auto octree = generateOctree(mesh);

	extractMeshFromOctree(octree,mesh);

	return 0;
}