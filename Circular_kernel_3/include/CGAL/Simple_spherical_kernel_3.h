// Copyright (c) 2008  INRIA Sophia-Antipolis (France).
// All rights reserved.
//
// This file is part of CGAL (www.cgal.org); you may redistribute it under
// the terms of the Q Public License version 1.0.
// See the file LICENSE.QPL distributed with CGAL.
//
// Licensees holding a valid commercial license may use this file in
// accordance with the commercial license agreement provided with the software.
//
// This file is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE
// WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.
//
// $URL$
// $Id$
//
// Author(s) : Monique Teillaud, Sylvain Pion, Pedro Machado, 
//             Julien Hazebrouck, Damien Leroy

// Partially supported by the IST Programme of the EU as a 
// STREP (FET Open) Project under Contract No  IST-006413 
// (ACS -- Algorithms for Complex Shapes)

#ifndef CGAL_SIMPLE_SPHERICAL_KERNEL_3_H
#define CGAL_SIMPLE_SPHERICAL_KERNEL_3_H

#include <CGAL/Circular_kernel_3/Circular_arc_point_3.h>
#include <CGAL/Circular_arc_point_3.h>

#include <CGAL/Circular_kernel_3/Line_arc_3.h>
#include <CGAL/Line_arc_3.h>

#include <CGAL/Circular_kernel_3/Circular_arc_3.h>
#include <CGAL/Circular_arc_3.h>

#include <CGAL/global_functions_spherical_kernel_3.h>

#include <CGAL/Circular_kernel_3/function_objects_polynomial_sphere.h>

#include <CGAL/Circular_kernel_3/get_equation_object_on_curved_kernel_3.h>

#include <CGAL/Spherical_kernel_type_equality_wrapper.h>


namespace CGAL {
  namespace CGALi {
    
    template < class SphericalKernel, class LinearKernelBase >
      struct Spherical_kernel_base_no_ref_count: public LinearKernelBase
				 // takes classes in internal sub-namespace
      {
        typedef CGALi::Circular_arc_point_3<SphericalKernel>                        Circular_arc_point_3;
        typedef CGALi::Line_arc_3<SphericalKernel>                                  Line_arc_3;
        typedef CGALi::Circular_arc_3<SphericalKernel>                              Circular_arc_3;
       
        // The mecanism that allows to specify reference-counting or not.
        template < typename T >
        struct Handle { typedef T    type; };

        #define CGAL_Spherical_Kernel_pred(Y,Z) typedef SphericalFunctors::Y<SphericalKernel> Y; \
	    Y Z() const { return Y(); }
        #define CGAL_Spherical_Kernel_cons(Y,Z) CGAL_Spherical_Kernel_pred(Y,Z)
	
        #include <CGAL/Circular_kernel_3/interface_macros.h>
      };
    
  } // namespace CGALi

  template < class LinearKernel, class AlgebraicKernel >
    struct Simple_spherical_kernel_3
    :  // there should be a derivation from
  // LinearKernel::Kernel_base<Self> to have types equalities for
  // the Linearkernel types
  public Spherical_kernel_type_equality_wrapper<CGALi::Spherical_kernel_base_no_ref_count<Simple_spherical_kernel_3<LinearKernel,AlgebraicKernel>,
    typename LinearKernel:: template Base<Simple_spherical_kernel_3<LinearKernel,AlgebraicKernel> >::Type >,
    Simple_spherical_kernel_3<LinearKernel,AlgebraicKernel> >
    {
      typedef Simple_spherical_kernel_3<LinearKernel,AlgebraicKernel>      Self;

      typedef typename LinearKernel::template Base<Simple_spherical_kernel_3<LinearKernel,AlgebraicKernel> >::Type  Linear_kernel;
      typedef AlgebraicKernel                                 Algebraic_kernel;

      //  //Please remove this if you consider it to be sloppy
      struct Circular_tag{};
      typedef Circular_tag Definition_tag;
      //  ////////////////////////////////////////////////////


      typedef typename LinearKernel::RT                       RT;
      typedef typename LinearKernel::FT                       FT;
      //~ typedef Algebraic_kernel AK;
      typedef typename Algebraic_kernel::Root_of_2                  Root_of_2;
      typedef typename Algebraic_kernel::Root_for_spheres_2_3       Root_for_spheres_2_3;
      typedef typename Algebraic_kernel::Polynomial_for_spheres_2_3 Polynomial_for_spheres_2_3;
      typedef typename Algebraic_kernel::Polynomial_1_3             Polynomial_1_3;
      typedef typename Algebraic_kernel::Polynomials_for_line_3     Polynomials_for_line_3;
      typedef std::pair< Polynomial_for_spheres_2_3, Polynomial_1_3 >
                                                 Polynomials_for_circle_3;

      // public classes
      typedef CGAL::Object Object_3;
  
    };

} // namespace CGAL

#endif // CGAL_SIMPLE_SPHERICAL_KERNEL_3_H
