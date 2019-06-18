#include <CGAL/Surface_mesh.h>
#include <CGAL/Curves_on_surface_topology.h>
#include <CGAL/Path_on_surface.h>
#include <CGAL/draw_face_graph_with_paths.h>

typedef CGAL::Exact_predicates_inexact_constructions_kernel Kernel;
typedef Kernel::Point_3                                     Point_3;
typedef CGAL::Surface_mesh<Point_3>                         SM;

///////////////////////////////////////////////////////////////////////////////
void create_path_1(CGAL::Path_on_surface<SM>& p)
{
  p.push_back_by_index(88); // Its starting dart
  for (int i=0; i<3; ++i)
  { p.extend_positive_turn(2); } // Extend the path
}

///////////////////////////////////////////////////////////////////////////////
void create_path_2(CGAL::Path_on_surface<SM>& p)
{
  p.push_back_by_index(300);  // Its starting dart
  for (int i=0; i<3; ++i)
  { p.extend_negative_turn(2); } // Extend the path
}

///////////////////////////////////////////////////////////////////////////////
void create_path_3(CGAL::Path_on_surface<SM>& p)
{
  p.push_back_by_index(87); // Its starting dart
  p.extend_positive_turn(1); // Extend the path
  for (int i=0; i<3; ++i)
  { p.extend_positive_turn(2); }
  p.extend_positive_turn(1);
}

///////////////////////////////////////////////////////////////////////////////
int main()
{
  SM sm;
  std::ifstream in("data/double-torus-example.off");
  if (!in.is_open())
  {
    std::cout<<"ERROR reading file data/double-torus-example.off"<<std::endl;
    exit(EXIT_FAILURE);
  }
  in>>sm;

  CGAL::Curves_on_surface_topology<SM> cst(sm);
  CGAL::Path_on_surface<SM> p1(sm), p2(sm), p3(sm);
  create_path_1(p1);
  create_path_2(p2);
  create_path_3(p3);

  bool res1=cst.are_base_point_homotopic(p1, p2);
  std::cout<<"Path p1 (pink) "<<(res1?"IS":"IS NOT")
           <<" base point homotopic with path p2 (green)."<<std::endl;

  bool res2=cst.are_base_point_homotopic(p2, p3);
  std::cout<<"Path p2 (green) "<<(res2?"IS":"IS NOT")
           <<" base point homotopic with path p3 (orange)."<<std::endl;

#ifdef CGAL_USE_BASIC_VIEWER
  std::vector<CGAL::Path_on_surface<SM> > paths={p1, p2, p3};
  CGAL::draw(sm, paths); // Enable only if CGAL was compiled with Qt5
#endif // CGAL_USE_BASIC_VIEWER
  
  return EXIT_SUCCESS;
}
///////////////////////////////////////////////////////////////////////////////
