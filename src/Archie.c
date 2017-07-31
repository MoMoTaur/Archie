/*
 * Archie.c
 *
 *  Created on: Jul 31, 2017
 *      Author: Connor Kalvig (MoMoTaur)
 */

#include "Archie.h"

#include <math.h>

// Just in case math doesn't provide these (which is often, apparently)
#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

#ifndef PI
#define PI M_PI
#endif

// Zero Methods

void ARC_ZeroPoint(ARC_Point *p) {
	p->x = 0;
	p->y = 0;
}

void ARC_ZeroTriangle(ARC_Triangle *t) {
	ARC_ZeroPoint(&t->p1);
	ARC_ZeroPoint(&t->p2);
	ARC_ZeroPoint(&t->p3);
}

void ARC_ZeroRect(ARC_Rect *r) {
	ARC_ZeroPoint(&r->p1);
	ARC_ZeroPoint(&r->p2);
}

void ARC_ZeroQuad(ARC_Quad *q) {
	ARC_ZeroPoint(&q->p1);
	ARC_ZeroPoint(&q->p2);
	ARC_ZeroPoint(&q->p3);
	ARC_ZeroPoint(&q->p4);
}

void ARC_ZeroCircle(ARC_Circle *c) {
	ARC_ZeroPoint(&c->v);
	c->r = 0;
}

void ARC_ZeroEllipse(ARC_Ellipse *e) {
	ARC_ZeroPoint(&e->v);
	e->rx = 0;
	e->ry = 0;
}

// Conversion Methods

void ARC_RectToTriangle(ARC_Rect r, ARC_Triangle *t1, ARC_Triangle *t2) {
	t1->p1.x = r.p1.x;
	t1->p1.y = r.p1.y;
	
	t1->p2.x = r.p2.x;
	t1->p2.y = r.p1.y;
	
	t1->p3.x = r.p1.x;
	t1->p3.y = r.p2.y;
	
	t2->p1.x = r.p2.x;
	t2->p1.y = r.p2.y;
	
	t2->p2.x = r.p1.x;
	t2->p2.y = r.p2.y;
	
	t2->p3.x = r.p2.x;
	t2->p3.y = r.p1.y;
}

void ARC_QuadToTriangle(ARC_Quad q, ARC_Triangle *t1, ARC_Triangle *t2) {
	t1->p1.x = q.p1.x;
	t1->p1.y = q.p1.y;
	
	t1->p2.x = q.p2.x;
	t1->p2.y = q.p2.y;
	
	t1->p3.x = q.p4.x;
	t1->p3.y = q.p4.y;
	
	t2->p1.x = q.p3.x;
	t2->p1.y = q.p3.y;
	
	t2->p2.x = q.p4.x;
	t2->p2.y = q.p4.y;
	
	t2->p3.x = q.p2.x;
	t2->p3.y = q.p2.y;
}

void ARC_RectToQuad(ARC_Rect r, ARC_Quad *q) {
	q->p1.x = r.p1.x;
	q->p1.y = r.p1.y;
	
	q->p2.x = r.p2.x;
	q->p2.y = r.p1.y;
	
	q->p3.x = r.p2.x;
	q->p3.y = r.p2.y;
	
	q->p4.x = r.p1.x;
	q->p4.y = r.p2.y;
}

void ARC_CircleToEllipse(ARC_Circle c, ARC_Ellipse *e) {
	e->v.x = c.v.x;
	e->v.y = c.v.y;
	
	e->rx = c.r;
	e->ry = c.r;
}

// Helper Methods

double ARC_Slope(ARC_Point p1, ARC_Point p2) {
	return ((p2.y - p1.y) / (p2.x - p1.x));
}

double ARC_Distance(ARC_Point p1, ARC_Point p2) {
	return sqrt(((p2.x - p1.x) * (p2.x - p1.x)) + ((p2.y - p1.y) * (p2.y - p1.y)));
}

void ARC_UnitVectorize(ARC_Point *p) {
	ARC_Point origin = { 0, 0 };
	double u = ARC_Distance(origin, *p);
	p->x = p->x / u;
	p->y = p->y / u;
}

double ARC_ArcAngle(ARC_Point p1, ARC_Point p2, ARC_Point p3) {
	double x_off = p2.x;
	double y_off = p2.y;
	ARC_TranslatePoint(&p1, -x_off, -y_off);
	ARC_TranslatePoint(&p2, -x_off, -y_off);
	ARC_TranslatePoint(&p3, -x_off, -y_off);
	ARC_UnitVectorize(&p1);
	ARC_UnitVectorize(&p3);
	return acos((p1.x * p3.x) + (p1.y * p3.y));
}

