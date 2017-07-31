/*
 * Archie.h
 *
 *  Created on: Jul 31, 2017
 *      Author: Connor Kalvig (MoMoTaur)
 */

#ifndef INC_ARCHIE_H_
#define INC_ARCHIE_H_

/*
 * \brief A single point in the 2D plane
 * 
 * \param x	The x coordinate
 * \param y	The y coordinate
 */
typedef struct ARC_Point {
	double x, y;
} ARC_Point;

/*
 * \brief A 2D triangle
 * 
 * \param p1	A first point
 * \param p2	A second point
 * \param p3	A second, second point
 */
typedef struct ARC_Triangle {
	ARC_Point p1, p2, p3;
} ARC_Triangle;

/*
 * \brief A 2D rectangle
 * 
 * \param p1	A point of the rectangle
 * \param p2	The opposite point of the rectangle
 */
typedef struct ARC_Rect {
	ARC_Point p1, p2;
} ARC_Rect;

/*
 * \brief A 2D 4-sided quadrilateral
 * 
 * \param p1	One 2D point
 * \param p2	Another 2D point
 * \param p3	Yet another 2D point
 * \param p4	A final 2D point
 * 
 * \note Good practice is to keep the points in a clockwise pattern, starting
 * 			with p1 and ending with p4. Keep in mind that if the points don't
 * 			follow this standard, or if they cross each other, some of this
 * 			library's functions will have undefined results.
 */
typedef struct ARC_Quad {
	ARC_Point p1, p2, p3, p4;
} ARC_Quad;

/*
 * \brief A 2D Circle
 * 
 * \param v	The center of the circle
 * \param r	The radius of the circle
 */
typedef struct ARC_Circle {
	ARC_Point v;
	double r;
} ARC_Circle;

/*
 * \brief A 2D Ellipse
 * 
 * \param v		The center of the ellipse
 * \param rx	The x radius of the ellipse
 * \param ry	The y radius of the ellipse
 */
typedef struct ARC_Ellipse {
	ARC_Point v;
	double rx, ry;
} ARC_Ellipse;

// More on the way!

// Function Time!

void ARC_ZeroPoint(ARC_Point *p);

void ARC_ZeroTriangle(ARC_Triangle *t);

void ARC_ZeroRect(ARC_Rect *r);

void ARC_ZeroQuad(ARC_Quad *q);

void ARC_ZeroCircle(ARC_Circle *c);

void ARC_ZeroEllipse(ARC_Ellipse *e);

void ARC_RectToTriangle(ARC_Rect r, ARC_Triangle *t1, ARC_Triangle *t2);

void ARC_QuadToTriangle(ARC_Quad q, ARC_Triangle *t1, ARC_Triangle *t2);

void ARC_RectToQuad(ARC_Rect r, ARC_Quad *q);

void ARC_CircleToEllipse(ARC_Circle c, ARC_Ellipse *e);

double ARC_Slope(ARC_Point p1, ARC_Point p2);

double ARC_Distance(ARC_Point p1, ARC_Point p2);

void ARC_UnitVectorize(ARC_Point *p);

double ARC_ArcAngle(ARC_Point p1, ARC_Point p2, ARC_Point p3);

double ARC_StandardAngle(ARC_Point p1, ARC_Point p2);

void ARC_PointOnEllipse(ARC_Ellipse e, double angle, ARC_Point *p);

void ARC_TranslatePoint(ARC_Point *p, double value_x, double value_y);

void ARC_TranslateTriangle(ARC_Triangle *t, double value_x, double value_y);

void ARC_TranslateRect(ARC_Rect *r, double value_x, double value_y);

void ARC_TranslateQuad(ARC_Quad *q, double value_x, double value_y);

void ARC_TriangleCentroid(ARC_Triangle t, ARC_Point *p);

void ARC_RectCentroid(ARC_Rect r, ARC_Point *p);

void ARC_QuadCentroid(ARC_Quad q, ARC_Point *p);

void ARC_RotatePoint(ARC_Point *p, ARC_Point v, double angle);

void ARC_RotateTriangle(ARC_Triangle *t, ARC_Point v, double angle);

void ARC_RotateQuad(ARC_Quad *q, ARC_Point v, double angle);

int ARC_PointInTriangle(ARC_Point p, ARC_Triangle t);

int ARC_PointInRect(ARC_Point p, ARC_Rect r);

int ARC_PointInQuad(ARC_Point p, ARC_Quad q);

int ARC_PointInCircle(ARC_Point p, ARC_Circle c);

int ARC_PointInEllipse(ARC_Point p, ARC_Ellipse e);

int ARC_RectsIntersect(ARC_Rect r1, ARC_Rect r2);

int ARC_QuadsIntersect(ARC_Quad q1, ARC_Quad q2);

int ARC_CirclesIntersect(ARC_Circle c1, ARC_Circle c2);

int ARC_EllipsesIntersect(ARC_Ellipse e1, ARC_Ellipse e2);

#endif /* INC_ARCHIE_H_ */
