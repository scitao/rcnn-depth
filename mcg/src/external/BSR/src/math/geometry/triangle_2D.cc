/*
 * Triangle with 2D vertex coordinates.
 */
#include "io/streams/ostream.hh"
#include "lang/exceptions/ex_invalid_argument.hh"
#include "math/geometry/point_2D.hh"
#include "math/geometry/triangle_2D.hh"
#include "math/math.hh"

namespace math {
namespace geometry {
/*
 * Imports.
 */
using io::streams::ostream;
using lang::exceptions::ex_invalid_argument;

/***************************************************************************
 * Constructors and destructor.
 ***************************************************************************/

/*
 * Constructor.
 * Specify the triangle vertices.
 */
triangle_2D::triangle_2D(point_2D& v0, point_2D& v1, point_2D& v2)
 : _v0(v0), _v1(v1), _v2(v2)
{ }

/*
 * Copy constructor.
 */
triangle_2D::triangle_2D(const triangle_2D& t)
 : _v0(t._v0), _v1(t._v1), _v2(t._v2)
{ }

/*
 * Destructor.
 */
triangle_2D::~triangle_2D() {
   /* do nothing */
}

/***************************************************************************
 * I/O.
 ***************************************************************************/

/*
 * Formatted output to stream.
 */
ostream& operator<<(ostream& os, const triangle_2D& t) {
   os << "triangle {" << t._v0 << " " << t._v1 << " " << t._v2 << "}";
   return os;
}

/***************************************************************************
 * Vertex reference.
 ***************************************************************************/

/*
 * Vertex reference.
 */
point_2D& triangle_2D::vertex(unsigned long n) const {
   if (n == 0)
      return _v0;
   else if (n == 1)
      return _v1;
   else if (n == 2)
      return _v2;
   else
      throw ex_invalid_argument("vertex # must be 0, 1, or 2");
}

/***************************************************************************
 * Triangle attributes.
 ***************************************************************************/

namespace {
/*
 * Helper function for computing angle at a vertex.
 * Return the angle between the vectors from the origin to the two points.
 */
double vector_angle(const point_2D& p0, const point_2D& p1) {
   return math::acos(dot(p0, p1)/(abs(p0)*abs(p1)));
}
} /* namespace */

/*
 * Angle at vertex.
 */
double triangle_2D::angle(unsigned long n) const {
   /* compute angle at specified vertex */
   if (n == 0)
      return vector_angle(_v1 - _v0, _v2 - _v0);
   else if (n == 1)
      return vector_angle(_v0 - _v1, _v2 - _v1);
   else if (n == 2)
      return vector_angle(_v0 - _v2, _v1 - _v2);
   else
      throw ex_invalid_argument("vertex # must be 0, 1, or 2");
}

/*
 * Altitude from vertex to opposite side.
 */
double triangle_2D::altitude(unsigned long n) const {
   if (n == 0)
      return _v0.distance_to_line(_v1, _v2);
   else if (n == 1)
      return _v1.distance_to_line(_v0, _v2);
   else if (n == 2)
      return _v2.distance_to_line(_v0, _v1);
   else
      throw ex_invalid_argument("vertex # must be 0, 1, or 2");
}

/*
 * Length of side opposite vertex.
 */
double triangle_2D::side_length(unsigned long n) const {
   if (n == 0)
      return abs(_v2 - _v1);
   else if (n == 1)
      return abs(_v2 - _v0);
   else if (n == 2)
      return abs(_v1 - _v0);
   else
      throw ex_invalid_argument("vertex # must be 0, 1, or 2");
}

/*
 * Area of triangle.
 */
double triangle_2D::area() const {
   double xb = _v1.x() - _v0.x();  double yb = _v1.y() - _v0.y();
   double xc = _v2.x() - _v0.x();  double yc = _v2.y() - _v0.y();
   return 0.5 * math::abs(xb*yc - xc*yb);
}

/*
 * Centroid.
 */
point_2D triangle_2D::centroid() const {
   return (_v0 + _v1 + _v2) / static_cast<double>(3);
}

} /* namespace geometry */
} /* namespace math */