double ARC_StandardAngle(ARC_Point p1, ARC_Point p2) {
	ARC_Point xa = { p1.x + 1, p1.y };
	if (p2.y < p1.y) return ((PI - ARC_ArcAngle(xa, p1, p2)) + PI);
	return ARC_ArcAngle(xa, p1, p2);
}

// Would like a new name for this as well
void ARC_PointOnEllipse(ARC_Ellipse e, double angle, ARC_Point *p) {
	double a = e.rx;
	double b = e.ry;
	double t = tan(angle);
	p->x = ((a * b) / sqrt((b * b) + (a * a) * (t * t)));
	p->y = ((a * b * t) / sqrt((b * b) + (a * a) * (t * t)));
	if (angle > (PI / 2) && angle <= ((3 * PI) / 2)) {
		p->x = -p->x;
		p->y = -p->y;
	}
	ARC_TranslatePoint(p, e.v.x, e.v.y);
}

// Translate Methods

void ARC_TranslatePoint(ARC_Point *p, double value_x, double value_y) {
	p->x += value_x;
	p->y += value_y;
}

void ARC_TranslateTriangle(ARC_Triangle *t, double value_x, double value_y) {
	ARC_TranslatePoint(&t->p1, value_x, value_y);
	ARC_TranslatePoint(&t->p2, value_x, value_y);
	ARC_TranslatePoint(&t->p3, value_x, value_y);
}

void ARC_TranslateRect(ARC_Rect *r, double value_x, double value_y) {
	ARC_TranslatePoint(&r->p1, value_x, value_y);
	ARC_TranslatePoint(&r->p2, value_x, value_y);
}

void ARC_TranslateQuad(ARC_Quad *q, double value_x, double value_y) {
	ARC_TranslatePoint(&q->p1, value_x, value_y);
	ARC_TranslatePoint(&q->p2, value_x, value_y);
	ARC_TranslatePoint(&q->p3, value_x, value_y);
	ARC_TranslatePoint(&q->p4, value_x, value_y);
}

// Centroid Methods

// A point is its own centroid!

void ARC_TriangleCentroid(ARC_Triangle t, ARC_Point *p) {
	p->x = (t.p1.x + t.p2.x + t.p3.x) / 3.0;
	p->y = (t.p1.y + t.p2.y + t.p3.y) / 3.0;
}

void ARC_RectCentroid(ARC_Rect r, ARC_Point *p) {
	p->x = (r.p1.x + r.p2.x) / 2.0;
	p->y = (r.p1.y + r.p2.y) / 2.0;
}

void ARC_QuadCentroid(ARC_Quad q, ARC_Point *p) {
	p->x = (q.p1.x + q.p2.x + q.p3.x + q.p4.x) / 4.0;
	p->y = (q.p1.y + q.p2.y + q.p3.y + q.p4.y) / 4.0;
}

// Circle and Ellipse centroids are their respective vertices

// Rotate methods

void ARC_RotatePoint(ARC_Point *p, ARC_Point v, double angle) {
	double c = cos(angle);
	double s = sin(angle);
	
	// translate point to origin:
	p->x -= v.x;
	p->y -= v.y;
	// rotate point
	double new_x = p->x * c - p->y * s;
	double new_y = p->x * s + p->y * c;
	
	// translate point back:
	p->x = new_x + v.x;
	p->y = new_y + v.y;
}

void ARC_RotateTriangle(ARC_Triangle *t, ARC_Point v, double angle) {
	ARC_RotatePoint(&t->p1, v, angle);
	ARC_RotatePoint(&t->p2, v, angle);
	ARC_RotatePoint(&t->p3, v, angle);
}

// Rects can't (meaningfully) rotate!

void ARC_RotateQuad(ARC_Quad *q, ARC_Point v, double angle) {
	ARC_RotatePoint(&q->p1, v, angle);
	ARC_RotatePoint(&q->p2, v, angle);
	ARC_RotatePoint(&q->p3, v, angle);
	ARC_RotatePoint(&q->p4, v, angle);
}

// Circles can't meaningfully rotate!

// Ellipses /can/ meaningfully rotate, but ARC's currently don't support it

// Intersect Methods

int ARC_PointInTriangle(ARC_Point p, ARC_Triangle t) {
	if (ARC_ArcAngle(t.p1, t.p2, p) <= ARC_ArcAngle(t.p1, t.p2, t.p3)) {
		if (ARC_ArcAngle(t.p2, t.p3, p) <= ARC_ArcAngle(t.p2, t.p3, t.p1)) {
			if (ARC_ArcAngle(t.p3, t.p1, p) <= ARC_ArcAngle(t.p3, t.p1, t.p2)) {
				return 1;
			}
		}
	}
	return 0;
}

int ARC_PointInRect(ARC_Point p, ARC_Rect r) {
	ARC_Triangle t1, t2;
	ARC_RectToTriangle(r, &t1, &t2);
	if (ARC_PointInTriangle(p, t1)) return 1;
	if (ARC_PointInTriangle(p, t2)) return 1;
	return 0;
}

int ARC_PointInQuad(ARC_Point p, ARC_Quad q) {
	ARC_Triangle t1, t2;
	ARC_QuadToTriangle(q, &t1, &t2);
	if (ARC_PointInTriangle(p, t1)) return 1;
	if (ARC_PointInTriangle(p, t2)) return 1;
	return 0;
}

int ARC_PointInCircle(ARC_Point p, ARC_Circle c) {
	if (ARC_Distance(p, c.v) <= c.r) return 1;
	return 0;
}

int ARC_PointInEllipse(ARC_Point p, ARC_Ellipse e) {
	// Eliminates NaN problem
	if (p.x == e.v.x && p.y == e.v.y) return 1;
	double angle = ARC_StandardAngle(e.v, p);
	ARC_Point tp = { 0, 0 };
	ARC_PointOnEllipse(e, angle, &tp);
	if (ARC_Distance(e.v, p) <= ARC_Distance(e.v, tp)) return 1;
	return 0;
}

/*
 * Consider an alternative to doing these this way. I'd like to do a single
 * function for intersection that can check between all types.
 */
int ARC_RectsIntersect(ARC_Rect r1, ARC_Rect r2) {
	if (ARC_PointInRect(r1.p1, r2)) return 1;
	if (ARC_PointInRect(r1.p2, r2)) return 1;
	if (ARC_PointInRect(r2.p1, r1)) return 1;
	if (ARC_PointInRect(r2.p2, r1)) return 1;
	
	ARC_Point p = { 0, 0 };
	p.x = r1.p1.x;
	p.y = r1.p2.y;
	if (ARC_PointInRect(p, r2)) return 1;
	
	p.x = r1.p2.x;
	p.y = r1.p1.y;
	if (ARC_PointInRect(p, r2)) return 1;
	
	p.x = r2.p1.x;
	p.y = r2.p2.y;
	if (ARC_PointInRect(p, r1)) return 1;
	
	p.x = r2.p2.x;
	p.y = r2.p1.y;
	if (ARC_PointInRect(p, r1)) return 1;
	
	return 0;
}

int ARC_QuadsIntersect(ARC_Quad q1, ARC_Quad q2) {
	if (ARC_PointInQuad(q1.p1, q2)) return 1;
	if (ARC_PointInQuad(q1.p2, q2)) return 1;
	if (ARC_PointInQuad(q1.p3, q2)) return 1;
	if (ARC_PointInQuad(q1.p4, q2)) return 1;
	
	if (ARC_PointInQuad(q2.p1, q1)) return 1;
	if (ARC_PointInQuad(q2.p2, q1)) return 1;
	if (ARC_PointInQuad(q2.p3, q1)) return 1;
	if (ARC_PointInQuad(q2.p4, q1)) return 1;
	return 0;
}

int ARC_CirclesIntersect(ARC_Circle c1, ARC_Circle c2) {
	if (ARC_Distance(c1.v, c2.v) <= (c1.r + c2.r)) return 1;
	return 0;
}

int ARC_EllipsesIntersect(ARC_Ellipse e1, ARC_Ellipse e2) {
	if (ARC_PointInEllipse(e1.v, e2)) return 1;
	if (ARC_PointInEllipse(e2.v, e1)) return 1;
	ARC_Point tp;
	ARC_PointOnEllipse(e1, ARC_StandardAngle(e1.v, e2.v), &tp);
	if (ARC_PointInEllipse(tp, e2)) return 1;
	
	ARC_PointOnEllipse(e2, ARC_StandardAngle(e2.v, e1.v), &tp);
	if (ARC_PointInEllipse(tp, e1)) return 1;
	return 0;
}
